#include <jni.h>
#include <windows.h>
#include <winioctl.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SystemMonitor.h"

// --- 1. MEMORY ENGINE ---
JNIEXPORT jdouble JNICALL Java_SystemMonitor_getMemoryLoad(JNIEnv *env, jobject obj) {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    if (GlobalMemoryStatusEx(&memInfo)) { return (jdouble)memInfo.dwMemoryLoad; }
    return -1.0; 
}

// --- 2. CPU ENGINE ---
JNIEXPORT jdouble JNICALL Java_SystemMonitor_getCpuLoad(JNIEnv *env, jobject obj) {
    // Placeholder - CPU load implementation
    return 25.0; 
}

// --- 3. PROCESS LIST ENGINE ---
JNIEXPORT jstring JNICALL Java_SystemMonitor_getProcessList(JNIEnv *env, jobject obj) {
    char resultBuffer[131072] = ""; 
    char tempBuffer[512];
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;

    if (hProcessSnap == INVALID_HANDLE_VALUE) return (*env)->NewStringUTF(env, "Error");
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) { CloseHandle(hProcessSnap); return (*env)->NewStringUTF(env, "Error"); }

    do {
        DWORD pid = pe32.th32ProcessID;
        DWORD threads = pe32.cntThreads;
        unsigned long memUsage = 0;
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
        if (hProcess != NULL) {
            PROCESS_MEMORY_COUNTERS pmc;
            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) { memUsage = (unsigned long)(pmc.WorkingSetSize / 1024); }
            CloseHandle(hProcess);
        }
        sprintf(tempBuffer, "%s|%lu|%lu KB|%lu;", pe32.szExeFile, pid, memUsage, threads);
        strcat(resultBuffer, tempBuffer);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return (*env)->NewStringUTF(env, resultBuffer);
}

// --- 4. THE KILL SWITCH ---
JNIEXPORT jboolean JNICALL Java_SystemMonitor_killProcess(JNIEnv *env, jobject obj, jint pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)pid);
    if (hProcess == NULL) { return JNI_FALSE; }
    if (TerminateProcess(hProcess, 0)) { CloseHandle(hProcess); return JNI_TRUE; }
    CloseHandle(hProcess);
    return JNI_FALSE;
}

// --- 5. DISK I/O ENGINE (RAW METAL TELEMETRY) ---
static LARGE_INTEGER prevRead = {0};
static LARGE_INTEGER prevWrite = {0};
static LARGE_INTEGER prevTime = {0};
static int diskInitialized = 0;

JNIEXPORT jstring JNICALL Java_SystemMonitor_getDiskData(JNIEnv *env, jobject obj) {
    HANDLE hDevice = CreateFile("\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    
    if (hDevice == INVALID_HANDLE_VALUE) {
        return (*env)->NewStringUTF(env, "0.0|0.0"); // Failsafe
    }

    DISK_PERFORMANCE diskPerf;
    DWORD bytesReturned;
    double readMBps = 0.0;
    double writeMBps = 0.0;

    // Direct hardware query bypassing Windows abstractions
    if (DeviceIoControl(hDevice, IOCTL_DISK_PERFORMANCE, NULL, 0, &diskPerf, sizeof(diskPerf), &bytesReturned, NULL)) {
        LARGE_INTEGER currentTime, frequency;
        QueryPerformanceCounter(&currentTime);
        QueryPerformanceFrequency(&frequency);

        if (diskInitialized) {
            double elapsedTime = (double)(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
            if (elapsedTime > 0) {
                double bytesRead = (double)(diskPerf.BytesRead.QuadPart - prevRead.QuadPart);
                double bytesWritten = (double)(diskPerf.BytesWritten.QuadPart - prevWrite.QuadPart);
                
                readMBps = (bytesRead / elapsedTime) / (1024.0 * 1024.0);
                writeMBps = (bytesWritten / elapsedTime) / (1024.0 * 1024.0);
            }
        } else {
            diskInitialized = 1;
        }

        prevRead = diskPerf.BytesRead;
        prevWrite = diskPerf.BytesWritten;
        prevTime = currentTime;
    }
    CloseHandle(hDevice);

    char buffer[64];
    sprintf(buffer, "%.2f|%.2f", readMBps, writeMBps);
    return (*env)->NewStringUTF(env, buffer);
}

// --- 6. GPU DATA ENGINE ---
JNIEXPORT jstring JNICALL Java_SystemMonitor_getGpuData(JNIEnv *env, jobject obj) {
    char buffer[128];
    sprintf(buffer, "0.0|0.0"); 
    return (*env)->NewStringUTF(env, buffer);
}
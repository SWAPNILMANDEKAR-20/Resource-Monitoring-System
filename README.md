Quantum-AI Resource Monitor

A futuristic **System Monitoring Dashboard** built using **JavaFX + Native C (JNI)** that provides real-time insights into system performance with AI-powered analytics and threat detection.


Features

Real-Time Monitoring
- CPU usage tracking
- Memory (RAM) utilization
- Disk I/O (Read/Write speeds)
- Process monitoring with live updates

Native System Integration
- Uses **JNI (Java Native Interface)** to interact with low-level system APIs
- Retrieves real-time system data using Windows APIs  
- Example: Memory, process list, disk performance :contentReference[oaicite:0]{index=0}  

Advanced UI (JavaFX)
- Glassmorphism + futuristic UI design :contentReference[oaicite:1]{index=1}  
- Interactive charts (AreaChart, LineChart)
- Process table with dynamic filtering  
- Smooth animations and neon-themed dashboard  

Process Management
- View all running processes  
- Kill processes directly from UI  
- Safe list protection for critical processes  

 AI Assistant
- Built-in chatbot for system insights  
- Commands like:


Threat Matrix System
- RAM & CPU threshold monitoring  
- Danger Zone visualization  
- Safe list management  
- Autonomous "Sentry Mode" for protection  

Disk Monitoring
- Real-time read/write speeds  
- Session tracking  
- Peak and average analytics  


Tech Stack

- **Frontend:** JavaFX  
- **Backend:** Java  
- **System Layer:** C (JNI)  
- **APIs:** Windows System APIs  
- **Styling:** CSS (Glassmorphism UI)

 Project Structure
├── SystemMonitor.java # Main JavaFX application
├── SystemMonitorFixed.java # Simplified working version
├── TestApp.java # Basic test UI
├── monitor.c # Native C implementation (JNI)
├── SystemMonitor.h # JNI header
├── style.css # UI styling
├── dxgi.h # GPU interface definitions


 How It Works

1. **JavaFX UI Layer**
   - Displays charts, tables, and controls
2. **Java Backend**
   - Handles logic, process management, and AI assistant
3. **JNI Layer**
   - Connects Java with native C code
4. **Native C Layer**
   - Fetches low-level system data (memory, disk, processes)



Key Functionalities

- Real-time process scanning  
- Disk performance monitoring  
- System analytics and prediction  
- Process termination (Kill Switch)  
- AI-based system assistant  

Known Issues

- JavaFX setup required (module path configuration)  
- Native library (`monitor.dll`) must be correctly loaded  
- Some metrics use fallback simulation if native calls fail  

Future Enhancements

- Cross-platform support (Linux/Mac)  
- Real GPU monitoring  
- Cloud-based analytics  
- Mobile dashboard integration  

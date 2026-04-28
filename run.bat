@echo off
echo Starting System Monitor...
java --module-path "javafx-sdk-21.0.1/lib" --add-modules javafx.controls,javafx.fxml,javafx.graphics --enable-native-access=ALL-UNNAMED -cp . SystemMonitor
pause

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import com.sun.management.OperatingSystemMXBean;
import java.lang.management.ManagementFactory;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

public class SystemMonitorFixed extends Application {
    
    private Label memoryLabel;
    
    @Override
    public void start(Stage stage) {
        memoryLabel = new Label("MEMORY: --");
        memoryLabel.setStyle("-fx-text-fill: #ff6b35; -fx-font-size: 16px; -fx-font-weight: bold;");
        
        // Simple layout
        javafx.scene.layout.VBox root = new javafx.scene.layout.VBox(20, memoryLabel);
        root.setStyle("-fx-background-color: #0d141a; -fx-padding: 20px;");
        
        // Start thread to update memory in real-time
        new Thread(() -> {
            while (true) {
                try {
                    // Get system memory usage
                    OperatingSystemMXBean osBean = 
                        (OperatingSystemMXBean) ManagementFactory.getOperatingSystemMXBean();
                    
                    long totalMemory = osBean.getTotalPhysicalMemorySize();
                    long freeMemory = osBean.getFreePhysicalMemorySize();
                    long usedMemory = totalMemory - freeMemory;
                    double memoryPercent = (double) usedMemory * 100 / totalMemory;
                    
                    long usedMB = usedMemory / (1024 * 1024);
                    long totalMB = totalMemory / (1024 * 1024);
                    
                    // Update UI on JavaFX thread
                    javafx.application.Platform.runLater(() -> {
                        memoryLabel.setText(String.format("MEMORY: %d MB / %d MB (%.1f%%)", 
                            usedMB, totalMB, memoryPercent));
                    });
                    
                    Thread.sleep(1000); // Update every second
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
        
        Scene scene = new Scene(root, 400, 300);
        stage.setTitle("Memory Monitor Test");
        stage.setScene(scene);
        stage.show();
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}

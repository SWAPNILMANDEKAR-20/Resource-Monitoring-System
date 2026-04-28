import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class TestApp extends Application {
    @Override
    public void start(Stage stage) {
        VBox root = new VBox(20);
        root.setStyle("-fx-background-color: #0d141a; -fx-padding: 20px;");
        
        Label label = new Label("Enhanced Resource Monitor - Test Version");
        label.setStyle("-fx-text-fill: white; -fx-font-size: 18px; -fx-font-weight: bold;");
        
        root.getChildren().add(label);
        
        Scene scene = new Scene(root, 800, 600);
        stage.setTitle("Test App");
        stage.setScene(scene);
        stage.centerOnScreen();
        stage.show();
    }
    
    public static void main(String[] args) {
        launch(args);
    }
}

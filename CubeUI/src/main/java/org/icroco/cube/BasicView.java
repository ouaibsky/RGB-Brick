package org.icroco.cube;

import java.awt.*;

import com.gluonhq.charm.glisten.application.MobileApplication;
import com.gluonhq.charm.glisten.control.AppBar;
import com.gluonhq.charm.glisten.control.Icon;
import com.gluonhq.charm.glisten.mvc.View;
import com.gluonhq.charm.glisten.visual.MaterialDesignIcon;

import lombok.Getter;


public class BasicView extends View {

    @Getter
    SimpleStringProperty hostName = new SimpleStringProperty("255.255.255.255");
    @Getter
    SimpleIntegerProperty port = new SimpleIntegerProperty(4321);

    public BasicView(String name) {
        super(name);
        
        Label label = new Label("Cube IP");
        TextField tfIp = new TextField("192.168.0.255");
        Label lblPort = new Label("Port");
        TextField tfPort = new TextField("4321");
        tfIp.textProperty().bindBidirectional(hostName);
        tfPort.textProperty().bindBidirectional(port, new NumberStringConverter());

        Button button = new Button("Change the World!");
        button.setGraphic(new Icon(MaterialDesignIcon.LANGUAGE));
        button.setOnAction(e -> label.setText("Hello Cube!"));
        HBox hBox1 = new HBox(15.0, label, tfIp);
        hBox1.setAlignment(Pos.CENTER);
        HBox hBox2 = new HBox(15.0, lblPort, tfPort);
        hBox2.setAlignment(Pos.CENTER);


        VBox controls = new VBox(15.0, hBox1, hBox2);
        controls.setAlignment(Pos.TOP_CENTER);
        //controls.setAlignment(Pos.CENTER);
        
        setCenter(controls);
    }

    @Override
    protected void updateAppBar(AppBar appBar) {
        appBar.setNavIcon(MaterialDesignIcon.MENU.button(e ->
                MobileApplication.getInstance().showLayer(CubeApplication.MENU_LAYER)));
        //appBar.setNavIcon(MaterialDesignIcon.MENU.button(e -> System.out.println("Menu")));
//        appBar.setNavIcon(MaterialDesignIcon.MENU.button(e -> System.out.println("Menu")));
        appBar.setTitleText("500 LEDs Cube");

        //appBar.
        //appBar.getActionItems().add(MaterialDesignIcon.SEARCH.button(e -> System.out.println("Search")));
    }
    
}

package org.icroco.cube.views;/*
 * Copyright 2015 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import com.gluonhq.charm.glisten.animation.BounceInRightTransition;
import com.gluonhq.charm.glisten.application.MobileApplication;
import com.gluonhq.charm.glisten.control.AppBar;
import com.gluonhq.charm.glisten.mvc.View;
import com.gluonhq.charm.glisten.visual.MaterialDesignIcon;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import org.icroco.cube.CubeApplication;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class DemoPresenter {
    @FXML
    private View demo;

    public void initialize() {
        demo.setShowTransitionFactory(BounceInRightTransition::new);

        demo.showingProperty().addListener((obs, oldValue, newValue) -> {
            System.out.println(MobileApplication.getInstance().getClass().getName());
            if (newValue) {
                AppBar appBar = MobileApplication.getInstance().getAppBar();
                appBar.setNavIcon(MaterialDesignIcon.MENU.button(e ->
                        MobileApplication.getInstance().showLayer(CubeApplication.MENU_LAYER)));
                appBar.setTitleText("Demo");
            }
        });
    }

    public void onNext(ActionEvent actionEvent) {
        System.out.println("Next Demo -> Send Animation");
        try {
            ((CubeApplication) MobileApplication.getInstance()).getParameters();
            DatagramSocket socket = new DatagramSocket();
            InetAddress address = InetAddress.getByName("192.168.0.66");
            byte buf[] = "Animation".getBytes();
            DatagramPacket packet = new DatagramPacket(buf, buf.length, address, 4321);
            socket.send(packet);

        } catch (SocketException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}

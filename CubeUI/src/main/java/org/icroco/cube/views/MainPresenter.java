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

import com.gluonhq.charm.glisten.control.Icon;
import com.gluonhq.charm.glisten.visual.MaterialDesignIcon;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import org.controlsfx.control.SegmentedButton;

public class MainPresenter {
	@FXML
	Label lblGame;
	@FXML
	Label lblMusic;
	@FXML
	Label lblText;
	@FXML
	Label lblDemo;
	@FXML
    TextField btnText;
	@FXML
    Button sendText;

    @FXML
    SegmentedButton demoBar;
    @FXML
    SegmentedButton gameBtnBar;
    @FXML
    SegmentedButton keyButtons;
    @FXML
    SegmentedButton musicBar;

	public void initialize() {
		lblGame.setGraphic(new Icon(MaterialDesignIcon.GAMES));
		lblDemo.setGraphic(new Icon(MaterialDesignIcon.PLAY_ARROW));
		lblText.setGraphic(new Icon(MaterialDesignIcon.TEXTSMS));
		lblMusic.setGraphic(new Icon(MaterialDesignIcon.MUSIC_NOTE));
        sendText.setGraphic(new Icon(MaterialDesignIcon.SEND));

        ToggleButton demo1 = new ToggleButton("1");
        ToggleButton demo2 = new ToggleButton("2");
        ToggleButton demo3 = new ToggleButton("3");
        ToggleButton demo4 = new ToggleButton("4");
        demoBar.getButtons().addAll(demo1,demo2,demo3,demo4);

        ToggleButton tetris = new ToggleButton("Tetris");
        ToggleButton snake = new ToggleButton("Snake");
        gameBtnBar.getButtons().addAll(tetris, snake);
        gameBtnBar.setToggleGroup(demoBar.getToggleGroup());

        ToggleButton equalizer = new ToggleButton("Equalizer");
        ToggleButton boum = new ToggleButton("Boum");
        musicBar.getButtons().addAll(equalizer, boum);
        musicBar.setToggleGroup(demoBar.getToggleGroup());

        ToggleButton tetrisLeft = new ToggleButton("", new Icon(MaterialDesignIcon.KEYBOARD_ARROW_LEFT));
        ToggleButton tetrisRight = new ToggleButton("", new Icon(MaterialDesignIcon.KEYBOARD_ARROW_RIGHT));
        ToggleButton tetrisRotate = new ToggleButton("", new Icon(MaterialDesignIcon.ROTATE_90_DEGREES_CCW));
        keyButtons.getButtons().addAll(tetrisLeft, tetrisRotate, tetrisRight);

        btnText.setOnKeyPressed(event -> {
            final Toggle selectedToggle = demoBar.getToggleGroup().getSelectedToggle();
            if (selectedToggle != null) {
                selectedToggle.setSelected(false);
            }
        });
		//segmentedButton.getButtons().add();
	}

    public void playTetris(ActionEvent actionEvent) {

    }

    public void playSnake(ActionEvent actionEvent) {

    }

    public void playEqualizer1(ActionEvent actionEvent) {

    }

    public void playEqualizer2(ActionEvent actionEvent) {

    }
}
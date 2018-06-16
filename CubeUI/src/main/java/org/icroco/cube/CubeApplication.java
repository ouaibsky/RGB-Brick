package org.icroco.cube;

import org.icroco.cube.views.DemoView;
import org.icroco.cube.views.MainView;
import org.icroco.cube.views.MusicView;

import com.gluonhq.charm.glisten.application.MobileApplication;
import com.gluonhq.charm.glisten.layout.layer.SidePopupView;
import com.gluonhq.charm.glisten.mvc.View;
import com.gluonhq.charm.glisten.visual.Swatch;

import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;

public class CubeApplication extends MobileApplication {

	public static final String BASIC_VIEW = HOME_VIEW;
	// public static final String EDITION_VIEW = "Edition View";
	public static final String DEMO_VIEW = "Demo Mode";
    public static final String EQUALIZER_VIEW = "Equalizer";
    public static final String TEXT_VIEW = "Display Text";
	public static final String GAMES_VIEW = "Games";
	public static final String SETTINGS_VIEW = "Settings";
	public static final String MENU_LAYER = "Side Menu";

	@Override
	public void init() {
		addViewFactory(BASIC_VIEW, () -> (View) new MainView().getView());
		addViewFactory(DEMO_VIEW, () -> (View) new DemoView().getView());
		addViewFactory(EQUALIZER_VIEW, () -> (View) new MusicView().getView());
		addLayerFactory(MENU_LAYER,
				() -> new SidePopupView(new DrawerManager().getDrawer()));
	}

	@Override
	public void postInit(Scene scene) {
		Swatch.BLUE.assignTo(scene);

		((Stage) scene.getWindow()).getIcons().add(new Image(CubeApplication.class.getResourceAsStream("/cube-color-32.png")));
	}
}

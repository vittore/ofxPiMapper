#pragma once

#include "ofGraphics.h"
#include "ofEvents.h"
#include "SurfaceManager.h"
#include "RadioList.h"
#include "MediaServer.h"
#include "CmdManager.h"
#include "SetSourceCmd.h"

namespace ofx {
namespace piMapper {

class SourcesEditorWidget {
	public:
		SourcesEditorWidget();

		void setup();
		void draw();
		void loadImage(std::string name, std::string path);
		void disable();
		void enable();
		void setSurfaceManager(SurfaceManager * newSurfaceManager);
		void setCmdManager(CmdManager * cmdManager);

		// Sets external MediaServer
		void setMediaServer(MediaServer * newMediaServer);
		MediaServer * getMediaServer();

		void selectSourceRadioButton(std::string & sourcePath);

		int getLoadedTexCount();
		ofTexture * getTexture(int index);

		void setFboSource(std::string & fboName);
        void setFileSource(std::string &filePath, int sourceType);
		void clearSource();

	private:
		MediaServer * mediaServer;
		SurfaceManager * surfaceManager;

		RadioList * fboSelector;
    
        map <std::string, RadioList*> dirSelector;
    
		CmdManager * _cmdManager;
	
		// Methods for creating and destroying the source selectors
		void createSelectors();
        void destroySelectors();

		// Methods for adding and removing listeners to the media server
		void addMediaServerListeners();
		void removeMediaServerListeners();

		// Handles GUI event, whenever someone has clicked on a radio button
		void handleFboSelected(std::string & fboName);
        void handleFileSelected(std::string &filePath);

		// Careful clearing of the media server,
		// clears only if the media server has been initialized locally
		void clearMediaServer();

		// MediaServer event handlers
		void handleImageAdded(std::string & path);
		void handleImageRemoved(std::string & path);
		void handleVideoAdded(std::string & path);
		void handleVideoRemoved(std::string & path);
		void handleImageLoaded(std::string & path);
		void handleImageUnloaded(std::string & path);
		void handleFboSourceAdded(std::string & name);
		void handleFboSourceRemoved(std::string & name);
		void handleFboSourceLoaded(std::string & name);
		void handleFboSourceUnloaded(std::string & name);

};

} // namespace piMapper
} // namespace ofx

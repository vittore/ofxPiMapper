#include "OMXPlayerCache.h"

#ifdef TARGET_RASPBERRY_PI

namespace ofx {
namespace piMapper {

OMXPlayerCache * OMXPlayerCache::_instance = 0;

OMXPlayerCache * OMXPlayerCache::instance(){
	if(_instance == 0){
		_instance = new ofx::piMapper::OMXPlayerCache();
	}
	return _instance;
}

ofxOMXPlayer * OMXPlayerCache::load(std::string moviePath){
	if(_players.find(moviePath) == _players.end()){
		ofxOMXPlayerSettings settings;
		settings.videoPath = moviePath;
		settings.useHDMIForAudio = VideoSource::useHDMIForAudio;
		settings.enableTexture = true;
		settings.enableLooping = true;
		settings.enableAudio = VideoSource::enableAudio;
        settings.initialVolume = 0.3;
//        settings.autoStart = true;
		
		ofxOMXPlayer * p = new ofxOMXPlayer();
        p->engine.m_config_audio.device="omx:alsa";
//        p->engine.m_config_audio.subdevice ="hw:1,0";
		p->setup(settings);
		_players[moviePath] = p;
		
		return p;
	}
	
    _players[moviePath]->restartMovie();
	return _players[moviePath];
}

void OMXPlayerCache::unload(std::string moviePath){
	if(_players.find(moviePath) != _players.end()){
		_players[moviePath]->setPaused(true);
	}
}

} // namespace piMapper
} // namespace ofx

#endif

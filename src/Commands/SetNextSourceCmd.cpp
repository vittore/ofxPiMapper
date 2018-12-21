#include "SetNextSourceCmd.h"

namespace ofx {
namespace piMapper {

SetNextSourceCmd::SetNextSourceCmd(BaseSurface * surface, SourcesEditorWidget * sourcesEditor){
	_surface = surface;
	_sourcesEditor = sourcesEditor;
}

void SetNextSourceCmd::exec(){
	ofLogNotice("SetNextSourceCmd", "exec");

	// Get current source
	BaseSource * source = _surface->getSource();
	int sourceType = source->getType();
	
	std::string sourceId;
	if(source->isLoadable()){
		sourceId = source->getPath();
	}else{
		sourceId = source->getName();
	}
	
	// MediaServer shortcut
	MediaServer * mediaServer = _sourcesEditor->getMediaServer();
	
	// Read sources into a single vector
    std::vector<std::string> dirNames = mediaServer->getDirectoryNames();
    for(int i=0; i<dirNames.size(); i++){
        std::vector<std::string> paths = mediaServer->getDirectoryFilePaths(dirNames[i]);
        for(int j=0; j<paths.size(); j++){
            SourceData data;
            data.type = SourceTypeHelper::GetSourceTypeHelperEnumByFile(paths[j]);
            data.id = paths[j];
            _sources.push_back(data);
        }
    }
	for(unsigned int i = 0; i < mediaServer->getFboSourceNames().size(); ++i){
		SourceData data;
		data.type = SourceType::SOURCE_TYPE_FBO;
		data.id = mediaServer->getFboSourceNames()[i];
		_sources.push_back(data);
	}
	
	if(_sources.size() <= 0){
		return;
	}
	
	_sourceIndex = -1;
	
	// Search for current source among all
	for(unsigned int i = 0; i < _sources.size(); ++i){
		if(sourceType == _sources[i].type && sourceId == _sources[i].id){
			_sourceIndex = i;
			break;
		}
	}
	
	if(_sourceIndex == -1){
		if(_sources.size()){
			_nextSourceIndex = 0;
		}else{
			return;
		}
	}
	
	_nextSourceIndex = _sourceIndex + 1;
	if(_nextSourceIndex >= _sources.size()){
		_nextSourceIndex = 0;
	}

    if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_IMAGE){
        _sourcesEditor->setFileSource(_sources[_nextSourceIndex].id, _sources[_nextSourceIndex].type);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_VIDEO){
        _sourcesEditor->setFileSource(_sources[_nextSourceIndex].id, _sources[_nextSourceIndex].type);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_sources[_nextSourceIndex].id);
	}else if(_sources[_nextSourceIndex].type == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}
	
	Gui::instance()->getTextureEditorWidget().createJoints();
}

void SetNextSourceCmd::undo(){
	ofLogNotice("SetNextSourceCmd", "undo");

    if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_IMAGE){
        _sourcesEditor->setFileSource(_sources[_sourceIndex].id, _sources[_sourceIndex].type);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_VIDEO){
        _sourcesEditor->setFileSource(_sources[_sourceIndex].id, _sources[_sourceIndex].type);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_FBO){
		_sourcesEditor->setFboSource(_sources[_sourceIndex].id);
	}else if(_sources[_sourceIndex].type == SourceType::SOURCE_TYPE_NONE){
		_sourcesEditor->clearSource();
	}
	
	Gui::instance()->getTextureEditorWidget().createJoints();
}

} // namespace piMapper
} // namespace ofx


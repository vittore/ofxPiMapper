//
//  DirectoryViewer.cpp
//
//  Created by 남정호 on 19/12/2018.
//

#include "DirectoryViewer.h"

namespace ofx {
namespace piMapper {

DirectoryViewer::DirectoryViewer(std::string path){
    directoryPath = path;
    _directory.allowExt("mp4");
    _directory.allowExt("h264");
    _directory.allowExt("mov");
    _directory.allowExt("avi");
    _directory.allowExt("ogv");
    _directory.allowExt("mpeg");
    _directory.allowExt("mkv");
    _directory.allowExt("png");
    _directory.allowExt("jpg");
    _directory.allowExt("jpeg");
    reload();
}

DirectoryViewer::~DirectoryViewer(){
    _filePaths.clear();
}
void DirectoryViewer::reload(){
    _directory.listDir(directoryPath);
    _directory.sort();
    
    _filePaths.clear();
    for(int i = 0; i < _directory.size(); ++i){
        _filePaths.push_back(directoryPath + _directory.getName(i));
        ofLog() << _directory.getName(i);
    }
}

std::vector<std::string> & DirectoryViewer::getFilePaths(){
    return _filePaths;
}
    
} // namespace piMapper
} // namespace ofx

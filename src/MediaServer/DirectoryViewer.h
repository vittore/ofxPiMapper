//
//  DirectoryViewer.h
//
//  Created by 남정호 on 19/12/2018.
//

#pragma once

#include "ofMain.h"
#include "SourceType.h"

namespace ofx {
namespace piMapper {

class DirectoryViewer {
    public:
        DirectoryViewer(std::string path);
        virtual ~DirectoryViewer();
        std::vector<std::string> &getFilePaths();
        void reload();
    
    private:
        ofDirectory _directory;
        std::string directoryPath;
        std::vector<std::string> _filePaths;
    
};
    
} // namespace piMapper
} // namespace ofx

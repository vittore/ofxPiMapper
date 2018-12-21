#pragma once

#include "ofLog.h"
#include "SourceType.h"

#define SOURCE_TYPE_NAME_NONE "none"
#define SOURCE_TYPE_NAME_IMAGE "image"
#define SOURCE_TYPE_NAME_VIDEO "video"
#define SOURCE_TYPE_NAME_FBO "fbo"

namespace ofx {
namespace piMapper {

class SourceTypeHelper {
	public:
		static std::string GetSourceTypeHelperName(SourceType sourceTypeEnum){
			if(sourceTypeEnum == SOURCE_TYPE_IMAGE){
				return SOURCE_TYPE_NAME_IMAGE;
			}else if(sourceTypeEnum == SOURCE_TYPE_VIDEO){
				return SOURCE_TYPE_NAME_VIDEO;
			}else if(sourceTypeEnum == SOURCE_TYPE_NONE){
				return SOURCE_TYPE_NAME_NONE;
			}else if(sourceTypeEnum == SOURCE_TYPE_FBO){
				return SOURCE_TYPE_NAME_FBO;
			}else{
				std::stringstream ss;
				ss << "Invalid source type: " << sourceTypeEnum;
				ofLogFatalError("SourceTypeHelper") << ss.str();
				exit(EXIT_FAILURE);
			}
		}

		static SourceType GetSourceTypeHelperEnum(std::string sourceTypeName){
			if(sourceTypeName == SOURCE_TYPE_NAME_IMAGE){
				return SOURCE_TYPE_IMAGE;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_VIDEO){
				return SOURCE_TYPE_VIDEO;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_NONE){
				return SOURCE_TYPE_NONE;
			}else if(sourceTypeName == SOURCE_TYPE_NAME_FBO){
				return SOURCE_TYPE_FBO;
			}else{
				std::stringstream ss;
				ss << "Invalid source type name: " << sourceTypeName;
				ofLogFatalError("SourceTypeHelper") << ss.str();
				exit(EXIT_FAILURE);
			}
		}
    
        static SourceType GetSourceTypeHelperEnumByFile(std::string & filePath){
            std::string ext = ofFilePath::getFileExt(filePath);
            
            int sourceType = SourceType::SOURCE_TYPE_NONE;
            
            if(ext == "mp4" || ext == "h264" || ext == "mov" || ext == "avi" || ext == "ogv" || ext == "mpeg" || ext == "mkv"){
                return SOURCE_TYPE_VIDEO;
            }else if(ext == "png" || ext == "jpg" || ext == "jpeg"){
                return SOURCE_TYPE_IMAGE;
            }
            return SOURCE_TYPE_NONE;
        }
};

} // namespace piMapper
} // namespace ofx

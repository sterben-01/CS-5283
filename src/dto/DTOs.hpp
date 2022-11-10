#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO) //代码生成部分起点

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
//text 下面这个就是一个DTO范例。可以辅助生成JSON 可以在mapper帮助下序列化和反序列化
class MyDto : public oatpp::DTO {
  
  DTO_INIT(MyDto, DTO)
  
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
  
};

#include OATPP_CODEGEN_END(DTO) //代码生成部分终点
//docs: https://oatpp.io/docs/components/dto/#declaration

#endif /* DTOs_hpp */
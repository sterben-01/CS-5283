#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"
#include<fcntl.h>
#include<unistd.h>
#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen 代码生成部分起点


class MyController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:
  
  ENDPOINT("GET", "/", root) {
    //这条示范路由采用了JSON格式返回。所以需要DTO来辅助生成json
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  // TODO Insert Your endpoints here !!!
  // TODO 每一个/后面的URL对应着一个端点。endpoint端点是RESTFUL规范的一部分。也就是对应一条路由。 
  /*
  text 比如下面这个路由返回了一个HTML页面。下面blabla大概是三个步骤：
  1.打开文件
  2.写入文件至缓存（这个buffer需要自己设置。就是m_readbuf)
  3. 生成HTTP响应报文。响应报文第一个必须要有一个响应代码。中间的字段应该是框架帮助我们填充了。剩下的部分可以是DTO/文字/或者是buffer
  4.就是关闭文件描述符
  */
  ENDPOINT("GET", "/login", login){
    int filefd = open("../resource/login.html", O_RDONLY);
    if(filefd < 0){
        OATPP_LOGI("MyApp", "FILE open failed");
        return 0;
    }
    struct stat myfileState;
    fstat(filefd, &myfileState); //fstat（）用来将参数filedes 所指向的文件状态复制到参数buf 所指向的结构中
    //下面就是老一套的文件打开流程
    int fileSize = myfileState.st_size;
    printf("fd:%d ,file size %d\n ", filefd ,myfileState.st_size);
    char m_readbuf[8192];
    bzero(m_readbuf, 8192);
    read(filefd, m_readbuf, sizeof(m_readbuf));
    auto response = ResponseFactory::createResponse(Status::CODE_200, m_readbuf);
    close(filefd);
    return response;
  }
  //此处的例子是告诉我们这个框架的路由匹配是按照最短优先的。第三个字段的名字是起了个名而已。
  ENDPOINT("GET", "/login/1", login1){
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "login1!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  ENDPOINT("GET", "/login/2", login2){
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "login2!";
    return createDtoResponse(Status::CODE_200, dto);
  }
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen 代码生成部分终点

#endif /* MyController_hpp */
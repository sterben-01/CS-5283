#include "./controller/MyController.hpp"
#include "./AppComponent.hpp"

#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {

  /* Register Components in scope of run() method */
  //text我们在AppComponent这个类中进行了所有模块的初始化。所以run的时候需要执行这个步骤
  AppComponent components;

  /* Get router component */
  //text 获取路由模块。
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Get connection handler component */
  // text 获取链接处理程序
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  //text获取tcp链接提供程序
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);


   /* Create MyController and add all of its endpoints to router */
  //text 把所有路由模块连接至处理程序。也就是把HTTP解析后的不同URL分派到不同的处理程序。处理程序就是我们的MyController
  router->addController(std::make_shared<MyController>());


  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  //text 创建服务器，它接受提供的 TCP 连接并将其传递给 HTTP 连接处理程序
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("MyApp", "Server running on port %s", connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
  
}

/**
 *  main
 */
int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
  
  return 0;
}
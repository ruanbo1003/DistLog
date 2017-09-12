/*
 * RunHelper.cpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ruanbo
 */

#include <RunHelper.hpp>

RunHelper::RunHelper()
{

}

RunHelper::~RunHelper()
{

}

void RunHelper::run(int argc, char* argv[])
{
    if(argc < 2)
    {
        LogError("program parameter invalid.");
        return;
    }

    int my_id = std::stoi(argv[1]);

    LogMngr inst(my_id);

    if(inst.init() == false)
    {
        LogError("LonMngr init() failed");
        return;
    }

    inst.start();

    std::string input = "";
    while(true)
    {
      std::cin >> input;
      if(input == "quit" || input == "QUIT")
      {
          break;
      }
      else
      {
          Log("unknow cmd:%s", input.data());
      }
      usleep(10000);
    }

    inst.stop();

    inst.join();
}


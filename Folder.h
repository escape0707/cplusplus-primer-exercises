#pragma once

#include <set>

class Message;

class Folder {
 public:
  Folder();
  ~Folder();
  void addMsg(Message *pmsg);
  void rmMsg(Message *pmsg);

 private:
  std::set<Message *> messages;
};

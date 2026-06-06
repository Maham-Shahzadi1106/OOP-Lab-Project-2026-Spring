#ifndef USERAUTHENTICATION_H
#define USERAUTHENTICATION_H

#include <string>
using namespace std;
class UserAuthentication
{
private:
  string accessCode;

public:
  UserAuthentication(const string &accessCode = "1234");
  ~UserAuthentication();
  bool verify(const string &code) const;
  void setAccessCode(const string &code);
  string getAccessCode() const;
  string serialize() const;
};

#endif // USERAUTHENTICATION_H

#include "UserAuthentication.h"
using namespace std;
UserAuthentication::UserAuthentication(const string &accessCode)
    : accessCode(accessCode)
{
}

UserAuthentication::~UserAuthentication()
{
}

bool UserAuthentication::verify(const string &code) const
{
  return code == accessCode;
}

void UserAuthentication::setAccessCode(const string &code)
{
  accessCode = code;
}

string UserAuthentication::getAccessCode() const
{
  return accessCode;
}

string UserAuthentication::serialize() const
{
  return accessCode;
}

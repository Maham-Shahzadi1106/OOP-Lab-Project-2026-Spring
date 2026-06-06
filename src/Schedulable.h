#ifndef SCHEDULABLE_H
#define SCHEDULABLE_H

#include <string>
using namespace std;
class Schedulable
{
public:
  virtual ~Schedulable() {}
  virtual void schedule(const string &time) = 0;
  virtual void cancelSchedule() = 0;
};

#endif // SCHEDULABLE_H

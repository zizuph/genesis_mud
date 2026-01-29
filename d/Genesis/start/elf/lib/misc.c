#pragma save_binary

#include "../stddefs.h"

/*
 * misc library.
 */


notify(string name, string message)
{
  object person;
  
  person=find_living(lower_case(name));
  
  if (person && interactive(person))
    tell_object(person, 
		"** " + file_name(this_object()) + " (" +
		extract(ctime(time()), 4, 15) + "):\n**   " + 
		message + "\n\n");
}

void load_object(string roomfile)
{
  string str;

  seteuid(getuid(this_object()));
  
  if ((str = catch(call_other(roomfile, "?????"))) != 0)
    notify(MAINTAINER, "*\n*" + roomfile + "\n" + str + "*\n");
}

object make_object(string roomfile)
{
  string str;
  object obj;

  seteuid(getuid(this_object()));
  
  if ((str = catch(obj = clone_object(roomfile))) != 0)
    notify(MAINTAINER, "*\n*" + roomfile + "\n" + str + "*\n");

  return obj;
}
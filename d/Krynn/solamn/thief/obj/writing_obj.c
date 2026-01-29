/* The text object that is written on the ground somewhere */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <macros.h>

#define READABLE_INTERVAL    150 + random(100)

string where = "ground";
string my_message = " I was here.";
string blanks = "                                              ";


void
create_object()
{
   set_name("writing");
   add_name("text");
   add_name("message");
   add_name("words");
   add_name("letters");
   set_no_show_composite(1);
   set_long("@@my_long");
   add_prop(OBJ_M_NO_GET,"Take the writing?? Good joke!\n");
}

init()
{
  ADA("read");
  ADA("erase");
}

string
my_long()
{
  return "The letters:\n    " + capitalize(my_message) +
    "\nhave been written with chalk on the " + where + ".\n";
}


void
set_writing_text(string str, string loc)
{
  where = loc;
  my_message = " " + str;
}

void
initiate_self_destruct()
{
  set_alarm(itof(READABLE_INTERVAL),0.0,"maybe_remove_this_writing");
}


int
read(string str)
{
  NF("It is too dark to see.\n");
  if (!CAN_SEE_IN_ROOM(TP))
    return 0;
  NF("Read what?\n");
  if (!str || (str != "writing" && str != "text" && str != "message" &&
	       str != "words" && str != "letters"))
    return 0;
  write(long());
  return 1;
}


int
erase(string str)
{
  NF("It is too dark to see.\n");
  if (!CAN_SEE_IN_ROOM(TP))
    return 0;
  NF("Erase what?\n");
  if (!str || (str != "writing" && str != "text" && str != "message" &&
	       str != "words" && str != "letters"))
    return 0;
  write("You erase the text from the " + where + ".\n");
  SAYBB(" bends down and wipes across the " + where + ".");
  E(TO)->remove_my_desc(TO);
  remove_object();
  return 1;
}


void
maybe_remove_this_writing()
{
  int let = random(strlen(my_message) - 1);
  my_message = my_message[0..let] + " " + my_message[(let + 2)..strlen(my_message)];
  if (blanks[0..(strlen(my_message) - 1)] == my_message)
    {
      E(TO)->remove_my_desc(TO);
      set_alarm(3.0,0.0,"remove_object");
    }
  else
    set_alarm(itof(READABLE_INTERVAL),0.0,"maybe_remove_this_writing");
}

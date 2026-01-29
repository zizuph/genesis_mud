inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"

create_room() {
  set_short("Inside an old building in Minas Tirith");
  set_long("@@long_func");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/minas/s3crc1","south",0);
  add_exit("/d/Gondor/minas/rooms/oldattic","up",0);
  add_exit("/d/Gondor/minas/rooms/oldcellar","down",0);
  add_item(({"marks","dust","floor"}),"@@exa_marks");
}

long_func() {
  string longstr;
  longstr = "You are in the dusty hall of the old building. The cold stone floor "+
    "is quite bare - in fact the whole hall is empty. There is however a set "+
      "of stairs leading up to the attic, and another leading down in the basement. ";
  if (this_player()->query_skill(107)>10) longstr = longstr+
    "Your skilled eyes discover some marks in the dusty floor. ";
  longstr = longstr + "The exit back out to the street is south.\n";
  return (break_string(longstr,75));
}

exa_marks()
{
  if (this_player()->query_skill(107)>15) 
      return (break_string("Studying the marks in the dust, you find that they lead towards the stairs to the basement.\n",75));
  else if (this_player()->query_skill(107)>10)
    return (break_string("You try to make something out of the marks in the dust, but you can't see where they lead.\n",75));
  else return "You don't see anything special about the floor.\n";
}

  

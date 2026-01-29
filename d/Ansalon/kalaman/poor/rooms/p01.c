#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

string query_door_desc();
string query_room_desc();
int query_door_open();
int query_door_show();

create_kalaman_room()
{
    set_short("Infront of Prison Gate");
    set_long("You stand just infront of the city prison gate " +
      "in a soon to be poor district of Kalaman.\n");

    add_exit(DROOM + "entrance","west", query_door_open, 0, query_door_show);
    add_exit("s11","east");
}

void
init()
{
  ::init();

  add_action("door_open", "open");
  add_action("door_close", "close");
}

string
query_door_desc()
{
  if (!KMASTER->query_status(S_MAINGATE) )
  {
    return "The oak door is currently closed.\n";
  }

  return "The oadk door is currently open.\n";
}

int
query_door_open()
{
   if (KMASTER->query_status(S_MAINGATE) ) return 0;

   write("The door is closed!\n");
   return 1;
}

int
query_door_show()
{
   if (KMASTER->query_status(S_MAINGATE) ) return 0;

   return 1;
}

string
query_room_desc()
{
   string text = "You stand just inside the city prison of " +
     "Kalaman. This is a building cut out of the little " +
     "mountain that exists beneath Kalaman. This prison " +
     "holds all the villians and thieves that has been " +
     "cought by the city and noble guard. " +
     "The east wall is pretty much a huge gate " +
     "that leads out to the poor district of Kalaman. To the " +
     "south is a guard room. Just right of the gate is a " +
     "smaller but still massive oak door that is used to " +
     "let new guards in and guards going on permission out.";

   if(!KMASTER->query_status(S_MAINGATE) )
     return text += " The oak door is currenly closed.\n";

  return text += " The oak door is currently open.\n";
}

int
door_open(string str)
{
  if(!str)
   return 0;

  KMASTER->set_status(S_MAINGATE, 1);
  write("You open the door.\n");

  return 1;
}

int
door_close(string str)
{
  if(!str)
   return 0;

  KMASTER->set_status(S_MAINGATE, 0);
  write("You close the door.\n");

  return 1;
}

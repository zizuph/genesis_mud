/* 
ROOM: City Council entrance hall
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
  ::create_room();                         
  hear_bell = 2;                           

  add_prop(ROOM_I_INSIDE, 1);
  
  set_short("The hallway of the City Council building");
  set_long(
    "The City Council building consists of a long hallway with several "+
    "offices on each side, and a debate chamber at the end. The hall is "+
    "is very plain, no accessories are standing anywhere, and no carpet "+
    "covers the dirty wooden floor. " 
  );
  set_time_desc(
    "Many people are walking up and down the corridor.\n",
    "You feel a light rush of air, and for a moment think you see "+
    "a shadow at the edge of your vision.\n"
  );

  add_exit(CENTRAL(plaza/cc_hall2), "north", 0, 0, 0);
   add_exit(CENTRAL(plaza/cc_off1), "west", 0, 0, 0);
  add_exit(CENTRAL(plaza/sq_north), "out", 0, 0, 0);

  add_item("offices",
    "There is an office to the east with a sign on the door.\n"
  );
  add_item(({"office", "sign"}),
    "The office to the west has a sign on the door reading 'Council "+
    "Administration.'\n"
  );

  add_item("shadow", "@@is_shadow@@\n");
}

string
is_shadow()
{
  if (DAY) return "You find no shadow.";
  return "Everything is quiet. You must have been mistaken.";
}

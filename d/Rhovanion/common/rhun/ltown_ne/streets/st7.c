#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("The street heads back to the west from here."
    +"  It is not paved, but its dirt surface is easily defined, and"
    +" well-marked.  Sections of the town wall which you may approach"
    +" lie to the east and south.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/bywall6", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/bywall5", "east", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st6", "west", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
}

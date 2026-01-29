#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("On the street");
  set_long("You walk down the street in this large"
    +" large town.  A few people pass by; but it is mostly"
    +" empty.  You wonder if something frightened the people away"
    +"-- or killed them off.  To the west stands a guard house, "
    +"apparently still in use, while a nicer building-- perhaps"
    +" the mayor's estate?-- lies"
    +" just south of here.  You may also approach the town's"
    +" low stone wall to the southwest.  The street continues from"
    +" north to east.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st7","east",0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/guard_house2", "west", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/mayor_house", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st5", "north", 0);
  add_exit(RHUN_DIR+"ltown_ne/streets/bywall7", "southwest", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item("guard house", "The guard house is a large"
    +" wooden structure.  It looks rather well built, though now"
    +" quite old.\n");
  add_item(({"house", "mayor house", "mayor's house", "estate", 
    "mayor's estate", "mayor estate", "mayoral estate", "building", 
    "nicer building", "nice building"}), "The larger"
    +" building just to the south-- the mayor's house-- seems much"
    +" nicer than the others in this town.  He apparently has more"
    +" money than his impoverished citizens.  The door is open, "
    +"if you'd like to step inside.\n");
}

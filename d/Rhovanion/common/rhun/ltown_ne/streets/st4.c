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
    +"-- or killed them off.  To the north stands a guard house, "
    +"apparently still in use, while an old training hall lies"
    +" just south of here.  You may also approach the town's"
    +" low stone wall to the east.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/bywall4","east",0);
  add_exit(RHUN_DIR+"ltown_ne/streets/st3", "west", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/train", "south", 0);
  add_exit(RHUN_DIR+"ltown_ne/bldgs/guard_house1", "north", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"house","guard house"}), "The guard house is a large"
    +" wooden structure.  It looks rather well built, though now"
    +" quite old.\n");
  add_item(({"hall", "training hall"}), "The training"
    +" hall is made of wood.  It was perhaps once a very busy and"
    +" prosperous place; now, it looks to have fallen into disuse and"
    +" disrepair.\n");
}

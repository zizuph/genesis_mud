#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

object guard;

void reset_room()
{
  if(!objectp(guard))
  {
    reset_euid();
    guard=clone_object(RHUN_DIR+"npc/guard");
    guard->arm_me();
    guard->set_random_move(4);
    guard->set_restrain_path(RHUN_DIR+"ltown_sw");
    guard->move(TO,1);
  }
}

void create_room()
{
  set_short("Town gate");
  set_long("This is the gate for this large town.  It"
    +" is made of steel, and stretches between two sections of the"
    +" low stone wall that surrounds the city.  There is a small"
    +" guard station here, presumably where the watch stands guard."
    +"  You may enter town to the east, leave by taking the dirt"
    +" road west, or follow along the inside edge of the wall to"
    +" the southwest.  There is also a guard house to the north,"
    +" while a side street heads south.\n");

  add_exit(RHUN_DIR+"ltown_sw/streets/st1","east",0);
  add_exit(RHUN_DIR+"ltown_sw/streets/bywall1", "southwest", 0);
  add_exit(RHUN_DIR+"roads/section4/g", "west", 0);
  add_exit(RHUN_DIR+"ltown_sw/bldgs/guard_house1", "north", 0);
  add_exit(RHUN_DIR+"ltown_sw/streets/st11", "south", 0);

  add_item("wall", "The town wall is made of stone,  and"
    +" surrounds the town.  It is quite low, not very useful for"
    +" defence.\n");
  add_item(({"plains", "plains of rhun"}), 
    "The plains of Rhun in eastern Rhovanion stretch"
    +" out to the west, seemingly endless.\n");
  add_item("gate", "The gate is made of shiny steel, though"
    +" a bit rusty in spots.  It doesn't look as though it would be"
    +" much good against an attack of any sort.\n");
  add_item("town", "This large town appears, if not"
    +" prosperous,  at least self-sufficient.  You guess that some"
    +" of the citizens, however, live rather poorly.\n");
  add_item(({"station", "guard station"}), "A low"
    +" wooden shack stands near the gate.  You guess that it is the"
    +" guard station, where the gate guard keeps his watch.\n");
  add_item("road", "The well-defined dirt road leads away"
    +" from the town to the west.\n");
  add_item(({"house", "guard house"}), "The guard house"
    +" is a large wooden structure that lies just north of the"
    +" gate.  It houses the city watch.\n");

  reset_room();
}

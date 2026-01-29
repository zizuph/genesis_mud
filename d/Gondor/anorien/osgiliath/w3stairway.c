inherit "/d/Gondor/common/room";
inherit "/d/Gondor/anorien/osgiliath/osgiliath";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

int door_broken;

create_room()
{
  set_short("In a dark corridor in the ruins of Central Osgiliath");
  set_long(BSN("This is the top of a narrow stairway. A doorway "+
    "is visible to the east. The dank stone walls show signs of age, "+
    "but may well stand for another millenium. A small sign by the "+
    "doorway shows the letters 'IIPR RY'. Stairs "+
    "lead down into the darkness below."));
  add_prop(ROOM_M_NO_TELEPORT, check_teleport);
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,0);
  add_item(({"torch-stands","stands","torch-stand","stand"}),BSN("They are "+
    "made of metal rings, now rusty beyond being usable."));
  add_item("walls",BSN("The walls are made of smooth white stone, though "+
    "the passage of hundreds of years since repair have left solid tracks."));
  add_item(({"door","doorway"}),"@@exa_door");
  add_item("sign","The sign is very old, and when you study it closely, you gather that\n"+
    "the letters are not complete .....\n");
  add_item(({"stairs","stair","stairway"}),BSN("The stone stairs lead "+
    "down from here, in a narrow stairway with white stone walls."));
  add_exit(OSG_DIR+"library1","east","@@test_door",1);
  add_exit(OSG_DIR+"w2stairway","down",0,2);
}

exa_door()
{
  if (door_broken) return "The doorway is open, leading into a dark room beyond.\n"+
    "On the floor lies the remains of the rotting wooden door.\n";
  else return BS("The doorway is closed by a wooden door, seemingly "+
    "rotting in the damp air. May be you can break it open.\n");
}

test_door()
{
  if (!door_broken) {
    write("The door is closed. You might be able to break it though.\n");
    return 1;
    }
  write("You step over the remains of the broken door.\n");
  return 0;
}

break_door(string str)
{
  if (!str) {
    write("Break what?\n"); return 1; }
  if (str != "door" && str != "open door") {
    NF("What do you want to break?\n");
    return 0; }
  if (door_broken) {
    notify_fail("The door is already lying on the floor in a collapsed heap.\n");
    return 0;
    }
  door_broken = 1;
  write("You easily kick down the rotten door.\n"+
    "The remains collapse in a heap on the floor.\n");
  say(QCTNAME(TP)+" breaks down the rotting door with little effort.\n",TP);
  return 1;
}

init()
{
  ::init();
  add_action("break_door","break");
  add_action("break_door","bash");
  add_action("break_door","kick");
}


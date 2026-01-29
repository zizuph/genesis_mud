inherit "/std/room";
#include "defs.h"

void 
create_room()
{
  ::create_room();

  set_short("On a path in a park");
  set_long(break_string(
    "Your standing in the northern part of the park called 'The Platinum "+
    "Park'. This park is very neatly kept and the grass is extremely short. "+
    "The high palmtrees cast long shadows on the ground, giving the place "+
    "a nice touch. You feel very relaxed while walking around and you can "+
    "hear birds singing. Southeast lies an opening and north is the exit "+
    "out of the park, where you can see some roofs of buildings."+
    "\n",70));

  OUTSIDE;
  LIGHT;

  add_item("path",
    "The path is made of marble bricks stuck together, which makes it "+
    "very comfortable to walk on it.\n");
  add_item(({"brick","bricks"}),
    "The path consists of them. They look expensive and heavy.\n");
  add_item("park",
    "This park is extremely well-kept. The atmosphere here really calms you "+
    "down.\n");
  add_item(({"palm","palms","tree","trees","palmtree","palmtrees"}),
    "The palm trees makes long shadows on the ground, and close to the "+
    "tops you notice that they have coconuts.\n");
  add_item("grass",
    "The grass is very short, they must be cutting it with scissors!\n");
  add_item("sun",
    "The sun hangs low in the sky. This creates this strange light that "+
    "makes this island so special.\n");
  add_item("marble",
    "The bricks are made of marble.\n");
  add_item(({"bird","birds"}),
    "You can't see them, only hear them.\n");
  add_item("opening",
    "Looks like a resting place in the park.\n");
  add_item("exit",
    "It's to the north of here.\n");
  add_item(({"roof","roofs"}),
    "It the roofs of some buildings outside the park. They are made of "+
    "straw, like natives' houses in the tropics.\n");
  add_item(({"building","buildings"}),
    "The buildings are white with straw roofs. They look neat and as "+
    "well-kept as everything else here.\n");

  //add_exit(RMCROOMS+"road1","north");
  //add_exit(RMCROOMS+"park8","west");
  //add_exit(RMCROOMS+"park9","east");
  //add_exit(RMCROOMS+"park6","south");
  add_exit(RMCROOMS+"path3","southeast");
}

void
init()
{
  ::init();

  add_action("climber","climb");
  add_action("picker","pick");
  add_action("getter","get");
  add_action("getter","take");
}

int
climber(string str)
{
  NF("Climb what?\n");
  if (str=="tree" || str=="palmtree")
  {
    write("Leave the path if you want to do that.\n");
    return 1;
  }
  return 0;
}

int
picker(string str)
{
  NF("Pick what?\n");
  if (str == "nut" || str == "coconut")
  {
    write("Leave the path if you want to do that.\n");
    return 1;
  }
  return 0;
}

int
getter(string str)
{
  NF("Get/Take what?\n");
  if (str == "brick")
  {
    write("You try to lift the marble brick... But it is stuck to "+
      "the ground.\n");
    say(QCTNAME(TP)+" tries to get one of the marble bricks, but fails.\n");
    return 1;
  }
  return 0;
}

inherit "/std/room";
#include "defs.h"

void 
create_room()
{
  ::create_room();

  set_short("On a path in a park");
  set_long(break_string(
    "You are walking on a small, bricked path through a calm and "+
    "relaxing park area called 'The Platinum Park'. In this park, "+
    "large palm trees are growing and the grass is short. This park "+
    "is neatly managed by loving hands. A tower is to the south and "+
    "beyond it, you can spot the lagoon with its green water shimmering "+
    "in the sunlight. A marble stairway lead up to an entrance in the "+
    "tower and the path continues further into the park to the northeast."+
    "\n",70));

  OUTSIDE;
  LIGHT;

  add_item("path",
    "The path is made of marble bricks stuck together, which makes it "+
    "very comfortable to walk on.\n");
  add_item(({"brick","bricks"}),
    "The path consists of them. They look expensive and heavy.\n");
  add_item("park",
    "This park is extremely well-kept. The atmosphere here really calms you "+
    "down.\n");
  add_item(({"palm","palms","tree","trees","palmtree","palmtrees"}),
    "The palm trees make long shadows on the ground, and close to the "+
    "tops you notice that they have coconuts.\n");
  add_item("grass",
    "The grass is very short, they must be cutting it with a small knife.\n");
  add_item("tower",
    "The tower is white and is quite high. It looks quite impressive "+
    "actually.\n");
  add_item("lagoon",
    "Behind the tower you catch a glimpse of the shimmering green water "+
    "in the lagoon.\n");
  add_item("water",
    "The water almost hypnotizes you with its green colour and the sun "+
    "that is reflected by the surface.\n");
  add_item("sun",
    "The sun hangs low in the sky. This creates this strange light that "+
    "makes this island so special.\n");
  add_item("stairway",
    "It's a marble stairway leading to the entrance in the tower.\n");
  add_item("marble",
    "Both the bricks and the stairway are made of marble.\n");
  add_item("entrance",
    "It leads inside the tower.\n");

  //add_exit(RMCROOMS+"park4","north");
  add_exit(RMCROOMS+"path2","northeast");
  add_exit(RMCROOMS+"park1","west");
  //add_exit(RMCROOMS+"park2","east");
  add_exit(RMCROOMS+"private1","south","@@stairway");
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

int
stairway()
{
  write("You enter the stairway and walk into the tower.\n");
  return 0;
}

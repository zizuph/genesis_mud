inherit "/std/room";
#include "defs.h"

object bench;

string
sign()
{
  return "\n"+
    "+-----------------------------+\n"+
    "| $                         $ |\n"+
    "|    Do not feed the fish!    |\n"+
    "|                             |\n"+
    "|       The park warden       |\n"+
    "| $                         $ |\n"+
    "+-----------------------------+\n\n";
}

void
restore_room()
{
  FIXEUID;

  if (!bench)
  {
    bench = clone_object(RMCOBJ + "bench");
    bench->move(TO);
  }
}

void 
create_room()
{
  ::create_room();

  set_short("On a path in a park");
  set_long(break_string(
    "This is a resting place in the park. A pond is here, and around it "+
    "the ground is covered with the marble bricks. Small fish swim around "+
    "in the pond, completely unaware of the world outside it. The "+
    "palm trees surround this spot, hiding it from the wind. "+
    "The air smells of all kinds of fragrances and you feel very relaxed. "+
    "here. Perhaps you should sit down for a second of meditation. A sign "+
    "is standing here."+
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
    "The palm trees makes long shadows on the ground, and close to the "+
    "tops you notice that they have coconuts.\n");
  add_item("grass",
    "The grass is very short, they must be cutting it with a small knife.\n");
  add_item("sun",
    "The sun hangs low in the sky. This creates this strange light that "+
    "makes this island so special.\n");
  add_item("marble",
    "The bricks are made of marble.\n");
  add_item("pond",
    "A small pond with fish swimming around in it.\n");
/*  add_item("fish","Small yellow fish swimming in the pond. You wonder what "+
    "kind of life that would be.\n");*/
  add_item("fish","Small yellow fish are swimming in the pond. You wonder what "+
    "species it might be.\n");
  add_item("sign","There's some readable text on it.\n");
  add_cmd_item("sign","read","@@sign");

  add_exit(RMCROOMS+"path4","northwest");
  //add_exit(RMCROOMS+"park9","north");
  //add_exit(RMCROOMS+"park6","west");
  //add_exit(RMCROOMS+"park7","east");
  add_exit(RMCROOMS+"path2","south");

  restore_room();
}

void
init()
{
  ::init();

  add_action("climber","climb");
  add_action("picker","pick");
  add_action("getter","get");
  add_action("getter","take");
  add_action("feeder","feed");
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
feeder(string str)
{
  NF("Feed what?\n");
  if (str == "fish")
  {
    write("You start walking towards the pond.\nSuddenly a little hobbit "+
      "rushes towards you, screaming: Can't you read? You're not allowed "+
      "to feed the fish!\nThe small hobbit sneers at you and walks away, "+
      "muttering something about a stupid "+TP->query_race_name()+".\n");
    say(QCTNAME(TP)+" starts walking towards the pond.\nSuddenly a little "+
      "hobbit rushes towards "+TP->query_objective()+", screaming: Can't "+
      "you read? You're not allowed to feed the fish!\nThe small hobbit "+
      "sneers at "+QCTNAME(TP)+" and walks away, muttering something about "+
      "a stupid "+TP->query_race_name()+".\n");
    return 1;
  }
  return 0;
}

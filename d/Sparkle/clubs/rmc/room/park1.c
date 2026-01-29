inherit "/std/room";
#include <ss_types.h>
#include "defs.h"

int coconut;

void
restore_room()
{
    if (!coconut)
        coconut = random(6);
}

string
cococheck()
{
    if (coconut)
        return "Hmmm... How to get hold of one of these. Maybe you could climb the "+
            "tree....or shake them down...\n";
    return "There are no coconuts on the tree.\n";
}

void 
create_room()
{
  ::create_room();

  set_short("In a park");
  set_long(break_string(
    "You are standing in a green and extremely well-kept park. The grass is very "+
    "short and it feels like a soft carpet under your feet. The trees are "+
    "stretching up towards the sky and shadowing some of the sunlight. "+
    "Some dark green bushes are growing to the north, and to the west you "+
    "can see a marble path leading through the park. Southeast lies a high "+
    "white tower and beyond it a shimmering lagoon."+
    "\n",70));

  OUTSIDE;
  LIGHT;

  add_item("path",
    "The path is made of marble bricks stuck together which makes it "+
    "very comfortable to walk on.\n");
  add_item(({"brick","bricks"}),
    "The path consists of them. Looks nice to walk on.\n");
  add_item("park",
    "This park is extremely well-kept. The atmosphere here really calms you "+
    "down.\n");
  add_item(({"palm","palms","tree","trees","palmtree","palmtrees"}),
    "The palm trees make long shadows on the ground, and close to the "+
    "tops you notice that they have coconuts. You wonder if you could "+
    "find a way to get hold of one...\n");
  add_item("grass",
    "The grass is very short, they must be cutting it with scissors!\n");
  add_item("sun",
    "The sun hangs low in the sky. This creates this strange light that "+
    "makes this island so special.\n");
  add_item("marble",
    "The bricks of the path are made of marble.\n");
  add_item(({"bird","birds"}),
    "You can't see them, only hear them.\n");
  add_item(({"bush","bushes"}),
    "The bushes are dark-green and have some reddish berries on them.\n");
  add_item("lagoon",
    "The lagoon's water is shimmering in the sunlight. It kind of breathtaking.\n");
  add_item("tower",
    "It's the RMC tower. There is an entrance to it if you walk east and follow "+
    "the path south.\n");
  add_item("water",
    "The water is green...\n");
  add_item(({"nut","nuts","coconut","coconuts"}),
    "@@cococheck");

  //add_exit(RMCROOMS+"park3","north");
  add_exit(RMCROOMS+"path1","east");

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
  add_action("shaker","shake");
}

int
climber(string str)
{
  NF("Climb what?\n");
  if (str=="tree" || str=="palmtree")
  {
    if (TP->query_skill(SS_CLIMB)>50 && random(100)<75)
    {
        if (coconut)
        {
/*            write("You managed to climb the palmtree and fetch a coconut "+
                  "the second you went down again.\n");*/
            write("You managed to climb the palmtree and fetch a coconut.\n");
            say(QCTNAME(TP)+" manages to climb the palmtree and fetch a "+
                "coconut.\n");
            coconut -= 1;
            return 1;
        }
        write("You managed to climb the palmtree, but there are no coconuts left...\n");
        say(QCTNAME(TP)+" manages to climb the palmtree, but there are no coconuts there.\n");
        return 1;
    }
    write("You tried to climb the palmtree, but you failed.\n");
    say(QCTNAME(TP)+" tried to climb the palmtree, but slipped "+
      "down again...\n");
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
      if (coconut)
          write("The coconut is so high up!\n");
      else
          write("There are no coconuts in the tree.\n");
      
      return 1;
  }
  return 0;
}

int
getter(string str)
{
  NF("Get/Take what?\n");
  if (str == "nut" || str == "coconut")
  {
      if (coconut)
          write("The coconut is so high up");
      else
          write("There are no coconuts in the tree.\n");
      
    return 1;
  }
  return 0;
}

int
coco()
{
  int str;

  str = TP->query_stat(SS_STR);
  if (random(str)>60)
  {
    write("Suddenly a coconut hits your head from above! Ouch...that hurts.\n");
    say("Suddenly a coconut fall down on "+QTNAME(TP)+"'s head! That must hurt!\n");
  }
  return 1;
}

int
shaker(string str)
{
  NF("Shake what?\n");
  if (str == "tree" || str == "palmtree")
  {
    write("You shake the palmtree and nothing happens.\n");
    write("You sigh deeply.\n");
    say(QCTNAME(TP)+" tries to shake down a coconut, but nothing happens.\n");
    say(QCTNAME(TP)+" sighs deeply.\n");

    if (coconut)
        set_alarm( 5.0, 0.0, "coco");
    
    return 1;
  }
  return 0;
}

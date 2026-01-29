inherit "/d/Gondor/anorien/nimrais/quest/wall.c";
#include "dirdefs.h"
#include "/d/Gondor/defs.h"
#include "/sys/ss_types.h"

#define UP_ROOM      "rock"
#define DOWN_ROOM    "plateau3"

create_room()
{
  area = "White Mountains";
  where = "a mountain wall";
  extraline = "";
  up_room = THIS_DIR + UP_ROOM;
  down_room = THIS_DIR + DOWN_ROOM;
  add_item(({ "blood" }), "@@blood_desc");
  add_item(({"eagle"}), "@@exa_eagle");
  make_the_room();
}

blood_desc()
{
  if (TP->query_skill(SS_AWARENESS) <= 10) return "You find no blood.\n";
  return "It seems to be rather fresh blood, because rain hasn't " +
    "washed it off yet.\n";
}

long_desc()
{
    string text, dir;
    text = "You are climbing " + where + " in the " + area + ". ";
    text += "It's a very uncomfortable place. Above you can see a projecting rock. ";
    if (extraline)
        text += extraline;

    if (TP->query_skill(SS_AWARENESS) > 10)
      text += "You spot some blood on the wall. ";

    if(!up_room->query_is_eagle())
      text += "You see an eagle circling the mountain. ";
    text += "You might be able to climb up or down.";

    return BS(text + "\n");
}

string
exa_eagle()
{
  if(up_room->query_is_eagle())
    return "You find no eagle. \n";
  return BSN("High above the rock, you can see an eagle circling the mountain. ");
}

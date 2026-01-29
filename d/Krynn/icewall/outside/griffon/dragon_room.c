/* Dragon back coded by Nick */

inherit  "/std/room";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "local.h"
#include "/d/Krynn/icewall/local.h"

/*prototype*/
string query_place();


object griffon;
object room;
int flying, place;

void
reset_room()
{
    add_prop(NO_DRAGON_ATTACK, 1);
    if(griffon)
      return;

    seteuid(getuid(TO));
    (griffon = clone_object(THE_DRAGON))->move(VOID, 1);
}

void
create_room()
{
    set_short("On griffon");
    set_long("You are on the back of a large fearless griffon high up in the air. " +
         "You can feel the wind in your hair. The griffon flies very fast. " +
         "Far below you can see the ground. It's a long way to fall if " +
         "you jump.\n");

    add_item("griffon",
         "You are sitting on its broad back, between the wings.\n");
    add_item("ground", "You really want to look down? Well, okay...\n" +
        "The ground is moving by too fast for you to see it very clearly. " +
        "You can tell you're heading south though. This griffon is really flying fast!\n");
    add_item("bird", "He's just flying along minding his own business. " +
        "You are directly above him, and he doesn't see you. " +
        "Nasty thoughts of what you could do to him enter your head.\n");
    OUTSIDE  /* An outside room */
    reset_room();
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(NO_DRAGON_ATTACK, 1);
}

void
init()
{
    object ob;

    flying = 1;
    call_out("wind", 2, TP);
    call_out("wind", 10, TP);
    if (find_call_out("land") == -1)
      call_out("land", 24, TP);

    ADA("jump");
    ADA("spit");
}

void
wind(object ob)
{
      tell_object(ob, "You see a bird pass by below you.\n");
}


void
land(object ob)
{
    int i;
    object *obj;

    griffon->time_to_land(0, TO);
    obj = all_inventory(TO);
    for (i = 0; i < sizeof(obj); i++)
      {
      if (!P(obj[i], TO))
        continue;
      tell_object(obj[i], "The griffon lands and you descend.\n");
      obj[i]->move_living("off the griffon", query_place());
      }
}

int
call_dragon(int i)
{
    object room;

    seteuid(getuid(TO));
    VOID->load_me();
    if (flying || !griffon)
      return 0;

    flying = 1;
    if (place == i)
      return 1;
    place = i;
    griffon->time_to_land(5, TO);
    return 1;
}

void
set_flying(int i) { flying = i; }

int
query_flying() { return flying; }

object
query_dragon() { return griffon; }

string
query_place()
{
    switch (place)
      {
    case 3:
    case 5:
      return LANDING1;
      break;
    case 2:
      return VOID;
      break;
    case 4:
      return LANDING2;
      break;
    default:
      write("Error.\n");
      break;
      }
}

void
set_place(int i)
{
    if (i == 6)
      i = 4;
    place = i;
}

int
query_place_num() { return place; }

int
jump()
{
    write("You stop looking down and leap into the air.\n");
    TP->move_living("with a big scream", LANDING2, 1);
    return 1;
}

int
spit(string str)
{
    if(!((str=="bird")||(str=="on bird")||(str=="on the bird")))
    {
    NF("Spit at whom?\n");
    return 0;
    }
    TP->catch_msg("You cough up a big gob of phlegm and spit at the " +
    "bird flying below you.\nSPLAT!!\nThe big gob of phlegm hits the bird " +
    "in the face, causing it to hurtle to the ground to it's death." +
    "\nYou killed the bird.\n");
    say(QCTNAME(TP) + " spits on the bird as it passes below.\n");
    return 1;
}

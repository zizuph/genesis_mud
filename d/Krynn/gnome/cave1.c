inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"

void
create_room()
{
    LIGHT;
    INSIDE;
    set_short("A cave-in");
    set_long("This narrow tunnel is NOT very old. A cave-in" +
      " seems to have happened here recently. There is rubble" +
      " all over the floor and the ceiling has been secured" +
      " with timbers to prevent further rocks from falling.\n");

    add_exit(TDIR + "cave2", "north", 0, 5);
    add_exit(TDIR + "corridor5", "south", 0, 1);

    add_item("rubble",
      "It consists of rocks, stones and pebbles. You take a "
      + "quick look through it\nbut cannot find anything of "
      + "interest.\n");
    add_item(({"timber", "timbers"}),
      "The timbers are thick and wooden.\n");
    add_item("dust", "You are COVERED with it!\n");
    add_item("ground",
      "There are cracks in the walls and ceiling "
      + "all over this place. You do\nnot feel too safe "
      + "in here.\n");
    add_item(({"smoke", "clouds"}), "It comes into here from the south. You can see "
      + "more and thicker smoke over there.\n");
}

void
expl1()
{
    tell_room(TO,
      "You hear some strange rumbling and rattling sounds from "
      + "the south.\n");
    set_alarm(20.0, -1.0, "expl2");
}

void
expl2()
{
    tell_room(TO, 
      "Suddenly the very ground you are standing on is trembling "
      + "fiercly! You start to feel really uncomfortable!\n");
    set_alarm(20.0, -1.0,"expl3");
}

void
expl3()
{
    tell_room(TO,
      "Suddenly there's a explosion to the west! "
      + "The walls start to tremble and dust"
      + "is raining onto you from the ceiling."
      + "Even more smoke fills the room. It becomes quite "
      + "dark.\n");
    add_prop(ROOM_I_LIGHT, 0);
    set_alarm(20.0, -1.0,"expl4");
}

void
expl4()
{
    tell_room(TO,
      "As suddenly as everything started it is quiet "
      + "again. Really quiet!\n");
    set_alarm(30.0, -1.0,"smokegone");
}


void
smokegone()
{
    tell_room(TO, "The smoke seems to have settled down.\n");
    add_prop(ROOM_I_LIGHT, 1);
}

string area() {return "Inthecorridors";}
string wayout() {return "south north";}
string tohelp() {return "north";}
string fromhelp() {return "south";}

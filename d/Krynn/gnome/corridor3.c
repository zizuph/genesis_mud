inherit "/d/Krynn/std/room.c";

#include "/d/Krynn/common/defs.h"
#include "local.h"

void
create_room()
{
    LIGHT;
    INSIDE;
    set_short("A smoky and really dusty corridor");
    set_long("There is dust all over the place. It especially sticks to "
	     + "the larger cracks in the walls. There are iron tracks on " +
	     "the ground. You see small clouds of black smoke bulging in " +
	     "from the west.\n");
    
    add_exit(TDIR + "corridor4.c", "west", 0, 1);
    add_exit(TDIR + "corridor2.c", "east", 0, 1);
    
    add_item(({"tracks", "iron tracks"}) ,
	     "They seem to be used quite often. They run from "
	     + "the west to the east.\n");
    add_item("dust",
	     "It sticks to some cracks in the walls clearly outlining " +
	     "their shape.\n");
    add_item("ground", "There are tracks on the ground.\n");
    add_item(({"walls","cracks"}),
	     "There are cracks in the walls and ceiling "
	     + "all over this place. You do not feel too safe "
	     + "in here.\n");
    add_item(({"smoke", "clouds"}),
	     "It comes into here from the east. You can see "
	     + "more and thicker smoke over there.\n");
}

void
expl1()
{
    tell_room(TO, "You hear some strange rumbling and rattling sounds to "
	      + "the west.\n");
    set_alarm(20.0, -1.0, "expl2");
}

void
expl2()
{
    tell_room(TO, "Suddenly the very ground you are standing on is trembling "
	      + "fiercely! You start feeling really uncomfortable!\n");
    set_alarm(20.0, -1.0, "expl3");
}

void
expl3()
{
    tell_room(TO, "Suddenly there's a explosion to the west! " +
	      "The walls start to tremble and dust "
	      + "is raining onto you from the ceiling. "
	      + "Even more smoke fills the room. It becomes quite "
	      + "dark.\n");
    add_prop(ROOM_I_LIGHT, 0);
    set_alarm(20.0, -1.0, "expl4");
}

void
expl4()
{
    tell_room(TO, "As suddenly as everything started it is quiet "
	      + "again. Really quiet!\n");
    set_alarm(30.0, -1.0, "smokegone");
}

void
smokegone()
{
    tell_room(TO, "The smoke seems to have settled down.\n");
    add_prop(ROOM_I_LIGHT, 1);
}

string area() {return "Inthecorridors";}
string wayout() {return "west east";}
string tohelp() {return "west";}
string fromhelp() {return "east";}

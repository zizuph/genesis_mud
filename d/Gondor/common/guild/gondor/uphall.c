#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

public int     check_ranger();

public void
create_room()
{
  set_short("in the hall of the second floor in the Gondorian Rangers Guildhouse");
  set_long(BSN("You are standing in the hall on the second floor of the Rangers "+
     "Guildhouse. There is a corridor leading north, and a door leading "+
     "south. A set of stairs lead down to the first floor. Above the "+
    "staircase hangs a black banner with a strange emblem. A small ladder "+
    "hangs from the ceiling, leading up through a hatch. A doorway leads "+
    "south to the office of the Rangers."));
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_M_NO_STEAL, no_theft);
  add_item(({"banner","emblem"}), BSN(
      "The banner shows a White Tree surrounded by Seven Stars on a black "+
   "background - the emblem of Gondor. Just below this you see a many-pointed "+
   "silver star - the emblem of Arnor. And at the bottom is a rising silver moon "+
   "- the emblem of Ithilien. This is probably to depict that the Rangers of "+
   "Gondor, Arnor and Ithilien are united under one Chieftain - Thorongil."));
  add_item("stairs","The stairs lead down to the first floor of the Guildhouse.\n");
  add_item(({"hatch","ladder"}), BSN(
    "The ladder is hanging down from the ceiling. It leads up to " +
    "an open hatch. Perhaps you can climb into a loft using the ladder."));
  add_exit(RANGER_GON_DIR + "boardhall", "down",  0, 0);
  add_exit(RANGER_GON_DIR + "upcorr1",   "north", 0, 0);
  add_exit(RANGER_GON_DIR + "office",    "south", check_ranger, 0);
}

public int
do_climb(string str)
{
    if (!strlen(str)) 
    {
        NFN("Climb what?");
	return 0;
    }
    if (str == "ladder")
    {
        if (TP->query_skill(SS_CLIMB) < 15) 
	{
	    write("You try to climb the ladder, but it's too hard for you to climb.\n");
	    say(QCTNAME(TP)+" tries to climb the ladder, but falls down again.\n");
	    return 1;
	}
	write("You climb the ladder up through the hatch.\n");
	TP->move_living("up the ladder", RANGER_GON_DIR + "pigeonroom");
	return 1;
    }
    return 0;
}

public int
check_ranger()
{
    if (TP->query_wiz_level()) 
        return 0;
    if (TP->query_skill(SS_PUNISHMENT) == NOACCESS) 
    {
        write("You are stopped in the doorway, since the Council of Rangers\n"+
	      "has punished you with limited access in the guildhouse.\n");
	return 1;
    }
    if (present("ranger_guild_object", TP))
        return 0;
    write("You are stopped in the doorway, as you have no membership-token to show.\n");
    return 1;
}

public void
init()
{
    ::init();
   add_action(do_climb, "climb");
}


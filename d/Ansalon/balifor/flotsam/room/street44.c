#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit FLOTSAM_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Street corner in the upper parts of Flotsam");
    set_long("@@long_descr");

    add_item("cliff","You look down over the cliff. At the bottom of quite " +
      "a drop, you can make out waves crashing against the jagged " +
      "rocks below. \n");
    add_item("inn","You look at the Saltbreeze Inn, the most " +
      "respectable inn, and probably building, in the whole of " +
      "Flotsam. It sits high on the edge of the cliff, overlooking " +
      "all of Flotsam. \n");
    add_item("square","To your south is a large square, heavily " +
      "guarded by draconian guards. You wonder why?\n");
    add_item(({"draconians","draconian","draconian guards","guards"}),
      "A large contingent of draconians guard the square to your " +
      "south.\n");

    add_exit(FROOM + "inn02","north","@@enter",0);
    add_exit(FROOM + "street43","east","@@down",0);
    add_exit(FROOM + "landing","south","@@construction");

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + tod_descr2() + "The rise " +
    "ends at the top of a cliff overlooking the " +
    "Blood Sea. Down below you can just hear the waves crashing " +
    "on the rocks. To the north stands the Saltbreeze, the " +
    "finest inn in Flotsam. The street continues to the " +
    "south towards a square guarded by large draconian guards, and to the " +
    "east, where the street " +
    "travels down to the lower district. " + season_descr() + 
    "\n";
}

int
down()
{
    write("You head down the slope... \n");
    return 0;
}

int
construction()
{
    return 0;
    /*
	if(this_player()->query_dragonarmy_occ_member() ||
	   this_player()->query_guild_name_occ() == "Priests of Takhisis")
	{
	    write("The draconian guards allow you to enter the square.\n");
	    say(QCTNAME(TP)+ " is allowed to pass through to the south by " +
	      "the draconian guards.\n");
	    return 0;
	}
	write("Draconian guards stop you from going south.\n");
	say(QCTNAME(TP)+ " is stopped from going south by " +
	  "draconian guards.\n");
	return 1;
    */
}

int
enter()
{
    write("You open the door and step into the " +
      "Saltbreeze Inn...\n");
    return 0;
}

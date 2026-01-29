/* Xak Tsorath coded by Percy */

#include "../xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  XAKINROOM

void
create_room()
{
    set_short("An old deserted street");
    
    set_long("You are in an old ruined street of Xak Tsaroth deep underground in"
	     + " a huge cavern. The buildings"
	     + " are in pretty good shape considering the stresses the cataclysm"
	     + " must have placed on them though many of the walls are leaning"
	     + " dangerously. The street comes to an end at a beautiful waterfall"
	     + ". The water cascading from high above and down the west cavern face"
	     + " forms a river that flows off to the east.\n");
    
    add_exit(DDIR + "plaza.c", "east", 0);
    
    add_item(({"fall", "waterfall", "water"}), "@@fall");
    
    INSIDE;
    DARK;
}

string
fall()
{
    write("The waterfall is truly magnificent, the water falling hundreds"
	  + " of feet from the marsh and ultimately the newsea above. Strange"
	  + " though... looking at the waterfall gives you an unreal feeling."
	  + " Ah! it must only be the awe of it all.\n");
    return "";
}

void
init()
{
    ::init();
    ADA("enter");
}

int
enter(string str)
{
    NF("Enter what?\n");
    if (str != "fall" && str != "water" && str != "waterfall")
      return 0;
    write("You step into the waterfall and now you can see that behind"
	  + " the waterfall is a tunnel leading south.\n");
    SAY(" walks through the waterfall.");
    tell_room(DDIR + "tunnel.c", QCTNAME(TP) + " comes through the waterfall.\n");

    TP->move_living("M", DDIR + "tunnel.c", 1);
    return 1;
}

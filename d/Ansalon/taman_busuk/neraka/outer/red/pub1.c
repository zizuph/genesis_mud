/* Carridin */
/* Navarre July 3rd 2006, added item for yellowy sign */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit OUTER_IN;
inherit "/d/Ansalon/lib/pub";

void
create_neraka_room()
{
    set_short("The Little Red Rooster drinking house");
    set_long("You have entered a run-down dusty little establishment " +
	     "in the Red quarter. The proprietor of the pub, having met little " +
	     "success with it, has cleared out most of decoration long ago, as " +
	     "number of patrons were never many. Nowadays, this is a rarely " +
	     "visited place in Neraka. The only noteworthy thing in the room " +
	     "is a large picture hanging behind the dusty barcounter.\n");
    set_quarter(RED);
    add_item_inside();
    add_item(({"bar", "barcounter"}), "You note a yellowy sign placed upon " +
    "the dusty counter.\n");
    add_item(({"picture", "large picture"}), "It displays a rooster, red of " +
    "colour.\n");
    add_item(({"rooster", "red rooster"}), "It's a wee one, if there ever was one.\n");
    add_item(({"sign", "yellowy sign"}),"@@sign@@");
    add_cmd_item("sign","read","@@sign@@");
    add_cmd_item("yellowy sign", "read", "@@sign@@");
    add_exit(NOUTER+"red/r13","west","@@msg@@",0);

    add_drink_object(({"ale","ales","outlander ale","outlander ales"}),
		     NOBJ + "drink/outale",
		     12);
    add_drink_object(({"beer","beers"}),
		     NOBJ + "drink/mbeer",
		     14);
    add_drink_object(({"whiskey","whiskeys"}),
		     NOBJ + "drink/swhiskey",
		     120);

    reset_room();
}

int
msg()
{
    write("With great relief, you leave the dull old pub.\n");
    return 0;
}


string
sign()
{
    return "----------------------------------------\n"+
           "Outlander Ale       ---   12cc          \n"+       
           "A mug of beer       ---   14cc          \n"+
           "Fire Blood Whiskey  ---  120cc          \n"+
           "----------------------------------------\n";
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    init_pub();
}


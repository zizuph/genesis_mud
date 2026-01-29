/* Based on the Telberin bank. Adapted for the Grunts guild by Tulix III. */
/* Grunts do not get any special deals here, for tax reasons.             */

inherit "/std/room.c";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>
#include "default.h"
#include "../guild.h"

/* Prototype function */
public void reset_room();

/*
 * Function name:   create_room
 * Description:     define the basics of the room
 */
public void
create_room()
{

    config_default_trade();

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Grunts' bank");
    set_long("   This is the Grunts' bank. It was taken over by the Gnome bank "
	   + "after the original one went bust (counting is not something "
	   + "goblins do very well).\nAs it is now run by gnomes, you can "
	   + "forget about getting a better deal even if you are a member "
	   + "of the Grunts guild....\n"
	   + "The gnomes don't really want to be here, but they couldn't "
	   + "resist the chance to earn a few easy coppers.\n"
          + "There is an easy to read plaque on the wall.\n\n");
    
    add_item(({"walls","wall"}),
	"There are torches fixed on two walls of the bank. " +
	"The walls are cold, and damp to touch. It seems to be made " +
	"of the usual volcanic rock like the rest of the caves. There is " +
	"a plaque on one of the walls.\n");
    
    add_item(({"roof","ceiling"}),
        "The roof is made of the same rock as the walls, the familiar "+
	"volcanic rock. At least you can " +
	"be fairly sure the roof won't be falling down, as volcanic rock " +
	"is pretty tough stuff.\n");

    add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is made " +
	"of volcanic rock.\n");

    add_item(({"torch","torches"}),
	"The torches are fixed firmly to the wall, and cannot be taken.\n");

    
    add_exit(THIS_DIR + "bar", "east");
    
    add_item("plaque","@@standard_bank_sign");

    set_bank_fee(25);    /* The Gnomes are not as generous down here */
    
    config_trade_data();

    reset_room();    
}

/*
 * Function name:   reset_room
 * Description:     add the object necessary to make this a gnome bank
 */
public void
reset_room()
{
    object misc;

    if (!present("deposit", TO))
    {
	misc = clone_object("/d/Genesis/obj/deposit.c");
	misc->move(TO, 1); 
    }

}

/*
 * Function name:   init
 * Description:     add the bank commands to players who enter the room
 */
public void
init()
{
    ::init();
    bank_init();
}

// file name:        port11.c
// creator(s):       Ilyian
// revision history: Lilith, made plalgus curse more mild, but
//                   don't want to encourage recidivism,  Jun 4, 2004.
//                   Boriska, Mar 24 1995, added ship stuff
//                   Boriska  Aug 95       sailor NPC added
//		     Denis, Sep'96: Changes due to the port inheritance recode.
//           Lilith, Feb 21, 2014 Tweaked room desc
//           Lilith, Sep 2021: Added fishing prop.
// purpose:
// note:             The ship from Sparkle lands here.
// bug(s):
// Ported by Tapakah to the new ship system, 05/2009

#pragma strict_types
#include "/d/Avenir/common/port/port.h"
#include "/d/Avenir/include/relation.h"
inherit PORT_ROOM;
inherit "/d/Genesis/gsl_ships/lib/pier";

private object sailor;

/*
 * Function name: check_exit
 * Description:   Warn recidivists on entering Sybarus. 
 *                We could do the old throw up a gate and pour boiling
 *                oil trick on them, like in Calathin...but for reasons
 *                of ambiance, the land will simply resist them.
 * Returns:       1/0 - closed/open
 */
public int
check_exit()
{


    /* Warn them they are wearing out their welcome */
    if (IS_INFIDEL(TP))
        write("A feeling of uneasiness weighs upon you, making you "+
            "feel unwelcome.\n");
    
    /* S/he may pass */
    return 0;
}


static void
create_port_room()
{
    object ship;

	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", "saltwater");
	
    set_short("Northern ledge in the Port of Sybarus. Berth for ship to Sparkle");
    set_long("You are on a wide ledge between the cavern wall to " +
             "the north and the churning waters of a rift lake to the south. " +
             "Mist seems to cling everywhere, making your footing " +
             "unsteady. This ledge narrows to the west, where the "+
             "berth for another ship can be seen. From the east you "+
		     "can hear the sounds of business as usual at the Port of "+
			 "Sybarus.\n");

    IN
    LIGHT

    add_exit("port10", "east", check_exit);
    add_exit("port12", "west");

    add_item(({ "wall", "walls" }),
	     "These rough hewn walls of the cavern " +
             "appear to be man made, hewn from the natural rock. They are " +
             "wet from the mist and spray of the stormy port, and rivulets " +
             "of water run down them to the floor. This section of the " +
             "wall contains a large vein of brightly glowing rock that " +
             "runs in a jagged line from the floor up to the ceiling " +
             "high above.\n");

    add_item(({ "vein", "rock" }),
             "This strange type of rock inexplicably " +
             "produces a dazzling pulse of unearthly light. For all its " +
             "brightness, it is cool to the touch, and is very smooth.\n");

    add_rift_no_see_item();
    add_ceiling_in_item();
    add_no_swim_cmditems();

    add_tell("From within the mist you hear the muffled cry of a " +
             "lonely foghorn.\n");

    add_tell("The roar from the great rift increases to a thunderous " +
             "climax, and then receeds again.\n");
	
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_pier_entry(MASTER_OB(TO), "Sybarus", "Pier to Sparkle");
    initialize_pier();
}

public void
reset_room()
{
    if (!objectp(sailor))
    {
        sailor = clone_object(PORT + "mon/sailor");
        sailor->equip_me();
        sailor->move(this_object(), 1);
    }
}


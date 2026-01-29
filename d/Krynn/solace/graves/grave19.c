/* The graveyard
 *
 * Nick & Dorak
 */


/**
 * Navarre December 15th 2007.
 * Fixed 'exa fence' bug, it was returning 1 instead of "" in the VBFC.
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
#include <ss_types.h>
inherit GRAVE_STD;

#define NO_CLIMB 200 /* can't climb fence */
#define DAMAGE   30  /* tangleshoots usually trap, this injures only */

create_solace_room()
{
    object door;

    set_short("Graveyard");
    set_long(BS(
	"You are in the Solace graveyard. Graves are all around you. " +
	"An old fence vanishes into thick tangleshoot to the west and " +
	"to the south. At the corner is a gate leading south. " +
	"A sign has been fastened to the fence beside the gate. " +
	"", 70));

    add_item(({"fence", "old fence", "the fence", "the old fence"}),
	    "@@fence");
    add_item("thistle brush", 
	    "A common undergrowth found in the wilds around Solace.\n");
    add_item("tangleshoot", BS(
            "This is the dreaded tangleshoot of Abanasinia. Rumour has it, " +
            "that it feeds off of blood.", 70));
    add_item(({"sign", "the sign"}), 
	    BS("This is a new sign, but it is already showing s" +
	    "igns of weathering. The paint is peeling a little " +
	    "and the lettering is a little faded. But it is st" +
	    "ill quite readable. It is also in the Common ton" +
	    "gue so you can read it.", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_cmd_item("sign", "read", "@@do_read");
    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
                "You can't kill the tangleshoot. You hack it up a bit, " +
                "but there is just too much of it to kill.", 70));

    add_exit(TDIR + "grave14", "north", 0);
    add_exit(TDIR + "grave18", "west", 0);

    door = clone_object(OBJ + "gate_s");
    door->move(TO);
}

tangleshoot()
{
     if (TP->query_skill(SS_CLIMB) < (NO_CLIMB))
     {
	say(QCTNAME(TP) + "was grabbed by the tangleshoot and injured.\n");
	TP->reduce_hit_point(DAMAGE);
	return("You are grabbed by the tangleshoot.  It injures you.\n");
    }
    else
	return(BS("You are either a wizard or you are cheating. I'm going t" +
		  "o assume the former. If you really want to get over this" +
		  " fence with out going the long way around, goto ~o_grave1" +
		  ".c.", 70));
}

fence()
{
    write(BS("This is an old wrought iron fence. It is in desperate need" +
	   " of repair and paint. Through the tangle of thistle brush and" +
	   " tangleshoot you see more graves beyond it to the south." +
	   "", 70));
    say(QCTNAME(TP) + " looks south.\n");
    return "";
}

do_read()
{
    write("This is the old graveyard of Solace.  \n");
    write("WARNING: DANGER\n");
    write("        This area is not in a good state of upkeep.\n");
    write("        It is locked because I'm on vacation.  Anyone\n");
    write("        wishing to go beyond wait til I return.\n");
    write("        Death lingers near by(or absolute boredom *yawn*)\n");
    write("                               -The Graveyard Keeper\n");
    say(QCTNAME(TP) + " reads the sign.\n");
    return 1;
}

query_grave_room() { return 19; }

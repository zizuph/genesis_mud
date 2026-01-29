/* The graveyard
 *
 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <ss_types.h>
#include <macros.h>
/*inherit "/sys/global/money.c";*/
inherit GRAVE_STD;

#define NO_CLIMB 200 /* can't climb fence */
#define DAMAGE   30  /* tangleshoots usually trap, this injures only */
void
create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are in the Solace graveyard. Graves are all around you. " +
	"There is an old fence to the south." +
	"", 70));

    add_item(({"fence", "old fence", "the fence", "the old fence"}),
	     "@@fence");
    add_item("thistle brush", 
	     "A common undergrowth found in the wilds around Solace.\n");
    add_item("tangleshoot", BS(
             "This is the dreaded tangleshoot of Abanasinia. Rumour has it, " +
             "that it feeds off of blood.", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    /*add_cmd_item("button","push","@@button");
    add_cmd_item("button","pull","@@pull");*/

    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
                "You can't kill the tangleshoot. You hack it up a bit, " +
                "but there is just too much of it to kill.", 70));

    add_exit(TDIR + "grave16", "east");
    add_exit(TDIR + "grave10", "north");
}

string
tangleshoot()
{
    if (TP->query_skill(SS_CLIMB) < (NO_CLIMB))
    {
	say(QCTNAME(TP) + "was grabbed by the tangleshoot and injured.\n");
	TP->reduce_hit_point(DAMAGE);
	return("You are grabbed by the tangleshoot. It injures you.\n");
    }
    else
	return(BS("You are either a wizard or you are cheating. I'm going t" +
		  "o assume the former. If you really want to get over this" +
		  " fence with out going the long way around, goto ~o_grave1" +
		  ".c.", 70));
}

string
fence()
{
    write(BS("This is an old wrought iron fence. It is in desperate need" +
	" of repair and paint. Through the tangle of thistle brush and" +
	" tangleshoot you see more graves beyond it to the south." +
	"", 70));
    say(QCTNAME(TP) + " looks south.\n");
    return "";
}

int
query_grave_room() { return 15; }








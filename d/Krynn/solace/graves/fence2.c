#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <ss_types.h>
#include <macros.h>
inherit GRAVE_STD;

#define NO_CLIMB 200 /* can't climb fence */
#define DAMAGE   30  /* tangleshoots usually trap, this injures only */

void
create_solace_room()
{
    set_short("An Old Fence");
    set_long(BS("This is an old weather worn wrought iron fence. It runs f" +
              "rom west to east. There are brambles all around that keep yo" +
              "u from going west. There is a path through the brambles lea" +
              "ding north." +
              "", 70));
     
    add_item("path", BS(
             "This is more of a thinning of the brush, then a real path, but" +
             " it looks like others have taken advantage  of it also.", 70));
    add_item(({"fence", "old fence", "old wrought iron fence",
		 "wrought iron fence"}),
	"You are suprised this fence still stands tall, despite its look.\n");

    add_cmd_item("fence", "climb", "@@tangleshoot");
    add_cmd_item("fence", "jump", "@@tangleshoot");
    add_cmd_item("tangleshoot", "kill",  BS(
                "You can't kill the tangleshoot. You hack it up a bit, " +
                "but there is just too much of it to kill.", 70));

    add_exit(TDIR + "o_grave2", "north", 0);
    add_exit(TDIR + "o_grave5", "east", 0);
}

string
tangleshoot()
{
    if (this_player()->query_skill(SS_CLIMB) < (NO_CLIMB))
      {
	  say(QCTNAME(this_player()) + "was grabbed by the tangleshoot and\n" +
	      "injured.\n");
	  this_player()->reduce_hit_point(DAMAGE);
	  return("You are grabbed by the tangleshoot. It injures you.\n");
      }
    else
      return("Greetings Guru climber. This is below your skill.\n");
}


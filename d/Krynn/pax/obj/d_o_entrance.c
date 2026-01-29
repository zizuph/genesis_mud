/* A hole, the entrance to Sla-Mori
 *
 * 941108 by Rastlin
 */

inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include "../local.h"

/* string check_hole(); */

create_door()
{
    ::create_door();

    set_door_id("rock_hole");
    set_pass_command(({"enter", "go"}));
    set_door_name(({"gaping hole", "hole", "Sla-Mori", "sla-mori"}));
/*    set_door_desc(VBFC_ME("check_hole")); */

    set_door_desc("This is the entrance to Sla-Mori, the burial " +
        "chamber of the great elven king Kith-Kanan. You sense " +
        "great evil coming from the hole, but the strange thing " +
        "is that you can sense great goodness too. The elves " +
        "are not truly forgotten within, though evil things have " +
        "come to rule in their stead.\n");

    set_other_room(PSLA + "entrance");
    set_open_desc("");
    set_closed_desc("");
    set_open_command("");
    set_close_command("");
    set_open(1);
    set_no_show();
}
	

/*
string
check_hole()
{
	return BS("This is the entrance to Sla-Mori, the burial " +
	"chamber of the great elven king Kith-Kanan. You sense " +
	"great evil coming from the hole, but the strange thing " +
	"is that you can sense great goodness too. The elves " +
	"are not truly forgotten within, though evil things have " +
	"come to rule in their stead.", 70);
}
*/

int
pass_door(string arg)
{
    if (TP->query_stat(SS_DIS) < 40)
    {
        write(BS("You are overwhelmed by the deep darkness and " +
      	     "the feeling of malevolence coming from the " +
       	     "entrance, you dare not enter.", 70));
        return 1;
    }
    ::pass_door(arg);
    return 1;
}

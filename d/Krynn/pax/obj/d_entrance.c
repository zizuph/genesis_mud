/* A hole, the exit from Sla-Mori
 *
 * 941108 by Rastlin
 */

inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include "../local.h"

create_door()
{
    ::create_door();

    set_door_id("rock_hole");
    set_pass_command(({"enter", "go", "out"}));
    set_door_name(({"gaping hole", "hole"}));
    set_door_desc(BS("This is the entrance to Sla-Mori, the burial " +
		"chamber of the great elven king Kith-Kanan. Outside " +
		"the hole there is a small opening surrounded by " +
		"thick brush and trees.", 70));
    set_other_room(PSLA + "o_entrance");
    set_open_desc("");
    set_closed_desc("");
    set_open_command("");
    set_close_command("");
    set_open(1);
    set_no_show();
}

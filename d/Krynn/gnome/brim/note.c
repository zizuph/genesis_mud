/* created by Aridor, 06/15/94 */

inherit "/std/object";
#include <stdproperties.h>


void
create_object()
{
    set_short("note of gratitude");
    set_pshort("notes of gratitude");
    set_name("note");
    add_name("note of gratitude");
    add_name("brimsch_note");
    set_long("It's a short note of gratitude given to you by Brimsch " +
	     "the gnome.\n");
    set_alarm(5.0,0.0,"add_prop",OBJ_M_NO_DROP, 1);
    add_cmd_item("note","read","You read that this is a short " +
		 "note of gratitude given to you by Brimsch the " +
		 "gnome. You should go back to the Questmaster to " +
		 "collect your reward now.\n");
}

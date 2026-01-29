/*
 * /d/Kalad/common/wild/pass/underdark/u28.c
 * Purpose    : Sometimes, while I'm doing this tedious crap, I wonder, too.
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>
# include <ss_types.h>

inherit DARK_DOM;

object ob1;

void reset_room();
 
void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northwest, south and west.\n");
    add_exit(DARK(u25), "northwest");
    add_exit(DARK(u32), "south", "@@move");
    add_exit(DARK(u27), "west");
    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
        ob1 = clone_object(H_SPIDER);
        ob1->move_living("xxx", this_object());
    }
}

int
move()
{
    if(this_player()->query_base_stat(SS_DIS) < 76)
    {
	write("You lack the will to continue further.\n");
	say(QCTNAME(this_player()) + " lacks the will to go further.\n");
	return 1;
    }
    write("You bravely continue onward.\n");
    say(QCTNAME(this_player()) + " bravely continues onward.\n");
    return 0;
}

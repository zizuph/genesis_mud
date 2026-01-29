/* 
 * /d/Kalad/common/wild/pass/underdark/u20.c
 * Purpose    : I don't ask you why you were born, do I?
 * Location   : Under Hespyre, near the shaft to the surface
 * Created By : Antharanos
 * Modifed By : Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>

inherit DARK_DOM;

object ob1;
object ob2;

void
create_dark_dom()
{
    set_short("Cavern Entrance");
    set_long(long()+"You've reached the entrance of a large cavern. The air "+
      "stale, and is filled with the stench of half-rotten flesh. You think "+
      "you can hear some faint sounds to the north. Dark passages lead to "+
      "the north and west.\n");
    add_item(({"large cavern","cavern"}),"A few low stalactites hang from "+
      "the ceiling, however there are no stalagmites on the cavern floor.\n");
    add_item(({"cavern floor","floor"}),"The floor is relatively smooth, "+
      "with no irregularities such as stalagmites.\n");
    add_item(({"dark stone","stone"}),"The cavern is made out of it.\n");
    add_exit(DARK(u19), "north", "@@query_move");
    add_exit(DARK(u11), "west");
    set_alarm(1.0, 0.0, "reset_room");
}

void
reset_room()
{
    if (!ob1)
	(ob1 = clone_object(TROG_GUARD))->move_living("xxx", this_object());
    if (!ob2)
	(ob2 = clone_object(TROG_GUARD))->move_living("xxx", this_object());

    ob1 -> team_join(ob2);
}

int
query_move()
{
    if (present(ob1) || present(ob2))
    {
	write("The troglodyte guard blocks your way!\n");
	say("The troglodyte guard stops " + QCTNAME(this_player()) + 
" from going north.\n");
	return 1;
    }
    return 0;
}

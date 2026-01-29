/*
 * /d/Kalad/common/wild/pass/underdark/u37a.c
 * Purpose    : Provide further panic for players weakened from fighting a dragon.
 * Located    : Dark Dominion southwestish of Undraeth
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"
# include <macros.h>
# include <stdproperties.h>

inherit DARK_DOM;
object ob1;
int
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object("/d/Kalad/common/wild/pass/npc/bronze_golem");
	ob1->move(this_object(), 1);        
    }

}



void
create_dark_dom()
{
    add_prop(ROOM_I_LIGHT, 10);
    set_short("Featureless chamber");
    set_long("You are in a seemingly large and featureless white room, the brightness "+
      "of the place nearly blinding you. Nothing is in this room, for "+
      "everywhere you look is an endless field of white.\n");
    add_item(({"room"}),"You're not quite sure you are even within a "+
      "room, as distances are hard to judge here.\n");
    add_exit(DARK(u9), "west", "@@query_move", 0, 1);
    add_exit(DARK(u12), "northwest", "@@query_move", 0, 1);
    add_exit(DARK(u15), "north", "@@query_move", 0, 1);
    add_exit(DARK(u17), "northeast", "@@query_move", 0, 1);
    add_exit(DARK(u31), "east", "@@query_move", 0, 1);
    add_exit(DARK(u42), "southeast", "@@query_move", 0, 1);
    add_exit(DARK(u46), "south", "@@query_move", 0, 1);
    add_exit(DARK(u36), "southwest", "@@query_move", 0, 1);
   reset_room();
}

int
query_move()
{
    if (present(ob1))
    {
	write("You cannot leave while the bronze golem is still here!\n");
	say(QCTNAME(this_player()) +
	  " tried to leave but was mercilessly stopped by the bronze golem!\n");
	return 1;
    }
    return 0;
}

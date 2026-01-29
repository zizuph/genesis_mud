/*
 * /d/Kalad/common/wild/pass/underdark/u35.c
 * Purpose    : Do you really read this?
 * Located    : Dark Dominion under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

object ob1;

void reset_room();
 
void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast and east.\n");
    add_exit(DARK(u34), "northeast");
    add_exit(DARK(u36), "east");
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

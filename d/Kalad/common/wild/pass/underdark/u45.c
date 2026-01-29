/*
 * /d/Kalad/common/wild/pass/underdark/u45.c
 * Purpose    : Passes time. Better than TV, innit?
 * Located    : Dark Dominion, Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

object ob1;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northwest and southwest.\n");
    add_exit(DARK(u44), "northwest");
    add_exit(DARK(u46), "southwest");
    set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
    if(!ob1)
	(ob1 = clone_object(ILLITHID))->move_living("xxx", this_object());
}

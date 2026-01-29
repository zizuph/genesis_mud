/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object baaz1, baaz2;

reset_tantallon_room()
{
    if(!objectp(baaz1))
        {
         baaz1 = clone_object("/d/Krynn/std/baaz");
         baaz1->set_color("red");
         BAAZ_COIN1->move(baaz1);
         BAAZ_COIN2->move(baaz1);
         baaz1->move(TO);
    }

    if(!objectp(baaz2))
        {
         baaz2 = clone_object("/d/Krynn/std/baaz");
         baaz2->set_color("red");
         BAAZ_COIN1->move(baaz2);
         BAAZ_COIN2->move(baaz2);
         baaz2->move(TO);
    }
}

create_tantallon_room()
{
    object door;

    set_short("Dark alley");
    set_long(BS(
    	"Now you stand in a dark alley between a big wall and a small tent. " +
    	"The ground is hard and sterile. The evil is very strong in the air." +
	"", SL));

    add_item("wall", BS(
    	"It's a black wall made out of stone. The wall is so big that it " +
    	"seldom lets the sun shine down here. The wall seems to radiate evil." +
	"", SL));
    add_item("ground", BS(
    	"Nothing grows here, and if it would have grown something it would " +
    	"have been dead.", SL));
    add_item("tent", BS(
    	"It's a small black tent. You cannot hear a sound from it and there " +
    	"is no entrance on this side.", SL));

    add_exit(TDIR + "city15", "east", 0);
    add_exit(TDIR + "city13", "west", 0);

    door = clone_object(OBJ + "d_city14_a");
    door->move(TO);
    door->set_key(K_CITY14);

    reset_tantallon_room();
}

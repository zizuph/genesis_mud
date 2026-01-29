/* Tantallon, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco, baaz1, baaz2, kapak;

#include RND_MEET

load_draco()
{
    (draco = RANDOM_MEET(DRACOS))->move_living("xxx", TO);
    if (draco->query_prop(OBJ_I_COLORABLE))
	draco->set_color("red");
    draco->set_random_move(30);
}

/* Commented out by Morrigan, removing invis potions
load_merchant()
{
    clone_object(MON + "pot_seller")->move(TO);
    tell_room(TO, "A strange looking merchant arrives.\n");
}
*/

reset_tantallon_room()
{
    if (!draco)
      set_alarm(1.0,0.0,"load_draco");
/*
    if (!present("merchant", TO))
    	set_alarm(1.0,0.0,"load_merchant");
*/

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

    if(!objectp(kapak))
        {
         kapak = clone_object("/d/Krynn/std/kapak");
         kapak->set_color("red");
         KAPAK_COIN1->move(kapak);
         KAPAK_COIN2->move(kapak);
         kapak->move(TO);
    }

}

create_tantallon_room()
{
    set_short("Center of Tantallon");
    set_long(BS(
    	"You are in the middle of Tantallon. You stand in the southwest corner " +
    	"of an opening. A lot of people are running around in what appears " +
	"to be circles. The evil in the air is very strong now. A small road " +
	"runs off south and you could follow the wall of the big building " +
	"west.", SL));

    add_item("people", BS(
    	"At a closer look you see that some are talking to each other and " +
	"others are walking quickly cross this place.", SL));
    add_item(({"building", "big building"}), BS(
    	"This is the biggest, and also the only, building in Tantallon. It " +
	"appears to be some kind of a temple. You understand that this is " +
	"the center of all evil in this city.", SL));
    add_item("road",
    	"It leads off south. It's made out of small stones.\n");
    add_item(({"stone", "stones"}), BS(
    	"The stones are small and round but they stick to the ground so you " +
    	"can't pick them up.", SL));

    add_exit(TDIR + "city19", "south", 0);
    add_exit(TDIR + "city16", "east", 0);
    add_exit(TDIR + "city14", "west", "@@follow");
    add_exit(TDIR + "city11", "north", 0);

    reset_room();
}
  
follow()
{
    write("You follow a big wall.\n");
    return 0;
}










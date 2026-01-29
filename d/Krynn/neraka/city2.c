/* Tantallon by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object kapak1, kapak2, baaz1, baaz2;

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

    if(!objectp(kapak1))
        {
         kapak1 = clone_object("/d/Krynn/std/kapak");
         kapak1->set_color("red");
         KAPAK_COIN1->move(kapak1);
         KAPAK_COIN2->move(kapak1);
         kapak1->move(TO);
    }

    if(!objectp(kapak2))
        {
         kapak2 = clone_object("/d/Krynn/std/kapak");
         kapak2->set_color("red");
         KAPAK_COIN1->move(kapak2);
         KAPAK_COIN2->move(kapak2);
         kapak2->move(TO);
    }
}

create_tantallon_room() 
{
    object door;
    set_short("Dead end");
    set_long(BS(
    	"You are at a dead end. In front of you are the west wall and some " +
    	"huge mountains. You might just as well walk east to the tent that " +
    	"stands there." +
    	"", SL));

    add_item(({"mountain", "mountains"}), BS(
    	"The mountains are very high. The look very dark and unfriendly. In " +
    	"fact most people avoid getting any closer than this to them.", SL));
    add_item(({"tent", "east tent"}), BS(
    	"It's a small grey tent. There isn't a sound to be heard from it. You " +
    	"can enter it by walking east.", SL));
    add_item("wall", BS(
    	"This wall efficiently blocks your way west. It runs south as long as " +
    	"you can see.", SL));

    add_exit(TDIR + "tent8", "east", 0);

    door = clone_object(OBJ + "d_city2_a");
    door->move(TO);
    door->set_key(K_CITY2);

    reset_tantallon_room();
}

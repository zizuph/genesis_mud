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

    set_short("End of path");
    set_long(BS(
    	"You have come to the end of the path. The mountains block any attempts " +
    	"to walk north. Far away to the east you can see a river floating. The " +
    	"path leads southwest towards the heart of Tantallon.", SL));

    add_item(({"mountain", "mountains"}),
    	"The mountains are very high. The look very dark and unfriendly.\n");
    add_item("path",
    	"It seems like a lot of people walk this path normally.\n");
    add_item("river", BS(
    	"The river runs from northeast to south. It flows next to the mountain " +
    	"leaving no space left to walk on. It seems Tantallon is well protected " +
    	"from attacks from this direction.", SL));

    add_exit(TDIR + "city4", "southwest", 0);

    door = clone_object(OBJ + "d_city1_a");
    door->move(TO);
    door->set_key(K_CITY1);

    reset_tantallon_room();
}

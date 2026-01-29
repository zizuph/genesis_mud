#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

object g1,g2;

void
reset_neraka_room()
{
	if (!objectp(g1))
    	g1 = clone_npc(NNPC + "humsergeant","black");
    if (!objectp(g2))
    	g2 = clone_npc(NNPC + "humsoldier","black");
}

void
create_neraka_room()
{
	set_short("Outside a large black tent");
    set_extra_long("You are outside a large tent in the Black Quarter. " +
        "a small dirt road leads soutwest, and the entrance to the " +
        "tent is to the northeast.");
    set_quarter(BLACK);

    add_item_dirtroad();

    add_item(({"tent","large tent","entrance"}),
        "The tent to the northeast is large and made of black canvas. " +
        "The entrance is covered with a thick flap.\n");

    add_item(({"flap","canvas flap","tent flap"}),"The flap covers the " +
        "entrance to the tent, to keep the heat in on cold nights.\n");

    add_exit(NOUTER+"black/t1","northeast","@@go_in");
    add_exit(NOUTER+"black/b16","southwest");

    reset_room();
}

int
go_in()
{
    object g;
    g = g1;
    if (!objectp(g))
        g = g2;
    
	if (objectp(g))
    {
    	if(TP->query_wiz_level())
        {
        	write("The guards let you enter the tent.\n");
            return 0;
        }
        /*
        TP->catch_msg("As you enter the tent, " + QTNAME(g) + " growls: " +
            "Try any fancy moves in there, and you're dead.\n");
        */
        TP->catch_msg(QCTNAME(g) + " grudgingly lets you pass.\n");
        return 0;
    }
	else
    {
        write("You pull aside the flap and enter the tent.\n");
        return 0;
    }
}


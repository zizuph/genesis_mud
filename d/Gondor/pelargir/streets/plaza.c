/*
 * /d/Gondor/pelargir/street/plaza.c
 *
 * Modification history:
 *  20 August 1998, Gnadnar: cleanup, add donations column
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define DID_VISIT_PELARGIR "_ranger_visited_pelargir"
public void	create_gondor();
public void	reset_room();
public string	exa_sign();

static object  Cit;

/*
 * Function name:	create_gondor
 * Description	:	set up the plaza
 */
public void
create_gondor()
{
    FIX_EUID;	/* will clone citizen, column */

    set_short("south of Pelargir square");
    set_long("The rough cobblestone street ends in a small plaza "
        + "surrounded by shops and offices. To the south is a bank, "
        + "and west of the plaza is a friendly looking inn. South of "
        + "the inn lies the post office, and north of it a shop. Next "
        + "to the shop is a jeweller's store. A newly painted sign "
        + "has been hung outside the jeweller's store to let everyone "
        + "know that there is a jewelry store beyond the jeweller's "
        + "store. To the northeast, a statue rises in Belfalas Square.\n");

    add_cobble();
    add_admiral();

    add_item(({"jeweller's store", "store"}), "The jeweller's store " +
        "is a small sturdy building to the north. You can see another " +
        "door leading to the jewelry store inside.\n");
    add_item(({ "sign", "newly painted sign", "painted sign" }),
        "Jewelry Shop, now open!\n");
    add_item("statue",BSN("The statue is rather tall and bulky but "+
       "other than that you cannot see details without getting "+
       "closer."));
    add_item("post office",BSN("The post office lies just southwest "+
       "of here. It is a small stone building though the grey "+
       "stone of the walls seems streaked with white; probably "+
       "from the inordinate amount of pigeons roosting on the roof."));
    add_item("inn",BSN("The inn has a sign hanging above the "+
       "door saying 'Dragon's Claw'. The sign seems to be the "+
       "most well kept thing about it though."));
    add_item("sign", exa_sign());
    add_cmd_item("sign", "read", exa_sign());

    add_exit(PELAR_DIR + "streets/belfalas10", "east",      0);
    add_exit(PELAR_DIR + "misc/pelbank",       "south",     0);
    add_exit(PELAR_DIR + "misc/pelpost",       "southwest", 0);
    add_exit(PELAR_DIR + "homes/inn/innter",   "west",      0);
    add_exit(PELAR_DIR + "misc/pelarms",       "northwest", 0);
    add_exit(PELAR_DIR + "misc/jewel_shop",    "north",     0);
    
    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	add citizen, column
 */
public void
reset_room()
{
    Cit = add_citizen(Cit, PELAR_DIR + "npc/citizen");
    if (!objectp(present("column", TO)))
    {
        clone_object("/d/Genesis/obj/donation/column")->move(TO, 1);
    }
} /* reset_room */


/*
 * Function name:	exa_sign
 * Description	:	handle exa/read sign
 * Returns	:	string -- the text of the sign
 */
public string
exa_sign()
{
    return "\n" +
        "    0                    0\n" +
        "    8                    8\n" +
        "    0                    0\n" +
        "._-_b__-_-_-___-__-___- _b_-_.\n" +
        "|                            |\n" +
        "| ***                        |\n" +
        "| *  * R A G O N ' S         |\n" +
        "| *  *                       |\n" +
        "| ***            ***         |\n" +
        "|               *            |\n" +
        "|               *    L A W   |\n" +
        "|                ***         |\n" +
        "|____-_-______-____-__-___-__|\n";
} /* exa_sign */

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (IS_RANGER(ob))
        ob->add_prop(DID_VISIT_PELARGIR, 1);
}


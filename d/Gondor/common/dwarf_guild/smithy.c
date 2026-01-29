/*
 * /d/Gondor/common/dwarf_guild/smithy.c
 *
 * This cave is the armoury of the Dwarven race guild. The strap is
 * outcommented on the sign since we are not sure whether a strap is a
 * good thing to cave when you look at the inter-guild tensions.
 *
 * /Mercade, 7 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define SMITH (DWARVEN_RACE_GUILD_NPCS + "smith")

#define POSTER_DESCRIPTION \
"Welcome to the smithy of the " + DWARVEN_RACE_GUILD_NAME + ".\n" +          \
"==============================================================\n\n" +       \
"Here you may <order> any type of axe and I will craft it for you. The\n" +  \
"possible types are: waraxe pickaxe\n" +                                     \
"Whetstones are available for 4 to 6 silver coins.\n\n" +                    \
"Give me a weapon and I will appraise it. If necessary I will polish or\n" + \
"repair it as good as I can. If you have a belt and want to have your\n" +   \
"name branded into it, just give it to me. The price is 5 silvers per\n" +   \
"letter.\n\n" +                                                              \
/* \
"You can <buy> a strap here too. A strap might help you to hold on to a\n" + \
"wielded weapon when someone forces you drop it. Do <order strap> for\n" +   \
"more information.\n" +                                                      \
*/ \
"After I have done you an offer you may always <decline> it and I will\n" +  \
"return you your property. You can <pay> me if you are done ordering.\n"

/*
 * Prototype
 */
void reset_room();

/*
 * Global variable, will not be saved.
 */
static object smith = 0;

void
create_room()
{
    set_short("the smithy of the " + DWARVEN_RACE_GUILD_NAME);
    set_long(BSN("This room is higher up in the mountains. It is open in " +
	"the air to prevent the room from getting overheated. There is " +
	"an anvil and of course a forge, making this place still rather " +
	"hot. It has all signs of being a smithy. Some stairs lead down " +
	"into a cavern. There is a poster with some information nailed to " +
	"the wall."));

#include "cavedesc.h" /* some add_items for the rocky cave etc. */

    /* undo the ceiling add_item from cavedesc.h */
    remove_item("ceiling");

    add_item( ({ "forge", "fire" }),
	BSN("In the forge, the smith heats the iron before forging it. " +
        "There is a fire, fueled with coal, roaring in it."));
    add_item( ({ "coal" }),
	BSN("They are red and very hot."));
    add_item( ({ "anvil" }),
	BSN("It is a very strong and even heavier anvil. It is used by a " +
	"smith to forge iron."));
    add_item( ({ "stair", "stairs" }),
	BSN("The stairs lead down into the mountains."));

    add_item( ({ "poster", "sign" }),
	BSN("It has readable words on it."));
    add_cmd_item( ({ "poster", "sign", "information" }), "read",
	POSTER_DESCRIPTION);

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "entrance", "down");

    add_prop(OBJ_I_HAS_FIRE, 1);

    reset_room();
}

void
reset_room()
{
    if (!objectp(smith))
    {
	FIX_EUID;

	smith = clone_object(SMITH);
	smith->arm_smith();
	smith->move_living("X", TO);
    }
    else if (ENV(smith) != TO)
    {
	smith->move_living("X", TO);
    }
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if ((objectp(ob)) &&
	(objectp(smith)) &&
	(ob == smith->query_client()))
    {
	smith->client_leaves();
    }
}

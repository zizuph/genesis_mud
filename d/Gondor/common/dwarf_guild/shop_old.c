/*
 * /d/Gondor/common/dwarf_guild/shop.c
 *
 * This cave is the shop of the dwarven race guild. It is modified from the
 * shop of the rangers guild, though altered in a major way.
 *
 * /Mercade, 7 January 1994
 *
 * Revision history:
 * Updated shop listing
 * Finwe, December 2017
 */

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/d/Faerun/lib/shop_list";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define KEEPER         (DWARVEN_RACE_GUILD_NPCS + "keeper")
#define KEEPERSAY(s)   keeper->npc_say(s)
#define STORE          (DWARF_DIR + "store")

#define POSTER_DESCRIPTION                                                   \
  "  Welcome to the supply store of the " + DWARVEN_RACE_GUILD_NAME + "!\n"+ \
  "  ============================================================\n" +       \
  "  You can try these instructions: \n\n" +                                 \
  "  buy sword for gold and get copper back\n" +                             \
  "  buy sword for gold coins\n" +                                           \
  "  sell sword for copper coins\n" +                                        \
  "  sell all  - will let you sell all items except for items you\n" +       \
  "              wield or wear.\n" +                                         \
  "  sell all! - will let you sell ALL items you have, well\n" +             \
  "              at least the droppable, and no coins.\n\n" +                \
  "  sell sword, sell second sword, sell sword 2, sell two swords\n" +       \
  "  also works. You might want to change the verb to 'value' or\n" +        \
  "  'buy' too. Beware, you will never buy more than one item at\n" +        \
  "  a time. So if you really want those three expensive swords,\n" +        \
  "  you have to repeat yourself three times.\n\n" +                         \
  "  If you want a list of all swords available in the store, the\n" +       \
  "  correct syntax is: list swords\n" +                                     \
  "              'list weapons', 'list armours' also works\n"

/*
 * Prototype
 */
void reset_room();

/*
 * Global variable
 */
object keeper;

void
create_room()
{
    set_short("the supply store of the " + DWARVEN_RACE_GUILD_NAME);
    set_long("@@long_description@@");

#include "cavedesc.h" /* some add_items for the rocky cave etc. */

    /* Dutch for teleledningsanka :-) */
    STORE->omtezorgendatiegeladenis();

    add_item( ({ "counter" }),
        "@@counter_description@@");

    add_item( ({ "cabinet" }), "@@long:" + STORE + "@@");
    add_item( ({ "door", "doors" }),
        BSN("The doors are made of the same wood as the rest of the " +
        "cabinet. They are secured with iron bands and closed shut!"));
    add_item( ({ "band", "iron band", "bands", "iron bands" }),
        BSN("Some iron bands are fastened to the cabinet and its doors to " +
        "make it secure and to make sure that no-one opens the cabinet " +
        "without the permission of the shopkeeper."));
    add_cmd_item( ({ "cabinet", "door", "doors" }),
        ({ "open", "enter", "unlock" }),
        BSN("The doors of the cabinet are closed and firmly locked. There " +
        "is no way you can open the doors so do not even think about " +
        "entering the cabinet."));

    add_item( ({ "poster", "posters" }),
        BSN("It has readable words on it."));
    add_cmd_item( ({ "poster", "posters" }), "read", POSTER_DESCRIPTION);

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "guild", "northeast");
    add_exit(DWARF_DIR + "pub",   "east");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO, BSN("Hmm... wizinfo? Well... The remark about " +
        "how to enter the cabinet is not available to mortals, but I guess " +
        "that is about it."));

    reset_room();
}

string
long_description()
{
    string str = "In this cave the shop of the " + DWARVEN_RACE_GUILD_NAME +
        " is situated. Here you may buy useful weapons, armours or gear, " +
        "lamps and oil or whatever else is in stock. There is a counter " +
        "and a cabinet in the cave. The cabinet is used to stock the items " +
        "for sale. To the east you see the inn of the guild and to the " +
        "northeast is the exit to the central guild cave.";

    if (TP->query_wiz_level())
    {
        str += " To enter the cabinet, use the command \"cabinet\".";
    }

    return BSN(str);
}

string
counter_description()
{
    string str = "It is a wooden counter. ";

    if ((!objectp(keeper)) || (ENV(keeper) != TO))
    {
        str += "Currently the counter is unattended. This means that you " +
            "cannot buy anything. However, this does not mean that you " +
            "can help yourself to the merchandize.";
    }
    else
    {
        str += "Behind the counter you see " + keeper->query_art_name(TP) +
            ", the shopkeeper.";
    }

    return BSN(str);
}

void
init()
{
    ::init();

    add_action("do_cabinet", "cabinet");
}

int
do_cabinet()
{
    object tp = TP;

    if (!(tp->query_wiz_level()))
    {
        return 0;
    }

    if (tp->move_living("M", STORE, 1))
    {
        write("For some dubious reason you could not enter the cabinet. " +
            "You might want to teleport yourself into the cabinet by typing " +
            "<goto " + STORE + ">.\n");
    }

    TELL_ROOM(TO, tp, " opens the cabinet and enters it. Then " + PRONOUN(tp) +
        " closes the doors behind " + OBJECTIVE(tp) + ".", tp);
    TELL_ROOM(STORE, tp, " open the cabinet and enters it. Then " +
        PRONOUN(tp) + " closes the doors behind " + OBJECTIVE(tp) + ".", tp);

    return 1;
}

void
reset_room()
{
    if (!objectp(keeper))
    {
        FIX_EUID;

        keeper = clone_object(KEEPER);
        keeper->arm_shopkeeper();
        keeper->move_living("X", TO);        
    }
    else if (ENV(keeper) != TO)
    {
        keeper->move_living("X", TO);
    }
}
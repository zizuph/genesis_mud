/*
 *      /d/Gondor/morgul/cellar/wsmithy.c
 *
 *      The weapon smith on the first floor of dungeons below 
 *      Minas Morgul
 *
 *      Olorin, 13-Mar-1997
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Modification log:
 *      31-08-2000, Stern, added exit for paintroom
 *      10-11-2000, Gwyneth, changed exit to new paintroom
 */
#pragma strict_types

inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

#define MM_WEAPON	(MORGUL_DIR + "obj/ithil_weapon")
#define MM_WSMITH	(MORGUL_DIR + "npc/ghashdurub")

/*
 *      Prototypes:
 */
static string *check_stock();
static string  exa_list();
static string  exa_weapons();
public void    make_weapon(string wt);

/*
 *      Global variables:
 */
static mapping In_Stock = ([]);
static int     Make_Alarm;
static object  WSmith;

static mapping
setup_weapon_stock()
{
    int     i;
    string *wtype;

    wtype = MM_WEAPON->query_weapon_types();

    for (i = 0; i < sizeof(wtype); i++)
    {
        In_Stock[wtype[i]] = 1;
        add_item( ({ wtype[i] }), BSN(
            MM_WEAPON->query_weapon_long(wtype[i])));
    }

    return In_Stock;
}

public void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("smithy");
    set_extra_long("This is one of the smithies in which weapons " +
        "for the Morgul army are forged. In the centre of the " +
        "room is a mighty anvil, and behind it, built into the " +
        "eastern wall of the smithy, is a large forge. On the " +
        "other walls, the weapons that are currently in stock " +
        "have been put onto display. For good money, the smith " +
        "is willing to part with them. He can also wax and " +
        "sharpen your weapon. Ask him about it if he is here. " +
        "There are two exits, an archway to the west " +
        "beyond which a dark dungeon is visible, and a small back " +
        "room to the east.");


    add_item("back room", "Shadows make it impossible to see inside " +
        "the back room from here.\n");
    add_item(({"wall", "walls", "weapons", "display", }),
        exa_weapons);

    add_item(({"sign", "pricelist", "list", }), exa_list);
    add_cmd_item(({"sign", "pricelist", "list", }), "read", 
        exa_list);

    add_item(({"forge", "corner", }), BSN(
        "The large forge has been built into the eastern wall of " +
        "the smithy. In it the metal is melted that is used for the " +
        "blades of the weapons forged here. The forge has a " +
        "chimney, but it nevertheless fills the smithy with smoke."));
    add_item(({"anvil", }), BSN(
        "On this anvil the weapon smith forges the blades of " +
        "swords, axes, polearms, and knives as well as the metal " +
        "parts of clubs."));

    add_floor();
    add_archway("west");
    add_ceiling("In the centre of the ceiling is a hole through " +
        "which the smoke coming from the fire can escape.");

    setup_weapon_stock();

    add_prop(ROOM_I_LIGHT, 1);

    add_exit(CELLAR_DIR + "dung_1e2", "west", check_exit, 1);
    add_exit(CELLAR_DIR + "mm_paint_shop", "east", check_exit, 1);

    reset_room();
}

static int
add_weapon(string wt)
{
    In_Stock[wt] += 1;
    remove_item(wt);
    add_item( ({ wt }), BSN(
        MM_WEAPON->query_weapon_long(wt)));
}

public int
remove_weapon(string wt)
{
    if (!In_Stock[wt])
        return 0;

    In_Stock[wt] -= 1;
    remove_item(wt);
    add_item( ({ wt }), "There is no "+wt+" on display or for sale.\n");

    if (!Make_Alarm)
    {
        Make_Alarm = set_alarm(rnd()*120.0 + 60.0, 0.0,
            &make_weapon(wt));
        WSmith->delay_command("emote starts forging a new "+wt+".");
    }

    return 1;
}

public void
make_weapon(string wt)
{
    Make_Alarm = 0;

    if (!objectp(WSmith) || !objectp(present(WSmith, TO)))
        return;

    WSmith->forge_weapon(wt);
    add_weapon(wt);

    check_stock();
}

static int
query_in_stock(string w)
{
    return In_Stock[w];
}

public string *
query_weapon_stock(int art = 0)
{
    object  lang;
    string *wep = m_indexes(In_Stock);

    if (!m_sizeof(In_Stock))
        return 0;

    wep = filter(wep, query_in_stock);

    if (art)
    {
        lang = find_object(LANG_FILE);
        wep = map(wep, &lang->add_article());
    }

    return wep;
}

static string *
check_stock()
{
    string *wep = m_indexes(In_Stock),
            nw;

    if (!m_sizeof(In_Stock))
        return 0;

    wep -= filter(wep, query_in_stock);

    if (!sizeof(wep))
        return 0;

    if (Make_Alarm || !objectp(WSmith) || !objectp(present(WSmith, TO)))
        return wep;
    else
    {
        Make_Alarm = set_alarm(rnd()*120.0 + 60.0, 0.0,
            &make_weapon(nw = ONE_OF_LIST(wep)));
        WSmith->delay_command("emote starts forging a new "+nw+".");
    }

    return wep;
}

public void
reset_room()
{
    WSmith = clone_npc(WSmith, MM_WSMITH);
    check_stock();
}

static string
exa_weapons()
{
    string  desc,
           *wstock;

    desc = "The weapon smith manufactures many different types of swords, "
      + "polearms, axes, maces, and knives. On the walls of his smithy he "
      + "displays the weapons he has for sale. Presently you can see ";

    if (sizeof(wstock = query_weapon_stock()))
        desc += COMPOSITE_WORDS(query_weapon_stock(1));
    else
        desc += "no weapons on the walls, they must all be sold out";

    desc += ".";

    return BSN(desc);
}

static string
exa_list()
{
    if (!objectp(WSmith))
    {
        write(BSN(
            "On the sign is a list of the prices for the weapons "
          + "that are for sale here. But since the weapon smith is not "
          + "here, the list is of no interest."));
    }
    else
    {
        WSmith->do_weapon_list("", 1);
    }
    return "";
}


/*
 *  The shop and smithy of Herumegil, Master Weapon Smith of Minas Tirith
 *
 *  Coded by Olorin, 16-nov-1994
 *
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MT_WEAPON	(MINAS_DIR + "obj/mt_weapon")
#define MT_WSMITH	(MINAS_DIR + "npc/herumegil")

// Templates
void    reset_room();

// Global variables
mapping in_stock = ([]);
int     make_alarm;
object  wsmith;

mapping
setup_weapon_stock()
{
    int     i;
    string *wtype;

    wtype = MT_WEAPON->query_weapon_types();

    for (i = 0; i < sizeof(wtype); i++)
    {
        in_stock[wtype[i]] = 1;
        add_item(({ wtype[i] }), BSN(
            MT_WEAPON->query_weapon_long(wtype[i])));
    }

    return in_stock;
}

void
create_gondor()
{
    set_short("the smithy of Herumegil, Master Weapon Smith of Minas Tirith");
    set_long(BSN(
        "This is the smithy of Herumegil of the House of Hador, Master "
      + "Weapon Smith of Minas Tirith. In a corner there is the mighty "
      + "forge and next to it stands a large anvil. "
      + "Herumegil supplies the Guard of "
      + "the Tower with weapons, but he also sells to citizens of "
      + "Minas Tirith and to travellers. On the walls can be seen "
      + "the weapons that presently are in stock for sale. Herumegil "
      + "will also wax and sharpen weapons. Ask him about it."));

    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"wall", "walls", "weapons", "display", }),
        VBFC_ME("exa_weapons"));

    add_item(({"sign", "pricelist", "list", }),
        VBFC_ME("exa_list"));
    add_cmd_item(({"sign", "pricelist", "list", }), "read", 
        VBFC_ME("exa_list"));

    add_item(({"forge", "corner", }), BSN(
        "In the corner is the mighty forge where Herumegil melts the "
      + "metal for the blades of the weapons he manufactures."));
    add_item(({"anvil", }), BSN(
        "On this anvil Herumegil forges excellent swords, axes, knives "
      + "and - praised above all others - halberds for use of the "
      + "men of the Guard of the Tower. Some of the weapons made "
      + "here are also sold to citizens of Minas Tirith and to "
      + "the occasional traveller that can afford them."));

    setup_weapon_stock();

    add_exit(MINAS_DIR + "s1crc4", "north", 0, 0);

    reset_room();
}

int
query_in_stock(string w)
{
    return in_stock[w];
}

string *
query_weapon_stock(int art = 0)
{
    string *wep = m_indexes(in_stock);

    if (!m_sizeof(in_stock))
        return 0;

    wep = filter(wep, "query_in_stock", TO);

    if (art)
        wep = map(wep, "add_article", LANG_FILE);

    return wep;
}

string
exa_weapons()
{
    string  desc,
           *wstock;

    desc = "Herumegil manufactures many different types of swords, "
      + "polearms, axes, and knives. On the walls of his smithy he "
      + "displays the weapons he has for sale. Presently you can see ";

    if (sizeof(wstock = query_weapon_stock()))
        desc += COMPOSITE_WORDS(query_weapon_stock(1));
    else
        desc += "no weapons on the walls, they must all be sold out";

    desc += ".";

    return BSN(desc);
}

string
exa_list()
{
    if (!objectp(wsmith))
    {
        write(BSN(
            "On the sign is a list of the prices for the weapons "
          + "that are for sale here. But since the weapon smith is not "
          + "here, the list is of no interest."));
    }
    else
    {
        wsmith->do_weapon_list("", 1);
    }
    return "";
}

int
add_weapon(string wt)
{
    in_stock[wt] += 1;
    remove_item(wt);
    add_item(({ wt }), BSN(
        MT_WEAPON->query_weapon_long(wt)));
}

int
remove_weapon(string wt)
{
    if (!in_stock[wt])
        return 0;

    in_stock[wt] -= 1;
    remove_item(wt);
    add_item(({ wt }), "There is no "+wt+" on display or for sale.\n");

    if (!make_alarm)
    {
        make_alarm = set_alarm(rnd()*120.0 + 60.0, 0.0,
            "make_weapon", wt);
        wsmith->delay_command("emote starts forging a new "+wt+".");
    }

    return 1;
}

string *
check_stock()
{
    string *wep = m_indexes(in_stock),
            nw;

    if (!m_sizeof(in_stock))
        return 0;

    wep -= filter(wep, "query_in_stock", TO);

    if (!sizeof(wep))
        return 0;

    if ((make_alarm) || !objectp(present("herumegil", TO)))
        return wep;
    else
    {
        make_alarm = set_alarm(rnd()*120.0 + 60.0, 0.0,
            "make_weapon", (nw = ONE_OF_LIST(wep)));
        wsmith->delay_command("emote starts forging a new "+nw+".");
    }

    return wep;
}

void
make_weapon(string wt)
{
    make_alarm = 0;

    if (!present(wsmith, TO))
        return;

    wsmith->forge_weapon(wt);
    add_weapon(wt);

    check_stock();
}

void
reset_room()
{
    wsmith = clone_npc(wsmith, MT_WSMITH);
    check_stock();
}


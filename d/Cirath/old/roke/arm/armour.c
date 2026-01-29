/*
 * armour.c
 *
 * Used in npc/people.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

/* Some defines of names and other stuff */

#define NO_OF_TYPES 6
#define NAMES ({ "helmet", "shield", "boots", "cloak", "hoses", "armour" })
#define CLASS ({ 9, 12, 10, 3, 20, 25 })
#define TYPE ({ A_HEAD, A_SHIELD, A_FEET, A_ROBE, A_LEGS, A_BODY })
#define VOLUME ({ 150, 550, 250, 4750, 450, 3040 })
#define MODIFY ({ ({ -5, 0, 5 }), ({ 6, -2, -4 }), ({ -3, 4, -1 }), \
    ({ -5, 10, -5 }), ({ 5, -3, -2 }), ({ -3, 4, -1 }) }) 
#define ADJ ({ ({ "copper", "tiny" }), ({ "wooden" }), ({ "blue" }), \
    ({ "silk" }), ({ "iron" }), ({ "iron" }) })
#define SHORT ({ "", "", "pair of blue boots", "", \
    "pair of iron hoses", "" })
#define PSHORT ({ "", "", "pairs of blue boots", "", \
    "pairs of iron hoses", "" })
#define LONG ({ \
    "It's a small copper helmet, mostly used for protecting your head.\n", \
    "It's made of wood and reinforced by small iron stripes.\n", \
    "Yuck! They are wet from sweat!\n", \
    "The cloak is made of shimmering silk.\n", \
    "A pair of iron hoses, they are worn by many of the guards.\n", \
    "Just an ordinary armour to protect your body.\n" })

int type;

/*
 * set_up: Set up all names and other stuff of the armour
 */

void
set_up(int i)
{
    int ac, *am, at, volume;
    string name, short, pshort, *adj, long;

    if (i < 0) i = 0;
    if (i >= NO_OF_TYPES) i = NO_OF_TYPES - 1;

    type = i;
    ac = CLASS[i];
    at = TYPE[i];
    am = MODIFY[i];
    volume = VOLUME[i];
    name = NAMES[i];
    adj = ADJ[i];
    short = SHORT[i];
    pshort = PSHORT[i];
    long = LONG[i];

    seteuid(getuid(TO));

    set_name(name);
    if (short != "")
	set_short(short);
    else
	set_short(0);
    if (pshort != "")
	set_pshort(pshort);
    else
	set_pshort(0);
    set_adj(adj);
    set_long(long);
    set_default_armour(ac, at, am);

    add_prop(OBJ_I_VOLUME, volume);
    add_prop(OBJ_I_WEIGHT, volume);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
    update_prop_settings();
}

void
create_armour()
{
  /* set by a call to set_up */
}

string
query_recover()
{
    return MASTER + ":" + type + "," + query_arm_recover();
}

void
init_recover(string arg)
{
    int i;
    sscanf(arg, "%d", i);
    set_up(i);
    init_arm_recover(arg);
}

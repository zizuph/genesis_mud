/*
 * weapon.c
 *
 * Used in npc/people.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"
#include <formulas.h>
#include <macros.h>

/* Some defines of names and other stuff */

#define NO_OF_TYPES 5
#define NAMES ({ "knife", "pole", "sword", "axe", "sword" })
#define PNAMES ({ "knives", "", "", "", "" })
#define ADJ ({ "rusty", "wooden", "dwarven", "copper", "battle" }) 
#define LONG ({ \
    "This knife is the worst case of rust attack you've ever seen.\n", \
    "Just an ordinary wooden log.\n", \
    "This sword is imported from the dwarven territories. It looks nasty.\n", \
    "An ordinary copper axe, used for cutting wood. And killing...\n", \
    "This sword is normally used by the guards to defend the city.\n" })
#define HIT ({ 9, 16, 21, 20, 27 })
#define PEN ({ 11, 15, 18, 22, 27 })
#define WEAPON ({ W_KNIFE, W_POLEARM, W_SWORD, W_AXE, W_SWORD })
#define HANDS ({ W_ANYH, W_ANYH, W_ANYH, W_ANYH, W_ANYH })
#define DAMAGE ({ W_SLASH | W_IMPALE, W_BLUDGEON, W_SLASH | W_IMPALE, \
    W_SLASH | W_BLUDGEON, W_SLASH | W_IMPALE })
#define VOLUME ({ 180, 450, 470, 258, 700})

int type;

/*
 * set_up: Set up all names and other stuff of the armour
 */

void
set_up(int i)
{
    object ob;
    int hit, pen, wt, dt, hands, volume;
    string name, pname, adj, long;

    if (i < 0) i = 0;
    if (i >= NO_OF_TYPES) i = NO_OF_TYPES - 1;

    type = i;
    wt = WEAPON[i];
    dt = DAMAGE[i];
    hit = HIT[i];
    pen = PEN[i];
    hands = HANDS[i];
    volume = VOLUME[i];
    name = NAMES[i];
    pname = PNAMES[i];
    adj = ADJ[i];
    long = LONG[i];

    set_name(name);
    set_adj(adj);
    set_short(adj + " " + name);
    if (pname != "")
    {
        set_pname(pname);
        set_pshort(adj + " " + pname);
    }
    set_long(long);
    set_default_weapon(hit, pen, wt, dt, hands);

    add_prop(OBJ_I_VOLUME, volume);
    add_prop(OBJ_I_WEIGHT, volume);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit,pen));
    update_prop_settings();
}

void
create_weapon()
{
    /* nothing here , should be set by a call to set_up */
}

string
query_recover()
{
    return MASTER + ":" + type + "," + query_wep_recover();
}

void
init_recover(string arg)
{
    int i;
    sscanf(arg, "%d", i);
    set_up(i);
    init_wep_recover(arg);
}

/*
 * weapon2.c
 *
 * Used in npc/campwarrior.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"
#include <macros.h>

/* Some defines of names and other stuff */

#define NO_OF_TYPES 5
#define NAMES ({ "spear", "knife", "axe", "halberd", "sword" })
#define PNAMES ({ "", "", "", "", "" })
#define HIT ({ 5, 10, 20, 25, 29 })
#define PEN ({ 5, 10, 20, 25, 35 })
#define WEAPON ({ W_POLEARM, W_KNIFE, W_AXE, W_POLEARM, W_SWORD })
#define HANDS ({ W_ANYH, W_ANYH, W_ANYH, W_BOTH, W_ANYH })
#define DAMAGE ({ W_IMPALE, W_IMPALE || W_SLASH, W_SLASH ,\
		    W_SLASH, W_SLASH || W_IMPALE })
#define VOLUME ({ 100, 200, 870, 4000, 2500 })
#define ADJ ({ "rusty", "average", "steel", "vicious", "mighty" })
#define LONG ({ \
    "The spear is so rusty that it makes your fingers brown.\n", \
    "It's a average knife. No more, no less.\n", \
    "It's a rather heavy axe which could hurt you real bad.\n", \
    "The vicious halberd looks really nasty. \n", \
    "A sword that seems to be able to cut through solid rock.\n" })

int type;

/*
 * set_up: Set up all names and other stuff of the armour
 */

void
set_up(int i)
{
    int hit, pen, wt, dt, hands, volume;
    string name, pname, adj, long;

    if (i < 0)
        i = 0;
    if (i >= NO_OF_TYPES)
        i = NO_OF_TYPES - 1;

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
    if (pname != "")
        set_pname(pname);
    set_short(0);
    set_adj(adj);
    set_long(long);
    set_default_weapon(hit, pen, wt, dt, hands);

    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 710);
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

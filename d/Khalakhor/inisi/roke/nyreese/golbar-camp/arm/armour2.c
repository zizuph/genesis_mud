/*
 * armour2.c
 *
 * Used in npc/campwarrior.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/* Some defines of names and other stuff */

#define NO_OF_TYPES 6
#define NAMES ({ "shoes", "mail", "boots", "cloak", "helmet", "armour" })
#define CLASS ({ 5, 12, 15, 4, 13, 28 })
#define TYPE ({ A_FEET, A_BODY, A_LEGS | A_FEET, A_ROBE, A_HEAD, A_BODY })
#define VOLUME ({ 150, 550, 450, 475, 450, 3540 })
#define MODIFY ({ ({ -2, 0, 2 }), ({ 1, 3, -4 }), ({ -3, 4, -1 }), \
    ({ -5, 10, -5 }), ({ 1, -3, 2 }), ({ -3, 4, -1 }) })
#define ADJ ({ ({ "leather"}), ({ "ring" }), ({ "nice" }), \
    ({ "red" }), ({ "mighty" }), ({ "mighty" }) })
#define SHORT ({ "pair of leather shoes", "", "pair of nice boots", "", \
    "", "" })
#define PSHORT ({ "pairs of leather shoes", "", "pairs of nice boots", "", \
    "", "" })
#define LONG ({ \
    "Good looking shoes made out of leather. \n", \
    "It's just a well-used ring mail.\n", \
    "Nice looking boots in a real good material.\n", \
    "The cloak shimmers in the light. Red is colour of love.\n", \
    "A really mighty helmet. Worn by heros and others.\n", \
    "This armour looks quite impressive. You wouldn't mind wearing it.\n" })

int type;

/*
 * set_up: Set up all names and other stuff of the armour
 */

void
set_up(int i)
{
    int ac, *am, at, volume;
    string name, short, pshort, long;
    mixed adj;

    if (i < 0)
        i = 0;
    if (i >= NO_OF_TYPES)
        i = NO_OF_TYPES - 1;

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

    set_name(name);
    if (short !="")
        set_short(short);
    else
        set_short((pointerp(adj) ? adj[0] : adj) + " " + name);
    if (pshort != "")
        set_pshort(pshort);
    else
        set_pshort(0);
    set_adj(adj);
    set_long(long);
    set_default_armour(ac, at, am);

/*
    add_prop(OBJ_I_VOLUME, volume);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
*/
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 8200);
    add_prop(OBJ_I_VALUE, 360);
    update_prop_settings();
}

void
create_armour()
{
    /* nothing here , should be set by a call to set_up */
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

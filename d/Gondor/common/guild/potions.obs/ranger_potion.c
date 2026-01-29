/*
 * /d/Gondor/common/guild/potions/ranger_potion.c
 *
 * The standard potion for the Rangers of the Westlands.
 *
 * Copied from /d/Gondor/common/guild2/potions/morgul_potion.c
 *
 * Olorin, December 1996
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *  Gwyneth, 12/11/02: Made ranger potions keep track of who
 *                     made them.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/potion.c";
inherit "/lib/herb_support.c";

#include <ss_types.h>
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include "/d/Gondor/defs.h"

#define RANGER_S_MADE_POTION "_ranger_s_made_potion"

// Prototypes
public string  strength_adj();
public string  short_desc();

// Global variables
static  int     Strength,
                Rank,
                gMade = 0;
static  string  Effect_name;

public void
set_rank(int r)
{
    Rank = r;
    if (Rank > 100)
	Rank = 100;
}

public int
query_xtra_strength()
{
    return Rank;
}

public void
create_ranger_potion()
{
    set_potion_name("ranger potion");
    set_id_long("A dummy ranger potion.\n");
}

public void
set_effect_name(string str)
{
    Effect_name = str;
}

nomask void
create_potion()
{
    set_unid_long("This is a strange herb potion.\n");
    create_ranger_potion();
    set_short(short_desc);
    set_adj(strength_adj);
}

public string
strength_adj()
{
    if (!query_identified())
        return "strange";

    switch(Strength)
    {
        default:
        case 0..50:
            return "watery";
        case 51..70:
            return "light";
        case 71..90:
            return "strong";
        case 91..1000:
            return "powerful";
     }
}

public string
short_desc()
{
    string *adjs = query_adjs(),
            adj = "";

    if (sizeof(adjs) > 1)
        adj = adjs[1] + " ";
    return (strength_adj() + " " + adj + query_name());
}

void
set_identified()
{
    identified = 1;
    add_name(potion_name);
}

string
query_recover()
{
    return MASTER + ":" +
           "#sa#" + soft_amount +
           "#aa#" + alco_amount +
	   "#xa#" + Rank +
           "#";
}

public varargs void
set_up_effect(int soft, int alco, int xtra)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
    set_rank(xtra);
}

/*
 * Function name: set_up_potion
 * Description:   set up the potion effect, check strength of ingredients
 * Arguments:     ingr - an array with the ingredients for the potion
 * Returns:       0 - if messages should be done by the mortar
 *                1 - if messages were done by the potion
 */
public int
set_up_potion(mixed ingr)
{
    set_up_effect(ingr[0]->query_soft_amount(),
                  ingr[0]->query_alco_amount(),
                  this_player()->query_ranger_rank());

    return 0;
}

void
special_effect()
{
}

void
init_recover(string str)
{
    string  dummy;
    int     soft,
            alco,
            xtra;

    sscanf(str, "%s#sa#%d#%s", dummy, soft, dummy);
    sscanf(str, "%s#aa#%d#%s", dummy, alco, dummy);
    sscanf(str, "%s#xa#%d#%s", dummy, xtra, dummy);

    set_up_effect(soft, alco, xtra);
}

public int
query_strength()
{
    return Strength;
}

public void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (!objectp(from) && !gMade)
    {
        TO->add_prop(RANGER_S_MADE_POTION, ob->query_real_name());
        gMade = 1;
    }
}

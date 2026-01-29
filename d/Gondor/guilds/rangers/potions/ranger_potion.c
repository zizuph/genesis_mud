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

#include <ss_types.h>
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include "/d/Gondor/defs.h"

#define RANGER_S_MADE_POTION "_ranger_s_made_potion"

public void
create_ranger_potion()
{
    set_potion_name("ranger potion");
    set_id_long("A dummy ranger potion.\n");
}

/* Mask this in the actual potion to define the strength. */
public int
query_strength()
{
    return 0;
}

public string
strength_adj()
{
    if (!query_identified())
        return "strange";

    switch(query_strength())
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

nomask void
create_potion()
{
    set_unid_long("This is a strange herb potion.\n");
    create_ranger_potion();
    set_short(short_desc);
    set_adj(strength_adj);
}

void
set_identified()
{
    identified = 1;
    add_name(potion_name);
}

public varargs void
set_up_effect(int soft, int alco, int xtra)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
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
                  ingr[0]->query_alco_amount());

    return 0;
}

void
special_effect()
{
}

/*
 * Function name: config_split
 * Description  : This is called before inserting this heap into the game
 *                It configures the split copy. 
 * Arguments    : int new_num - the number to split off.
 *                object orig - the original object.
 */
void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);

    add_prop(RANGER_S_MADE_POTION, orig->query_prop(RANGER_S_MADE_POTION));
}

public void
enter_env(object ob, object from)
{
    ::enter_env(ob, from);

    if (!objectp(from) && !query_prop(RANGER_S_MADE_POTION))
    {
        add_prop(RANGER_S_MADE_POTION, ob->query_real_name());
    }
}

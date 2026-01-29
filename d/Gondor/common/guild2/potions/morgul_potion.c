/*
 *      /d/Gondor/common/guild2/potions/morgul_potion.c
 *
 *      The standard potion for the Morgul mages
 *
 *      Copyright (c) 1995, 1997 by Christian Markus
 *
 *      Olorin, January 1995
 *
 *      Modification log:
 *      13-March-1997, Olorin:  Changes to stop potions from intoxicating.
 *
 *      29-Nov-2006, Toby: Updated all potions to include from the correct folder.
 *                         Also *sigh* removed all the old friggin BSN! =o)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/potion";
inherit "/lib/herb_support";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/newspells/spells.h"
#include "potion_defs.h"

static int     Strength;
static string  Effect_Name;

public void
create_morgul_potion()
{
    set_potion_name("morgul potion");
    set_id_long("A dummy morgul potion.\n");
}

public void
set_effect_name(string str)
{
    Effect_Name = str;
}

nomask public void
create_potion()
{
    set_unid_long("This is a strange herb potion.\n");
    set_id_diff(22);
    create_morgul_potion();
    set_short(VBFC_ME("short_desc"));
    set_adj(VBFC_ME("strength_adj"));
}

public varargs int
query_spell_active(object player, int spell_min)
{
    if (!objectp(player))
        player = this_player();

    if (player->query_guild_name_occ() != GUILD_NAME)
        return 0;
    if (player->query_morgul_level() < spell_min)
        return 0;

    return 1;
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

public void
set_identified()
{
    identified = 1;
    add_name(potion_name);
}

/*
 * Function name: set_up_effect
 * Description:   set up the potion effect
 *                called from the init_recover
 */
static void
set_up_effect(int soft, int alco)
{
    set_soft_amount(soft);
    set_alco_amount(alco);
}

/*
 * Function name: set_up_potion
 * Description:   set up the potion effect, check strength of ingredients
 *                called from the mortar
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

static void
set_strength(int val)
{
    Strength = val;
}

public int
query_strength()
{
    return Strength;
}

void
init_recover(string arg)
{
    string  dummy;
    int     value;

    ::init_recover(arg);

    /* Support for old style recovery of morgul potions. */
    sscanf(arg, "%s#sa#%d#%s", dummy, value, dummy);
    if (value) set_soft_amount(value);
    sscanf(arg, "%s#aa#%d#%s", dummy, value, dummy);
    if (value) set_alco_amount(value);

    set_up_effect(soft_amount, alco_amount);
}

/*
 * Navarre, November 2006.
 *
 * The object behind the scop con drain effect
 *
 */
inherit "/std/object";
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

int amount;

void
create_object()
{
    ::create_object();
    set_name("_scop_shadow_wall_drain_object");
    set_no_show();

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
                            "scop con drain effect.\n");
}



varargs public int
dispel_spell_effect(object player)
{
    player->catch_msg("You seem to regain your strength.\n");
    player->set_stat_extra(SS_CON, (TP->query_stat_extra(SS_CON) + amount));
    remove_spell_effect_object();
    return 1;
}

public int
start()
{
    object player = environment(this_object());    
    player->set_stat_extra(SS_CON, (player->query_stat_extra(SS_CON) - amount));
    set_alarm(itof(600+random(600)), 0.0, &dispel_spell_effect(player));
}

void
set_amount(int amt)
{
    amount = amt;
}

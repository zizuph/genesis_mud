/* This is the spell object of the alchemist in the gnome
village of Rust. I thought I'd use one, and learn a bit about
the magic system in the process. By Bishop of Calia, 4.1.99. */


#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/magic/spellcasting";

inherit "/d/Calia/central/rust/specials/magneticfun.c";
inherit "/d/Calia/central/rust/specials/alchemistheal.c";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"

object user;

void
activate_spells()
{
    add_spell("magneticfun", "Attraction", 
        create_spell_magneticfun, spell_target_one_present_enemy);
    add_spell("alchemistheal", "Healing spell",
        create_spell_alchemistheal, spell_target_caster);
}


void
create_object()
{
    set_name("_alchemistspells_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

void
init()
{
    ::init();
    activate_spells();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
    user = env;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
    user = 0;
}

public int
query_spell_mess(string verb, string arg)
{
    write("You prepare to unleash a spell.\n");
    say(QCTNAME(user)+ "'s forehead furrows in concentration.\n");
    return 1;
}
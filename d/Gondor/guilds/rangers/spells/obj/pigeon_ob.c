/*
 * /d/Gondor/guilds/rangers/spells/obj/pigeon_ob.c
 *
 * Allows Ranger npcs to clone this and use the whistle spell.
 */
#include "/d/Gondor/defs.h"
#include "../../rangers.h"
#include <stdproperties.h>

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

void
create_object()
{
    set_name("paper");
    set_short("scrap of paper");
    set_adj("scrap");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);

    add_spell(RANGERS_SPELL + "whistle");
    set_no_show();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!env->query_npc())
        return;

    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

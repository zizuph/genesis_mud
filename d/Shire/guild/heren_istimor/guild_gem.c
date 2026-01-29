/*
 * /d/Shire/guild/heren_istimor/guild_gem.c
 *
 * The guild gem / spell object for Heren Istimor
 *
 */
#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/guild/heren_istimor/heren_istimor.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

public void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }

    setuid();
    seteuid(getuid());

    set_name("gem");
    add_name("_shire_heren_istimor_guild_gem_");
    add_name("Istimor gem");
    add_adj(({"glittering","translucent"}));
    set_short("glittering gem");
    set_long("This is a royal blue gem, glistening and pulsing.\n");

            
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    remove_prop(OBJ_I_VALUE);
    add_spell("/d/Shire/guild/heren_istimor/spells/flame_of_anor");
    add_spell("/d/Genesis/newmagic/spells/identify");
    add_spell("/d/Genesis/newmagic/spells/invisibility");
    add_spell("/d/Genesis/newmagic/examples/spells/heal");

    add_spell(clone_object("/d/Genesis/newmagic/spells/tell"));

        
}

mixed
command_read(int more)
{
    write("Your gem glows and pulses. You see a spell in each facet...\n\n"+
      "cmagic for detecting magic in a room or person\n"+
      "cexits for detecting hidden exits.\n");
    return 1;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (IS_MEMBER(env) || env->query_wiz_level())
        add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

public int
query_recover()
{
    return 0;
}

/*
 * /d/Shire/guild/heren_istimor/guild_gem.c
 *
 * The guild gem / spell object for Heren Istimor
 *
 */
#pragma strict_types
#pragma save_binary
#include <stdproperties.h>
#include "/d/Shire/guild/heren_istimor/heren_istimor.h"

inherit "/d/Genesis/magic/spellcasting";
inherit "/std/object";
inherit "/d/Shire/guild/heren_istimor/spells/cmagic";
inherit "/d/Shire/guild/heren_istimor/spells/cexits";
inherit "/d/Shire/guild/heren_istimor/spells/peace";
inherit "/d/Shire/guild/heren_istimor/spells/dispell";
inherit "/d/Shire/guild/heren_istimor/spells/stell";

public void
create_object()
{
    set_name("gem");
    add_name("_shire_heren_istimor_guild_gem_");
    add_name("Istimor gem");
    add_adj(({"glittering","translucent"}));
    set_short("glittering gem");
    set_long("This is a royal blue gem, glistening and pulsing.\n");

    add_spell("stell", "distant tell", create_stell_spell,
      spell_target_one_distant_known_living, 1);    
    
    add_spell("cmagic", "detect enchantments", create_cmagic_spell,
      spell_target_one_distant_known_living, 1);

    add_spell("cexits", "detect hidden paths", create_cexits_spell,
      spell_target_caster_environment);

    add_spell("peace", "make peace", create_peace_spell,
      spell_target_caster_environment);      

    add_spell("dispell", "remove magic", create_dispell_spell,
      spell_target_one_other_present_living);      
            
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    remove_prop(OBJ_I_VALUE);
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

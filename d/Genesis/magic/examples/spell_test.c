inherit "/std/object";

inherit "/d/Genesis/magic/spells/invisibility";
inherit "/d/Genesis/magic/spells/identify";
inherit "/d/Genesis/magic/spells/dispel";
inherit "/d/Genesis/magic/spells/harm";
inherit "/d/Genesis/magic/spells/bolt";
inherit "/d/Genesis/magic/spells/darkvision";
/*
inherit "/d/Genesis/magic/examples/spells/tell";
*/

inherit "/d/Genesis/magic/examples/spells/ice_bolt";
inherit "/d/Genesis/magic/examples/spells/fire_ball";

inherit "/d/Genesis/magic/spellcasting";

void
create_object()
{
    set_name("spells");
    
    add_spell_invisibility();
    add_spell_identify();
    add_spell_dispel();
    add_spell_harm();
    add_spell_darkvision();
    add_spell_tell();

    add_spell("icebolt", "Shoot a bolt of ice",
         create_spell_ice_bolt, spell_target_one_other_present_living);
    add_spell("fireball", "Shoot bolts of fire at multiple targets",
         create_spell_fire_ball, spell_target_present_enemies);
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

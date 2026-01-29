#include "spells.h"

inherit "/d/Khalakhor/std/object";
inherit "/d/Genesis/magic/spellcasting";
inherit "/d/Genesis/magic/spells/identify";
inherit (SPELL_DIR + "lightningbolt");
inherit (SPELL_DIR + "icestorm");
inherit (SPELL_DIR + "sunburst");
inherit (SPELL_DIR + "freeze");
inherit (SPELL_DIR + "heal");
inherit (SPELL_DIR + "barrier");
inherit (SPELL_DIR + "curse");

void
create_khalakhor_object()
{
    set_name("spell book");
    set_short("igneous' spellbook");
    set_long("This is a spellbook igneous uses to "+
      "test his spells.\n");

    add_spell_identify();
    add_spell("sunburst", "A burst of light", create_sunburst,
      spell_target_caster_environment);
    add_spell("icestorm", "A storm of ice", create_icestorm,
      spell_target_non_team_members);
    add_spell("lightningbolt", "A bolt of lightning", create_lightning_bolt,
      spell_target_one_present_enemy);
    add_spell("freeze", "Freeze another living", create_freeze,
      spell_target_one_present_living);
    add_spell("heal", "Transfer your life energy to another",
      create_heal, spell_target_one_present_living);
    add_spell("barrier", "Create a barrier of water", create_barrier,
      spell_target_caster_environment);
    add_spell("curse", "Curse someone", create_curse,
      spell_target_non_team_members);
}

void
enter_env(object env, object from)
{
    ::enter_env(env,from);
    if (living(env))
	add_spell_object(env);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from))
	remove_spell_object(from);
}

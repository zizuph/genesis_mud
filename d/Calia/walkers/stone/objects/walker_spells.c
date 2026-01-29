
#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/magic/spellcasting";

inherit "/d/Calia/walkers/wave/spells/pititso";
inherit "/d/Calia/walkers/wave/spells/gsechon";
inherit "/d/Calia/walkers/wave/spells/tuphlono";
inherit "/d/Calia/walkers/wave/spells/diabnero";
inherit "/d/Calia/walkers/wave/spells/phatria";
inherit "/d/Calia/walkers/wave/spells/therapeaou";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/photostepsanos";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/stoiecheio";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/orasae";
inherit "/d/Calia/walkers/wave/spells/";
inherit "/d/Calia/walkers/wave/spells/";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include COUNCIL_HEADER
#include STONE_HEADER


public int
query_spell_mess(string verb, string arg)
{
    write("You draw power from the planes of earth.\n");
    say(QCTNAME(TP)+" draws power from the planes of earth.\n");
    return 1;
}

void
activate_spells()
{
    if (TP->query_skill(SS_WALKER_PUNISHMENT) == SPELL_BANNED)
    {
        write("You have been banned by the Walkers Council "+
            "from using the gifts of Lady Gu.\n");
        THIS->remove_object();
        return;
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_ONE_FLAG)
    {
        add_spell("pititso","Water Speak",
            create_spell_tell, target_tell);
        add_spell("gsechon","Name Forget",
            create_spell_gsechon, spell_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
    {
        add_spell("tuphlono","Tearing Eyes",
            create_spell_tuphlono, spell_target_one_present_living);
        add_spell("diabnero","Sweet Water",
            create_spell_diabnero, diabnero_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_THREE_FLAG)
    {
        add_spell("phatria","Peace",
            create_spell_phatria, phatria_target_caster);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
    {
        add_spell("therapeaou","Heal",
            create_spell_therapeaou, spell_target_one_present_living);
        add_spell("","Ice Wall",
            create_spell_, _target_caster);
        add_spell("","Ice Armour",
            create_spell_, _target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
    {
        add_spell("","Ice Shower",
            create_spell_, _target_one_other_present_living);
        add_spell("","Create Water",
            create_spell_, spell_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
    {
        add_spell("","Ice Bolt",
            create_spell_, _target_one_other_present_living);
        add_spell("","Breathe Water",
            create_spell_, _target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
    {
        add_spell("","Fatigue",
            create_spell_aeras, aeras_target_one_other_present_living);
        add_spell("photostepsanos","Shimmering Aura",
            create_spell_photostepsanos, photostepsanos_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
    {
        add_spell("","Resist Cold",
            create_spell_, _target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
    {
        add_spell("stoiecheio","Elemental Form",
            create_spell_stoiecheio, stoiecheio_target_caster);
        add_spell("","Cure Poison",
            create_spell_, spell_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
    {
        add_spell("orasae","Rune of Warding",
            create_spell_orasae, spell_target_caster);
        add_spell("","Ice Sheet",
            create_spell_, _target_one_present_object);
        add_spell("","Freeze",
            create_spell_, _target_one_present_living);
    }
}

void
create_object()
{
    set_name("_stone_walker_spells_");
    add_name("walker_spells");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_no_show();
}

string
query_auto_load()
{
    return MASTER + ":";
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
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}


#pragma strict_types
#pragma save_binary

inherit "/std/object";

inherit "/d/Calia/walkers/wind/spells/anemos";
inherit "/d/Calia/walkers/wind/spells/gsechon";
inherit "/d/Calia/walkers/wind/spells/aernero";
inherit "/d/Calia/walkers/wind/spells/tuphlono";
inherit "/d/Calia/walkers/wind/spells/aertrophia";
inherit "/d/Calia/walkers/wind/spells/ochetos";
inherit "/d/Calia/walkers/wind/spells/therapeaou";
inherit "/d/Calia/walkers/wind/spells/upala";
inherit "/d/Calia/walkers/wind/spells/pichno";
inherit "/d/Calia/walkers/wind/spells/topi";
inherit "/d/Calia/walkers/wind/spells/nuchta";
inherit "/d/Calia/walkers/wind/spells/aulaki";
inherit "/d/Calia/walkers/wind/spells/pleko";
inherit "/d/Calia/walkers/wind/spells/photostepsanos";
inherit "/d/Calia/walkers/wind/spells/antidroaera";
inherit "/d/Calia/walkers/wind/spells/stoiecheio";
inherit "/d/Calia/walkers/wind/spells/aeras";
inherit "/d/Calia/walkers/wind/spells/diarroae";
inherit "/d/Calia/walkers/wind/spells/agios";
inherit "/d/Genesis/magic/spellcasting";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include COUNCIL_HEADER
#include WIND_HEADER


public int
query_spell_mess(string verb, string arg)
{
    write("You draw power from the planes of air.\n");
    say(QCTNAME(TP)+" draws power from the planes of air.\n");
    return 1;
}

void
activate_spells()
{
    if (TP->query_skill(SS_WALKER_PUNISHMENT) == SPELL_BANNED)
    {
        write("You have been banned by the Walkers Council "+
            "from using the gifts of Lady Aeria.\n");
        THIS->remove_object();
        return;
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_ONE_FLAG)
    {
        add_spell("anemos","Wind Speak",
            create_spell_tell, target_tell);
        add_spell("gsechon","Name Forget",
            create_spell_gsechon, spell_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TWO_FLAG)
    {
        add_spell("aernero","Spirits",
            create_spell_aernero, aernero_target_one_present_living);
        add_spell("tuphlono","Tearing Eyes",
            create_spell_tuphlono, spell_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_THREE_FLAG)
    {
        add_spell("aertrophia","Peace",
            create_spell_aertrophia, aertrophia_target_caster);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FOUR_FLAG)
    {
        add_spell("ochetos","Armour Of Air",
            create_spell_ochetos, ochetos_target_one_present_living);
        add_spell("therapeaou","Heal",
            create_spell_therapeaou, spell_target_one_present_living);
        add_spell("pichno","Wall Of Debris",
            create_spell_pichno, pichno_target_caster);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_FIVE_FLAG)
    {
        add_spell("upala","Air Blast",
            create_spell_upala, upala_target_one_other_present_living);
        add_spell("nuchta","Darkness",
            create_spell_nuchta, spell_target_caster);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SIX_FLAG)
    {
        add_spell("topi","Lightning Bolt",
            create_spell_topi, topi_target_one_other_present_living);
        add_spell("aulaki","Far Sight",
            create_spell_aulaki, find_aulaki_targets);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_SEVEN_FLAG)
    {
        add_spell("pleko","Hurricane",
            create_spell_pleko, target_pleko);
        add_spell("photostepsanos","Invisibility",
            create_spell_photostepsanos, photostepsanos_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_EIGHT_FLAG)
    {
        add_spell("antidroaera","Resist Electricity",
            create_spell_antidroaera, antidroaera_target_one_present_living);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_NINE_FLAG)
    {
        add_spell("stoiecheio","Elemental Form",
            create_spell_stoiecheio, stoiecheio_target_caster);
        add_spell("aeras","Whisper Wind",
            create_spell_aeras, target_aeras);
    }
    if (TP->query_skill(SS_WALKER_CHOSEN) & SPELLS_TEN_FLAG)
    {
        add_spell("diarroae","Slow",
            create_spell_diarroae, diarroae_target_one_other_present_living);
        add_spell("agios","Fly",
            create_spell_agios, spell_target_caster);
    }
}

void
create_object()
{
    set_name("_wind_walker_spells_");
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

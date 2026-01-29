inherit "/std/object";


inherit "/d/Calia/walkers/wind/spells/anemos";
inherit "/d/Calia/walkers/wind/spells/gsechon";
inherit "/d/Calia/walkers/wind/spells/aernero";
inherit "/d/Calia/walkers/wind/spells/tuphlono";
inherit "/d/Calia/walkers/wind/spells/aertrophia";
inherit "/d/Calia/walkers/wind/spells/ochetos";
inherit "/d/Calia/walkers/wind/spells/therapeaou";
inherit "/d/Calia/walkers/wind/spells/pichno";
inherit "/d/Calia/walkers/wind/spells/upala";
inherit "/d/Calia/walkers/wind/spells/nuchta";
inherit "/d/Calia/walkers/wind/spells/aulaki";
inherit "/d/Calia/walkers/wind/spells/pleko";
inherit "/d/Calia/walkers/wind/spells/photostepsanos";
inherit "/d/Calia/walkers/wind/spells/antidroaera";
inherit "/d/Calia/walkers/wind/spells/stoiecheio";
inherit "/d/Calia/walkers/wind/spells/aeras";
inherit "/d/Calia/walkers/wind/spells/agios";
inherit "/d/Calia/walkers/wind/spells/topi";
inherit "/d/Genesis/magic/spellcasting";

void
create_object()
{
    set_name("spells");
    
    add_spell("windtell","Tell Line for Windwalkers",
        create_spell_tell, target_tell);
    add_spell("agios","Fly for Windwalkers",
        create_spell_agios, spell_target_caster);
    add_spell("aulaki","Far Sight for Windwalkers",
        create_spell_aulaki, find_aulaki_targets);
    add_spell("pleko","Hurricane for Windwalkers",
        create_spell_pleko, target_pleko);
    add_spell("aeras","Whisper Wind for Windwalkers",
        create_spell_aeras, target_aeras);
    add_spell("stoiecheio","Elemental Form for Windwalkers",
        create_spell_stoiecheio, spell_target_caster);
    add_spell("gsechon","Name Forget for Windwalkers",
        create_spell_gsechon, spell_target_one_present_living);
    add_spell("nuchta","Darkness for Windwalkers",
        create_spell_nuchta, spell_target_caster);
    add_spell("upala","Air Blast for Windwalkers",
        create_spell_upala, spell_target_one_other_present_living);
    add_spell("topi","Topi Spell for Windwalkers",
        create_spell_topi, spell_target_one_other_present_living);
    add_spell("aernero","Spirits Decanter for Windwalkers",
        create_spell_aernero, spell_target_one_present_living);
    add_spell("tuphlono","Tearing Eyes for Windwalkers",
        create_spell_tuphlono, spell_target_one_present_living);
    add_spell("aertrophia","Peace for Windwalkers",
        create_spell_aertrophia, spell_target_caster);
    add_spell("ochetos","Air Armour for Windwalkers",
        create_spell_ochetos, spell_target_one_present_living);
    add_spell("therapeaou","Heal for Windwalkers",
        create_spell_therapeaou, spell_target_one_present_living);
    add_spell("pichno","Wall of Debris for Windwalkers",
        create_spell_pichno, spell_target_caster);
    add_spell("photostepsanos","Invisibility for Windwalkers",
        create_spell_photostepsanos, spell_target_one_present_living);
    add_spell("antidroaera","Resist Electricity for Windwalkers",
        create_spell_antidroaera, spell_target_one_present_living);
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

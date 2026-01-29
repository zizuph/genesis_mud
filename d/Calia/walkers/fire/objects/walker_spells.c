
#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/magic/spellcasting";

inherit "/d/Calia/walkers/fire/spells/astraphto";
inherit "/d/Calia/walkers/fire/spells/photitso";
inherit "/d/Calia/walkers/fire/spells/tuphlono";
inherit "/d/Calia/walkers/fire/spells/akoutari";
inherit "/d/Calia/walkers/fire/spells/aspida";
inherit "/d/Calia/walkers/fire/spells/bromos";
inherit "/d/Calia/walkers/fire/spells/saita";
inherit "/d/Calia/walkers/fire/spells/aemera";
inherit "/d/Calia/walkers/fire/spells/phlogaphulo";
inherit "/d/Calia/walkers/fire/spells/kausae";
inherit "/d/Calia/walkers/fire/spells/aeras";
inherit "/d/Calia/walkers/fire/spells/lampas";
inherit "/d/Calia/walkers/fire/spells/ektomon";
inherit "/d/Calia/walkers/fire/spells/aithos";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include COUNCIL_HEADER
#include FIRE_HEADER


public int
query_spell_mess(string verb, string arg)
{
    write("You draw power from the planes of fire.\n");
    say(QCTNAME(TP)+" draws power from the planes of fire.\n");
    return 1;
}

void
activate_spells()
{
    if (TP->query_skill(SS_WALKER_PUNISHMENT) == SPELL_BANNED)
    {
        write("You have been blocked from accessing the elemental" +
            " planes by the Assembly.\n");
        THIS->remove_object();
        return;
    }

    add_spell("astraphto","Flame Speak",
        create_spell_tell, target_tell);
    add_spell("photitso","Light",
        create_spell_photitso, spell_target_caster);
    add_spell("tuphlono","Blinding Flash",
        create_spell_tuphlono, spell_target_one_present_living);
    add_spell("akoutari","Flame Wall",
        create_spell_akoutari, akoutari_target_caster);
    add_spell("aspida","Flame Shield",
        create_spell_aspida, spell_target_caster);
    add_spell("bromos","Frenzy",
        create_spell_bromos, spell_target_one_other_present_living);
    add_spell("saita","Flame arrow",
        create_spell_saita, saita_target_one_other_present_living);
    add_spell("aemera","Luminosity",
        create_spell_aemera, spell_target_caster);
    add_spell("phlogaphulo","Flame Weapon",
        create_spell_phlogaphulo, phlogaphulo_target_caster);
    add_spell("kausae","Fire storm",
        create_spell_kausae, kausae_target_present_enemies);
    add_spell("aeras","Flame Wind",
        create_spell_aeras, aeras_target_one_other_present_living);
    add_spell("lampas", "Burst of light",
        create_spell_lampas, lampas_target_all_present_livings);
    add_spell("ektomon", "Hellscape",
        create_spell_ektomon, spell_target_caster);
    add_spell("aithos", "Fire spirit",
        create_spell_aithos, spell_target_one_other_present_living);
}

void
create_object()
{
    set_name("_fire_walker_spells_");
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

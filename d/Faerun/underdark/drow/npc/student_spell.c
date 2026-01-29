/*
 * Wizard students
 * /d/Faerun/underdark/drow/npc/student_spell.c
 * -- Finwe, April 2006
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

inherit DROW_NPC_BASE;
inherit FAERUN_TEAM_BASE;
inherit FAERUN_LIB + "spellcasting";

#define DESC1 ({ "malicious", "haughty", "dark", "treacherous", "arrogant",\
    "dangerous", "vicious", "calculating"})

#define DESC2 ({"skinny", "young", "dark-skinned", "black-skinned",\
    "ebony-skinned", "white-haired", "silvery-haired", "red-eyed", "crimson-eyed"})

#define DROW_COUNT 3    /* how many drow types */

int drow_num; /* pick drow type */

void set_equip();
void set_drow_type();

void create_faerun_npc()
{
    string adj1 = ONE_OF_LIST(DESC1);
    string adj2 = ONE_OF_LIST(DESC2);

    seteuid(getuid());
    set_name("drow");
    set_pname("drow");
    set_adj(adj1);
    add_adj(adj2);
    set_gender(random(1));
    set_race_name("drow");
    add_name("drow");
    set_short(adj1 + " " + adj2 + " drow");
    set_pshort(adj1 + " " + adj2 + " drows");
    set_long("You are observing one of the wizard " + 
        "students of the Sorcere. You notice an air of " +
        "of arrogance about this student. His eyes burns " +
        "red like glowing embers in his dark-skinned face " +
        "and his white hair runs straight a bit down his neck.\n");

    drow_num = random(DROW_COUNT);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_stats(({ 120, 185, 140, 155, 140, 130 }));
    set_alignment(-800);

    set_skill(SS_ELEMENT_WATER, 60);
    set_skill(SS_ELEMENT_AIR, 60);
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_FORM_CONJURATION, 50);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_WEP_KNIFE, 70);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Set up our spellcasting stuff
    set_alarm(0.5, 0.0, &set_drow_type());

    // Fetch my equipment
    set_alarm(0.5,0.0, &set_equip());

    // We always use our weapon, no unarmed combat
    set_no_unarmed_combat(1);
    
    set_exp_factor(120);
    drow_setup();
}

void equip()
{
    seteuid(getuid());

    // Create and move all armours
    clone_object(ARM_DIR + "ns_armband")->move(this_object());
    clone_object(ARM_DIR + "ns_greaves")->move(this_object());
    clone_object(ARM_DIR + "ns_vest")->move(this_object());
    clone_object(ARM_DIR + "ss_boots")->move(this_object());
    clone_object(ARM_DIR + "s_circlet")->move(this_object());
    clone_object(WEP_DIR + "Studentrobe")->move(this_object());
    clone_object(WEP_DIR + "qstaff")->move(this_object());
    command("wear all");
    command("wield all");
}

void set_drow_type()
{

    switch(drow_num)
    {
        case 0: // viper spell
        {
            add_spell(FAERUN_SPELLS + "drow_viperhand");
            set_cast_chance(20);
            break;
        }
        case 1: // web spell
        {
            add_spell(FAERUN_SPELLS + "drow_spiderweb");
            set_cast_chance(20);
            break;
        }
        case 2: // acid spell
        {
            add_spell(FAERUN_SPELLS + "drow_acid_bolt");
            set_cast_chance(29);
            break;
        }
        case 3: // fire spell
        {
            add_spell(FAERUN_SPELLS + "drow_fireball");
            set_cast_chance(20);
            break;
        }
        default:
            add_spell(FAERUN_SPELLS + "drow_spiderweb");
            set_cast_chance(20);
            break;
    }

}

void set_equip()
{

    clone_object(ARM_DIR + "m_bracers")->move(this_object());
    clone_object(ARM_DIR + "m_greaves")->move(this_object());
    clone_object(ARM_DIR + "m_chainmail")->move(this_object());
    clone_object(ARM_DIR + "m_boots")->move(this_object());
    clone_object(ARM_DIR + "m_circlet")->move(this_object());
    clone_object(ARM_DIR + "masterrobe")->move(this_object());

    
    switch(drow_num)
    {

        case 0: // viper spell
        {
            clone_object(WEP_DIR + "roncone")->move(this_object());
            break;
        }
        case 1: // web spell
        {
            clone_object(WEP_DIR + "s_sword")->move(this_object());
            break;
        }
        case 2: // acid spell
        {
            clone_object(WEP_DIR + "qstaff")->move(this_object());
            break;
        }
        case 3: // fire spell
        {
            clone_object(WEP_DIR + "kukri")->move(this_object());
            break;
        }
        default:
            clone_object(WEP_DIR + "qstaff")->move(this_object());
            break;
    }
    
    command("wear all");
    command("wield all");

}



int
special_attack(object new_victim)
{
    // Cast spells
    if(special_attack_spellcast(new_victim))
        return 1;
    
    // If we are levitating, and we didnt cast a spell, see if we use
    // a missile weapon, then allow the round to continue, otherwise
    // fail.
    if(drow_levitating && !using_missile_weapon())
        return 1;

    // Just continue with the round
    return 0;

}
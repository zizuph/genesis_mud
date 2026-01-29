/*
 *  faerun/underdark/upper/menzo/sorcere/npc/student_fire.c
 *
 *  A 1st level wizard student in the Sorcere
 *
 *  Created by Midnight, 21-2-2004
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_drow";

#define DESC1 ({ "malicious", "haughty", "dark",\
"treacherous", "arrogant", "dangerous", "vicious",\
"calculating"})

#define DESC2 ({"skinny", "young", "dark-skinned",\
"black-skinned","ebony-skinned","white-haired",\
"silvery-haired","red-eyed","crimson-eyed"\
})

void equip();

string  adj1 = DESC1[random(sizeof(DESC1))],
        adj2 = DESC2[random(sizeof(DESC2))];
/*
 * Function name: create_sorcere_drow
 * Description  : Construct a drow for the Sorcere part of Menzoberranzan
 */
void create_sorcere_drow()
{
    set_name("drow");
    set_pname("drows");
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

    add_prop(LIVE_I_NEVERKNOWN, 1);
    
    set_stats(({ 120, 185, 140, 155, 140, 130 }));
    set_alignment(-800);

    set_skill(SS_ELEMENT_FIRE, 70);
    set_skill(SS_ELEMENT_AIR, 60);
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_FORM_CONJURATION, 50);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_PARRY, 50);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_WEP_KNIFE, 80);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Set up our spellcasting stuff
    add_spell(P_FAERUN_SPELLS + "drow_fireball");
    set_cast_chance(50);

    // Fetch my equipment
    equip();

    // We always use our weapon, no unarmed combat
    set_no_unarmed_combat(1);
    set_exp_factor(120);
}

void equip()
{
    seteuid(getuid());

    // Create and move all armours
    clone_object(P_MENZO_SORCERE + "arm/ns_armband")->move(this_object());
    clone_object(P_MENZO_SORCERE + "arm/ns_greaves")->move(this_object());
    clone_object(P_MENZO_SORCERE + "arm/ns_vest")->move(this_object());
    clone_object(P_MENZO_SORCERE + "arm/ss_boots")->move(this_object());
    clone_object(P_MENZO_SORCERE + "arm/s_circlet")->move(this_object());
    clone_object(P_MENZO_SORCERE + "arm/studentrobe1")->move(this_object());
    clone_object(P_MENZO_SORCERE + "wep/kukri")->move(this_object());
    command("wear all");
    command("wield all");
}

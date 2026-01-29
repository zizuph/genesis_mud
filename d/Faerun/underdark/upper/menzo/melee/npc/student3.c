/*
 *  faerun/underdark/upper/menzo/melee/npc/student3.c
 *
 *  A warrior student in the Melee-magthere
 *
 *  Created by Midnight, 15-4-2004
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_MELEE + "std/base_drow";
inherit P_FAERUN_AUTOTEAM;


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
 * Function name: create_melee_drow
 * Description  : Construct a drow for the Melee-magthere
 */
void create_melee_drow()
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
    set_long("You look at the, by drowish standards, young drow. " +
             "He looks welltrained with muscles tensing under " +
             "his ebony black skin. His eyes burn like blood red " +
             "glowing embers in his dark face, which is drained of " +
             "emotional display.\n"); 

    
    set_stats(({ 170, 185, 150, 130, 130, 130 }));
    set_alignment(-800);

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_2H_COMBAT,80);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);

    // Fetch my equipment
    equip();

    // We always use our weapon, no unarmed combat
    set_no_unarmed_combat(1);

}

void equip()
{
    seteuid(getuid());

    // Create and move all armours
    clone_object(P_MENZO_MELEE + "arm/s_chainmail")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/s_bracers")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/piwafwi")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/ss_boots")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/s_greaves")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/s_mask")->move(this_object());
    clone_object(P_MENZO_MELEE + "arm/buckler")->move(this_object());
    clone_object(P_MENZO_MELEE + "wep/s_sword")->move(this_object());
    command("wear all");
    command("wield all");
}

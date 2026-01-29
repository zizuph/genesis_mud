/*
 *  /d/Faerun/underdark/drow/npc/student.c
 *  Created by Midnight, 8-4-2004
 *  Updated by Finwe, 2006
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

inherit DROW_NPC_BASE;
inherit FAERUN_TEAM_BASE;

#define DESC1 ({ "malicious", "haughty", "dark", "treacherous", "arrogant",\
    "dangerous", "vicious", "calculating"})

#define DESC2 ({"skinny", "young", "dark-skinned", "black-skinned",\
    "ebony-skinned","white-haired", "silvery-haired","red-eyed","crimson-eyed"})

void equip();

/*
 * Function name: create_melee_drow
 * Description  : Construct a drow for the Melee-magthere
 */
// void create_faerun_drow()
void create_faerun_npc()
{
    string adj1 = ONE_OF_LIST(DESC1);
    string adj2 = ONE_OF_LIST(DESC2);

    seteuid(getuid());
    
    set_name("drow");
    set_adj(adj1);
    add_adj(adj2);
    set_gender(random(1));
    set_race_name("drow");
    add_name("drow");
//    set_short(adj1 + " " + adj2 + " drow");
//    set_pshort(adj1 + " " + adj2 + " drow");
    set_long("You look at the young drow. " +
             "He looks well-trained with muscles tensing beneath " +
             "his ebony black skin. His eyes burn like blood red " +
             "glowing embers in his dark face, which is drained of " +
             "emotional display.\n"); 

    
    set_stats(({ 170, 185, 150, 130, 130, 130 }));
    set_alignment(-800);

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_2H_COMBAT,80);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_random_move(5);
//    set_restrain_path(TUN_DIR);

//    set_aggressive(my_aggressive);



    // Fetch my equipment
    equip();

    // We always use our weapon, no unarmed combat
    set_no_unarmed_combat(1);

    drow_setup();

}


void equip()
{
    seteuid(getuid());
    clone_object(ARM_DIR + "s_chainmail")->move(this_object());
    clone_object(ARM_DIR + "s_bracers")->move(this_object());
    clone_object(ARM_DIR + "piwafwi")->move(this_object());
    clone_object(ARM_DIR + "ss_boots")->move(this_object());
    clone_object(ARM_DIR + "s_greaves")->move(this_object());
    clone_object(ARM_DIR + "s_mask")->move(this_object());
    clone_object(WEP_DIR + "kukri")->move(this_object());
    clone_object(WEP_DIR + "scimitar")->move(this_object());

    command("wear all");
    command("wield all");
}


int
my_aggressive()
{
    string race = TP->query_race();
    // Leave the poor wizards alone.
    if (TP->query_wiz_level())
    	return 0;
    // Dont attack other Drow
    if (TP->query_guild_name_race() == "Racial Drow")
	    return 0;
    // Let's kill them all, we don't trust them.
    return 1;
}

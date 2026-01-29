/*
 *  Drow warrior who patrols the underdark
 *  Created by Midnight, 8-4-2004
 *  Updated by Finwe, July 2007
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Faerun/defs.h"

inherit FAERUN_STD + "drow_npc";
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define DESC1 ({ "malicious", "haughty", "dark", "treacherous", "arrogant",\
    "dangerous", "vicious", "calculating"})
#define DESC2 ({"skinny", "young", "dark-skinned", "black-skinned",\
    "ebony-skinned","white-haired", "silvery-haired","red-eyed","crimson-eyed"})
#define DROW_ARM_DIR    "/d/Faerun/underdark/drow/arm/"
#define DROW_WEP_DIR    "/d/Faerun/underdark/drow/wep/"

void equip();

void create_monster()
{
    string adj1 = ONE_OF_LIST(DESC1);
    string adj2 = ONE_OF_LIST(DESC2);

    seteuid(getuid());

    npc_name = "_drow_npc";

    set_name("drow");
    add_name(npc_name);
    set_adj(adj1);
    add_adj(adj2);
    set_gender(random(1));
    set_race_name("drow");
    
//    set_short(adj1 + " " + adj2 + " drow");
//    set_pshort(adj1 + " " + adj2 + " drow");
    set_long("You look at the young drow. This is one of the many drow warriors that patrol the Underdark. He looks well-trained with muscles tensing beneath his ebony black skin. His eyes burn like blood red glowing embers in his dark face, which is drained of emotional display.\n"); 
    
    set_stats(({ 170, 185, 150, 130, 130, 130 }));
    set_alignment(-800);

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_2H_COMBAT,80);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_random_move(5);
    set_restrain_path(TUN_DIR);

    equip();

    set_no_unarmed_combat(1);

    set_pick_up_team(({npc_name}));

    add_spell(FAERUN_SPELLS + "drow_acid_bolt");
    set_cast_chance(50);

    drow_setup();

}


void equip()
{
    seteuid(getuid());
    clone_object(DROW_ARM_DIR + "s_chainmail")->move(this_object());
    clone_object(DROW_ARM_DIR + "s_bracers")->move(this_object());
    clone_object(DROW_ARM_DIR + "piwafwi")->move(this_object());
    clone_object(DROW_ARM_DIR + "ss_boots")->move(this_object());
    clone_object(DROW_ARM_DIR + "s_greaves")->move(this_object());
    clone_object(DROW_ARM_DIR + "s_mask")->move(this_object());
    clone_object(DROW_WEP_DIR + "kukri")->move(this_object());
    clone_object(DROW_WEP_DIR + "scimitar")->move(this_object());

    command("wear all");
    command("wield all");

    make_gems(TO, 1);
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

int special_attack(object ob)
{
    return special_attack_spellcast(ob);
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}


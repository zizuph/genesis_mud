/*
 *  /d/Faerun/underdark/drow/npc/master.c
 *
 *  A warrior master in the Melee-magthere
 *
 *  Created by Midnight, 16-4-2004
 */

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit DROW_NPC_BASE;

#define DESC1 ({ "commanding", "muscular", "dominating", "overbearing" })

#define DESC2 ({"skinny", "aged", "dark-skinned",\
"black-skinned","ebony-skinned","white-haired",\
"silvery-haired","red-eyed","crimson-eyed"\
})

void equip();

/*
 * Function name: create_melee_drow
 * Description  : Construct a drow for the Melee-magthere
 */
void create_faerun_npc()
{
    string adj1 = ONE_OF_LIST(DESC1);
    string adj2 = ONE_OF_LIST(DESC2);

    seteuid(getuid());

    set_name("drow");
    add_name("elf");
    set_pname("drow");
    set_adj(adj1);
    set_adj(adj2);
    set_gender(G_FEMALE);
    set_race_name("drow");
    add_name("drow");
    set_short(adj1 + " " + adj2 + " drow");
    set_pshort(adj1 + " " + adj2 + " drow");
    set_long(CAP(HE_SHE(TO)) + " carries " + HIM_HER(TO) + 
        "self with immense authority. " + CAP(HIS_HER(TO)) + 
        " black skin is extremely well trained with tense muscles. The " +
        "eyes burn like blood red glowing embers in a dark face, which is " +
        "drained of emotional display.\n"); 

    
    set_stats(({ 190, 195, 175, 140, 140, 140 }));
    set_alignment(-800 + random(-100));

    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 80);
    set_skill(SS_WEP_POLEARM, 100);
    
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_random_move(5);

    // Fetch my equipment
    equip();

    // We always use our weapon, no unarmed combat
    set_no_unarmed_combat(1);
    drow_setup();

}

void equip()
{
    seteuid(getuid());

    // Create and move all armours
    clone_object(ARM_DIR + "m_chainmail")->move(this_object());
    clone_object(ARM_DIR + "m_bracers")->move(this_object());
    clone_object(ARM_DIR + "piwafwi")->move(this_object());
    clone_object(ARM_DIR + "ss_boots")->move(this_object());
    clone_object(ARM_DIR + "m_greaves")->move(this_object());
    clone_object(ARM_DIR + "helmet")->move(this_object());
    clone_object(WEP_DIR + "roncone")->move(this_object());
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

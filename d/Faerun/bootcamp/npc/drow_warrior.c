/*
 * Drow Warrior NPC/Entrance camp Underdark city
 * by Clyptas, July, 2017
 */
inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"

#define OBJ "/d/Faerun/bootcamp/obj/"

create_monster()
{
    set_name("mercenary");

    set_race_name("drow");

    set_adj( ({"cautious"}) );

    set_stats( ({90, 114, 90, 90, 90, 90}) );

    set_alignment(0);

    set_gender(G_MALE);
	
	remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,75);
    set_skill(SS_WEP_SWORD,85);
    set_skill(SS_WEP_KNIFE,65);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_2H_COMBAT, 50);
	
	set_act_time(10);
    set_cact_time(10);
    add_act("emote looks around cautiously.");
    add_act("emote draws his scimitar from it's sheath and practices forms.");
    add_act("emote yawns slightly, covering his mouth and looks around quickly.");
    add_act("emote drinks from a wineskin hanging on his hip.");
   
    set_chat_time(25);
    add_chat("How did you find us?");
    add_chat("Vagabond! Inform the commander!");

    set_cchat_time(5);
    add_cchat("Die, coward!");
    add_cchat("My scimitar will taste your blood.");
    add_cchat("Don't even try to run.");
 
        equip(({ 
          (OBJ + "d_scimitar"),
          (OBJ + "warrior_boots"),
          (OBJ + "warrior_breeches"),
    }));
}
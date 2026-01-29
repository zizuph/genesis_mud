/*
 * Jarlaxle NPC/Entrance quest Underdark city
 * Clyptas, July, 2017
 */
inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"
#define QUEST_NAME_PROP "_missing_wineskin"

#define OBJ "/d/Faerun/bootcamp/obj/"



create_monster()
{
    set_name("jarlaxle");
    
    set_title("Baenre, Commander of the Bregan D'aerthe");

    set_race_name("drow");

    set_adj( ({"stoic","pompous"}) );

    set_stats( ({190, 210, 210, 210, 210, 210}) );

    set_alignment(0);

    set_gender(G_MALE);
    
    set_skill(SS_UNARM_COMBAT,55);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_SWORD,85);
    set_skill(SS_WEP_KNIFE,65);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);
    
    set_act_time(10);
    set_cact_time(10);
    add_act("emote sctratches his chin with his fingers.");
    add_act("emote places his hands on his hips and looks around.");
    add_act("emote smirks, his eyes calculating and dangerous.");
    add_act("emote smiles slyly, and tips his hat.");
    add_act("emote plays idly with the silver whistle hanging at his hip.");
	add_ask(({"wine", "task", "help", "quest", "wineskin"}),
         VBFC_ME("ask_wineskin"));
    
    set_chat_time(25);
    add_chat("What do you seek here?");
    add_chat("You may be of interest to me.");


    set_cchat_time(5);
    add_cchat("Die, coward!");
    add_cchat("I will gladly put you in your place.");
    add_cchat("You think you can best me?");
	add_cchat("An illusion can kill you, if you believe it to be real.");
       
        equip(({ 
          (OBJ + "j_hat"),
          (OBJ + "j_rapier"),
          (OBJ + "j_cape"),
          (OBJ + "j_boots"),
          (OBJ + "j_bracelets"),
          (OBJ + "j_breeches"),
          (OBJ + "j_vest"),
		  
    }));
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

string ask_wineskin()
{
	Object wineskin;
	
    if(TP->test_bit(DOMAIN, WINESKIN_QUEST_GROUP, WINESKIN_QUEST_BIT))
    {
        command("emote smirks and nonchalantly wipes dust from his cape.");
	    command("say You've returned what I asked, begone.");
	    return "";
    }
	
	    if (TP->query_prop(QUEST_NAME_PROP))
    {
	    command("say Have you fetched what I asked?");
	    command("say If you haven't, begone. I'll fetch it myself.");
	    return "";
    }
	
	
    command("say If you want to help me, fetch me a wineskin."); 
    command("emote looks at you expectantly.");

    command("emote eyesparkle brightly");
    command("say Much obliged, you may not be as dull as I thought.");

    player->remove_prop(QUEST_NAME_PROP);

    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " was rewarded.\n");


    player->set_bit(WINESKIN_QUEST_GROUP, WINESKIN_QUEST_BIT);

    player->add_exp_quest(WINESKIN_QUEST_EXP);

    QUEST_LOG_FILE(WINESKIN_QUEST_LNG, WINESKIN_QUEST_EXP);
    obj->remove_object();

}
	



    
    

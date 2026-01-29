/* Modified by Mirandus to direct players to the new location of the 
*  Thanar Racial Guild. Also add some actions indicating that those below 
*  are folks who disagree with the softening of the stance of the Order
*  which allows them to remain.
*/
#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void arm_me();


void
create_kalad_monster()
{
    set_name("abbathor");
    add_name("priest");
    add_name("knight");
    add_name("warrior");
    set_race_name("human");
    set_adj("brutal");
    add_adj("unholy");
    set_long("A figure whose features don't seem quite right. It is as if "+
      "his features are somehow muddled, and are constantly changing. An "+
      "aura of dreadful evil emanates from him, like the rays of the sun "+
      "falling down upon Kalad.\n");
    set_stats(({190, 190, 190, 190, 190, 190}));
    set_alignment(-1200);
    set_title("the Skull Priest and Warrior Knight of Thanar");
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 60);
    set_act_time(3);
    add_act(({"say Thanar is the most glorious of gods.", 
    "emote bows his head in utter reverence."}));
    add_act(({"emote sings an unholy chant, as if casting a spell.", 
    "say The guardians watch over me now.", "grin dem"}));
    add_act("say Only humans may join the Order. Seek out our Cathedral "
    +"in the city.");
    add_act("say There are those who disagree with our changes.");
    add_act("say Damned Goblins and Saurians trying to take Kalad.");
    add_act("say The order has moved to the Cathedral within the city "
    +"and reclaimed their power.");
    add_act("say There are lose who remained here that disagree with what "
    +"the order has done to regain power.");
    add_act("I am here to direct you to the Cathedral if you seek Thanar.");
    set_cact_time(3);
    add_cact("say Thanar curse you!");
    add_cact("say This attack was most unwise of you.");
    add_cact("slam");
    set_default_answer("The skull knight says: What are you speaking of, "
    +"you fool!\n");
    add_ask(({"altar", "order"}), "The skull knight says: Only the chosen "+
      "children of Thanar may serve him. Seek out the Cathedral.\n");
    set_knight_prestige(900);

    arm_me();

    MONEY_MAKE_GC(random(10))->move(TO, 1);
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "ktmed");
    arm->move(TO);
    arm = clone_object(ARM + "skbanded");
    arm->move(TO);
    arm = clone_object(ARM + "skrobe");
    arm->move(TO);
    arm = clone_object(OBJ + "npc_symbol");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "skwarham");
    wep->move(TO);
    command("wield all");
}

void
do_die(object killer)
{
    string text;
    object avatar;

    if(query_hp() > 0) return;

    /* Changes as it's not always safe and a new Thanar is coming*/
    if (!find_living("_thanar_demon_"))
    {
	write("With a thunderous burst of power like nothing you have ever "+
	      "felt in the whole of your existence, a presence so utterly sinister "+
	      "enters the room, almost causing you to flee in complete terror.\n");
	say("With a thunderous burst of power like nothing you have ever "+
	    "felt in the whole of your existence, a presence so utterly sinister "+
	    "enters the room, almost causing you to flee in complete terror.\n");
	
	avatar = clone_object(NPC + "avatar_thanar");
	avatar->my_equipment();
	avatar->move(environment(TO));
	avatar->command("emote laughs in pure, unadulterated "
    +"ecstacy.");
	avatar->command("say FOOLS! You bring the wrath of a "
    +"god down upon this world!");
	avatar->move_living("west and towards the city", CVAN + "caravan-wayfar");
	
	/*
	 * This part is added by Korat:
	 * It will send a message to the watchman in central district.
	 */
	
	text = "and rumours say the Avatars are slaughtering innocents "+
	    "in the streets of Kabal.";
	call_other(CENTRAL + "high-circle-south", "patrol_text", text);
	
    }
    
    ::do_die(killer);
}

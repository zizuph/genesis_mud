/* Derryn: A powerful Mul gladiator, who escaped from the slave pits
   of one of the more powerful noble houses of Tyr. He must be overcome
   for the gladiator guru quest.
   Code (c) 1998 Damian Horton
   Updated for Raumdor, March 2001
*/

#pragma strict_types
#pragma save_binary 

#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/athas/gladiator/guruquest/guruquest.h";

inherit STD + "monster";
inherit "/lib/unique"; //his weapon may be 'unique'
inherit "/d/Genesis/lib/intro.c"; //so he may introduce himself

void
create_monster ()
{
    object axe; //the axe he wields

    set_living_name("derryn");
    set_name("derryn");
    set_title("the Retired Master Gladiator of Athas");
    set_race_name("dwarf");
    set_adj("thoughtful");
    add_adj("hairless");
    set_long("Large, and well-built for a dwarf, his skin betrays the "+
             "brutal scars of a gladiator. His face and head are completely "+
	     "shaven, including his beard and eyebrows! "+
	     "His steely grey eyes are set deeply into his "+
             "rough-hewn face. He displays an air of quiet "+
             "confidence, and contentment. He handles his "+
             "obsidian battleaxe with practiced grace.\n");
   
    set_stats(({135, 105, 150, 96, 130, 140}));
    set_skill(SS_WEP_AXE, 94);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 88);
    set_skill(SS_PARRY, 86);
    set_skill(SS_UNARM_COMBAT, 68);
    set_skill(SS_AWARENESS, 56);
    set_alignment(150);
    set_exp_factor(100);
   
    set_appearance(-15); //above average appearance
    add_prop(OBJ_I_WEIGHT, 90000);
    add_prop(OBJ_I_VOLUME, 88000);

    
    //only two enormous obsidian battleaxes may be in the game at once,
    //and he boots with one only 35% of the time

      

    axe = clone_unique(QUEST_DIR + "wep/enormous_axe", 2, 
		       QUEST_DIR + "wep/long_axe", 1, 35);
    axe->move(TO);
    
    command("wield all");

    equip(({QUEST_DIR + "arm/leather_bands",
	      QUEST_DIR + "arm/skull_helmet",
	      QUEST_DIR + "arm/kank_greaves",
	      QUEST_DIR + "arm/scaled_shirt",
	      QUEST_DIR + "arm/worn_robe"}));

    set_act_time(3);
    add_act("emote contemplates his existance.");
    add_act("emote breathes deeply, at peace with himself.");
    add_act("emote twirls his obsidian battleaxe idly.");
    add_act("say What brings you into these forsaken parts?");
    add_act("emote chuckles softly to himself.");

    set_cact_time(3);
    add_cact("say If its a fight you want, I'll give it to ya!");
    add_cact("say It was unwise of you to challenge me.");
    add_cact("say Leave me in peace, and I will consider not leaving you "+
             "in pieces!");
    add_cact("emote 's eyes glaze over, reason being lost to bloodlust.");
    add_cact("emote works himself into a wild battlerage.");
    add_cact("emote breaks into a sweat as his breathing becomes heavier.");

    LOAD_GURU_SHADOW(DERRYN);
}
 
/* sets unarmed combat off, giving more axe attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

/* This is Derryn's special attack, always called at the start of combat,
   and used 1 round in 8 throughout the battle. */
void
charge(object enemy)
{
    mixed* hitresult; //result of the attack
    string how;       //string describing the damage

    //he might miss, if you have high wisdom
    if (random(1000)< (enemy->query_stat(SS_WIS)))
    {
	enemy->catch_msg(QCTNAME(TO)+" charges ferociously at you, "+
			 "but you somehow manage to get out of his way.\n");
	tell_watcher(QCTNAME(TO)+" charges ferociously at "+
		     QTNAME(enemy)+", but the latter somehow manages "+
		     "to get out of his way.\n", TO, enemy);
	return; //do no more
    }
    
    hitresult = enemy->hit_me(500, W_BLUDGEON, TO, -1);
    
    if (enemy->query_hp() <= 0) 
    {   //killed enemy with the charge
	enemy->catch_msg(QCTNAME(TO) + " charges into you with lethal "+
			 "force!\n");
	tell_watcher(QCTNAME(TO) + " strikes " + QCTNAME(enemy) + 
		     "with lethal force!\n", TO, enemy);
	enemy->do_die(TO);
    }

    how = "unharmed";
    
    if (hitresult[0] > 0) how = "dazed";
    if (hitresult[0] > 15) how = "injured";
    if (hitresult[0] > 30) how = "hurt";
    if (hitresult[0] > 50) how = "severely hurt";
    if (hitresult[0] > 75) how = "on the verge of collapse";
 
    enemy->catch_msg(QCTNAME(TO)+" strikes you with his ferocious "+
		     "charge!\n");
    enemy->catch_tell("You are " + how + ".\n");
    tell_watcher(QCTNAME(TO)+" strikes "+QCTNAME(enemy)+
		 " with his ferocious charge!\n"+QCTNAME(enemy)+" is "+
		 how+"!\n", TO, enemy);
 
    if(enemy->query_hp() <= 0) enemy->do_die(TO);
}

/* Uses his charge 1 round in 8 */
int
special_attack(object enemy)
{ 
    if(random(8)) return 0;
    
    charge(enemy);
    return 1;
}

/* Done chiefly to prevent players from doing in, special, leave
   tactics against him: He always charges immediately upon being engaged.
*/
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    // alarmed so that the messages will be printed after the room
    // description, etc.
    set_alarm(0.0, 0.0, &charge(ob));
}

/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, not however that it should never contain an
 *                'introduce myself' command. Personalized for Derryn.
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("nod ack " + OB_NAME(who));
}

/*
 * Function name:       introduce
 * Description:         This function makes the npc do an introduction to a
 *                      player that has not been introed to it earlier.
 *                      Changed for variety.
 * Arguments            object who - the livint that introduced tome
 *
 */
public void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));
} 






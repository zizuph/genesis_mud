/* Myrdoth. An opponent for the gladiators sup.guru quest. The 
   elven champion. Code (c) 1998 Damian Horton.
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
inherit "/d/Khalakhor/khail/open/width_height"; //so I can set an appropriate 
// width and height for his race 
inherit "/d/Genesis/lib/intro.c"; //so he may introduce himself

void
create_monster ()
{
    set_living_name("myrdoth");
    set_name("myrdoth");
    set_title("Best Warrior of the Mikla Noth");
    set_race_name("elf");
    set_adj("extremely tall");
    add_adj("muscular");
    set_long("This elf must be almost seven feet tall, and is unusually "+
             "muscular for that slender race. He has piercing blue eyes "+
             "which gaze confidently at his surroundings. You can see "+
             "why he is the tribe's champion.\n");
    set_size("extremely tall", "fat"); // width_height broken :(
   
    set_stats(({120, 150, 125, 135, 120, 135}));

    set_skill(SS_WEP_SWORD, 92);
    set_skill(SS_BLIND_COMBAT, 45);
    set_skill(SS_DEFENCE, 94);
    set_skill(SS_PARRY, 90);
    set_skill(SS_UNARM_COMBAT, 54);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_AWARENESS, 52);
    set_alignment(-100);
    set_exp_factor(125);
   
    equip(({QUEST_DIR + "wep/elvish_scimitar",
	      QUEST_DIR + "wep/obsidian_scimitar",
	      QUEST_DIR + "arm/better_breastplate",
	      QUEST_DIR + "arm/studded_bracers",
	      QUEST_DIR + "arm/mekillot_greaves"}));

    set_act_time(3);
    add_act("emote assesses you with an unflinching eye.");
    add_act("emote smiles confidently.");
    add_act("emote curses at the thought of Imperial Necromancer Decius, "+
            "who keeps trying to 'recruit' him for the Arena.");
    add_act("emote declares: The Makla Noth shall ever be free, and never "+
            "be slaves!");
    add_act("emote stretches his long legs.");
    add_act("say I am the best warrior of the Makla Noth.");
 
    set_cact_time(3);
    add_cact("emote shakes his head in disbelief.");
    add_cact("emote declares: The Makla Noth shall ever be free, and never "+
             "be slaves!");
    add_cact("say Return to whence you came, ruffian!");
    add_cact("say Fool, you asked for it!");
    add_cact("spit");
    add_cact("emote mutters some elvish obscenities.");

    //cloning privileges: is this necessary at this point?
    setuid();
    seteuid(getuid());

    LOAD_GURU_SHADOW(MYRDOTH);
}
 
/* This is done so that Myrdoth gets the benefits of being an elf
when wielding the elvish scimitar. Of course no other NPC will,
but that seems to be a minor consideration. */

string
query_race()
{
  return "elf";
}
 
/* sets unarmed combat off, giving more scimitar attacks! */
int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}

/* Damage special. */
void 
kick(object enemy)
{ 
    mixed* hitresult; //result of the attack
    string how; //description of the damage

    if (random(250) + query_stat(SS_DIS) - enemy->query_stat(SS_WIS) > 80)
    {
	// he hit!
        hitresult = enemy->hit_me(250, W_BLUDGEON, TO, -1);
   
	if (enemy->query_hp() <= 0) 
	{   //mortal damage
	    enemy->catch_msg(QCTNAME(TO) + " kicks you lethal force!\n"); 
	    tell_watcher(QCTNAME(TO) + " kicks " + QTNAME(enemy) + 
			 "with lethal force!\n");
	    enemy->do_die(TO);
	    return;
	}

	how = "hit without effect";
        if (hitresult[0] > 0) how = "bruised";
        if (hitresult[0] > 10) how = "hurt";
        if (hitresult[0] > 20) how = "seriously injured";
        if (hitresult[0] > 40) how = "crushed";
        if (hitresult[0] > 75) how = "near death";
 
        enemy->catch_msg(QCTNAME(TO)+" kicks you hard! You are "+how+"!\n");
        tell_watcher(QCTNAME(TO)+" kicks "+QTNAME(enemy)+ 
		      " hard.\nAs a result, " + HE_SHE(enemy)+" is "
		     + how + "!\n", TO, enemy);
	
    }
    else
    {
        enemy->catch_msg(QCTNAME(TO)+" tries to kick you, but misses!\n");
        tell_watcher(QCTNAME(TO)+" tries to kick "+QTNAME(enemy)+
            ", but misses.\n",TO,enemy);
    }
}

/* Psionic stun attack.*/
void
stun(object enemy)
{
    int mental_attack; //determines whether or not the attack succeeded
    object special; //the object which does the stunning

    /* cannot stun an already stunned opponent, cannot stun if out of mana.
       so he'll kick him, instead */
    if ((present("_myrdoth_stun_", enemy)) || query_mana() < 25)
    {
	kick(enemy);
	return;
    }
	
    mental_attack = random(200) + query_stat(SS_DIS) -
	enemy->query_stat(SS_DIS) - random(40);

    if (mental_attack > 0)
    {//attack succeeded!
	special=clone_object(QUEST_DIR + "obj/myrdoth_stun");
	special->set_remove_time(mental_attack / 3);
	//the length of stun depends upon the success of the attack
	special->move(enemy);

	enemy->catch_msg("Abruptly, "+QTNAME(TO)+" bursts into your "+
			 "mind. You try your hardest to fight off "+
			 HIS_HER(TO)+  " mental assault, but " + HE_SHE(TO) +
			 " is so strong that you cannot maintain the "+
			 "physical battle, and the mental one at the same "+
			 "time!\n");
	tell_watcher(QCTNAME(enemy)+" appears to be occupied with "+
                "some sort of internal struggle.\n", TO, enemy);
    }
        
    else 
    {//attack failed
	enemy->catch_msg("Abruptly, "+QTNAME(TO)+" bursts into your "+
			 "mind. You quickly fight off his attempted mental "+
			 "assault.\n");
    }
} 
    
/* Done chiefly to prevent players from doing in, special, leave
   tactics against him: He always stuns to begin battle.
*/
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    // alarmed so that the messages will be printed after the room
    // description, etc.
    set_alarm(0.0, 0.0, &stun(ob));
}

/* Myrdoth has two special attacks. One, occurring fairly frequently,
   is a mere kick. The other, less frequent attack, is a psionic attack
   which dazes his foe. The latter is the only attack in the round, 
   while the former is in addition to all normal attacks.
*/
int
special_attack(object enemy)
{
    //attempts to stun his foe one around in 20
    if (! random(20))
    {
	stun(enemy);
	return 1; //only attack for the round
    }
	
    //uses his kick special 1 round in 6, otherwise
    if (! random(6))
    {
	kick(enemy);
    }

    return 0;//gets normal attacks in addition kicking, if applicable
}

/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, not however that it should never contain an
 *                'introduce myself' command. Personalized for Myrdoth.
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("emote nods briefly.");
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





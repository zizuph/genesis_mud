/*
 * Benton the Cannibal Corpse (BOSS NPC)
 *   Created by Lord Sorgum
 *   some code based on Mortricia's warlord (Mergula)
 * Cloned to /d/Terel/common/moor/tomb/gore_chamber.c
 *  via clone_unique so no need to do clone_unique on
 *  his weapons, per Arman AoB Feb 2022.
 *
 * updated by Lilith Jan 2022
 *   Moved the files for this npc and his area out of Sorgum's dir.
 *   Updated the file to current code standards. 
 *   Updated Tanto weapon and created Wasp.
 *   Native armour is 45 (+eq he has 85 head and 124 body.)
 * 
 * updated by Zizuph Jan 2022 
 *   Got the break bones working correctly.
 *   Broken bones can be repaired at the doctor in Last
 *     or they will heal naturally in ~1 hour.
 *
 * updated by Lilith Feb 2022
 *   Added logging of team info on Benton kills.
 *   Fixed indentation (I hope--my file editor hates me :)
 *   Added exp modifier 200 per Arman.
 *   moved cloning of weapons up in the equip function so the
 *    shield doesn't block it.
 *
 *  updated by Lilith May 2022
 *   -added various magical gear appealing to wider range of players 
 *   -boosted the hit/pen of unarmed attacks when unarmed
 *   -boosted his heals
 *   -boosted freq of damage in his specials
 *   -added an evade via query_not_attack_me()
 *  
 *  updated by Lilith June 2022
 *   -changed the paralyze so it only happens once per enemy.
 */
// As of May 26, 2022, Benton is cloning about 10 times a month.--Lilith
// see /d/Terel/log/benton_clones or benton_kills

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/seqaction";     
inherit "/lib/unique";
#include "/d/Genesis/gems/gem.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>
#include <composite.h>
#include "../local.h"

#define BASE_SIZE     200
#define NHEALS        20 
#define KILL_LOG      "/d/Terel/log/benton_kills"
#define BREAK_LOG     "/d/Terel/log/benton_breaks"
#define UNIQUE_LOG    "/d/Terel/unique/log/benton_gear"
#define FRACTURE      "/d/Terel/common/moor/obj/fracture"
#define PARA_PROP     "_i_was_paralyzed_by_Benton"

#define TANTO         "/d/Terel/unique/tanto"
#define WASP_SW       "/d/Terel/unique/wasp_sword"
#define MEAT_HOOK     "/d/Terel/unique/bmeathook"
#define VAMBRACES     "/d/Terel/unique/bvambraces"
#define DRAGON_EYE    "/d/Terel/unique/dragon_eye"
#define BREASTPLATE   "/d/Terel/unique/bbreastplate"
#define GREAVES       "/d/Terel/unique/bgreaves"

//void set_spell_prop(object ob);
public object *query_my_enemies();
void drain_all_enemies();
void heal_myself();
void paralyze_enemy(object ob);
void fireball(object ob);
void break_arm(object ob);

int nheals, been_attacked;
int prop_check = 0;

string *chats = ({
  "I'll rip out your eyes and piss in your dead skull!",
  "Resistance is futile, you will never beat me.",
  "I'll cut your head off and drink blood from your severed neck.",
  "I'll rip you in half you twerp!",
  "I'll cut off your eyelids so you can can watch your own dismemberment.",
  "I'll send your soul to eternal torment.",
  "Your lungs will explode when I cave in your chest.",
  "I am your worst reality! The Pain and Torture of humanoids is my Pleasure.",
  "My armies of zombies will inherit the earth and answer my spells.",
  "Chewing the heart of my kill builds my evil.",
  "Bodies will be emptied of blood to fill my sacrificial chalice.",
  "Your final breath will be the fearful gasp from realizing that " +
  "you will be my next meal.",
  //    "I am sodomizing your soon to be lifeless body.", 
  "I crave gore! I'll eat your guts!",
  "I love gore, blood drives me nuts",
  "I'll make your lymphatic nodes implode and your brain explode.",
  "I'll have your gonads for breakfast and your liver for lunch.",
  "Your fingers and nose will be tasty appetizers.",
  "I'll feed your guts to the hellhounds, but your ass is mine."
});

void
reset_monster()
{
    ::reset_monster();

    nheals = NHEALS;
}

void
create_monster()
{
    int i;

    default_config_npc(random(30) + BASE_SIZE);
    set_exp_factor(200); // per Arman.

    set_name("benton");
    set_living_name("benton");   
    set_title("the Cannibal, the Master of Necromancy and Leader of the "+
      "Zombie Apocalypse");	
    add_name(({"cannibal","corpse","benton"}));
    set_adj("cannibal");
    set_race_name("corpse");
    set_long(    
      "This is a savage, brutal being -- a real badass! -- and a "
      +"spellcaster to boot.\nHe seems to be a myth in size, and "
      +"his ego is even bigger.\n"
      +"There are fingers missing from his hands, and his bones look ready "
      +"to snap.\nHis body parts are crudely sewn together.\nHis face is "
      +"smashed to a pulp and fluid is drooling from an empty eye socket.\n"
      +"He is covered with bleeding sores that stink with rot "
      +"and a green infection that discharges a sickening pus.\n"
      +"You find yourself pondering what sort of power is worth the "
      +"terrible price he is paying for his."
      +"\n");

    set_gender(G_MALE);
    set_alignment(-1200);

    // Bumped up acro since he sometimes has a shield that halves it.
    set_skill(SS_ACROBAT,         150);	
    set_skill(SS_DEFENCE,         100);
    set_skill(SS_UNARM_COMBAT,     90);
    set_skill(SS_BLIND_COMBAT,    100);

    set_skill(SS_PARRY,           100);	
    set_skill(SS_WEP_SWORD,       100);
    set_skill(SS_WEP_KNIFE,       100);     
    set_skill(SS_WEP_POLEARM,     100);     	

    set_skill(SS_AWARENESS,       150);
    set_skill(SS_SPELLCRAFT,      100);
    set_skill(SS_ELEMENT_DEATH,    60);
    set_skill(SS_FORM_ABJURATION, 100);
    set_skill(SS_FORM_CONJURATION, 60);
    set_skill(SS_ELEMENT_FIRE,     60);

    // Native armour is 45.
    set_all_hitloc_unarmed(45);
    // Unarmed attacks are 35/35 except 
    // when set higher in the equip_me()
    set_all_attack_unarmed(35, 35);

    add_prop(LIVE_I_UNDEAD,      1);
    add_prop(LIVE_I_NO_CORPSE,   1);
    add_prop(LIVE_I_NO_STUN,     1);
    add_prop(LIVE_I_SEE_DARK,    1);
    add_prop(LIVE_I_QUICKNESS, 100);

    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(NPC_I_NO_FEAR,      1);
    add_prop(NPC_I_NO_LOOKS,     1);
    add_prop(NPC_I_NO_RUN_AWAY,  1);
    add_prop(BOSS_NPC,           1);

    add_prop(MAGIC_I_RES_DEATH,  40);
    add_prop(MAGIC_I_RES_LIFE,   40);
    add_prop(MAGIC_I_RES_POISON, 75);
    add_prop(MAGIC_I_RES_MAGIC,  40);    

    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_VOLUME,     100000);
    add_prop(CONT_I_MAX_WEIGHT, 350000);
    add_prop(CONT_I_MAX_VOLUME, 350000);

    trig_new("%s 'introduces'  %s", "intro_me");

    for (i = 0; i < sizeof(chats); i++) 
    {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }

    set_act_time(10);
    set_chat_time(5);
    set_cchat_time(3);    

    add_act("emote looks at you with murder in his eye-sockets.");
    add_act("emote wipes puss from his face and flings it at you!");
    add_act("emote grabs a severed limb and chews on it.");
    add_act("emote picks at his bloody sores.");
    add_act("emote snaps some bones to tenderize his meal.");
    add_act("grin");
    add_act("frown");  

    set_default_answer("say I think I will eat your tongue, first. "+
      "That way you can't talk but you can still scream.", 1);
    add_ask("vercus", "say He's an old competitor of mine--from "+
      "the cradle, you might say. Now be off with you, before "+
      "I have your tongue for dinner.", 1);	
    add_ask("menablix", "say He was trapped in his tower by a group "+
      "of Mystics and all the hedge witches they could find. "+
      "He was burned to ash, just like he deserved. Like "+
      "you deserve for bothering me.", 1); 
    add_ask(({"brother", "brothers"}), "say I had two brothers "+
      "once. Menablix was defeated in his tower near Calathin. "+
      "Vercus lives, but the familial bond was broken long "+
      "ago. Questions can get you killed, fool.", 1);
    add_ask(({"[about] [the] 'tower' [in] [calathin]"}),
      "say Menablix built a tower southeast of Calathin. It is "+
      "a ruin now. You're a nosy bugger aren't you. Perhaps "+
      "I'll be eating your nose first.", 1);
    add_ask(({"[about] [the] [old] 'hag' / 'regata'"}),
      "say Regata! Ha! You wouldn't know it but she was once "+
      "a powerful hedge witch. She helped destroy Menablix. "+
      "You ask too many questions, food.", 1);
    add_ask(({"[what] [is] [a] 'hedge' [witch] / [wizard]"}),
      "Hedge witches and wizards are people with a natural "+
      "talent for magic but no formal training... they are "+
      "self-taught. Now bugger off, would you?", 1);	  
    add_ask("book", "I am looking for the Book of Darkness.", 1);
    add_ask("ring", "The ring of the Ancients is safely locked away.", 1);
    add_ask("cannibal", "The flesh of sentients feeds my mind "+
      "and my magic. Bother me with another question and I might "+
      "eat you.", 1); 
    add_ask(({"spells","magic"}), 
      "My magic is dark and terrible--and irresistible.", 1);
    add_ask(({"mind", "brain", "brains" }), 
      "My mind is hungry and must be fed brains.", 1);
    add_ask(({"zombie", "zombie apocalypse", "apocalypse", "army", 
      "zombie army"}), 
      "say All shall answer to my magic, and become zombies who follow "+
      "me to the ends of the earth.", 1);		

    seteuid(getuid(this_object()));

    reset_monster();
	
//	equip_me();   called by the room
}

void
equip_me()
{
    object wep, arm, unarm;
	string wpath, apath, upath;
	
	wep = clone_unique(one_of_list(({ TANTO, WASP_SW, MEAT_HOOK })), 
	                   12, 0, 0, 100);
	if (wep)
    {
		wep->move(this_object());
    	write_file(UNIQUE_LOG, "Benton cloned "+ wep->short() +" " + 
        ctime(time()) + "\n"); 
        wpath = file_name(wep);		
    }		
    else
    {
	    unarm = clone_unique(one_of_list(({ VAMBRACES, DRAGON_EYE})), 
		                     10, 0, 0, 100);
	    if (unarm)
        {
            unarm->move(this_object());			
    	    write_file(UNIQUE_LOG, "Benton cloned "+ unarm->short() +" " + 
            ctime(time()) + "\n");
		    upath = file_name(unarm);
        }
    }
	
	arm = clone_unique(one_of_list(({GREAVES, BREASTPLATE})), 
	                   10, 0, 0, 100);
    if (arm)
    {
        arm->move(this_object());		
    	write_file(UNIQUE_LOG, "Benton cloned "+ arm->short() +" " + 
        ctime(time()) + "\n");
        apath = file_name(arm);
    }
	
    // The clone uniques are done, lets handle the results:
	// These are always cloned:
    add_armour(OBJDIR + "dw_boots4");    
    add_armour(OBJDIR + "dw_helmet4");
     
    if (arm)
    {   
        if (apath == BREASTPLATE)
        {   // Don't clone the dw chainmail
            command("wear breastplate");
            add_armour(OBJDIR + "dw_greaves4");     
        }
        else
        {
            // don't clone the dw greaves
            command("wear greaves");	        
  	        add_armour(OBJDIR + "dw_chainmail4");
        }
    }
    else  
    {   // clone the dw breastplate and greaves
        add_armour(OBJDIR + "dw_greaves4");     
        add_armour(OBJDIR + "dw_chainmail4");
    }

    if (wep)
    {
        command("wield all");
    } 
    
    if (!wep && !unarm)
    {
	    add_weapon(OBJDIR + "dw_sword4");
    }
    
	if (unarm)
    {   // no weapons, make fists powerful
 	    set_all_attack_unarmed(55, 55);			
        if (upath == DRAGON_EYE)
        {
			command("hold dragoneye");
        }
        command("wear all");
    }
    else
    {
        add_armour(OBJDIR + "dw_shield4");
    }        
   
}

void
intro_me(string s1, string s2)
{
    set_alarm(2.0, -1.0, "do_intro");
}

void
do_intro()
{
    command("say Thank you! I do like to know who I am going to kill!");
    command("introduce myself");
    command("grin");
}


/*
 * query_my_enemies(): written by Mortricia
 */

public object *
query_my_enemies()
{
    int i;
    object *all, *enemies;

    all = all_inventory(environment(TO));

    enemies = ({ });
    for (i=0; i<sizeof(all); i++) {
	if (living(all[i]) && all[i] != TO &&
	  member_array(TO, all[i]->query_enemy(-1)) >= 0) {
	    enemies += ({ all[i] });
	}
    }
    return enemies;
}

/* 
 * Special attack that does MAGIC_DT to all enemies.
 * This means the person tanking isn't the only one
 * who takes damage in the fight.
 */
void
drain_all_enemies()
{
    int i, dam;
    object *all;
    int pen;
    mixed *hitresult;
    int xp;

    all = query_my_enemies();

    command("laugh sadistically");
    command("reveal all");
    for (i=0; i<sizeof(all); i++) 
    {
	// damage equivalent to 1 to 2 white hits?
	pen = 300 + random(300);
	hitresult = all[i]->hit_me(pen, MAGIC_DT, TO, -1);
	tell_room(environment(TO), QCTNAME(all[i]) +
	  " is drained of lifeforce by " + QTNAME(TO) +"!\n", all[i]);
	if (all[i]->query_alignment() > -500) 
	{
	    all[i]->catch_msg("The evil within "+QTNAME(TO) +" feeds "+
	      "upon the light of your lifeforce!\n");
	}
	else
	{
	    all[i]->catch_msg(QTNAME(TO) +" feeds upon "+
	      "the darkness within you, draining your lifeforce!\n");        	
	}	
    }

    // heal 10% of hitpoints for each opponent.
    TO->heal_hp(500 + (500 * i));

}

/* Heals himself, called in the special attack */
void
heal_myself()
{
    object room;
	object *all;
	int i;

	--nheals;
	if (nheals >= 0)
	{		
	    command("emote speaks thundering words of power and heals himself.\n");
	    heal_hp(500 + random(500)); 
	    command("say I feel much better now!");
	    command("grin");
	    command("reveal all");
	}	

	all = all_inventory(TO);
	for (i =0; i <sizeof(all); i++) 
	{
	    if (function_exists("cure_poision", all[i]) ==
	      "/std/poison_effect") 
	    {
		all[i]->cure_poison(({"all"}), 100);
		command("say I thrive on poison!");
		command("say Give me some more.");
		heal_hp(1000);
		TO->set_fatigue(query_max_fatigue());
		TO->set_mana(query_max_mana());
	    }
	}
}

    /* Paralyze enemy for 10 seconds, then prevent paralysis 
     * for another 20 seconds for a full-cycle of 30s.
     */
void
unparalyze(object ob)
{
	tell_room(environment(ob), QCTNAME(ob) + " recovers from being " +
	  "paralyzed.\n", ob);
	ob->catch_msg("You recover from being paralyzed.\n");
}

void
paralyze_enemy(object enemy)
{
	object para;
	int prop;

	setuid();
	seteuid(getuid(TO));

	prop = enemy->query_prop(PARA_PROP);
	if (!prop)
	{
    enemy->add_prop(PARA_PROP, 1);		
	para = clone_object("/std/paralyze");
	para->set_stop_verb("");
	para->set_remove_time(10); // two heartbeats
	para->set_stop_fun("unparalyze");
	para->set_stop_message("The paralysis wears off.\nYou can move again.\n");
	para->set_fail_message("You are paralyzed! You can't do that right now.\n");
	para->move(enemy);
	tell_room(environment(TO), QCTNAME(TO) +" looks stonily at "+
	  QCTNAME(enemy) +" and utters some words in a guttural tongue.\n", enemy);
	enemy->catch_msg(QCTNAME(TO) +" pierces your mind with a " +
	  "stony look as he speaks in a guttural tongue. The words grate against "+
	  "your consciousness and numb your brain. You are paralyzed!\n");     
	command("cackle");
	// Enemy can't be paralyzed again.
	}
	else 
	drain_all_enemies();
}

/* Fireball special attack */
void
fireball(object enemy)
{
	int res_fire;
	string msg;

	command("reveal all");
	tell_room(environment(TO), QCTNAME(TO) +" makes a glowing " +
	  "symbol in the air.\n");
	tell_room(environment(TO), "A huge fireball screams toward " +
	  QCTNAME(enemy) + "!\n", enemy);
	enemy->catch_msg(QCTNAME(TO) +" sends a fireball screaming in "+
	  "your direction.\n");

	if (query_combat_object()->cb_tohit(-1, 100, enemy)) 
	{
	    res_fire = enemy->query_magic_res(MAGIC_I_RES_FIRE);
	    switch (res_fire)
	    {
	    case 1..10: 
		msg="What little magic resistance you have "+
		"is no match for the fireball's power. You "+
		"sustain terrible burns!"; break;
	    case 11..30:
		msg="You are somewhat resistant to the power "+
		"of the fireball, but not enough. You are "+
		"badly burned!"; break;
	    case 31..50: 
		msg="Luckily, you've got some decent fire-resistance "+
		"to protect you, but you still endure at least "+
		"half of the fireball's power!"; break;
	    case 51..100: break; 
		msg="You have a resistance to fire magic that does "+
		"a good job of protecting you from the ball of "+
		"flame, but you are still burned. Ouch!";
	    default: msg="The flames splash over you. It burns! It "+
		"burns! You feel like you're going to die!"; break ;
	    }

	    int damage = 300 + random(250);
	    damage -= damage * res_fire / 100;
	    enemy->hit_me(damage, MAGIC_DT, this_object(), -1);
	    enemy->catch_msg(msg +"\n");
	    tell_room(environment(TO), QCTNAME(enemy) + " is hit by the "+
	      "flames!\n", enemy);
	}
	else 
	{
	    enemy->catch_msg("You manage to dodge the fireball entirely.\n");
	    tell_room(environment(TO), QCTNAME(enemy) + " somehow manages "+
	      "to jump out of the fireball's path!\n", enemy);
	}
}

void
break_arm(object enemy)
{
	if (enemy->query_broken_arms() == W_BOTH)
	{
	    paralyze_enemy(enemy);
	    return;
	}

	tell_room(environment(TO), QCTNAME(TO) +" seizes " +
	  QTNAME(enemy) + " by the arm and snaps it just below " +
	  "the elbow!\n", enemy);

	enemy->catch_msg(QCTNAME(TO) +" seizes you by the arm and " +
	  "breaks it just below the elbow! OUCH!! That HURT!\n");

	// HEre we break the arm.
	int arm = random(2) ? W_LEFT : W_RIGHT;
	FRACTURE->apply_fracture(enemy, arm);
	write_file(BREAK_LOG, enemy->query_cap_name() +
	  " " + ctime(time()) + "\n");
}

void
dispell_them(object enemy)
{
	object *effects = enemy->query_magic_effects();

	if (sizeof(effects))
	{
	    object effect = one_of_list(effects);
	    string effect_name = effect->query_spell_effect_name();

	    if(effect_name)
	    {
		tell_room(environment(TO), QCTNAME(TO) +" shouts out some "+
		  "syllables in an emphatic, commanding voice!\n", TO);			
		enemy->catch_msg(QCTNAME(TO)+"'s words pierce through the "+
		  "magic of your "+ effect_name +" and dispells it "+
		  "completely! Crap!\n");				
		tell_room(environment(TO), QCTNAME(enemy) +" appears to "+
		  "be magically affected by "+ QTPNAME(TO)+ " words!\n", 
		  ({ enemy, TO }));
	    }

	    effect->dispel_effect(enemy);
	    return;		
	}  
	// do damage too.
	drain_all_enemies();		
}

int 
special_attack(object enemy)
{

	if (ENV(enemy) != ENV(TO) || enemy->query_ghost())
	{
	    TO->stop_fight(enemy);
	    return 1;
	}

	switch (random(6)) 
	{
	case 0: drain_all_enemies();
	    //		 say("DRAIN ENEMIES\n");
	    break;
	case 1: heal_myself();
	    //		 say("HEAL ME\n");
	    break;
	case 2: paralyze_enemy(enemy);
	    //	     say("PARALYZE IT\n");
	    break;
	case 3: fireball(enemy);
	    //	     say("FIREBALL\n");		
	    break;
	case 4: break_arm(enemy);
	    //	     say("BREAK ARM\n");
	    break;	  
	case 5: dispell_them(enemy);
	    //	     say("DISPELL MAGIC\n");
	    break;		
	default: command("say "+ one_of_list(chats));
	    break;
	}
	// We want normal white hits to happen, too, because Badass.
	return 0;
}


void
do_die(object killer)
{
	object gem;

	object *foos = query_enemy(-1);
	string *killers;

	if (query_hp() > 0)
	    return 0;

	if (!killer)
	    killer = previous_object();

	foos -= ({ killer });
	killers = (foos)->query_name();

	if (interactive(killer)) 
	{
	    write_file(KILL_LOG,
	      ctime(time()) +" Benton ("+ TO->query_average_stat() +") by "+ 
	      killer->query_name() +"("+ killer->query_average_stat() +
	      ") "+ (sizeof(killers) ? "with "+
		COMPOSITE_WORDS(killers) : "solo") +".\n");
	}

	// Need to come up with some good treasure for killing him since 
	// it should be a team effort. For now, giving out PC they will
	// need to fix broken arms at 25pc each plus a bit more
	MONEY_MAKE_PC(52 + random(15)) -> move(TO);

	gem = RANDOM_GEM(GEM_EXTREMELY_RARE);	 
	gem->set_heap_size(6 + random(5));
	gem->move(this_object(), 1);

	::do_die(killer);
}


void
attacked_by(object ob)
{	

	::attacked_by(ob);

	// If helpers are present, have them jump in 
	object td;
	td = present("_i_am_td", environment(TO));
	if (td)
	{ 
	    td->command("say I defend you, master!");
	    td->attack_object(ob);
	}
}	


/* Easy evade effect for Benton */
int 
query_not_attack_me(object who, int aid)
{
	if (random(4) == 0)  //  1 in 4 attacks fail
	{		
	    who->catch_msg(QCTNAME(this_object()) +" stops your attack "+
	    "with a hand motion that resembles batting away a fly.\n"); 
	    return 1;
	}
	// attack proceeds
	return 0;
}

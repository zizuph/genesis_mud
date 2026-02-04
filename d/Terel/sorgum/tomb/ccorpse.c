/*
 * A cannibal corpse
 *
 * some code based on Mortricia's warlord
 */

inherit "/std/monster";
inherit "/std/act/action";     
inherit "/std/act/seqaction";
inherit "/std/act/domove";     
     
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

#define ARM_DIR  SORGUMDIR + "armour/"
#define WEP_DIR  SORGUMDIR + "weapon/"

void set_spell_prop(object ob);
public object *query_my_enemies();
void drain_all_enemies();
void heal_myself();
void paralyze_enemy(object ob);
void fireball(object ob);
void break_arm(object ob);

int nheals;
int prop_check = 0;

string *chats = ({
"I'll rip out your eyes and piss in your dead skull!",
"Resistance is futile, you will never beat me.",
"I'll cut your head off and drink blood from your severed neck.",
"I'll rip you in half!",
"I'll cut off your eyelids so you can can watch your own dismemberment.",
"I'll send your soul to Hell.",
"Your lungs will explode when I cave in your chest.",
"I am your worst reality!  Pain and Torture of humanity.",
"My armies of zombies will inherit the earth and answer my spells",
"Chewing the heart of my kill builds my evil.",
"Bodies will be emptied of blood to fill my sacrificial chalice.",
"Your final breath will be the fearful gasp from realizing that " +
    "I am sodomizing your soon to be lifeless body.",
"I crave gore! I'll eat your guts!",
"I love gore, blood drives me nuts",
"I'll make your lymphatic nodes implode and your brain explode."
});


create_monster()
{
    int i;
    if (!IS_CLONE) return;

    set_name("Benton");
    set_living_name("Benton");     
    add_name("cannibal corpse");
    add_name(({"cannibal","corpse","benton"}));
    /*    set_short("cannibal corpse"); */
    set_long(
     
	 "This is a savage, brutal being-- a real badass!" +
	 "There are fingers missing from his hands, his bones are ready " +
	 "to snap.  His body parts are crudely sewn together.  His face " +
	 "is smashed to a pulp and fluid is drooling from an empty eye socket.  " +
	 "He is covered with bleeding sores that are beginning to stench " +
	 "and a green infection that discharges a sickening pus."
	 );

    set_adj("cannibal");
    set_race_name("Corpse");
    set_gender(0);
    set_alignment(-1000);

    nheals = 10;
     
    set_stats(({210, 200, 200, 90, 90, 100}));
    set_hp(9999);
    set_mana(9999);
    set_fatigue(9999);
     
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 100);     
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_PARRY, 100);
     
    set_all_hitloc_unarmed(45);
    set_all_attack_unarmed(20, 20);

    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME, 200000);
    add_prop(CONT_I_MAX_WEIGHT, 350000);
    add_prop(CONT_I_MAX_VOLUME, 350000);
    add_prop(MAGIC_I_RES_FIRE, 50);
    add_prop(LIVE_I_UNDEAD,100);
    add_prop(MAGIC_I_RES_POISON,100);

    trig_new("%s 'introduces'  %s", "intro_me");

    for (i = 0; i < sizeof(chats); i++) {
	add_chat(chats[i]);
	add_cchat(chats[i]);
    }

    add_act("emote looks at you with murder in his eye-sockets.");
    add_act("emote wipes puss from his face and flings it at you!");
    add_act("emote grabs a severed limb and chews on it.");
    add_act("emote pickes at his bloody sores.");
    add_act("emote snaps some of his bones.");
    add_act("grin");
    add_act("frown");    

    set_act_time(10);
    set_chat_time(2);
    set_cchat_time(2);    
     
    set_spell_prop(TO);

    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");

    prop_check = 1;

    set_whimpy(0);
}

dress_me()
{
    seteuid(getuid(this_object()));
    clone_object(ARM_DIR + "dw_helmet4")->move(TO);
    clone_object(ARM_DIR + "dw_shield4")->move(TO);
    clone_object(ARM_DIR + "dw_chainmail4")->move(TO);
    clone_object(ARM_DIR + "dw_greaves4")->move(TO);     
    clone_object(WEP_DIR + "corpse_knife")->move(TO);          

    command("wield tanto");
    command("wear armours");
    MONEY_MAKE_PC(10 + random(15)) -> move(TO);
    command("frown");
}


void
intro_me(string s1, string s2)
{
    set_alarm(2.0, -1.0, "do_intro");
}

void
do_intro()
{
    command("say Thank you! I like to know who I am going to kill!");
    command("introduce myself");
    command("grin");
}

void
spell_attack(object me, object enemy)
{
    int i;

    i = random(5);
     
    switch (i) {
    case 0:
	drain_all_enemies();
	break;
    case 1:
	heal_myself();
	break;
    case 2:
	paralyze_enemy(enemy);
	break;
    case 3:
	fireball(enemy);
	break;
    case 4:
	break_arm(enemy);
	break;	  
    default:
	command("say You are dead meat!");
	break;
    }
    call_out("set_spell_prop", 25 + random(15), me);
}

void
set_spell_prop(object ob)
{
    prop_check = 0;
    add_prop(LIVE_O_SPELL_ATTACK, ob);
    prop_check = 1;
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

void
drain_all_enemies()
{
    int i, dam;
    object *all;
    int pen;
    mixed *hitresult;
    int xp;

    all = query_my_enemies();

    command("laugh satanically");
    
    for (i=0; i<sizeof(all); i++) {
	pen = 100 + random(100);
	hitresult = all[i]->hit_me(pen, W_SLASH, TO, -1);
	if (all[i]->query_alignment() > -1000) {
	    all[i]->catch_msg("You are drained of lifeforce by " +
			      "the cannibal corpse!\n");
	    tell_room(environment(TO), QCTNAME(all[i]) +
		      " is drained of life force by " +
		      "the cannibal corpse!\n", all[i]);
/*
	    all[i]->add_exp((0 - (hitresult[0] * 50 + random(4000))), 1);
*/
	}
    }
}

void
heal_myself()
{
    object room;
    object *all;
    int i;

    --nheals;
    if (nheals == 0) {
	all = query_my_enemies();
	if (sizeof(all)) {
	    break_arm(all[random(sizeof(all))]);
	    return;
	}
    }
    
    room = environment(TO);

    tell_room(environment(TO), "The cannibal corpse speaks some " +
	      "strange words and heals himself.\n");
    heal_hp(1000 + random(400));
    command("say I feel much better now!");
    command("grin");
    all = all_inventory(TO);
    for (i =0; i <sizeof(all); i++) {
	if (function_exists("cure_poision", all[i]) ==
	    "/std/poison_effect") {
	    all[i]->cure_poison(({"all"}), 100);
	    command("say I thrive on poison!");
	    command("say Give me some more.");
	    heal_hp(200);
	    TO->set_fatigue(query_max_fatigue());
	}
    }
}

unparalyze(object ob)
{
    tell_room(environment(ob), QCTNAME(ob) + " recovers from being " +
	      "paralyzed.\n", ob);
    tell_object(ob, "You recover from being paralyzed.\n");
}

void
paralyze_enemy(object enemy)
{
    object para;

    setuid();
    seteuid(getuid(TO));
    para = clone_object("/std/paralyze");
    para->set_stop_verb("");
    para->set_remove_time(30);
    para->set_stop_fun("unparalyze");
    para->set_stop_message("The paralysis wears off.  " +
			   "You can move again.\n");
    para->set_fail_message("You are paralyzed!  You can't " + 
			   "do that right now.\n");
    para->move(enemy);
    tell_room(environment(TO), "The cannibal corpse looks stonily at " +
	      QCTNAME(enemy) + " and " +
	      "utters some words in a guttural tongue.\n");
    tell_object(enemy, "The cannibal corpse pierces your soul with a " +
		"stony look as he " +
		"speaks in a guttural tongue.  The words grate against your " +
		"consciousness and numb your brain.  You are paralyzed!\n");
     
    command("cackle");
}

void
fireball(object enemy)
{
    int stat_dex;
     
    tell_room(environment(TO), "The cannibal corpse makes a glowing " +
	      "symbol in the air.\n");
    tell_room(environment(TO), "A huge fireball explodes near " +
	      QCTNAME(enemy) + "!\n", enemy);
     
    stat_dex = enemy->query_stat(SS_DEX);
    if (random(stat_dex) < 100) {
	enemy->reduce_hit_point(random(350) + 500);
	tell_object(enemy, "You are nearly burned to a crisp " +
		    "by a fireball!\n");
	tell_room(environment(TO), QCTNAME(enemy) + " is nearly burned to " +
		  "a crisp!\n", enemy);
    }
    else {
	tell_object(enemy, "You manage to dodge the fireball and only " +
		    "get minor burns.\n");
    }
}

void
break_arm(object enemy)
{
    object fracture;

    if (present("fracture", enemy)) {
	paralyze_enemy(enemy);
	return;
    }
	
     tell_room(environment(TO), "The cannibal corpse siezes " +
	       QCTNAME(enemy) + " by the arm and snaps it right at the " +
	       "elbow!\n", enemy);

     tell_object(enemy, "The cannibal corpse siezes you by the arm and " +
		 "breaks it at the elbow!  OUCH!! That HURT!\n");
    seteuid(getuid(this_object()));
    fracture = clone_object("/d/Terel/sorgum/fracture");
    fracture->move(enemy);
    fracture->add_fracture(enemy);
    write_file("/d/Terel/sorgum/log/benton_fracture", enemy->query_name() +
	       " " + ctime(time()) + "\n");
}
     
    

void
do_die(object killer)
{
     if (interactive(killer)) {
	  write_file("/d/Terel/sorgum/log/benton_kills",
		     killer->query_name()+ " " + ctime(time()) + "\n");
     }
     ::do_die(killer);
}


/*
 * Function name: remove_prop_live_o_spell_attack
 * Description:   To prevent unauthorized removal of LIVE_O_SPELL_ATTACK.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
remove_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_o_spell_attack
 * Description:   To prevent unauthorized changing of LIVE_O_SPELL_ATTACK.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_attack_delay
 * Description:   To prevent changing of LIVE_I_ATTACK_DELAY.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_quickness
 * Description:   To prevent changing of LIVE_I_QUICKNESS.
 *                Since Mergula is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

/* Andregoras, the Knight sup guru npc coded by Morrigan in Jan 97 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include "../knight/guild.h"

inherit M_FILE

inherit "/std/act/action";

#include "killer.h"

#define GURU_LOG KLOG + "guru_log"
#define MERCYFUL "_knight_mercyful"
#define FAILED_TO_DUEL "_i_failed_to_duel"
#define DUEL_CHEATER "_i_cheated_in_duel"
#define I_CHALLENGED "_i_challenged"

int soul_id;
int i = 0;
void get_me_soul();

int query_knight_level() { return 4; }

int query_knight_sublevel() { return 10; }

string query_race_name() {
    return (calling_function() == "query_presentation" ? "Solamnian" : "human");
}

void
create_krynn_monster()
{
    set_name("andregoras");
    set_living_name("andregoras");
    set_race_name("human"); /*should be real race names only here*/
    add_name("knight");
    add_name("solamnian");
    set_title("Makar, the Master Swordsman of Solamnia");
    set_long("His hawkish features are the first thing you notice; beneath " +
      "an aged face, his piercing pale blue eyes take in everything " +
      "of his surroundings. A sharp nose leads down to a flowing " +
      "grand moustache, of solid black, the same as the wavy hair " +
      "that falls around his broad shoulders. He stands with the " +
      "measured grace of a warrior, and handles his sword as if it " +
      "were an extension of his arm. This man is quite apparently a " +
      "battle-hardened veteran of many battles. Your attention is " +
      "drawn back to his eyes, which gleam with a coldness that " +
      "unnerves you. You wonder momentarily what one like this is " +
      "doing in the Knighthood, but notice a twinge of a smile on his " +
      "lips, and realize that behind the cool demeanor is the heart " +
      "of a true Knight.\nHis tunic is decorated with the symbols of " +
      "the Order of the Sword.\n");
    set_adj("hawkish");
    add_adj("dark-haired");
    set_gender(G_MALE);
    set_introduce(1);

    set_stats(({200,200,250,140,140,160}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_PARRY,          100);
    set_skill(SS_WEP_SWORD,      100);
    set_skill(SS_AWARENESS,      65);
    set_skill(67531,             100);   

    set_alignment(1000);
    set_knight_prestige(-12);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(CONT_I_WEIGHT, 46750);

    set_default_answer("For some reason, you are ignored.\n");

    add_ask(" [about] 'duel' / 'challenge' / 'combat'", "say Now "+
      "there is something I know about. I would be more than "+
      "happy to duel with you. I fight with one sword, and those are my "+
      "terms if you wish to duel. Arms courteous of course... for your " +
      "sake.",1);
    add_ask(" [about] [arms] 'courteous' / 'mercy'",
      "say Yes, all friendly duels are known as arms courteous " +
      "because you do not kill your opponent, which is known as arms " +
      "extreme.",1);
    add_ask(" [about] 'training' / 'train'","say I train those who are " +
      "worthy.",1);
    set_act_time(5);
    add_act("kbow");
    add_act("pledge");
    add_act("ksomber");
    add_act("emote frowns at the unjust battles raging across Krynn.");
    add_act("emote declares: Vingaard has never fallen to the wretched " +
      "minions of the Dragonqueen, and so long as I am able to lift a " +
      "sword it never shall!");
    add_act("emote runs his thumb across the edge of his ancient two handed "+
      "sword, mumbling something about how he never gets to fight any duels.");
    add_act("emote muses: The final battle in which Huma and his silver mount "+
      "banished the Dragonqueen, now there was a battle.");
    set_cact_time(4);
    add_cact("emote fights effortlessly and casually, no strain apparent on " +
      "his cool face.");
    add_cact("emote nonchalantly parries a blow, and drives his opponent " +
      "back a step.");
    add_cact("emote dodges a swing with a smile and a wink.");

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());
    set_alarm(1.0, 0.0, "arm_me");
}

void
init_living()
{
    add_action("challenge", "challenge");
    add_action("challenge", "kduel1");
    add_action("challenge", "kd1");
    add_action("challenge", "kduel2");
    add_action("challenge", "kd2");
    ::init_living();
}

void
notify_you_killed_me(object ob)
{
    string str;
    object para, *ene;

#ifdef NEW_MERCY
    if (TO->query_option(OPT_MERCIFUL_COMBAT))
#else
    if (P("pal_med",TO)->query_generous())
#endif
    {
	seteuid(getuid(TO));
	para = clone_object(KOBJ + "no_die_paralyze");
	para->set_remove_time(query_knight_level() * 20 +
	  query_knight_sublevel() * 2 + 1);
	para->move(ob,1);
	ob->add_subloc("unconscious_subloc",para);
#ifdef NEW_MERCY
#else
	ob->set_all_knight_generous(1);
#endif

	ene = ob->query_enemy(-1);
	ene->stop_fight(ob);
	ob->stop_fight(ene);
	ob->add_prop(MERCYFUL, TO);
	TO->set_alignment(TO->query_alignment() +
	  F_KILL_ADJUST_ALIGN(TO->query_alignment(),
	    ob->query_alignment()));
	return;
    }

    ::notify_you_killed_me(ob);
}

int
challenge(string str)
{
    NF("Challenge whom to a duel?\n");
    if (!str)
	return 0;

    if (str != "Andregoras" && str != "andregoras")
	return 0;

    if (TP->test_bit("Krynn", 1, 6))
    {
	command("say You've already proven yourself! No need to do so "+
	  "again.");
	command("smile .");
	return 1;
    }

    if (TP->query_knight_level() == 2)
    {
	write(TO->query_The_name(TP)+" smiles at you and says: You are definitely brave, "+
	  "I'll give you that much. Grow up a bit first, though.\n");
	return 1;
    }

    if (TP->query_knight_level() == 1)
    {
	write(QCTNAME(TO)+" refuses to acknowledge your existance.\n");
	return 1;
    }

    if (TP->query_prop(DUEL_CHEATER))
    {
	TO->command("say I think not. You did not abide by the rules of the "+
	  "duel, and I will not waste my time with you until you " +
	  "learn some honour.");
	return 1;
    }

    if (TP->query_prop(FAILED_TO_DUEL))
    {
	TO->command("say You've had your chance for today, "+TP->query_name()+
	  ". Another day, perhaps.");
	TO->command("smile slightly "+TP->query_real_name());
	return 1;
    }

    if (TP->query_prop(I_CHALLENGED))
    {
	TO->command("say Yes, yes, I know. I am still waiting for you to " +
	  "begin the duel. It's only fair, as I'll undoubtedly be " +
	  "the one ending it.");
	TO->command("smile slightly");
	return 1;
    }

    TO->command("say Ahh, a good duel! I do so enjoy them. As you are the "+
      "one who challenged, I set the terms. I fight with one " +
      "sword, and one sword only. We fight until there is an " +
      "obvious winner; arms courteous... for your sake, of " +
      "course...");
    TO->command("wink . "+TP->query_real_name());
    TP->add_prop(I_CHALLENGED, 1);
    TO->command("say Ready when you are.");
    TO->command("emote spins his sword around with intimidating speed and " +
      "ability.");
    return 1;
}

void
stop_fights(object enemy)
{
    TO->stop_fight(enemy);
    enemy->stop_fight(TO);
}

void
attack_object(object ob)
{
    object sh;

    seteuid(getuid(TO));
    sh = clone_object(KOBJ + "no_die_shadow");
    if (!sh->shadow_me(ob))
	sh->remove_object();

    ::attack_object(ob);
}

void
attacked_by(object enemy)
{
    object *weapon = enemy->query_weapon(-1);
    object medal = P("pal_med", enemy);
    object sh;
    object *enemies;
    int j;


    seteuid(getuid(TO));
    sh = clone_object(KOBJ + "no_die_shadow");
    if (!sh->shadow_me(enemy))
	sh->remove_object();

    ::attacked_by(enemy);


    i = 0;

    enemies = TO->query_enemy(-1);
    if (enemies && sizeof(enemies) > 1)
    {
	TO->command("say I'm busy here! Can't you see that?");
	for (j = 0; j < sizeof(TO->query_enemy(-1)); j++)
	{
	    TO->stop_fight(enemies[j]);
	    enemies[j]->stop_fight(TO);
	    set_alarm(3.0, 0.0, "stop_fights", enemy);
	    enemies[j]->add_prop(DUEL_CHEATER, 1);
	}
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	return;
    }

    if (TO->query_hp() != TO->query_max_hp())
    {
	TO->command("say I've only recently dueled, and am not in "+
	  "the mood to do so now. Perhaps another time?");
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	return;
    }

    if (enemy->query_prop(FAILED_TO_DUEL))
    {
	TO->command("chuckle .");
	TO->command("say Eager! I like that, but you've already had your "+
	  "chance for today.");
	TO->stop_fight(enemy);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	enemy->stop_fight(TO);
	return;
    }

    if (enemy->query_prop(DUEL_CHEATER))
    {
	TO->command("say You had your chance, and you chose to fight " +
	  "dishonourably. I don't have time to deal with that " +
	  "sort of behavior.");
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	return;
    }

    if (!enemy->query_prop(I_CHALLENGED))
    {
	TO->command("say Have you gone stark raving mad? Do you just walk " +
	  "around attacking whomever you please? Get out of here " +
	  "before I teach you why I am known as the Master " +
	  "Swordsman!");
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	enemy->add_prop(DUEL_CHEATER, 1);
	return;
    }

    if (!medal ||
#ifdef NEW_MERCY
	enemy->query_option(OPT_MERCIFUL_COMBAT)
#else
	medal->query_generous() != 1
#endif
	)
    {
	TO->command("say I said the duel was arms courteous! Bah, I will not " +
	  "waste my time with blood thirsty Knights!");
	enemy->add_prop(DUEL_CHEATER, 1);
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	return;
    }

    if (!weapon || (pointerp(weapon) && sizeof(weapon) > 1) ||
      (sizeof(weapon) && weapon[0]->query_wt() != 0))
    {
	TO->command("say I told you, the terms of the duel were one sword, " +
	  "and one sword only! I do not duel those without honour.");
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	enemy->add_prop(DUEL_CHEATER, 1);
	return;
    }

    if (enemy->query_whimpy() != 0)
    {
	TO->command("say The terms of the duel were fighting until there " +
	  "was an obvious winner. Not fighting until you ran like " +
	  "a coward. I do not have time for this...");
	enemy->add_prop(DUEL_CHEATER, 1);
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	return;
    }

    TO->heal_hp(TO->query_max_hp());
    TO->command("say Good luck, "+enemy->query_name()+"!\n");
    TO->command("kc1");
}

void
get_me_soul()
{
    TO->add_cmdsoul("/d/Krynn/solamn/vin/knight/obj/solamnian_soul");
    TO->add_cmdsoul("/d/Krynn/solamn/vin/obj/kattack_special");
    TO->update_hooks();
    remove_alarm(soul_id);
}

public void
arm_me()
{
    object sword = clone_object("/d/Krynn/solamn/splains/obj/bclaymore");
    sword->set_short("ancient two-handed sword");
    sword->move(TO);
    clone_object(VARM + "full_armour")->move(TO);
    clone_object(VARM + "s_boots")->move(TO);
    clone_object(KOBJ + "npc_medal")->move(TO);
    command("wear all");
    command("wield all");
#ifdef NEW_MERCY    
    command("options mercy on");
#else
    command("mercy on");
#endif
}

int
special_attack(object enemy)
{
    int attacktype, penet;
    mixed* hitresult;
    string how, you;
    object me=TO;
    object *weapon;

    attacktype = random(9);

    if (i >= 10)
    {
	TO->command("say Well done, "+enemy->query_name()+". You are an " +
	  "excellent swordsman, and worthy of my training. One " +
	  "day you will be as fine as any swordsman in Solamnia. " +
	  "Well, save me, that is...\n");
	TO->command("grin .");
	TO->command("kdeem "+enemy->query_real_name());
	TO->stop_fight(enemy);
	enemy->stop_fight(TO);
	set_alarm(3.0, 0.0, "stop_fights", enemy);
	write_file(GURU_LOG, ctime(time()) + ", "+TP->query_name()+
	  " ("+TP->query_average_stat()+") completed the guru quest.\n");
	enemy->set_bit(1, 6);
	return 1;
    }

    if (attacktype == 1 || attacktype == 4 || attacktype == 5)
    {
	TO->command("sp");
	i = i + 1;
    }
    else if (attacktype == 2)
    {
	i = i + 1;
	if (enemy->query_knight_level() < 4 &&
	  enemy->query_knight_sublevel() < 10)
	{
	    enemy->catch_msg(QCTNAME(TO)+" feigns with his sword, and you " +
	      "fall for the move, realizing only a second too " +
	      "late your mistake!\n\nYou find yourself " +
	      "looking up the length of a one meter blade into "+
	      "the piercing blue eyes. Andregoras' face breaks "+
	      "into a grin as he looks at you, and you feel a " +
	      "bit of relief.\n");
	    tell_room(E(TO), enemy->query_The_name(TP)+" pales slightly as he "+
	      "is suddenly staring down the blade of "+
	      TO->query_the_name(TP)+", and into his piercing blue " +
	      "eyes. "+TO->query_The_name(TP)+"' face breaks into a " +
	      "grin.\n", enemy);
	    TO->stop_fight(enemy);
	    enemy->stop_fight(TO);
	    set_alarm(3.0, 0.0, "stop_fights", enemy);
	    TO->command("say You will be a fine Knight some day, " +
	      enemy->query_name() + ". Feel free to challenge me " +
	      "again when you feel ready.\n");
	    enemy->add_prop(FAILED_TO_DUEL, 1);
	    return 1;
	}
	else
	{
	    enemy->catch_msg(QCTNAME(TO)+" feigns with his sword, and you " +
	      "almost fall for it, but at the last second " +
	      "realize your mistake and bring your blade up " +
	      "to parry the following attack.\n");
	    TO->command("say Well done! Well done, indeed!");
	    return 1;
	}
    }
    else if (attacktype == 3)
    {
	i = i + 1;
	if (enemy->query_skill(SS_WEP_SWORD) < 90)
	{
	    weapon = enemy->query_weapon(-1);
	    if (!weapon || (pointerp(weapon) && sizeof(weapon) > 1))
	    {
		TO->command("say I said that the terms of the duel were arms " +
		  "courteous and with one sword as the used " +
		  "weapon!\n");
		TO->command("emote scowls and says: Come back when you have " +
		  "learned how to honour the terms of the duel!");
		enemy->add_prop(DUEL_CHEATER, 1);
		TO->stop_fight(enemy);
		enemy->stop_fight(TO);
		set_alarm(3.0, 0.0, "stop_fights", enemy);
		return 1;
	    }
	    else
	    {
		enemy->catch_msg(QCTNAME(TO)+" strikes your hand with the " +
		  "flat of his blade, the skill of the blow " +
		  "causing you to drop your sword!\n");
		tell_room(E(TO), TO->query_The_name(TP)+" strikes "+
		  enemy->query_the_name(TP) + "'s hand with the flat " +
		  "of his blade. "+enemy->query_The_name(TP)+" drops "+
		  POSSESSIVE(enemy)+" sword!\n", enemy);
		weapon->move(E(TO));
		TO->stop_fight(enemy);
		enemy->stop_fight(TO);
		set_alarm(3.0, 0.0, "stop_fights", enemy);
		TO->command("emote chuckles and says: Well fought, you " +
		  "promise to be a great warrior, come back when " +
		  "you are a little more skilled.");
		TO->command("kbow "+enemy->query_real_name());
		return 1;
	    }
	}
	enemy->catch_msg(QCTNAME(TO)+" strikes your hand with the flat of " +
	  "his blade and you almost drop your sword. You feel " +
	  "renewed respect for this Knight as you marvel at " +
	  "his skill with the sword.\n");
	return 1;
    }

    return 0;
}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Andregoras", killer);
    return 0;
}


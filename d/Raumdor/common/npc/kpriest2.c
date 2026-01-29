/* Khiraa Priest, Sarr */

/* Made into a questgiver.
 *
 * It currently start 4 quests, and reward 3 of them:
 * - Khiraa entrance quest  (Rewarded elsewhere)
 * - Sacrificial dagger quest
 * - Black book quest
 * - Spectre medallion quest (Currently closed, under review)
 *
 * The questgiver also points the player in the right
 * direction of the other two quests.
 *
 * - Neutralized the quests for the possibility of making them
 *   repeatable.   1/7-10 - Nerull.
 *
 * Nerull
 *
 * 2017-05-21 Malus: Aesthetic changes. Some details noted inline.
 *
 */

#include "defs.h"
inherit "/d/Raumdor/std/monster";

#define BLACK_BOOK_QUEST "_black_book_quest_raumdor"

object friend;

void
create_monster()
{
    ::create_monster();
	
	seteuid(getuid());
	
    set_name("human");
    set_adj("red-robed");
    add_adj("contemplative");
    set_gender(0);
    set_race_name("human");
    set_stats(STAT_ARRAY(110));
    set_alignment(UNDEAD_ALIGN);
    set_long(
      "He is a strange looking individual, wrapped in all red, and wearing " +
      "many exotic medallions. Looking into his hood, you see an aged old " +
      "man with wrinkled skin and piercing black eyes. He looks focused on " +
      "some task.\n");
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 6);
    add_prop(LIVE_I_SEE_INVIS, 6);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    set_act_time(5);
    add_act("grumbles to himself about his missing dagger.");
    add_act("emote turns his hood toward you and narrows his eyes.");
    add_act("emote adjusts his robe.");
    add_act("emote paces pensively.");

    set_default_answer(
      "say What are you asking about? Are you here for a task?", 1);
    add_ask(({"quest", "task", "tasks", "help", "aid", "join"}),
      "@@task_response@@");
    add_ask(({"dagger"}), "@@dagger_response@@");
	//add_ask(({"altar"}), "@@altar_response@@");
    add_ask("pass",
      "say There is a pass through the mountains, at the northeast end of " +
      "that wretched path.\n",
      1);
    add_ask(({"dungeon", "old dungeons"}),
      "say Under the ruins along that loathsome road to Drakmere, yes. It " +
      "can be a good place to find...  pieces.\n",
      1);
    add_ask("drakmere", "say I will not speak of that obnoxious city.");
    add_ask("pieces", "say That is none of your concern.", 1);
    add_ask("ruins", "say We leave no refuge for our foes.", 1);
    add_ask(({"foe", "foes"}),
      "say All those who stand against the Nameless One, of course.", 1);
    add_ask(({"nameless one", "lord of dead"}),
      "say His power grows. The Netherworld awaits.", 1);
    add_ask(({"netherworld"}),
      "say It is the realm that lies between here and Hell, ruled by the " +
      "Nameless One.",
      1);
    add_ask("hell",
      "say You do not know of Hell? I am sure we could find someone to " +
      "educate you.",
      1);
    add_ask("temple",
      "say The temple is for followers of the Nameless One. Are you here to " +
      "seek the Khiraa?",
      1);
    add_ask(
      ({"service", "higher service", "worth", "serve", "join", "khiraa"}),
      "say This temple embodies the Khiraa, servants of the Nameless One. " +
      "Mortals could once prove their worth to be considered for service. " +
      "That time has passed, but a test is sill avaiable to those who would " +
      "dare.",
      1);
    add_ask("beast",
      "say The Beast Lord, they call him. It. Who knows what it was before " +
      "the necromancer achieved his contortions.",
      1);
    add_ask(
      "lord", "say Many are called lords. I serve the Lord of the Dead.", 1);
    add_ask(({"necromancer", "necromancers", "sorcerers"}),
      "say Necromancers are sorcerers of death magic. Their patience should " +
      "not be tested.",
      1);
    add_ask(({"magic", "death magic"}),
      "say You will not receive such information from me.", 1);
    add_ask(({"test", "dare"}), "@@test_response@@");
    /*
    add_ask(({"book"}),
      "say There is a chest somewhere in the undead-festered temple of " +
      "Khiraa. In it, you will find a black book among...other things. Fetch " +
      "it for me and you will be rewarded. It is said that a Khiraa death " +
      "knight still have the key to the chest. My other book I seek..a " +
      "beastlord somewhere near Drakmere may have more information about " +
      "it.\n",
      1);
    add_ask(({"medallion"}),
      "say Somewhere in the cursed forest you find dreadful spectres. One of " +
      "them found my..medallion..but I do not know which one. Find it, and " +
      "bring it to me, and you will be rewarded.\n",
      1);
    */

    equip(COMMON_WEP_DIR + "wstaff");
}

string
test_response()
{
    if (TP->test_bit("Raumdor", 3, 2))
    {
        set_alarm(2.0, 0.0, &command("say Your reputation precedes you. You " +
                                     "have already completed the test."));
    }
    else
    {
        set_alarm(2.0, 0.0,
          &command("say Only a guardian of Hell may guide you further, and " +
                   "won't do so unless you first pay homage. It happens to " +
                   "be that such a warrior lies in wait, hidden beneath " +
                   "Drakmere. Do not expect it to welcome you if you go " +
                   "empty-handed. Instead, go to the Chamber of Blood here " +
                   "in the temple. Search there for a suitable offerring."));
    }
}

string
task_response()
{
    float delay = 2.0;
	
    set_alarm(delay, 0.0, &command("hmm"));
	
    delay += 2.0;
	
    if (!TP->test_bit("Raumdor", 3, 0))
    {
        set_alarm(delay, 0.0,
          &command(
            "say You would not go unrewarded if you found my dagger."));
        delay += 2.0;
    }
	
    if (!TP->test_bit("Raumdor", 3, 2))
    {
        set_alarm(
          delay, 0.0, &command("say Higher service is no longer available to " +
                               "mortals, but you may some still seek to " +
                               "demonstrate their worth to the Khiraa."));
        delay += 2.0;
    }
	
    set_alarm(
      delay, 0.0, &command("say I have heard the beast that dwells in the " +
                           "old dungeons is in search of something."));
    delay += 2.0;
	
	
	/*set_alarm(
      delay, 0.0, &command("say Also, there is an altar somewhere "
							   +"below Khiraa Doombuards once used for collecting "
							   +"magical purple orbs..."));	*/			   
    delay += 2.0;
	
	
    set_alarm(
      delay, 0.0, &command("say Otherwise, you should prepare yourself for " +
                           "The Netherworld. The Nameless One awaits."));
}


string
altar_response()
{
    set_alarm(2.0, 0.0,
        &command("say The altar trigger a ritual that the Doomguards of Khiraa "
		          +"once used to bolster their defence against cursed "
 		          +"holy clerics and various paladin orders and their "
				  +"magic. Offer an item sufficiently worthy of the altar, and "
				  +"bring...whatever you receive back to me, and "
				  +"you will be rewarded."));
}


string
dagger_response()
{
    if (TP->test_bit("Raumdor", 3, 0))
    {
        set_alarm(
          2.0, 0.0, &command("say Yes, you found it and were generously " +
                             "rewarded. Don't pretend otherwise."));
    }
    else
    {
        set_alarm(2.0, 0.0,
          &command("say My dagger must have fallen when I ventured to the " +
                   "old dungeons over the pass. It is essential to my work. " +
                   "Return it to me and you will not regret it."));
    }
}

void
do_die(object killer)
{
    // clone_object(COMMON_WEP_DIR + "staff_of_ages2")->move(TO, 1);
    log_file("occultist_killed",
      capitalize(killer->query_real_name()) + " (" +
        killer->query_average_stat() + "), killed the occultist at " +
        extract(ctime(time())) + ".\n");

    ::do_die(killer);
}

int
reward_dagger(object player, object ob)
{
    if (present(player, environment()) && present(ob, TO))
    {
        set_alarm(0.0, 0.0,
          &seen_emote("quickly tucks the " + ob->short(player) + " away."));
        ob->remove_object();
        if (!player->test_bit("Raumdor", 3, 0))
        {
            player->catch_msg("You feel more experienced!\n");
            player->add_exp_quest(500);
            player->set_bit(3, 0);
        }
        set_alarm(2.0, 0.0,
          &command("say Ahh, yess. I can once again perform my rituals!"));
    }
    else
        command("confused");
}


int
reward_altar(object player, object ob)
{
    if (present(player, environment()) && present(ob, TO))
    {
        set_alarm(0.0, 0.0,
          &seen_emote("cracks the " + ob->short(player) + " like an egg, and "
		  +"spill some of its content onto a grey robe that suddenly turns purple!"));
		  
        ob->remove_object();
		
        if (!player->test_bit("Raumdor", 3, 6))
        {
            player->catch_msg("You feel more experienced!\n");
            player->add_exp_quest(2500);
            player->set_bit(3, 6);
			
			log_file("altar_orb_quest_q",
              capitalize(player->query_real_name()) + " (" +
                player->query_average_stat() +
                "), Delivered the Purple orb(questxp) at " +
                extract(ctime(time())) + ".\n");
        }
		else
		{
			player->catch_msg("You are rewarded with some general experience!\n");
            player->add_exp_general(2500);
			
			log_file("altar_orb_general_q",
              capitalize(player->query_real_name()) + " (" +
                player->query_average_stat() +
                "), Delivered the Purple orb(general xp) at " +
                extract(ctime(time())) + ".\n");
		}
		
        set_alarm(2.0, 0.0,
          &command("say Excellent! I would love to have more of these orbs "
		  +"if possible, as the content within them is...very valuable "
		  +"to me! Very well, I guess a proper reward is in order..."));
		
        seteuid(getuid());
		
		object purp_robe;
		  
		purp_robe = clone_object(QUEST_DOOMGUARD_ROBE);
		purp_robe->move(TP, 1);
		
		set_alarm(2.0, 0.0,
          &TP->catch_tell("The "+short()+" gives you a dim purple robe!\n"));
    }
    else
        command("confused");
}


void
enter_inv(object ob, object from)
{
    ::enter_inv();
    if (from)
    {
        if (MASTER_OB(ob) == QUEST_DAGGER_FILE)
            reward_dagger(from, ob);
		
		if (MASTER_OB(ob) == QUEST_ALTAR_OBJ)
            reward_altar(from, ob);
		

        /*
        if (ob->short() == "black dusty book")
            set_alarm(2.0, 0.0, "reward_book", from);
        */
        // Currently under review.  Nerull
        /*if(ob->short() == "small ghostly medallion")
            set_alarm(2.0,0.0,"reward_spectre_med",from);
        */

        // Correction quest.
        /*
        if (ob->short() == "pink white medallion")
            set_alarm(2.0, 0.0, "reward_white_med", from);
        */

        if (!ob)
            return;

        set_alarm(0.0, 0.0,
          &seen_emote("lets the " + ob->short(from) + " fall to the ground."));
        ob->move(E(TO), 1);
    }
}




int
reward_spectre_med(object obj)
{
    if (present(obj, environment()))
    {
        // The quest is repeatable, except it gives 15k general xp.
        // Reward for repeating the quest removed by order of AoB.
        // 1/7-10.
        /*if(obj->test_bit("Raumdor",3,4))
        {
            command("emote says: Thank you! Splendid work!");
            obj->catch_msg("You feel Generally more experienced.\n");
            obj->add_exp_general(15000);

            log_file("spectre_quest_g",
    capitalize(obj->query_real_name()) +
    " (" + obj->query_average_stat() + "), Delivered the spectre
    medallion(generalxp) at " +
            extract(ctime(time())) + ".\n");
        }*/

        if (obj->test_bit("Raumdor", 3, 4))
        {
            command("emote says: Thanks again!");
        }

        else
        {
            command("emote says: Thank you! Excellent work!");
            obj->catch_msg("You feel Questwise more experienced.\n");
            obj->add_exp_quest(5000);
            obj->set_bit(3, 4);

            log_file("spectre_quest_q",
              capitalize(obj->query_real_name()) + " (" +
                obj->query_average_stat() +
                "), Delivered the spectre medallion(questxp) at " +
                extract(ctime(time())) + ".\n");
        }
    }
}

// For fixing players that was given double xp on 3.5 quest. They will not be
// able to get the reward (or do) the Spectre medallion quest (3.4), which
// gives
// the same qxp as 3.5.
int
reward_white_med(object obj)
{
    if (present(obj, environment()))
    {
        // Testing.
        if (obj->test_bit("Raumdor", 3, 4))
        {
            command("emote says: Thank you! You are fixed!");
        }

        else
        {
            command("emote says: Thank you! You should be fixed!");
            obj->catch_msg("You feel No more experienced.\n");
            obj->set_bit(3, 4);

            log_file("fixing_quest_q",
              capitalize(obj->query_real_name()) + " (" +
                obj->query_average_stat() +
                "), Delivered the big white medallion (zero xp, questbit 3.4 " +
                "set) at " +
                extract(ctime(time())) + ".\n");
        }
    }
}

int
reward_book(object obj)
{
    if (present(obj, environment()))
    {
        // The quest is repeatable, except it gives 15k general xp.
        // Reward for repeating the quest removed by order of AoB.
        // 1/7-10.

        /*if(obj->test_bit("Raumdor",3,5))
        {
            command("emote says: Thank you! Splendig work!");
            obj->catch_msg("You feel Generally more experienced.\n");
            obj->add_exp_general(5000);

            log_file("blackbook_quest_g",
    capitalize(obj->query_real_name()) +
    " (" + obj->query_average_stat() + "), Delivered the black
    book(generalxp)
    at " +
            extract(ctime(time())) + ".\n");
        }*/

        if (!obj->query_prop(BLACK_BOOK_QUEST))
        {
            command(
              "emote says: Thanks, but next time, make sure YOU kill the " +
              "Death knight.\n");
            return 1;
        }

        if (obj->test_bit("Raumdor", 3, 5))
        {
            command("emote says: Thanks once again.");
        }

        else
        {
            command("emote says: Thank you! Excellent work!");
            obj->catch_msg("You feel more experienced.\n");
            obj->add_exp_quest(5000);
            obj->set_bit(3, 5);
            obj->remove_prop(BLACK_BOOK_QUEST);

            log_file("blackbook_quest_q",
              capitalize(obj->query_real_name()) + " (" +
                obj->query_average_stat() +
                "), Delivered the black book(questxp) at " +
                extract(ctime(time())) + ".\n");
        }
    }
}

int
special_attack(object enemy)
{
    int sp;
    if (random(2))
        return 0;
    if (!friend && random(3))
    {
        if (TO->query_mana() < 100)
            return 0;

        TO->add_mana(-100);

        friend = clone_object(COMMON_NPC_DIR + "imp");
        tell_room(E(TO), QCTNAME(TO) + " chants strange magical words.\n");
        friend->move_living("M", E(TO));
        TELL_SEEN(friend,
          QCNAME(friend) + " steps out from another dimension!\n");
        TO->team_join(friend); 
        friend->command("kill " + OB_NAME(enemy));
        return 1;
    }
    tell_room(E(TO),
      "The red-robed contemplative male human cackles as a beam of black " +
      "light strikes " +
        QCTNAME(enemy) + " in the chest!\n",
      enemy);
    enemy->catch_msg(
      "The red-robed contemplative male human cackles as a beam of black " +
      "light strikes you in the chest!\n");
    tell_room(E(TO), QCTNAME(enemy) + " seems drained of life!\n", enemy);
    enemy->catch_msg("You feel drained of life!\n");
    tell_room(
      E(TO), "The red-robed contemplative male human seems restored!\n");
    enemy->heal_hp(-600);
    TO->heal_hp(300);
    return 1;
}

int
add_prop_live_i_attack_delay(mixed val)
{
    return 1;
}

int
add_prop_live_i_stunned(mixed val)
{
    return 1;
}

int
add_prop_live_as_attack_fumble(mixed val)
{
    return 1;
}

public int
query_panic()
{
    return 0;
}

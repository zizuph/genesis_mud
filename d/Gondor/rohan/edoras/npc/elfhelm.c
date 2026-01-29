/*
 * Elfhelm, Third Marshal of the Riddermark
 * Quest npc and Captain of the King's Eored
 *
 * Recoded by Elessar, July 28 1999
 * Now summons help when attacked,
 * logs killers and refuses to help them later.
 * Thanks to Gnadnar for much inspiration with her Carastur code.
 * Gwyneth, November 10, 2000
 * Added gold dust to his inventory.
 * Gwyneth, 8/7/02, Commented out special attack as players were
 * being provided with a seemingly endless supply of npcs.
 */

inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier.c";
inherit "/d/Gondor/common/lib/logkill";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define MIN_STAT 60
#define EDORAS_GUARD (EDORAS_DIR + "npc/edoras_guard")
#define OFFICE_ROOM ("/d/Gondor/rohan/edoras/rooms/boffice2")
#define QUERY_KILLER(ob) (EDORAS_MASTER->query_enemy(ob))
#define ADD_KILLER(ob) (EDORAS_MASTER->add_enemy(ob, "Elfhelm"))

int     tour_done(object player);

object  harding,
        giver,
        sword;
string  killer;
int     set_action;

void	  do_die(object killer);
void    clone_guards(object attacker);
void    attacked_by(object ob);
//int     special_attack(object victim);

int	Guards_summoned;

void
create_guard()
{
    set_living_name("elfhelm");
    set_name("elfhelm");
    add_name(({"marshal", "captain", "rohirrim"}));
    set_adj(({"tall","golden-haired"}));
    set_long(BSN("This is Elfhelm the Marshal, the Captain of the King's "
      + "Eored of the riders of Rohan. Even among the Rohirrim, he is among "
      + "the tallest of men. His golden hair is braided on his shoulders."));
    set_title("the Marshal, Captain of the King's Eored");
    default_config_npc(95);
    set_base_stat(SS_CON,135);
    set_base_stat(SS_STR,145);
    set_base_stat(SS_DEX, 130);
    set_base_stat(SS_DIS,155);

    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 85);
    set_skill(SS_AWARENESS, 80);
    set_alignment(850);
    set_chat_time(5);
    add_chat("Orders may come at any moment!");
    add_chat("Some of our scouts report that they have seen uruk-hai on the plains.");
    add_chat("I need information about the orc bands on the plains.");
    add_chat("If you are looking for work, traveller, you might ask me for a task.");
    add_chat("I need hard facts to verify the scout reports.");
    add_cchat("Forth Eorlingas!");
    set_default_answer(BS("The Marshal says: I do not know what you mean. " +
      "Perhaps you would like to ask for a task?\n"));
    add_ask(({"about task","about tasks","for tasks","for a task","about a task",
      "for task","task","quest","job","tasks","quests","jobs"}),
      VBFC_ME("give_task"));
    add_ask(({"name","about name"}),VBFC_ME("asked_name"));
    add_ask(({"rohan","about rohan"}),VBFC_ME("inform_rohan"));
    add_ask(({"gondor","about gondor"}),VBFC_ME("inform_gondor"));
    add_ask(({"harding","about harding"}),VBFC_ME("ask_harding"));
    add_ask(({"duty","about duty"}),"say Our Duty is to protect " +
        "the Eorlingas!", 1);
    add_ask(({"dust", "gold dust", "gold"}), "say I won't part with " +
        "it for anything!", 1); 
    set_action = 0;
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    /* really tall and lean */
    add_prop(CONT_I_HEIGHT, 204);
    add_prop(CONT_I_WEIGHT, 81900);
}

void
test_tour(object player)
{
    object note;

    if (note = present("Minas_Tirith_Tour_Note",player))
    {
        if (note->query_tour_no()!=3) return;
        note->set_tour_done();
        set_alarm(5.0, 0.0, &tour_done(player));
    }
    return;
}

void
init_living()
{
    ::init_living();
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return;
    }
    test_tour(TP);

    if (set_action)
        add_action("report_uruk","report");
}

public void
introduce_me(object tp = TP)
{
    if (!objectp(tp) || !present(tp, ENV(TO)) ||
        tp->query_met(query_name()))
        return;
    if (QUERY_KILLER(tp))
    {
        command("glare " + OB_NAME(tp));
    }
    else if (!(tp->query_met(query_real_name())))
    {
        command("say My name is Elfhelm, and I am the "
          + "Captain of the King's Eored.");
        command("introduce me");
    }
}

public string
asked_name()
{
    introduce_me(TP);
    return "";
}

public void
add_introduced(string str)
{
    object  tp = find_player(str);

    if (!objectp(tp) || !present(tp, ENV(TO)) ||
        tp->query_met(query_name()))
        return;

    set_alarm(3.0, 0.0, &introduce_me(tp));
}

void
arm_me()
{
    FIX_EUID
    clone_object(EDORAS_DIR + "obj/guardsword")->move(TO);
    command("wield sword");
    clone_object(EDORAS_DIR + "obj/corslet")->move(TO);
    command("wear armour");
    clone_object(EDORAS_DIR + "obj/roshield")->move(TO);
    command("wear armour");
    clone_object(OBJ_DIR + "gdust")->move(this_object());
}

string
inform_gondor()
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return "";
    }
    command("say Gondor has been our ally since the days of Eorl.");
    command("say Since they are so much closer to Mordor,");
    command("say they have more problems than we do.");
    command("say They even lost Ithilien and Osgiliath to the Enemy!");
    command("say But if Mundburg falls, that will be the end of Rohan, too.");
    command("sigh");
    return "";
}

string
inform_rohan()
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return "";
    }

    command("say Rohan! Ah, our wonderful land! Green plains, perfect horse country!");
    command("say Look at the map, and you will see Rohan, how it stretches ");
    command("say from the Isen and the Gap of Rohan in the West to the Anduin ");
    command("say and Mouths of the Entwash in the East, from Fangorn to the White ");
    command("say Mountains in the South. Too bad that the plains are full of orcs, ");
    command("say nowadays! ");
    command("sigh");
    return "";
}

void
west_emnet_uruk()
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return;
    }
    if (TP->query_prop("_elfhelm_uruk_quest"))
    {
        command("peer " + TP->query_name());
        command("say Didn't I already assign you a task?");
        command("say Go and find Harding!");
        command("say If you have further questions, he can help you.");
        command("say I have other business to do! Dismissed! ");
        return;
    }
    if (TP->query_average_stat() < MIN_STAT)
    {
        command("peer " + TP->query_real_name());
        command("say I do not think that you are experienced enough for this task.");
        command("say But we need all the help we can get.");
        command("say But be warned, this is dangerous!");
    }
    command("say We need information about the plains!");
    command("say Some scouts have reported that they saw uruk-hai on the plains, ");
    command("say but some ... ");
    command("sigh deeply");
    command("say Well, some who have the ear of Theoden King, say that there are ");
    command("say no uruk-hai on the plains, only some scattered orcs! ");
    command("say So we need proof that there are really organized bands there ");
    command("say that are led by uruk-hai! ");
    command("say Probably, it would be best if you found Harding.");
    command("say He was the leader of the last patrol that reported uruk-hai.");
    command("say He can tell you where you have to look!");
    TP->add_prop("_elfhelm_uruk_quest",1);
    START_QUEST(TP, "ELFHELM URUK QUEST");
    if (!objectp(harding))
    {
        if (!objectp(harding = find_living("harding")))
        {
            harding = clone_object(EDORAS_DIR + "npc/harding.c");
            harding->arm_me();
        }
        harding->move_living("to the gates", EDORAS_DIR + "guard_e");
    }
}

string
give_task()
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return "";
    }

    if (!TP->test_bit("Gondor", GONDOR_GROUP, ELFHELM_URUK_BIT)) 
        west_emnet_uruk();
    else 
        command("say I'm sorry - I have no more tasks for you.");
    return "";
}

void
reward_uruk_quest(object player)
{
    int rew;
    if (!present(player,ENV(TO)))
        return;

    rew = TP->query_exp();
    if(rew > ELFHELM_URUK_EXP)
        rew = ELFHELM_URUK_EXP;
    player->remove_prop("_elfhelm_uruk_quest");
    player->remove_prop("_elfhelm_uruk_quest_leftover");
    player->remove_prop("_elfhelm_uruk_quest_weapon");
    player->remove_prop("_elfhelm_uruk_quest_report");
    player->set_bit(GONDOR_GROUP, ELFHELM_URUK_BIT);
    player->adjust_alignment(200);
    player->add_exp_quest(rew);
    LOG_QUEST(player, rew, "ELFHELM URUK QUEST");
    tell_object(player,"You feel much more experienced!\n");
}

void
test_uruk_quest(object player)
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        command("say Eorlingas do not deal with murderers!");
        command("say Get out of here!");
        return;
    }
    if (TP->test_bit("Gondor", GONDOR_GROUP, ELFHELM_URUK_BIT))
    {
        command("say We went through this once before, didn't we?");
        command("Dismissed!");
        return;
    }

    if (player->query_prop("_elfhelm_uruk_quest_leftover"))
    {
        if(player->query_prop("_elfhelm_uruk_quest_weapon"))
        {
            if(player->query_prop("_elfhelm_uruk_quest_report"))
            {
                command("say This information will help us much!");
                command("thank " + player->query_name());
                reward_uruk_quest(player);
            } 
            else
            {
                command("say Very interesting!");
                command("say But where did you meet with the uruk?");
                command("say Can you 'report' where you found him?");
            }
        }
        else
        {
            command("say Now that I know there are uruks on the plains, ");
            command("say I still need to know what weapons they have!");
            command("say I hope you brought the weapon along!");
            command("say Can I have it, please?");
        }
    }
    else
    {
        command("hmm");
        command("say I need a proof that there are really uruk-hai on the plains!");
        command("peer " + player->query_name());
        command("say Hard, undeniable facts! That is what I need! Can you deliver that?");
    }
}

void
give_back(object ob, object from)
{
    if (!objectp(ob) || !objectp(from))
        return;

    command("say What am I supposed to do with this?");
    command("peer " + TP->query_name());
    command("give " + OB_NAME(ob) + " to " + from->query_real_name());
    if (from->query_prop("_elfhelm_uruk_quest"))
    {
        command("say This is not really what I was looking for!");
    }
    else
    {
        command("say If you want to help us, ask for a task here first!");
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);

    if (!objectp(from) || !objectp(ob) || !interactive(from))
        return;
    
    add_action("report_uruk","report");
    set_action = 1;
    
    if (!from->query_prop("_elfhelm_uruk_quest"))
    {
        set_alarm(1.0, 0.0, &give_back(ob, from));
        return;
    }

    command("say Ah, there you are! Did you complete the task I gave you?");
    if (ob->query_prop("_elfhelm_uruk_quest_leftover"))
    {
        command("emote examines " + LANG_ADDART(ob->query_name()) + " closely.");
        command("gasp");
        command("say It is really " + LANG_ADDART(ob->query_name()) + " of an uruk!");
        from->add_prop("_elfhelm_uruk_quest_leftover",1);
        test_uruk_quest(from);
        return;
    }
    if (ob->query_prop("_elfhelm_uruk_quest_weapon") ||
        ob->query_prop("_uruk_quest_weapon") == from->query_real_name())
    {
        command("emote examines " + LANG_ADDART(ob->query_name()) + " closely.");
        command("whistle");
        command("say That is an excellent " + ob->query_name() + ", even though it is of orkish fabrication!");
        from->add_prop("_elfhelm_uruk_quest_weapon",1);
        giver = from;
        ob->remove_object();
        test_uruk_quest(from);
        return;
    }
    if (ob->query_prop("_uruk_quest_weapon"))
    {
        command("emote examines " + LANG_ADDART(ob->query_name()) + " closely.");
        command("whistle");
        command("say That is an excellent " + ob->query_name() + ", even though it is of orkish fabrication!");
        command("say But I do not believe that you killed an uruk wielding this sword!");
        command("say Either you are trying to deceive me, or you had help!");
        command("say So, if I shall believe in your report, 'name' the valiant person that killed the uruk!");
        giver = from;
        sword = ob;
        killer = ob->query_prop("_uruk_quest_weapon");
        add_action("name_killer", "name");
        return;
    }
    set_alarm(1.0, 0.0, &give_back(ob, from));
}

string
ask_harding()
{
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        return "";
    }
    if(TP->query_prop("_elfhelm_uruk_quest"))
    {
        command("say Harding? Well, he returned from the patrol last night.");
        command("say Now he is probably on stand-by duty at the city gate. ");
        command("shrug");
        command("say He must be in the town, that is all I know for certain.");
        command("say If you do not find him at the gate, look around a bit.");
        return "";
    }
    command("say Harding? What do you want from him?");
    command("say I do not think that his whereabouts are any of your business!");
    command("peer suspiciously");
    command("say Dismissed!");
    return "";
}

void
check_presence(string killer)
{
    if (present(killer,ENV(TO)))
    {
        command("say Ah, congratulations!");
        command("shake " + killer);
        giver->add_prop("_elfhelm_uruk_quest_weapon",1);
        sword->remove_object();
        test_uruk_quest(giver);
    }
    else
    {
        command("say Well, why is " + killer + " then not here?");
        command("peer " + giver->query_real_name());
        command("say I do not think that I can rely on your report.");
        command("say I need hard facts, not hearsay!");
        command("give sword to " + giver->query_real_name());
        command("say Take this and be gone!");
    }
}

int
report_uruk(string str)
{
    string dummy;
    if (QUERY_KILLER(TP))
    {
        command("glare " + OB_NAME(TP));
        command("say I do not take reports from enemies!");
        return 1;
    }

    if (!strlen(str))
    {
        NF("Report what?\n");
        return 0;
    }

    if (TP != giver)
    {
        command("say I didn't talk to you, did I?");
        command("peer " + TP->query_real_name());
        return 1;
    }
 
    str = lower_case(str);

    if (sscanf(str,"%swest emnet%s",dummy, dummy) > 0)
    {
        TP->add_prop("_elfhelm_uruk_quest_report",1);
        command("say In the West Emnet? So close to Edoras?");
        command("say This is bad news indeed!");
        set_action = 0;
        test_uruk_quest(TP);
    }
    else if(str == killer)
        check_presence(killer);
    else
    {
        command("say I don't understand you!");
        command("say I need to know where you met the orcs!");
        command("say Look at the map, and then tell me, in which ");
        command("say part of the plains you met them.");
    }
    return 1;
}

int
name_killer(string str)
{
    string *words;
    int i;

    if (!strlen(str))
    {
        NF("What?\n");
        return 0;
    }

    if (TP != giver)
    {
        command("say I didn't talk to you, did I?");
        command("peer " + TP->query_real_name());
        return 1;
    }
 
    str = lower_case(str);

    words = explode(str," ");
    for (i = 0; i < sizeof(words); i++)
    {
        if(words[i] == killer)
        {
            check_presence(killer);
            return 1;
        }
    }
    command("say I do not understand you.");
    command("say What is the name of the person who killed the uruk?");
    command("say Use 'name <name>'");
    return 1;
}

/* Solemnian knight prestige */
int     query_knight_prestige() {return (-10);}

int
tour_done(object player) 
{
    command("say Ah, I see that you come from Hunthor, the Master of Advice in Minas Tirith!");
    command("shake " + player->query_real_name());
    introduce_me();
    command("say You can now return to Hunthor.");
    command("say Give him my regards! ");  
    return 1;
}

public void
do_die(object killer)
{
    if (interactive(killer))
    {
	ADD_KILLER(killer);
    }
    ::do_die(killer);
}

public void
return_to_office()
{
    TO->move_living("back to his office", OFFICE_ROOM);
}
/*
 * Function name:	clone_guards
 * Description	:	clone up some protection
 */
public void
clone_guards(object attacker)
{
    int n;
    object tmp;

    FIX_EUID

    if (!objectp(attacker) ||
	ENV(attacker) != TO)
    {
	attacker = TO->query_attack();
    }

    n = sizeof(filter(all_inventory(ENV(TO)), 
        &->id("_Rohirrim_guard")));
    if (n < 6)
    {
        tmp = clone_object(EDORAS_GUARD);
        tmp->set_size(Guards_summoned);
        tmp->arm_me();
        tmp->move_living("away", ENV(TO));
        tmp->command("say " + ONE_OF_LIST(({"For Theoden!",
           "Eorlingas for the Mark!", "What's all this noise?",
           "I thought I heard fighting!", "Enemies in Edoras!"})));
        if (TO->query_attack())
        {
            tmp->do_attack(TO->query_attack());
            TO->query_attack()->attack_object(tmp);
        }
        set_alarm(5.0, 0.0, clone_guards);
    }
    else if (objectp(TO->query_attack()) &&
        TO->query_attack()->query_average_stat() >= 100)
    {
        command("emote considers the situation, then retreats.");
        TO->move_living("out the side door",
          VOID, 1);
        set_alarm(700.0, 0.0, return_to_office);
    }
} /* clone_guards */



/*
 * Function name:	attacked_by
 * Description	:	respond to an attack
 * Arguments	:	object ob -- the attacking object
 */
public void
attacked_by(object ob)
{
    if (!Guards_summoned &&
	!present("_Rohirrim_guard", ENV(TO)))
    {
	log_file("edoras", ctime(time()) +
	     ": Elfhelm attacked by " + ob->query_name() + ".\n");
        clone_guards(ob);
	Guards_summoned = 1;
    }
    ::attacked_by(ob);
} /* attacked_by */



/*
 * Function name:	special_attack
 * Description	:	Called from the external combat object's heart_beat
 *                	routine. We summon guards when attacked.
 * Arguments	:	object victim -- the person we're fighting
 * Returns	:	int -- 0 if we want this round to continue
 *			       1 if we are done with this round
public int
special_attack(object victim)
{
    if ((Guards_summoned < 4) &&
	!present("_Rohirrim_guard", ENV(TO)))
    {
	log_file("edoras", ctime(time()) +
	     ": Elfhelm attacked by " + victim->query_name() + ".\n");
        clone_guards(victim);
	Guards_summoned += 1;
    }
    return ::special_attack(victim);
} 
*/

public void	set_guards_summoned(int g)	{ Guards_summoned = g; }

public void
reset_monster()
{
    Guards_summoned = 0;
}


/*
 * This npc has been coding with the help of
 * 
 * /doc/examples/mobiles/intro_npc.c
 *
 * By Hordak@Genesis
 */

#include "/d/Gondor/dunland/wild/dunlendings.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

inherit DUN_WILD_NPC + "std_dunl_npc";

inherit "/d/Genesis/lib/intro";

#include "/d/Gondor/defs.h"

#include <const.h> 
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

void      default_answer();
string    quest_give1();
string    quest_give2();
string    quest_give3();
string    quest_give4();
string    quest_give5();
string    revenge1();
string    revenge2();

void
default_answer()
{
    if (TP->query_alignment() < -100)
    {
	command("say I am not sure what you want, but soon " +
	  "the rohirrim will bow to us!");
	command("laugh evilly");
    }

    if (TP->test_bit("Gondor", MEARAS_HEAD_GROUP, MEARAS_HEAD_BIT))
    {
	command("say You go ahead and throw one more head, but " +
	  "I will only reward you once!\n");
	command("snicker");
    }

    else
    {
	command("say I have nothing to say to you!");
	command("grin");
    }
}


string
quest_give1()
{
    if (TP->query_alignment() < -100)
    {
	command("say During a journey in westfold my party "
	  + "got ambushed by Elfhelm and his riders!");
	set_alarm(3.0, 0.0, &quest_give2());
    }

    else
    {
	command("say I have nothing to say to you!");
	command("grin");
    }
}

string
quest_give2()
{
    command("say The battle was fierce, and after I finished "
      + "one rohirrim I turned to the next, which turned "
      + "out to be Elfhelm himself.");
    set_alarm(3.0, 0.0, &quest_give3());
}

string
quest_give3()
{
    command("say After a while, I managed to hit Elfhelm a " 
      + "hard blow with my shield, making him drop his "
      + "weapon. He looked at me in fear, knowing I was "
      + "to be the one who ended his miserable life.");
    set_alarm(3.0, 0.0, &quest_give4());
}

string
quest_give4()
{
    command("say Then out of nowhere a panicky mearas came "
      + "galloping. It came from behind, I had only "
      + "time to turn around and see its ugly face before "
      + "it crashed into me.");
    set_alarm(3.0, 0.0, &quest_give5());
}

string
quest_give5()
{
    command("say The impact was stunning, I fell down and the "
      + "mearas just kept on running. One of its hooves "
      + "crushed my left elbow, making me loosing my left "
      + "arm. It saved Elfhelms life, and marked me for "
      + "life. How I would like some sweet tasting revenge.");
    TP->add_prop("_galuk_revenge_", 1);
}

string
revenge1()
{
    if (TP->query_alignment() < -100)
    {
	if(TP->query_prop("_galuk_revenge_"))
	{
	    command("say Yes, some sweet revenge! I have since "
	      + "that day been collecting the heads of their "
	      + "ugly horses!");
	    set_alarm(3.0, 0.0, &revenge2());
	}
	else
	    command("say Why ask me about revenge? Do you even "
	      + "know why I seek revenge for something?");
    }
    else
	command("say I have nothing to say to the allies of "
	  + "Rohan!");
}

string
revenge2()
{
    command("say You could help me you know. Bring me a head of a "
      + "mearas and add it to my collection outside. Do that, and "
      + "you will be rewarded.");
    TP->add_prop("_have_galuk_quest_", 1);
}


void
create_dunl_npc()
{
    set_name("galuk");
    add_name(({"dunlending", "man"}));
    add_pname("men");
    set_race_name("human");
    set_adj(({"short", "one-armed"}));
    set_long("This human has short brown hair and " +
      "his face is adorn with a thick mustache. Some " +
      "scars can been seen in his face. That he has " +
      "great experience in combat is obvious. He has " +
      "lost his left arm, right above the elbow. Perhaps " +
      "this was also during combat.\n");

    set_gender(G_MALE);
    /*           STR  DEX  CON  INT WIS DIS */
    set_stats(({ 198, 231, 264, 136, 134, 178 }));
    set_title("the Conquerer of the stolen lands");
    set_alignment(-600);

    set_skill(SS_WEP_SWORD, 85);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);

    set_default_answer("@@default_answer");
    add_ask(({"elfhelm", "task", "quest"}), quest_give1);
    add_ask(({"revenge", "sweet revenge"}), revenge1);

    set_chat_time(7);
    add_chat("I was so close at finishing Elfhelm, if " +
      "it hadn't been for that darn mearas!");
    add_chat("Theoden is a weak king, Rohan will burn!");

    remove_hitloc(A_L_ARM);

    equip(({ 
	DUN_WILD_ARMOUR + "boots",
	DUN_WILD_ARMOUR + "breastplate",
	DUN_WILD_ARMOUR + "gloves",
	DUN_WILD_ARMOUR + "bracers",
	DUN_WILD_ARMOUR + "pants",
	DUN_WILD_WEAPON + "sword",
	DUN_WILD_ARMOUR + "cap"
      }));


}


void
greet(object who)
{
    if (TP->query_wiz_level())
    {
	command("say A wizard. A pleasure indeed. Nice to meet " +
	  "you " + who->query_name() + "!\n");
	command("introduce myself to " + OB_NAME(who));
    }
    else

	command("say Nice to meet you again, " + who->query_name() + "!");
    command("smile");
}


void
introduce(object who)
{

    if (TP->query_alignment() < -100)
    {
	command("introduce myself to " + OB_NAME(who));
	command("say A pleasure to meet you, " + who->query_name() + "!\n");
    }
    else

	command("say I dont reveal my name to allies of Rohan!");
    command("frown");
}

int
special_attack(object enemy)
{
    mixed *hitresult;
    int avg_stat;
    string how;

    avg_stat = query_average_stat();

    if (random(3))
    {
	return 0;  /* Continue with the normal attacks */
    }

    hitresult = enemy->hit_me(avg_stat + 20 + random(20), W_BLUDGEON, TO, -1);
    switch (hitresult[0])
    {
    case 0:
	how = "barely bruised";
	break;
    case 1..20:
	how = "lightly bruised";
	break;
    case 21..40:
	how = "badly bruised";
	break;
    default:
	how = "severly bruised";
	break;
    }

    enemy->catch_tell(query_The_name(enemy) + " suddenly knees you " +
      "in the gut!\n"+
      "You are " + how + ".\n");
    tell_watcher(QCTNAME(TO) + " suddenly knees " + QTNAME(enemy) + 
      " in the gut!\n" +
      capitalize(enemy->query_pronoun()) + " is " + how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(this_object());
    }

    return 1;
}



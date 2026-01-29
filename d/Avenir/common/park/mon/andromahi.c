// file name:	andomahi.c
// creator(s):	Ilyian(18 April, 1995)
// last update: Ilyian 26 April 995
//              Cirion, Feb 1996: put in the new reward_quest function.
//		Denis, May'97: Obsolete code update.
//              Lilith, Dec '04: She removes herself after quest reward
//                 so th quest will reset.
// purpose:	One that gives out the Faerie Quest and rewards it
// note:	At /d/Avenir/common/park/glade.c
// bug(s):
// to - do:

# pragma strict_types

# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/paths.h"
# include <formulas.h>
# include <cmdparse.h>
# include <macros.h>
# include <ss_types.h>
# include <wa_types.h>
# include <stdproperties.h>

# include "faerie_quest.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/d/Avenir/inherit/quest";

void            test_faerie_quest(object player);
void            reward_faerie_quest(object player);
void            faerie_quest();
string          give_faerie_quest();
object          faerie;

# define A_WINGS 0
# define A_RHAND 1
# define A_LHAND 2
# define A_BITE 3
# define A_RFOOT 4
# define A_LFOOT 5

# define H_HEAD 0
# define H_BODY 1
# define H_LEGS 2
# define H_WINGS 3

void
create_creature()
{
    set_name("andromahi");
    add_name("faerie");
    add_name("_quest_faerie_");
    set_title("the Speaker of the Faeries");
    set_living_name("andromahi");
    set_race_name("faerie");
    set_gender(G_FEMALE);
    set_adj("silvery");
    set_long("This tiny creature looks just like the other "
	     + "faeries, except that her naked body is silver and "
	     + "her wings are a bright gold.\n");

    set_alarm(1.0, 0.0, "set_m_in", "flits in.");
    set_alarm(1.0, 0.0, "set_m_out", "flits");
    set_alignment(300);

    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 30);
    add_prop(LIVE_I_QUICKNESS, 100);
    //fast little critter

	set_stats(({2, 70, 30, 30, 90, 50}));

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_SNEAK, 60);
    set_skill(SS_HIDE, 60);
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_BLIND_COMBAT, 93);

    set_attack_unarmed(A_WINGS, 3, 3, W_BLUDGEON, 10, "wings");
    set_attack_unarmed(A_RHAND, 3, 3, W_BLUDGEON, 10, "right hand");
    set_attack_unarmed(A_LHAND, 3, 3, W_BLUDGEON, 10, "left hand");
    set_attack_unarmed(A_BITE, 5, 8, W_IMPALE, 50, "bite");
    set_attack_unarmed(A_RFOOT, 3, 3, W_BLUDGEON, 10, "right foot");
    set_attack_unarmed(A_LFOOT, 3, 3, W_BLUDGEON, 10, "left foot");

    set_hitloc_unarmed(H_HEAD, 70, 2, "head");
    set_hitloc_unarmed(H_BODY, 95, 60, "body");
    set_hitloc_unarmed(H_LEGS, 90, 30, "legs");
    set_hitloc_unarmed(H_WINGS, 75, 8, "wings");

    set_cact_time(10);
    add_cact("emote screams in a high pitched voice.");
    add_cact("glare enemy");
    add_cact("growl angr enemy");
    add_cact("emote waves her wings in irritation.");
    add_cact("whine soft");
    add_cact("fume");
    add_cact("point enemy");
    add_cact("slap enemy");
    add_cact("pout .");
    add_cact("emote utters a loud exclamation in a lost language.");

    set_act_time(5);
    add_act("@@do_act1");
    add_act("@@do_act2");
    add_act("@@do_act3");
    add_act("sob");
    add_act("whine petu");

    add_leftover(PK + "obj/faerie_wing_g", "wing", 2, 0, 0, 0);

    add_ask(({"astarte", "lost", "help", "task", "quest"}),
	    VBFC_ME("give_faerie_quest"));

    add_ask(({"key", "prison", "cage"}), VBFC_ME("exp_key"));
    add_ask(({"creature", "monster", "singing"}), VBFC_ME("exp_creature"));
    //add_ask(({"faerie", "faeries"}), "@@exp_faerie", 1);
    //add_ask(({"glade", "ring", "circle", "stones", "magic"}), "@@exp_glade", 1);

    trig_new("%s 'drops' 'a' 'shining' 'faerie.\n'", "do_reward");
    add_ask(({"for reward", "reward"}), VBFC_ME("reward_me"));

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
}

string
do_act1()
{
    if (present(FAERIE_ID, environment()))
    {
	command("tickle astarte");
	return "";
    }
    command("emote whines: Astarte! Astarte!");
    return "";
}

string
do_act2()
{
    if (present(FAERIE_ID, environment()))
    {
	command("cuddle astarte");
	return "";
    }
    command("emote sings: Where has she gone? Who has taken Astarte?");
    return "";
}

string
do_act3()
{
    if (present(FAERIE_ID, environment()))
    {
	command("smile sweetly astarte");
	return "";
    }
    command("emote whines: It came when the Source was black! It took "
	    + "her from us!");
    return "";
}

static void
do_intro(string who)
{
    object          obj;
    if (obj = present(who, environment()))
    {
	command("whisper " + who + " I am Andromahi, Speaker of the faeries.");
	this_player()->add_introduced("andromahi");
	command("smile seduct");
    }
}

public void
add_introduced(string who)
{
    set_alarm(3.0, 0.0, &do_intro(who));
}

string 
give_faerie_quest()
{
    if (present(FAERIE_ID, environment()))
    {
	command("say Astarte is my friend!");
	command("cuddle astarte");
	command("say She had been stolen from us, but now she is back!");
	return "";
    }

    if (!TP->test_bit("Avenir", GROUP, BIT))
    {
	faerie_quest();
	return "";
    }
    else
    {
	command("say You have already saved our Astarte for us, we "
		+ "could not ask you to do it again.");
	return "";
    }
}

string 
exp_key()
{
    command("say The key is in a place of stone, surrounded by shadow, "
       + "through the water.");
    command("emote smiles enigmaticly.");
    return "";
}

string 
exp_creature()
{
    command("say The creature is a beast of darkness that holds "
       + "singing death within its grasp.");
    command("say Fear it.");
    return "";
}

void 
faerie_quest()
{
    if (TP->query_prop(QUEST_VERSION))
    {
	command("say I've told you everything I know.");
	command("say Please bring her back to us!");
	command("cry");
	return;
    }
    command("say A foul creature came and took our Astarte away from "
	    + "us! Please save her for us!\n");
    command("say She is held in the arms of the stone in water.\n");
    TP->add_prop(QUEST_VERSION, 1);
    WRITE_LOG(" asked for and got the faerie quest.\n");
}

string 
reward_me()
{
    if (!present(FAERIE_ID, environment()))
    {
	command("say But you have not brought her back!");
	command("emote blinks.");
	return "";
    }
    test_faerie_quest(TP);
    return "";
}

string
do_reward()
{
    if (!present(FAERIE_ID, environment()))
    {
	command("say But this is not out Astarte!");
	command("sob");
        WRITE_LOG(" somehow dropped a shining faerie, but it was not Astarte.\n");
	return "";
    }
    test_faerie_quest(TP);
    return "";
}

void 
test_faerie_quest(object player)
{
    int             ix;
    ix = player->test_bit("Avenir", GROUP, BIT);
    if (player->test_bit("Avenir", GROUP, BIT))
    {
	command("say Thanks you for saving her for us again!");
	command("cuddle astarte");
        WRITE_LOG(" saved Astarte (again!)\n");
	return;
    }
    set_alarm(2.0, 0.0, "command", "say You found her!");
    set_alarm(4.0, 0.0, "command", "hug astarte");
    set_alarm(5.0, 0.0, "command", "thank " + player->query_real_name());
    reward_faerie_quest(player);
}

void
reward_faerie_quest(object player)
{
    tell_object(player, "You are bathed in a pale white light for "
		+ "a moment.\n");
    say(QCTNAME(player) + " is momentarily touched by a white light.\n");

    reward_quest("Faerie Quest", player, GROUP, BIT, FAERIE_QUEST_XP,
                 600, 200);

    WRITE_LOG(" saved Astarte and was rewarded: " + FAERIE_QUEST_XP + " xp.\n");
    
    set_alarm(60.0, 0.0, &remove_object());
}

void
do_die(object killer)
{
    ::do_die();
}

//special attack
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    if (random(15) == 1) {
	tell_object(enemy, "The silvery faerie raises her hand and "
	      + "chants some arcane syllables.\nA tiny bolt of light flies "
		  + "from her hand and strikes you. It burns painfully.\n");

	tell_room(environment(TO), "The silvery faerie raises her hand and "
	 + "chants some arcane syllables.\nA tiny bolt of light flies from "
		  + "her hand and strikes " + QTNAME(enemy) + ".\n", enemy);

	enemy->heal_hp(-40 - random(70));
    }
}

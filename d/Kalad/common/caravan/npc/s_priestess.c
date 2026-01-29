#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include <time.h>

#define   QUEST_NAME      "QUEST/holyquest"
#define   SOLARA_SWORD    CPASS + "wep/sword_of_solara"
#define   THIS_FILE       (NPC + "s_priestess")

int    sword;
string long;
object priestess;

void
create_kalad_monster()
{
    set_name("aleanna");
    add_name("priestess");
    set_race_name("human");
    set_adj("compassionate");
    add_adj("devoted");
    set_long("\nA woman in the prime of youth whose clear blue eyes "+
      "and long golden tresses remind one more of a fair damsel than "+
      "a dilligent member of the Church of Solara.  A noticeable warmth "+
      "and slight glow seems to emanate from her very person.\n");

    set_title("the Golden Priestess of Solara");
    set_knight_prestige(-5);
    set_gender(G_FEMALE);
    set_stats(({ 50, 50, 75, 75, 100, 50 }));
    set_alignment(750);  /* blessed */
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_BLIND_COMBAT, 10);  /* low because she is a being of light */
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_AWARENESS, 60);

    set_act_time(random(3));
    add_act(({ "smile kind",
	"emote whispers a prayer to Solara.",
	"say I am in great need of assistance.",
	"pray solara",
	"emote closes her eyes in a prayer of reverence.",
      }));

    set_cact_time(2);
    add_cact(({ "gasp",
	"emote hisses: May Solara burn your soul with fiery "+
	"pureness!",
	"scream"
      }));

    add_speak("\tA terrible evil may soon be unleashed upon the world...\n"+
      "\tI seek a great and powerful hero or heroine that may\n"+
      "\tstand up to and help bring about this evil's defeat.\n"+
      "\tTo this end the fabled Sword of Solara must be recovered.\n\n");
    add_ask(({ "assistance" }),
      "The priestess says: There is a great quest which the Church of "+
      "Solara seeks a great and brave adventurer to fullfill.\n\n");
    add_ask(({ "terrible evil", "evil" }),
      "The priestess says: The Holy Order of Thanar seeks to bring "+
      "into this world the avatar of their god, Thanar himself. It is "+
      "rumoured that the Order is counting on the actions of their enemies "+
      "to bring about Thanar's return to the world.\n\n");
    add_ask(({ "holy order of thanar", "holy order", "order", "thanar" }),
      "The priestess says: The self-styled 'Holy Order of Thanar' is "+
      "nothing more than a band of human supremacist fanatics of the "+
      "forgotten god, Thanar. But be wary, for they are quite dangerous.\n\n");
    add_ask(({ "sword" }),
      "The priestess says: There are two swords... one of good, the Sword "+
      "of Solara... and one of evil, the Sword of Thanar.\n\n");
    add_ask(({ "fabled sword", "sword of solara", "holy sword" }),
      "The priestess says: It is an ancient artifact of the Church of "+
      "Solara. It must be recovered at all costs! With its power, a great "+
      "hero may yet be able to turn the tide against the forces of Thanar.\n\n");
    add_ask(({ "quest", "great quest" }),
      "The priestess says: I need one of great strength and determination. "+
      "One strong enough to withstand the terrible dangers that plague this "+
      "quest that is in need of fulfilling. Only by fullfilling this quest "+
      "can all of Kalad -- nay, all of the world! -- be saved from total "+
      "and complete destruction.\n\n"+
      "The priestess says: The Avatar of Thanar possesses a mighty sword. One "+
      "that must be forcibly retrieved from the dark god. Once it has been "+
      "recovered you must seek out Gurden the Lonely, for only that sage "+
      "possess' intimate knowledge of the weapon... as well as the key to "+
      "fulfilling this sacred quest. You must follow his words to the letter, "+
      " for if you do not, it could mean your untimely end.\n\n");
    add_ask(({ "foul stygion-black sword", "sword of thanar" }),
      "The priestess says: Only by undergoing Solara's quest will you "+
      "receive any knowledge pertaining to that accursed sword.\n\n");
    add_ask(({ "avatar", "avatar of thanar" }),
      "The priestess says: A powerful being! The Avatar is hard to locate and "+
      "shows up on its terms.  You must defeat this being!\n\n");
    set_default_answer("\nThe priestess says: I am sorry, my child, but I do "+
      "not understand what it is you speak of.\n\n");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

void
sword_return()
{
    sword = 1;
}

void
drop_the_object(object ob)
{
    command("drop all");
}

void
remove_the_object(object ob)
{
    command("say This day shall forever be marked as a holy day\n\t"+
      "for the Church of Solara!");
    command("smile warm " + ob->query_real_name());
    command("hug " + ob->query_real_name());
    command("say " + capitalize(this_player()->query_real_name()) + ", you "+
      "have truly proven yourself a brave and\n\tresourceful adventurer. "+
      "If you are true of heart, then this\n\tsword shall serve you well!");
    command("drop sword");
    command("say Farewell my friend! I must inform the High Priest\n\t"+
      "himself of this momentous occassion!");
    command("wave " + ob->query_real_name());
    command("emote leaves to tell the High Priest of Solara the good news.");

    if(priestess = present("aleanna", environment(this_player())))
    {
	priestess->remove_object();
    }
}

public void
enter_inv(object ob, object from)
{
    if (MASTER_OB(ob) != SOLARA_SWORD)
    {
	::enter_inv(ob, from);

	set_alarm(3.0, 0.0, &drop_the_object(ob));

	return;
    }

    if (!interactive(from))
	return;
    else
	set_this_player(from);

    if(from->test_bit("Kalad", 0, 13))
    {
	write(query_The_name(from) + " thanks you for once again "+
	  "retrieving the sword of Solara.\n");
	this_player()->catch_msg("\nYou have completed this quest pre"+
	  "viously.\nYou do NOT feel more experienced.\n\n");
    }
    else
    {
	write("\nThe priestess thanks you profusely, tears streaming down "+
	  "her cheeks at the great service you have done for the Church of "+
	  "Solara.\n");
	write("\nThe priestess whispers to you: The foul stygion-black sword "+
	  "\tresponds to dilvardyn while the pure snow-white sword comes to "+
	  "\tlife at aralos.  Use this knowledge wisely!\n\n");

	this_player()->catch_msg("You feel MUCH more experienced!!\n\n");
	this_player()->add_exp(20000, 0);
	this_player()->set_bit(0, 13);

	seteuid(getuid(this_object()));

	log_file(QUEST_NAME, extract(ctime(time()), 4, 15) + " " +
	  capitalize(this_player()->query_real_name()) + "\tgot 20, 000XP; "+
	  "Stat ave = " + this_player()->query_average_stat() + "\t" +
	  "Age = " + TIME2STR(this_player()->query_age() * 2, 2) +
	  "\n\t\tRewarded by " + THIS_FILE + "\n");
    }

    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &remove_the_object(ob));
}

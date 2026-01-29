#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <formulas.h>

#include HOBBIT_FILE

inherit HOBBITMAKER;
inherit KILL_LOGGER;
inherit "/lib/unique";

#define QUEST_NAME "writing"
void
create_hobbit()
{
    set_type(CITIZEN);
    set_power(80);

    set_name("bilbo");
    set_adj(({"cheerful", "chatty"}));
    set_title("");
    set_living_name("bilbo");
    set_long("This hobbit looks like he's seen many an adventure " +
      "but doesn't get out much anymore. He has brown curly " +
      "hair and is dressed in bright clothes. He looks " +
      "cheerful and is studying something, most likely a book " +
      "or something. He is a personal friend of Elrond, and " +
      "lives in the Valley under the protection of the elves.\n");
    set_gender(G_MALE);
    set_family_name("baggins");

    set_kill_log_name("bilbo");
    set_kill_log_size(5000);
    set_alignment(250);
    add_prop(CONT_I_WEIGHT,43000);   /* 40 Kg */
    add_prop(CONT_I_HEIGHT,87);      /* 82 cm */
    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_stats(({ 80, 77, 65, 70, 70, 75}));
    set_hp(10000); /* Heal fully */

    set_chat_time(3);
    set_act_time(3);

    add_chat("Imladris is the most restful place around.");
    add_chat("Those elves are so funny sometimes.");
    add_chat("Have you any news from the Shire?");
    add_chat("Pull up a seat and tell me about your adventures.");
    add_chat("I have seen many things during my journeys.");

    add_act("dips his quill in the inkpot and writes something down.");
    add_act("nods off and falls asleep.");
    add_act("rubs his tummy hungrily.");
    add_act("smiles happily.");

    set_default_answer(VBFC_ME("idontknow"));
    add_ask(({"hobbiton"}),
      VBFC_ME("hobbiton"));
    add_ask(({"ring", "the one ring"}),
      VBFC_ME("the_ring"));
    add_ask(({"bagend", "bag end"}),
      VBFC_ME("bagend"));
    add_ask(({"shire", "the shire"}),
      VBFC_ME("shire"));
    add_ask(({"hobbits"}),
      VBFC_ME("hobbits"));
    add_ask(({"adventures", "travels", "tales"}),
      VBFC_ME("adventures"));
    add_ask(({"smaug", "smaug the golden", "smaug the terrible"}),
      VBFC_ME("smaug"));
    add_ask(({"kingdom under the mountain"}),
      VBFC_ME("kotm"));
    add_ask(({"dain", "dain ii", "dain II", "dain ii ironfoot"}),
      VBFC_ME("dain"));
    add_ask("dale",
      VBFC_ME("dale"));
    add_ask(({"battle of five armies", "the battle of five armies",
	"the battle of the five armies"}),
      VBFC_ME("battle"));
    add_ask(({"thorin", "thorin ii"}),
      VBFC_ME("thorin"));
    add_ask(({"nazgul", "black riders", "ring wraiths",
	"wraiths", "the nine", "servants of sauron", "sauron",
	"mordor", "nine riders"}),
      VBFC_ME("the_ring"));

    /* gives quest */


    add_ask(({"task", "help", "quest", "ink", "inkpot", "quills",
	"parchments"}),
      VBFC_ME("give_task"));

    equip(({ clone_unique("/d/Shire/rivendell/wep/sting", MAX_UNIQUE_ITEMS, "/d/Shire/rivendell/wep/dagger"),
        RARM_DIR+"mail" }));
}

void
arm_hobbit()
{
}

void
introduce_hobbit(string who)
{
    command("introduce me");
    command("say Hello there, my name is "+query_met_name()+"!");
}

string idontknow()
{
    switch(random(5))
    {
    case 0:
	command("say Good question, but I don't know.");
	return "";
    case 1:
	command("say When I find out about that, I'll " +
	  "be sure to let you know.");
	return "";
    case 2:
	command("say Ask Elrond. He probably knows.");
	return "";
    case 3:
	command("say I've probably got something on it, " +
	  "but don't know where the answer would be at " +
	  "right now.");
	return "";
    case 4:
	command("say I have no idea what you're talking about.");
	return "";
    }
}

public string
hobbiton()
{
    command("say Hobbiton is the most famous village of my folk " +
      "in the Shire. The village is in the Westfarthing and " +
      "is a humble town built around Hobbiton Hill with a " +
      "mill and a granary on a stream on the Water.");
    command("say What was the miller's name?...Hmm, I forgot.");
    command("shrug carelessly");
    command("say His name is not important. Now where was I...");
    command("emote looks around confusedly.");
    command("say Oh, I remember now.");
    command("say The most famous part of the village was my " +
      "old hole, Bag End on Bagshot Row! That hole was the " +
      "envy of every hobbit, but I left it to my nephew, " +
      "Frodo, when I came to live here.");
    return "";
}

public string
bagend()
{
    command("say I can say proudly that Bag End is one of the " +
      "finest hobbit-holes to be found in the Shire. It's not " +
      "a house--big people live in those things--but a very " +
      "clean hole in a lovely hill. Many a hobbit tried to " +
      "buy it from me but I wouldn't have anything to do with " +
      "them. You see, my gaffer, Bungo Baggins built it. He " +
      "and my mother, Belladona Took, moved into it and made " +
      "it the family residence. There are lots of pantries " +
      "and cellars, a big kitchen, bedrooms, a sitting room, " +
      "a parlour, and other good rooms. Lovely gardens " +
      "surround the hill making the whole hill beautiful.");

    return "";
}

public string
shire()
{
    command("say The Shire is a beautiful place. It's covered " +
      "with green hills, and pleasant lands. It is the home " +
      "of my people, the hobbits. It is located west of the " +
      "Brandywine river and has several major villages and " +
      "towns. You've probably heard of some of them: Michel " +
      "Delving, Whitfurrows, Frogmorton, and my favorite, " +
      "Hobbiton! The Great East Road runs through the Shire " +
      "from the Grey Havens to Bree.");
    return "";
}

public string
the_ring()
{
    say("A dark shadow falls upon the valley, leaving everyone " +
      "speachless. The feeling passes.\n");
    command("emote looks troubled.");
    command("say Such things are not discussed in the House " +
      "of Elrond nor in the valley of Imladris.");
    return "";
}

public string
hobbits()
{
    command("say You won't find a better people than us " +
      "hobbits. Just look at me and you'll get a good idea " +
      "what we are like. As you can tell, we are short " +
      "compared to the Big People, and have hairy toes. We " +
      "don't mind. We're just the right height if you ask us. " +
      "Hobbits live in the Shire and are a jolly people. We " +
      "love good food and prefer six meals a day. We love to " +
      "dress in bright clothes and can hide quickly when we " +
      "need to.");
    return "";
}

public string
adventures()
{
    command("say Adventures?!? Oh my, I have been on adventures " +
      "you wouldn't believe. I have been all over the place " +
      "and even saw Smaug the Terrible! Right now, I am " +
      "writing my memoirs for later and writing about what I " +
      "have seen.");
    return "";
}

public string
smaug()
{
    command("say Smaug the Dragon, also known as Smaug the Golden, " +
      "destroyed Dale and and drove the dwarves away from the " +
      "Kingdom under the Mountain. Apparently he lived there " +
      "for about 200 years. Then with my help, Thorin and " +
      "company were able to rid the land of him. He was slain " +
      "by Bard the Bowman.");
    return "";
}


public string
kotm()
{
    command("say The Kingdom under the Mountain is a dwarven kingdom " +
      "near Dale in Erebor under the Lonely Mountain. The Kingdom " +
      "was re-established by Dain II after the Battle of the " +
      "Five Armies. This battle, which I was a part of, took " +
      "place after Smaug was killed. Last I heard, the " +
      "kingdom is doing very well, especially since they " +
      "trade with the men of Dale.");
    return "";
}


public string
dain()
{
    command("say He's the dwarf king of the Kingdom under the " +
      "Mountain near Dale. He's a great warrior and a good " +
      "king who is also known as Dain II Ironfoot.");
    return "";
}


public string
dale()
{
    command("say This town is just south of the Lonely Mountain. " +
      "Bard the Bowman rebuilt it after the Battle of the " +
      "Five Armies. The town has grown and is quite wealthy, " +
      "thanks to the trade between the dwarves in the Lonely Mountain.");
    return "";
}

public string
battle()
{
    command("say The Battle of Five Armies was amazing. " +
      "It involved the Men of Esgaroth, the Elves of Northern " +
      "Mirkwood, the Dwarves of Erebor and of the Iron Hills, " +
      "and a huge army of orcs. The silly thing was that it " +
      "was over how the dwarven treasure was to be divided " +
      "after Smaug was killed. We were almost defeated until " +
      "the Eagles came to save us. They drove the orcs off " +
      "and destroyed them. Gandalf was there, too! I don't " +
      "remember much about it because I was knocked out, but " +
      "we won. Unfortunately, Thorin was mortally wounded.");
    return "";
}


public string
bard()
{
    command("say Bard is one of those big people, but still a " +
      "good person. He is a great archer and slew Smaug " +
      "when the dragon attacked Dale. He was the leader of " +
      "the big people during the Battle of Five armies " +
      "and last I heard, he was made king of Dale after the " +
      "city was rebuilt. I remember Bard as somewhat grim " +
      "of spirit but he is a wise and able leader.");
    return "";
}


public string
thorin()
{
    command("say Thorin II was a great dwarf who led a group " +
      "of dwarves and myself on an expedition. We went to " +
      "Erebor to their former realm to recover a horde of " +
      "treasure. The kingdom is under the Lonely Mountain " +
      "in Erebor near the town of Dale. He was also the " +
      "leader of the dwarves in the Battle of Five Armies " +
      "but was mortally wounded.");
    return "";
}


/* 
 * quest routines 
 */

string give_task()
{
    if (CHECK_QUEST(TP, QUEST_NAME))
    {
	command("say Thank you for asking, but you have helped " +
	  "me already.");
	return "";
    }


    if (TP->query_prop("_brought_inkpot"))
    {
	command("say How do you expect me to write when my quills are " +
	  "all bad? Please find me some new ones.");
	return "";
    }

    if (TP->query_prop("_inkpot_quest"))
    {
	command("say What are you waiting for? I need those supplies.");
	return "";
    }

    /* give out first part of quest */

    command("say Thank you so much for your interest in helping " +
      "me. I have been very busy writing my memoirs, and they " +
      "are many. But I seem to have run out of ink. Would you " +
      "help me and get some more ink for my inkpot? I would " +
      "be very grateful. And be sure it's elven ink. Ink from " +
      "Bree is all lumpy and doesn't write as smooth. Thanks!");
    TP->add_prop("_inkpot_quest",1);
    return "";
}

void give_second_task(object player)
{
    command("say Oh dear me. My quills are all bad. As you " +
      "know, a good quill makes all the difference when " +
      "writing. Unfortunately, mine are pretty sad looking " +
      "and well used. Secretly, I think the elves sneak in " +
      "and use them when I'm not around. Can you help me " +
      "again and find some? When you find them, bring them " +
      "back and I'll have an elf take them to the fletcher " +
      "for me. Thanks! Oh, and be sure the feathers are " +
      "eagle; they make the best quills.");
    player->add_prop("_brought_inkpot",1);
}

void give_third_task(object player)
{
    command("say Thank you!");
    command("say One last favour before you go. I am almost out " +
      "of parchments and have been unable to get some. Can " +
      "you be a helpful little " + player->query_race_name() +
      " and find some for me, " +
      "please? I'll be very grateful for your help. If you " +
      "can't find any good parchments, just return with a " +
      "bunch of reeds. I'll have them made into parchments " +
      "for me. Thanks again!");
    player->add_prop("_brought_feathers",1);
}


void test_reward_tasks(object player)
{
    if (!player->query_prop("_brought_inkpot"))
    {
	command("say Hey, have you found some ink for me? You " +
	  "know I need some more.");
	command("sigh");
	return;
    }

    if (!player->query_prop("_brought_feathers")) 
    {
	command("say Hey, have you found some feathers for me? You " +
	  "know I need some more.");
	command("sigh");
	return;
    }

    if (!REWARD_QUEST(player, QUEST_NAME))
    {
	command("say Thanks for your concern, but you have " +
	  "helped me already.");
	return;
    }

    command("sigh thankfully");
    command("say Thank you very much for helping me. Now I can " +
      "continue writing my memoirs. Hopefully they will be " +
      "done soon.");
    command("scratch head");
    command("say Oh, I should give you something for your troubles.");
    tell_object(player, "You feel more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
}


void
failed_give(object obj,object from)
{
    command("say I have no need for such things.");
    write(TO->query_The_name(from)+" gives it back to you.\n");
    obj->move(from);
    return;
}


public void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!objectp(from)) return;
    if(obj->id("_imladris_ink_")) 
    {
	set_alarm(2.0,0.0,&give_second_task(from));
	return;
    }

    if(obj->id("_imladris_feather_")) 
    {
	set_alarm(2.0,0.0,&give_third_task(from));
	return;
    }

    if(obj->id("_imladris_reeds_")) 
    {
	set_alarm(2.0,0.0,&test_reward_tasks(from));
	return;
    }
    if(obj->id("_quill_"))
    {
	command("say That Bree ink will ruin my quills worse " +
	  "than they are now. It is all lumpy and dirty. I " +
	  "need you to bring me some better ink. Thank you " +
	  "for trying, though.");
	set_alarm(1.5, 0.0, &failed_give(obj, from));
	return;  
    }
    else
	set_alarm(1.5, 0.0, &failed_give(obj, from));
    return;
}

/*
 * Updated locations since some have been outdated for years.
 * -- Finwe February 2007
 */
#pragma save_binary

#include "/d/Shire/bits.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "/d/Shire/common/defs.h"

inherit HOBBITMAKER;

#define MAP_LOC ONE_OF_LIST(({ "/d/Shire/bree/rooms/town/hhouse1", \
         "/d/Shire/michel/pet_garden4", \
         "/d/Shire/eastroad/village/ut/1d",\
         "/d/Shire/annuminas/pub", \
         "/d/Shire/bombadil/rooms/path10" }))


#define QUEST_NAME "hobentrance"

/* Function prototypes */
void reward_locket_quest(object player);
void locket_quest();


void
create_hobbit()
{
    set_type(MILITA);
    set_power(150);
    set_name("togo");
    set_family_name("Took");
    set_title("Guard of the Adventuresome Hobbit Guild");
    set_living_name("_togo_");
    add_name(({"doorman","guard"}));
    set_adj(({"old","sleepy"}));
    set_gender(0);

    set_long("This hobbit seems to be the guard of the Adventuresome "+
      "Hobbit Guild. Please try not to disturb him, he is probably dreaming "+
      "of his old adventures.\n");

    disable_all_noise();
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_chat_time(6);
    add_chat("Welcome to the guild!");
    add_chat("I should be getting a new rocking chair soon.");
    add_chat("I hate thieves.");
    add_chat("I hear the post office has a leaky roof here!");
    add_chat("I drew that first map, here on the walls.");
    add_chat("Now what was I saying?");
    add_chat("Where has that map gotten off to?");
    add_chat("Do you know something interesting?");
    add_chat("Old Mister Bilbo has told me almost all of his tales.");
    add_chat("One time, I stole some gold right out of a troll's hand.");
    add_chat("Have you ever been to Gondor? Lovely place.");
    add_chat("We only take adventurous types here.");
    add_chat("I don't know, why don't you go see for yourself?");
    set_act_time(10);
    add_act("sit in chair");
    add_act("rock chair");
    add_act("ponder where the map has gotten off to.");
    add_act("emote mutters something under his breath.");
    add_ask(({"help","quest","entrance","map"}),VBFC_ME("give_task"));

}

void
arm_hobbit()
{
    object tunic;

    FIXEUID
    tunic = clone_object(MICH_DIR + "arm/h_cloak");
    tunic->move(TO);
    command("wear all");
}
void test_locket_quest(object player)
{
    int ix;
    ix = player->test_bit("Shire",WESTERN_GROUP,HOBBIT_ENTRANCE_BIT);
    if(player->test_bit("Shire",WESTERN_GROUP,HOBBIT_ENTRANCE_BIT))
    {
	command("say Hey, I know you, you've already done this.");
	return;
    }

    command("say This is what I wanted.");
    command("say You'll make a fine adventurer!");
    command("say Well done!");
    command("shake " + player->query_name());
    reward_locket_quest(player);

}


string give_task()
{
    if (!TP->test_bit("Shire",WESTERN_GROUP,HOBBIT_ENTRANCE_BIT))
    {
	locket_quest();
	return "";
    }
    else 
    {
	command("say Hey, I know you, you've done this already.");
	return "";
    }
}


void locket_quest()
{

    if(TP->query_prop("_hobbit_entrance_quest"))
    {
	command("eyebrow " + TP->query_name());
	command("say I've told you what to do already.");
	command("say Snap to it!");
	return;
    }
    command("say We have had a map stolen from us recently...");
    command("say I don't know how they got past me, but they did.");
    command("say Anyway, it's a very fine map, a complete map of");
    command("say all the lands known to hobbits.  It is very valuable,");
    command("say and would prove you an adventurous person if you could find it.");
    command("say Naturally, I have other rewards as well.");
    command("smile misc");
    TP->add_prop("_hobbit_entrance_quest",1);

    set_alarm(5.0,0.0,"move_map");
}


void
move_map()
{
    object mymap;

    FIXEUID
    mymap = clone_object("/d/Shire/hobbit/map");
    mymap->move(MAP_LOC,1);
    //   command("say Moving to:"+ MAP_LOC);

}

void
reward_locket_quest(object player)
{
    player->remove_prop("_hobbit_entrance_quest");
    player->set_bit(WESTERN_GROUP,HOBBIT_ENTRANCE_BIT);
    player->add_exp(HOBBIT_ENTRANCE_EXP,0);
    seteuid(getuid(TO));
    log_file(QUEST_NAME, extract(ctime(time()),4,15) + " " +
      CAP(player->query_real_name()) + " rewarded with "+HOBBIT_ENTRANCE_EXP+" exp, "+
      "<"+player->query_average_stat()+"> avg stats.\n");
    tell_object(player,"You feel more experienced!\n");
    say(QCTNAME(player) + " got a nice reward.\n");
}

public void
enter_inv(object obj, object from)
{ 
    ::enter_inv(obj, from);
    /*command("say DEBUG: enter_inv entered with from = " + (objectp(from) ? from->query_name() : " no object ") +
       " and obj = " + (objectp(obj) ? obj->query_name() : " no object "));*/
    if (!living(from))
	return;
    if (obj->id("_hobbit_map_"))
    {
	if (!(obj->query_gotten() < 2))
	{
	    obj->remove_object();
	    command("say I don't want this old torn up map!");
	    command("say It's been handled so roughly I can hardly read it.");
	    command("emote rips the very fine map up into tiny shreds.");
	    return;
	}
	command("say This map appears to be in fine condition.");
	test_locket_quest(from);
	obj->remove_obj();
	return;
    }

    command("say Why would you think I would want that?");
    set_alarm(1.0,0.0, &command("give "+OB_NAME(obj)+" to "+from->query_real_name()));
    return;
}


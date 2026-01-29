/* goblin caves */

#include <ss_types.h>
#include "../local.h"
#include "/d/Shire/sys/defs.h"

inherit SHIRE_ROOM;

int pot_is_empty,
key_is_in_pot,
fire_is_on,
soup_is_hot;
object key;

/*
 * Prototypes
 */
void reset_shire_room();

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_fun");

    set_short("goblin guard common room");
    set_long("Here goblin guards rest between their duty. They play their "+
      "rude games here, eat, sleep and sometimes even fight here. "+
      "There are rumours that they cook their victims and prisoners. "+
      "It seems pretty likely to you when you see the big pot "+
      "hanging on a chain over the "+"@@fire_logs@@"+".\n");

    add_item("pot", "@@pot_desc");
    add_item("fire", "@@fire_desc");
    add_item("soup", "@@soup_desc");
    add_item("chain", "It is an ordinary iron chain hanging from the ceiling "+
      "with a bit pot at the end.\n");
    add_item(({"wall","walls"}),"These walls seems to be natural. But "+
      "then again you have seen so many strange things in these "+
      "caves that you are not sure about anything you see or feel.\n");

    add_exit(ROOMS_DIR+"c93", "north");

    reset_shire_room();
}

void
reset_shire_room()
{
    object goblin1; 
    object goblin2; /* there are several goblins here    */
    int i;

    seteuid(getuid());

    if(!present("_misty_goblin_"))
    {
	goblin1 = clone_object(NPC_DIR + "goblin_high");
	goblin1->arm_me();
	goblin1->move_living("xxx", this_object());
	for(i=0 ; i<2 ; i++ )
	{
	    goblin2 = clone_object(NPC_DIR + "goblin_med");
	    goblin2->arm_me();
	    goblin2->move_living("xxx", this_object());
	    goblin1->team_join(goblin2); /* goblin1 will be the leader */
	}
	for(i=0 ; i<2 ; i++ )
	{
	    goblin2 = clone_object(NPC_DIR + "goblin_low");
	    goblin2->arm_me();
	    goblin2->move_living("xxx", this_object());
	    goblin1->team_join(goblin2); /* goblin1 will be the leader */
	}
	pot_is_empty = 0;
	key_is_in_pot = 1;
	fire_is_on = 1;
	soup_is_hot = 9;
    }
}

string
fire_logs() {
    if(fire_is_on) return "fire";
    return "small heap of half burned logs";
}

string
pot_desc() {
    if(present("_misty_goblin_", TO))
	return "It is big iron pot. Goblins will not let you come any closer "+
	"to it and so you don't see what is in it. Maybe it is better "+
	"that you don't know.\n";
    if(!pot_is_empty)
	return "It is big iron pot with some thick soup in it. What is "+
	"the soup made from you can't tell but sure it isn't beef.\n";
    if(key_is_in_pot)
	return "It is big iron pot. Surprisingly enough you see small "+
	"rusty key in it.\n";
    return "It is big empty iron pot.\n";
} 

string
fire_desc() {
    if(fire_is_on)
	return "It is quite big fire and it is heating the pot "+
	"hanging above it.\n";
    return "You find no fire.\n";
}

string
logs_desc() {
    if(!fire_is_on)
	return "It is only small heap of half burned logs.\n";
    return "You find no logs.\n";
}

string
soup_desc() {
    if(present("_misty_goblin_", TO) || pot_is_empty)
	return "You find no soup.\n";
    if(soup_is_hot)
	return "It is thick soup. It is too hot for eating.\n";
    return "It is thick soup. It is cool enough for eating.\n";
} 

init()
{
    ::init();
    add_action("extinguish_fire", "extinguish");
    add_action("light_logs", "light");
    add_action("cool_soup", "cool");
    add_action("eat_soup", "eat");
    add_action("empty_pot", "empty");
    add_action("get_key", "get");
}

int
extinguish_fire(string arg) 
{
    if(!fire_is_on) return 0;
    if(arg == "fire")
    {
	NF("Goblins don't let you do that.\n");
	if(present("_misty_goblin_", TO)) return 0;
	NF("Extinguish fire with what?\n");
	return 0;
    }
    if(arg == "fire with soup")
    {
	NF("Goblins don't let you do that.\n");
	if(present("_misty_goblin_", TO)) return 0;

	NF("But there is no soup left here.\n");
	if(pot_is_empty) return 0;

	TP->catch_msg("You swing pot on the chain. Some soup is spilled on "+
	  "the fire and extinguishes it.\n");
	say(QCTNAME(TP)+" swings pot on the chain. Some soup is spilled on "+
	  "the fire and extinguishes it.\n");
	fire_is_on = 0;
	TO->remove_item("fire");
	TO->add_item("logs", "@@logs_desc");
	set_alarm(40.0,0.0,"cool_soup_slowly");
	return 1;
    }
    return 0;
}

int
light_logs(string arg)
{
    if(fire_is_on) return 0;
    if(arg == "logs")
    {
	TP->catch_msg("You light the heap of logs.\n");
	say(QCTNAME(TP)+" lights the heap of logs.\n");
	fire_is_on = 1;
	soup_is_hot = 9;
	TO->add_item("fire", "@@fire_desc");
	TO->remove_item("logs");
	return 1;
    }
    return 0;
}

void 
cool_soup_slowly()
{
    if(!fire_is_on && !pot_is_empty && soup_is_hot)
    {
	tell_room(TO, "Soup in the pot cools down a bit.\n");
	soup_is_hot -= 1;
	set_alarm(180.0,0.0,"cool_soup_slowly");
    }
    return;
}

int
cool_soup(string arg)
{

    if((arg != "soup") || present("_misty_goblin_", TO) || pot_is_empty)
    {
	NF("Cool what?\n");
	return 0;
    }
    if(soup_is_hot)
    {
	if(fire_is_on)
	{
	    TP->catch_msg("You try to cool down soup by blowing at it.\n");
	    say(QCTNAME(TP)+" tries to cool down soup by blowing at it.\n");
	    return 1;
	}
	TP->catch_msg("You cool down soup a bit by blowing at it.\n");
	say(QCTNAME(TP)+" cools down soup a bit by blowing at it.\n");
	soup_is_hot -= 1;
	return 1;
    }
    TP->catch_msg("You try to cool down already cool soup.\n");
    say(QCTNAME(TP)+" tries to cool down already cool soup.\n");
    return 1;
}

int
eat_soup(string arg)
{
    if((arg != "soup") || present("_misty_goblin_", TO) || pot_is_empty)
    {
	NF("Eat what?\n");
	return 0;
    }
    if(soup_is_hot)
    {
	TP->catch_msg("You try to eat soup but it burns your tongue.\n");
	say(QCTNAME(TP)+" tries to eat soup but it burns "+
	  TP->query_possessive()+" tongue.\n");
	return 1;
    }
    if(TP->query_race_name() != "goblin")
    {
	TP->catch_msg("You eat a spoonful of the soup.\n"+
	  "It has horrible taste and makes you sick.\n"+
	  "You are very sick!\n"+
	  "You vomit even your yesterdays lunch!\n");
	say(QCTNAME(TP)+" eats a spoonful of the soup.\n"+
	  CAP(TP->query_pronoun())+" makes an unpleasant grimace. Maybe "+
	  TP->query_pronoun()+" doesn't like soup?\n"+
	  CAP(TP->query_pronoun())+" looks very sick!\n"+
	  CAP(TP->query_pronoun())+" vomits even "+TP->query_possessive()+
	  " yesterdays lunch!\n");
	TP->set_hp(MAX(1,(TP->query_hp())*4/5));
	return 1;
    }
    TP->catch_msg("You eat all the soup without leaving anything.\n");
    say(QCTNAME(TP)+" eats all the soup without leaving anything.\n");
    pot_is_empty = 1;
    TO->remove_item("soup");
    TP->set_stuffed(TP->query_stuffed() + 1000);
    return 1;
}

int
empty_pot(string arg)
{
    if((arg != "pot") || pot_is_empty)
    {
	NF("Empty what?\n");
	return 0;
    }
    if(present("_misty_goblin_", TO))
    {
	NF("Goblins don't allow you to do that.\n");
	return 0;
    }
    if(soup_is_hot)
    {
	TP->catch_msg("You touch the pot but it burns your hands.\n");
	say(QCTNAME(TP)+" touches the pot but it burns "+
	  TP->query_possessive()+" hands.\n");
	return 1;
    }
    if(TP->query_race_name() == "goblin")
    {
	TP->catch_msg("No! You can't simply throw this soup away.\n");
	say(QCTNAME(TP)+" takes pot with aim to empty it. Then "+
	  TP->query_pronoun()+" hesitates and put it back.\n");
	return 1;
    }
    TP->catch_msg("You take the pot and throw all the soup on the floor.\n");
    say(QCTNAME(TP)+" takes the pot and throws all the soup on the floor.\n");
    pot_is_empty = 1;
    TO->remove_item("soup");
    return 1;
}

int
get_key(string arg)
{
    if(!pot_is_empty || !key_is_in_pot) return 0;
    if((arg == "key") || (arg == "rusty key") || 
      (arg == "small key") || (arg == "small rusty key"))
    {
	NF("Get key from where?\n");
	return 0;
    }
    if((arg == "key from pot") || (arg == "rusty key from pot") || 
      (arg == "small key from pot") || (arg == "small rusty key from pot"))
    {
	TP->catch_msg("You get small rusty key from the pot.\n");
	say(QCTNAME(TP)+" gets small rusty key from the pot.\n");
	key_is_in_pot = 0;
	key = clone_object(OBJ_DIR + "rusty_key");
	key->set_key("_rusty_gcaves_quest_key_");
	key->move(TP);
	return 1;
    }
    return 0;
}

string
search_fun(object searcher, string str)
{
    if(!CAN_SEE_IN_ROOM(searcher))  return "";
    if((str != "pot") && (str != "soup") && 
      (str != "fire") && (str != "logs")) 
	return "";

    add_prop(OBJ_I_SEARCH_TIME, 1);

    if(fire_is_on && ((str == "fire") || (str != "logs")))
    {
	searcher->set_hp(MAX(1,(searcher->query_hp())*4/5));
	return "Ouch!!! You burn your hands severely on a fire.\n";
    }

    if(pot_is_empty && (str == "soup"))
	return "But there is no soup in pot!\n";

    if(soup_is_hot && ((str == "pot") || (str == "soup")))
    {
	searcher->set_hp(MAX(1,(searcher->query_hp())*6/7));
	return "Ouch!!! You burn your hands severely on a hot pot.\n";
    }

    add_prop(OBJ_I_SEARCH_TIME, 10);
    return "Your search reveals nothing special.\n";
}

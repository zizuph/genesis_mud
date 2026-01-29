/*
* Kala Stoneshaft of Thornhold, by Twire June, 2016
*/
inherit "std/monster";

#include <const.h>   // for G_FEMALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes
int return_yawn(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

public void
init_size()
{
	set_size_descs("short", "plump");
}

void
create_monster()
{
	if (!IS_CLONE) 
		return;

		set_name("kala");
	add_name(({"stoneshaft", "proprietress", "shopkeeper", "kala", "Kala"}));
	set_living_name("kala");
	set_title("Stoneshaft the Proprietress of the Thornhold Alehouse");
	set_race_name("dwarf"); 
	set_gender(G_FEMALE);
	set_adj(({"plump","rosy-cheeked"}));
	set_long("@@my_long");
	default_config_npc(30);
	set_base_stat(SS_CON, 100);
	set_base_stat(SS_STR, 100);
	set_base_stat(SS_DEX, 50);
	set_base_stat(SS_INT, 50);
	set_base_stat(SS_WIS, 50);

	set_skill(SS_UNARM_COMBAT,20);
	set_skill(SS_DEFENCE,80);
	set_pick_up(75);

	set_aggressive(0);
	set_attack_chance(0);

	add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
	add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */

	set_act_time(20);
	set_chat_time(20);
	add_act("grin broadly");
	add_act("emote collects some empty mugs from a nearby table.");
	add_act("emote wipes down a vacant table with a rag.");
	add_act("emote approaches the hearth and stirs the pot of onion soup " +
		    "with a wooden spoon.");
	add_act("emote opens the tap on a tankard and pours a mug of ale.");
	add_chat("Clan Stoneshaft brews the best ale on the Sword Coast!");
	add_chat("Ye've come to the right place to rest from yer travels.");
	add_chat("If ye need to stay the night, we've got room in the bunkhouse.");
	add_chat("We've had some strange lodgers lately, but all are welcome.");
	add_chat("Ye'll want to be well-fed and well-rested before ye dare " +
			 "brave the Mere of Dead Men.");
	set_alarm(0.0, 0.0, init_size);
}

init_living() 
{
	::init_living();
	if (interactive(this_player()))
	{
		set_alarm(1.0,0.0,&greet(this_player()));
	}
}

void
greet(object ob)
{
    if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) 
		return;
		
    command("say Welcome to the Thornhold Alehouse " +
    ob->query_nonmet_name() + "!");
}

my_long()
{
	if (notmet_me(this_player())) 
		this_player()->add_introduced("kala");
		
	return "This is the proprietress of the Thornhold " +
           "Alehouse. She is plump with rosy cheeks, and has coarse auburn hair " +
		   "styled into a spiraled braid on her head. Her matronly features are " +
           "framed with curly whiskers at the edge of her hairline. \n";
}

int
return_smile(string who)
{
	object ob;
   
	ob = present(who, environment());
   
	if (!ob) 
		return 0;
	   
	switch (random(4))
	{
	case 0: 
		command("smile"); 
		return 1;
	case 1: 
		command("smile " + who); 
		return 1;
	case 2: 
		if (notmet_me(ob)) 
		{
			command("introduce myself to " + who);
			return 1; 
		}
		break;
	default:
		break;
	}
	
	return 0;
}

int
return_yawn(string who)
{
	if (!who) 
		return 0;
		
	who = lower_case(who);
	
	if (random(3)) 
		return 0;
		
	command("say Tired? Ye welcome to spent the night in our bunkhouse!");
	return 1;
}

/*
 * Function name:   add_introduced
 * Description:     Add the name of a living who has introduced herself to us
 * Arguments:       str: Name of the introduced living
 * 
 * We mask this function to do some of our own things.
 */
public int
add_introduced(string who)
{
    object ob;
   
    if (!who)
    {
        return 0;
    }
	
    who = lower_case(who);
    ob = present(who, environment());
    if (!ob                         ||
        !CAN_SEE(this_object(), ob) ||
        !notmet_me(ob)              ||
        !random(20) )
    {
        return 0;
    }
	
    set_alarm(itof(random(9)), 0.0, &return_introduce());
	
	return 1;
} 

void
return_introduce()
{
	command("introduce myself");
}

void
emote_hook(string emote,object actor,string averb = 0)
{
	string name = actor->query_real_name();
   
	switch(emote)
	{
	case "yawn":
		set_alarm(3.0,0.0,&return_yawn(name));
		break;
	case "smile":
		set_alarm(3.0,0.0,&return_smile(name));
		break;
	}
}

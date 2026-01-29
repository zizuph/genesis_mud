/*
 * Trail in the hills near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <language.h>
#include <money.h>
#include <terrain.h>

//inherit HIGH_RD_DIR + "std/base_road.c";
inherit BASE_ROAD;
inherit "/lib/trade";

#define S_MASTER ("/secure/master")
#define CVP 1728
#define CONTRACTS "/d/Faerun/guilds/fire_knives/master/log/contracts"
#define CONTRACT_LOG "/d/Faerun/guilds/fire_knives/master/log/contract_log"
#define LIMIT 50
#define FIREKNIVES_MASTER "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master"

string *bHunters = ({});
string *bNames = ({});
	
mapping bRewards = ([]);
mapping bDates = ([]);

object old_man;

void
create_road()
{
//    add_prop(OBJ_S_SEARCH_FUN, "search_boulder");
//    add_prop(OBJ_I_SEARCH_TIME, 3);

    seteuid(getuid());
    
    config_default_trade();

    add_prop(ROOM_S_MAP_FILE, "sword_mt_map.txt");

    set_short("a rocky trail");
    set_extraline("Large boulders and rocks are scattered across the trail. The trail dips down into the hills, hiding your view of the surrounding area.");

    add_item(({"trail", "rocky trail", "path"}),
        "The trail is a thin line that wanders through the mountains. It " +
        "is littered with rocks which hide it from casual travellers.\n");
//    add_item(({"large boulder"}),
//        "The boulder is twice as tall as a yeti and several times as " +
//        "wide as a barrel. It's cracked and jagged partially buried in " +
//        "the dirt.\n");

    reset_faerun_room();

    add_grasslands();
    add_hills1();

    add_exit(HR_DIR + "htr06", "northeast");
    add_exit(HR_DIR + "htr04", "south");
   
    


}


int offer_contract(string a)
{
	string name;
	int reward;
	string *args;
	object player;
	
	restore_object(CONTRACTS);
    
    if (!present("_olufander", this_object()))
    {
        write("What?\n");
        
        return 1;
    }
    
	notify_fail("What? Try 'offer <number of platinum coins> "
    +"on <desired target> in order to create a contract with the "
    +"Fire Knives Assassination Outfit. Be warned - once offered, "
    +"there will be no refund.\n");
	if(!strlen(a))
		return 0;
    
	args = explode(a, " ");
    
	if(sizeof(args) != 3)
		return 0;
    
	name = args[2];
    
	if(args[1] != "for" && args[1] != "on")
		return 0;
    
	sscanf(args[0], "%d", reward);
    
	if(!reward || MAXINT / CVP < reward)
		return 0;
    
    if(member_array(TP->query_real_name(), bNames) >= 0)
	{
		notify_fail("The old decrepid man refuses to deal with you on "
        +"such matters as these.\n");
		return 0;
	}
    
    if(m_sizeof(bRewards) >= 10)
    {
        notify_fail("The old decrepid man whispers: We are not "
        +"accepting more contracts for now.\n");
		return 0;
    }
    
	if (FIREKNIVES_MASTER->is_guild_enemy(this_player()->query_name()) == 1)
    {
		notify_fail("The old decrepid man refuses to deal with you on "
        +"such matters as these.\n");
		return 0;
	}
	
	if (FIREKNIVES_MASTER->is_occ_fireknife(name) == 1)
    {
		notify_fail("The old decrepid man whispers to you: That individual is not a concern "
        +"for you at this time. Come back later.\n");
		return 0;
	}
	
	if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
    {
		notify_fail("The old decrepid man whispers to you: You are "
		+"not allowed to create contracts since you are a member.\n");
		return 0;
	}
	   
	if(!S_MASTER->exist_player(name))
	{
		notify_fail("The old decrepid man whispers to you: No such individual exist "
        +"in the Realms. Try somebody else.\n");
		return 0;
	}
    
	player = find_player(name);
    
	//if(!player)
		//player = S_MASTER->finger_player(name);
    
    if(!player)
    {
        write("The old decrepid man whispers to you: Your target must "
        +"be awake in the realms.\n");
        
        return 1;
    }
    
	if(player->query_wiz_level())
	{
		notify_fail("The old decrepid man whispers to you: We don't deal with "
        +"the immortals.\n");
		return 0;
	}
	
	int pavg = player->query_average();
	int pclimit = 1000;
	
	switch(pavg)
    {
		case 100..150:
		pclimit = 1000;
		break;
		
		case 151..200:
		pclimit = 3000;
		break;
		
		case 201..250:
		pclimit = 7000;
		break;
		
		case 251..500:
		pclimit = 9900;
		break;
		
		default:
		pclimit = 1000;
	}
	
	if (pavg < 100)
	{
		notify_fail("The old decrepid man whispers to you: We don't "
		+"deal with the weak and the frail. Try someone else of "
		+"mightier stature.\n");
		return 0;
	}
    
    if(reward < pclimit)
	{
		notify_fail("The old decrepid man whispers to you: The offer is "
        +"too low. It will cost you atleast "+pclimit+" platinum coins.\n");
		return 0;
	}
    
	if(bRewards[name] != 0)
	{
		notify_fail("The old decrepid man whispers to you: That individual is not a concern "
        +"for you at this time. Come back later.\n");
		return 0;
	}
	
	/*if(sizeof(member_array(bRewards)) > 3)
	{
		notify_fail("The old decrepid man whispers to you: Too many contracts.\n");
		return 0;
	}*/
    
	if(sizeof(pay(CVP * reward, TP, "", 0, 0, "", 1)) == 1)
	{
		notify_fail("The old decrepid man whispers to you: Bring the money first, then we "
        +"can talk.\n");
		return 0;
	}
	
	bRewards += ([name:reward]);
    bDates += ([name:ctime(time())]);
    save_object(CONTRACTS);
    
	
    
    write_file(CONTRACT_LOG, TP->query_real_name() + " PLACED: name: " + name +  
		", reward: " + bRewards[name] + " | " + ctime(time()) + "\n");
    
    write("You make a contract with the Fire Knives Assassin Outfit, placing " + 
		(reward > 1 ? reward + " platinum coins on" : "one platinum coin on") + 
		(name == TP->query_real_name() ? " - oddly enough - yourself" : " " 
		+ capitalize(name)) + ".\nThe old decrepid man urgently writes something "
		+"down on a note and sends it away with a raven.\n");
        
	say(QCTNAME(TP) + " hands some money to the old decrepit man, which "
	+"urgently writes something down on a note and sends it away with "
	+"a raven.\n");

	return 1;
}



/*

    CREATE_MAIL("Reward", "hunters", name, "",
		CAP(TP->query_real_name()) + " has sponsored a bounty for your head.\n"+
		"The hunt will now begin, consider yourself warned.\n");*/


public void init()
{
	::init();
	add_action("offer_contract", "offer");
}

void
reset_faerun_room()
{
    if (!old_man)
    {
        clone_object("/d/Faerun/guilds/fire_knives/npc/old_man")->move(this_object(), 1);
    }
	
	if(file_size(CONTRACTS + ".o") != -1)
		restore_object(CONTRACTS);
}
//
//public string
//search_boulder(object me, string arg)
//{
//    if (arg != "large boulder" )
//	    return "";
//
//    if (this_player()->query_skill(SS_AWARENESS) < 30)
//	    return "";
//
//    add_exit(HR_DIR + "mtr06", "northeast");
//    set_alarm(12.0,0.0,"remove_exit","northeast");
//    return "You search the the large boulder and find a rocky trail " +
//        "going around it.\n";
//}

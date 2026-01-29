/*
 * Nov hut for bank
 * -- Finwe, November 2007
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <terrain.h>
#include <mail.h>

inherit FAERUN_INDOORS_BASE;
inherit "/lib/trade";

#define S_MASTER ("/secure/master")
#define CVP 1728
//#define CONTRACTS "/d/Faerun/private/restrictlog/guilds/fire_knives/contracts"
//#define CONTRACT_LOG "/d/Faerun/private/restrictlog/guilds/fire_knives/contract_log"
#define CONTRACTS "/d/Faerun/guilds/fire_knives/master/log/contracts"
#define CONTRACT_LOG "/d/Faerun/guilds/fire_knives/master/log/contract_log"
#define LIMIT 50
#define FIREKNIVES_MASTER "/d/Faerun/guilds/fire_knives/master/occ_fireknives_master"
#define I_CAN_CREATE_CONTRACT       "_i_can_create_contract"
#define I_CAN_VISIT_MEETINGROOM     "_i_can_visit_meetingroom"

#define WIZARD_ENTRY_MEETING_LOG(x,y)   write_file("/d/Faerun/private/restrictlog/guilds/fire_knives/" + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

object old_man;

mapping bRewards = ([]);
mapping bDates = ([]);


string contract_instructions()
{
    string res;
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
    {
		res = "The plaque reads: Anyone who "
        +"wants to place a contract "
        +"must have been granted the permission to do so by the "
        +"Elders. The price should be agreed upon in advance(the "
        +"minimum price, 1000 Platinum coins + additional cost).\nThe command "
        +"for someone to set a contract is: offer <number of platinum coins> "
        +"on <desired target>.\n\n";
        
		return res;
	}
 
    if (this_player()->query_prop(I_CAN_CREATE_CONTRACT))
    {
        res = "The plaque reads: Anyone who "
        +"wants to place a contract "
        +"must have been granted the permission to do so by the "
        +"Elders. The price should be agreed upon in advance.\nThe command "
        +"for someone to set a contract is: offer <number of platinum coins> "
        +"on <desired target>.\n";  
        
        return res;
    }
    
    res = "The old decrepid man suddenly stops you from reading the plaque.\n";
        
    return res;
}


void
create_indoor_room()
{
    config_default_trade();
    
    set_short("inside a small meeting room");
    
    set_extraline("The hut is larger than the others and looks better "
    +"built. A single lamp hangs from the ceiling. It illuminates the many chinks "
    +"in the walls of this part of the hut. The floor is swept clean and is rather "
    +"barren with the exception of the plaque hanging on the wall here. A doorway is "
    +"seen to the east.");

    add_item(({"walls"}),
        "They are made of wood stacked on top of each other. There are chinks in "
        +"the walls where cold air blows through. The walls look sturdy and have "
        +"some shelves against them. There is a plaque on the wall, and there is a doorway "
        +"into the bank to the east.\n");
        
    add_item(({"doorway"}),
        "The doorway to the east seems to lead into the main bank area.\n");
        
    add_item(({"roof", "ceiling"}),
        "The ceiling is peaked and supported by strong beams. Hanging from the beams is a single lamp.\n");
        
    add_item(({"plaque"}), contract_instructions);

    add_item(({"lamp"}),
        "The lamp hangs from the ceiling, casting a warm glow around the room. The lamp is large and and unusually bright.\n");
        
    add_item(({"floor", "ground"}),
        "The floor is swept clean. It is made of hard-packed dirt and is oddly warm.\n");
        
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_I_NO_SCRY, "You focus on finding your "
    +"target but are suddenly repelled by an aura of musky ice.\n");

    add_exit(HR_DIR + "hut_bank", "east");
    
    add_npc("/d/Faerun/guilds/fire_knives/npc/old_man", 1);

    reset_faerun_room();
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
    +"on <desired target>' in order to create a contract with the "
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
    
    if (!this_player()->query_prop(I_CAN_CREATE_CONTRACT))
    {
        notify_fail("You have not yet permission to order a contract.\n");
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
    
	/*player = find_player(name);
    
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
	}*/
	
	//int pavg = player->query_average();
	int pclimit = 1000;
	
	/*switch(pavg)
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
	}*/
	
	/*if (pavg < 100)
	{
		notify_fail("The old decrepid man whispers to you: We don't "
		+"deal with the weak and the frail. Try someone else of "
		+"mightier stature.\n");
		return 0;
	}*/
    
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
    
	if(sizeof(pay(CVP * reward, TP, "", 0, 0, "", 1)) == 1)
	{
		notify_fail("The old decrepid man whispers to you: Bring the money first, then we "
        +"can talk.\n");
		return 0;
	}
	
	bRewards += ([name:reward]);
    bDates += ([name:ctime(time())]);
    save_object(CONTRACTS);
    
    int customerid = random(50000);
    
    string boss;
    string mentor;
    string fist;
    
    boss = FIREKNIVES_MASTER->list_boss();
    mentor = FIREKNIVES_MASTER->list_mentor();
    fist = FIREKNIVES_MASTER->list_fist();
      
    //write_file(CONTRACT_LOG, TP->query_real_name() + " PLACED: name: " + name +  
	//	", reward: " + bRewards[name] + " | " + ctime(time()) + "\n");
        
    write_file(CONTRACT_LOG, "Customer "+customerid+" PLACED: Target: " + name +  
		", reward: " + bRewards[name] + " | " + ctime(time()) + "\n");
    
    write("You make a contract with the Fire Knives Assassin Outfit, placing " + 
		(reward > 1 ? reward + " platinum coins on" : "one platinum coin on") + 
		(name == TP->query_real_name() ? " - oddly enough - yourself" : " " 
		+ capitalize(name)) + ".\nThe old decrepid man urgently writes something "
		+"down on a note and sends it away with a raven.\n");
        
	say(QCTNAME(TP) + " hands some money to the old decrepit man, which "
	+"urgently writes something down on a note and sends it away with "
	+"a raven.\n");
    
    TP->remove_prop(I_CAN_CREATE_CONTRACT);
    
    if (boss != 0)
    {
        CREATE_MAIL("Contract", "Customer", boss, "",
        "Customer "+TP->query_real_name()+" placed a contract on "+
        name+".\nCustomer ID = "+customerid+".");
    }
    
    if (mentor != 0)
    {   
        CREATE_MAIL("Contract", "Customer", mentor, "",
        "Customer "+TP->query_real_name()+" placed a contract on "+
        name+".\nCustomer ID = "+customerid+".");
    }
     
    if (fist != 0)
    {     
        CREATE_MAIL("Contract", "Customer", fist, "",
        "Customer "+TP->query_real_name()+" placed a contract on "+
        name+".\nCustomer ID = "+customerid+".");
    }

	return 1;
}


int check_target(string a)
{
	string name;
	int reward;
	string *args;
	object player;
	
	restore_object(CONTRACTS);

    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
    {
		notify_fail("What? Try 'check <target>'.\n");
    
        if(!strlen(a))
            return 0;
        
        name = a;
        
        /*args = explode(a, " ");
        
        if(sizeof(args) != 3)
            return 0;
        
        name = args[1];
        
        if(args[1] != "for" && args[1] != "on")
            return 0;
        
        sscanf(args[0], "%d", reward);
        
        if(!reward || MAXINT / CVP < reward)
            return 0;*/
        
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
        {
            notify_fail("Only the Elders can use this command.\n");
            return 0;
        }
                
        if(m_sizeof(bRewards) >= 10)
        {
            notify_fail("We have enough contracts for now. New ones can't be made "
            +"until old ones are completed.\n");
            return 0;
        }
            
        if (FIREKNIVES_MASTER->is_occ_fireknife(name) == 1)
        {
            notify_fail("That is a member of the Outfit.\n");
            return 0;
        }
               
        if(!S_MASTER->exist_player(name))
        {
            notify_fail("No such individual exist "
            +"in the Realms. Try somebody else.\n");
            return 0;
        }
        
        player = find_player(name);
        
        if(!player)
        {
            write("The individual must "
            +"be awake in the realms.\n");
            
            return 1;
        }
        
        if(player->query_wiz_level())
        {
            notify_fail("We don't deal with "
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
            notify_fail("Too small. We don't "
            +"deal with the weak and the frail.\n");
            return 0;
        }
        
        if(bRewards[name] != 0)
        {
            notify_fail("That individual is already contracted by someone.\n");
            return 0;
        }
        
        write("The base price for that individual is "+pclimit+" platinum coins. The "
        +"price you should request is: Baseprice + additioal fees and cost of your "
        +"own choosing.\n");
        
        return 1;
	}
    
    
    notify_fail("What?\n");
    
    if(!strlen(a))
    return 0;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_MEETING_LOG("wizard_entry_meeting_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives contract meeting room in the village.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


public void init()
{
	::init();
	add_action("offer_contract", "offer");
    //add_action("check_target", "check");
}


void
reset_faerun_room()
{
    /*if (!old_man)
    {
        old_man = clone_object("/d/Faerun/guilds/fire_knives/npc/old_man");
        old_man->move(this_object(), 1);
    }*/
	
	if(file_size(CONTRACTS + ".o") != -1)
		restore_object(CONTRACTS);
}

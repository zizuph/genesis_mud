/* /d/Faerun/guilds/fire_knives/rooms/contracts.c
 *
 * Contracts Room.
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h> 
#include <wa_types.h>
#include <filter_funs.h>
#include <language.h>
#include <money.h>
#include <files.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;
inherit "/d/Faerun/lib/tail.c";
inherit "/lib/trade";

#define S_MASTER ("/secure/master")

/* How much copper one pc is worth. */
#define CVP 1728

#define CONTRACTS "/d/Faerun/guilds/fire_knives/master/log/contracts"
//#define CONTRACTS "/d/Faerun/private/restrictlog/guilds/fire_knives/contracts"
#define LIMIT 50
#define S_MASTER ("/secure/master")
#define CONTRACT_LOG "/d/Faerun/guilds/fire_knives/master/log/contract_log"
//#define CONTRACT_LOG "/d/Faerun/private/restrictlog/guilds/fire_knives/contract_log"

//#define TP this_player()
//#define CAP capitalize(x);

public string contract_log();

string *bHunters = ({});
string *bNames = ({});
    
mapping bRewards = ([]);
mapping bDates = ([]);


/*
* Function name: list_log
* Description  : Print the file that keeps the logs 
* Returns      : ""
*/
public string contract_log()
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return "Only the Elders may read the contract logs.\n";
    }
    
    write("You read the log containing the information "
    +"about the contracts:\n");
    
    seteuid(getuid());
    
    if (query_verb() == "tail")
    {
        tail_file(CONTRACT_LOG);
    }
    else
    {
        this_player()->more(read_file(CONTRACT_LOG, 1), 0);
    }

    tell_room(this_object(), QCTNAME(this_player())
        + " reads the log of the contracts.\n", this_player());
        
    return "";
}


string contract_list()
{
    string res;
    
    restore_object(CONTRACTS);
    
    res = "The plaque is used for keeping track of "
    +"active assassination contracts, and if you have completed one, "
    +"you may, with the permission of the Elders, "
    +"'complete contract of <target>'. Elders may 'forfeit' a contract "
    +"if it's somehow no longer valid (coins are collected by the "
    +"Elder forteiting it).";
    
    if(!m_sizeof(bRewards))
        return res + " The plaque is empty at this time.\n";
            
    res += ". It shows the following contracts: \n";
    
    for(int i = 0; i < sizeof(m_indexes(bRewards)); ++i)
        res += capitalize(m_indexes(bRewards)[i]) 
        + " is contracted for a " +
        (bRewards[m_indexes(bRewards)[i]] > 1 ?
            bRewards[m_indexes(bRewards)[i]] 
            + " platinum coins.\n": "one platinum coin.\n");
    return res;
}


public string *get_bounties()
{
    return m_indexes(bRewards);
}


public string *get_hunters()
{
    return bHunters;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hall of commitment");
    
    set_long("Inside the small cubic room there is nothing "
    +"that stands out more "
    +"that the small three-leveled fountain "
    +"in the middle of the room, from which "
    +"clear fresh water continuously falls from "
    +"the uppermost level downwards and "
    +"finally into the recess at its base. The "
    +"flowing, calming sound drowns any "
    +"other made in this place. The stone walls "
    +"have been cut evenly and layered "
    +"with perfectly placed bricks. From the "
    +"western end hang two double candle "
    +"holders with lit candles in them, one "
    +"to each side of a small plaque "
    +"containing information about "
    +"contracts. Next to the small plaque you notice "
    +"a record and a wooden board.\n");
    
    add_item(({"room", "cubic room"}),
    "The room is small and cubic, perfectly evened "
    +"by expertedly layed layers "
    +"of bricks on each wall. In its center is "
    +"a fountain from which fresh "
    +"clean water flows.\n");

    add_item(({"fountain"}),
    "The fountain has three levels. At the top, "
    +"water springs upwards and falls "
    +"down to the second, and then to the "
    +"third before it overflows down into "
    +"the recess at the base through which it "
    +"disappears. It is bare of any "
    +"special carvings, its existence more functional than decorative. \n");

    add_item(({"water"}),
    "The water appears fresh and clean, clear "
    +"as you have ever seen.\n");

    add_item(({"recess", "base"}),
    "At the base of the fountain is a recess into "
    +"which the overflowing water from "
    +"the fountain falls into before disappearing through it.\n");

    add_item(({"wall","walls","bricks",}),
    "The walls are cut perfectly even, giving the "
    +"sense of being within a cube and "
    +"surrounded by bricks. From the western one "
    +"hang two double candle holders with "
    +"lit candles on it, each at a side of the "
    +"rectangular orifice at stomach level "
    +"height.\n");

    add_item(({"candle holders","holders","holder","candle holder"}),
    "The candle holders seem simple and functional, "
    +"made of a strong metal and rather "
    +"bare. They each hold two lit candles.\n");

    add_item(({"candles","candle","lit candle","lit candles"}),
    "Thick wax candles burn rather slowly at each "
    +"side of each candle holder, shedding "
    +"off enough light to the area that most demands it.\n");

    add_item(({"orifice","rectangular orifice"}),
    "A small rectangular orifice is at about half a "
    +"body upwards from the floor in the "
    +"western end of the room. Its width and "
    +"height is barely enough to make your voice "
    +"heard through, pass scrolls and documents, "
    +"or other similar items.\n");

    add_item(({"darkness"}),
    "Within the orifice you can see nothing but "
    +"darkness. Whatever lies beyond is hidden "
    +"from view.\n");

    add_item(({"ceiling"}),
    "The ceiling is lost in its height, the light "
    +"of the candles not reaching it.\n");

    add_item(({"floor"}),
    "The floor is covered with dark reddish tiles "
    +"that seem thick enough to withstand "
    +"any weight. The sound of the falling water "
    +"reverberates on it and bounces off the "
    +"walls, covering every other possible sound.\n");
    
    add_item(({"plaque"}), contract_list);
    
    add_item(({ "contractlog", "record" }), contract_log);
    add_cmd_item(({ "contractlog", "record" }), 
    ({ "read", "tail" }), contract_log);
    
    room_add_object(FIREKNIVES_BOARDS_DIR + "contract_board");

    config_default_trade();
    
    add_exit(FIREKNIVES_ROOMS_DIR + "h6.c", "east");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if(file_size(CONTRACTS + ".o") != -1)
        restore_object(CONTRACTS);
}


int complete_contract(string a)
{
    string name;
    
    restore_object(CONTRACTS);
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        if (!this_player()->query_prop(I_CAN_COMPLETE_CONTRACT))
        {
            notify_fail("You have no permission to currently complete "
            +"a contract. Contact the Elders.\n");
            return 0;
        }
    }
    
    notify_fail("What? 'Complete contract of <target>'.\n");
    if(!strlen(a))
        return 0;
    
    if(!parse_command(a, ({}), " [contract] 'of' %w ", name))
        return 0;
    
    notify_fail("No contract on that one.\n");
    
    if(!S_MASTER->exist_player(name))
        return 0;
    
    if(!bRewards[name])
        return 0;
    
    MONEY_MAKE_PC(bRewards[name])->move(TP);
    write("You get your payment for completing the contract.\nBy "
    +"completing a contract, your reputation as an effective assassin "
    +"has improved slightly!\n");
    
    say(QCTNAME(TP) + " collects some money for completing a contract.\n");
    
    write_file(CONTRACT_LOG, TP->query_real_name() 
    + " CLAIMED: name: " +name +  
    ", reward: " + bRewards[name] + " | " + ctime(time()) + "\n");
        
    m_delkey(bRewards, name);
    m_delkey(bDates, name);
    
    save_object(CONTRACTS);
    
    this_player()->remove_prop(I_CAN_COMPLETE_CONTRACT);
    
 
    int x;

    x = FIREKNIVES_MAPPINGS->query_assassin_gauge(this_player()->query_name());

    if (x >= MAX_ASSASSIN_GAUGE)
    {
        // Cleanup. In case the rank os somehow above the
        // allowed limit.
        x = MAX_ASSASSIN_GAUGE;
        
        FIREKNIVES_MAPPINGS->set_assassin_gauge(this_player()->query_name(),x);

        return 1;
    }

    x = x + 1;

    FIREKNIVES_MAPPINGS->set_assassin_gauge(this_player()->query_name(), x);

    return 1;
}


int forfeit_contract(string a)
{
    string name;
    
    restore_object(CONTRACTS);
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {     
        return 0;     
    }
    
    notify_fail("What? 'Forfeit contract of <target>'.\n");
    if(!strlen(a))
        return 0;
    
    if(!parse_command(a, ({}), " [contract] 'of' %w ", name))
        return 0;
    
    notify_fail("No contract on that one.\n");
    
    if(!S_MASTER->exist_player(name))
        return 0;
    
    if(!bRewards[name])
        return 0;
    
    MONEY_MAKE_PC(bRewards[name])->move(TP);
    write("You take the payment for forfeiting the contract.\nThe contract is "
    +"removed from the list.\n");
    
    say(QCTNAME(TP) + " collects some money for forfeiting a contract.\n");
    
    write_file(CONTRACT_LOG, TP->query_real_name() 
    + " FORFEITED: name: " +name +  
    ", forfeited: " + bRewards[name] + " | " + ctime(time()) + "\n");
        
    m_delkey(bRewards, name);
    m_delkey(bDates, name);
    
    save_object(CONTRACTS);
    
    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_CONTRACTS_LOG("wizard_entry_conracts_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives contract room.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


public void init()
{
    ::init();
    add_action("complete_contract", "complete");
    add_action("forfeit_contract", "forfeit");
}


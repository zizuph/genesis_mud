#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <state_desc.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Ansalon/guild/neidar/guild.h"

inherit THARK_IN;
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

mapping most_kill_list = ([ ]);
mapping average_kill_list = ([ ]);
mapping flagellants_list = ([ ]);

object board;

void
reset_tharkadan_room()
{
    if(!objectp(board))
    {
       board = clone_object(TOBJ + "slayers_board");
       board->move(TO, 1);
    }
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"hall","lodgepole hall","chapter house",
        "hall of slayers","house"}),
        "@@long_descr");

    add_item(({"great carved lists","carved lists","lists","list",
        "walls","wall"}),
        "Along the walls here hang great carved lists outlining " +
        "the various feats of the Doomslayers. You can:\n" +
        "     'list' Greatest Slayers\n"+
        "     'list' Prolific Killers\n"+
        "     'list' Dwarven Flagellants\n"+
        "     'list' Greatest Kills\n\n");

    add_item(({"plaque"}),
        "@@read_plaque");
    add_cmd_item(({"plaque"}),"read","@@read_plaque");

    add_exit(ROOM + "dwarf/village1","south", 0);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "the hill dwarven Hall of Slayers";
}

string
long_descr()
{
    return "You stand within a great lodgepole hall within the " +
        "centre of a dwarven village in the Tharkadan Mountain Range, " +
        "the Hall of Slayers - a chapter house for those dwarves " +
        "who have taken a death oath and dedicated their life to " +
        "meeting their end in glorious battle. Great carved lists " +
        "highlight the feats of the greatest of the Doomseekers, " +
        "and hang along the walls here. A plaque has been nailed to " +
        "the back wall that can be read.\n"; 
}

string
read_plaque()
{
   string plaque_str = "Neidar Clan Warrior Death Oath\n\n"+
       "Carving your name into the dwarven Tree of Ancestors is the act\n" +
       "of taking a death-oath before your clan, your kin, your family.\n\n" +
       "You are publicly claiming ownership of an act of dishonour,\n" +
       "shame, or cowardice that can only be redeemed through forsaking\n" +
       "everything and seeking nothing more than an honourable and\n" +
       "glorious death as a Doomseeker.\n\n" +
       "Doomseekers dedicate their entire fibre of being to the hardest\n" +
       "and most destructive life of battle that can be found. They\n" +
       "travel into treacherous wilderness and deliberately seek out mighty\n" +
       "battles, fearsome foes, and overwhelming odds.\n\n" +
       "They forsake all armours and defensive abilities, relying only on\n" +
       "a furious chop and and potentially suicidal battlerage that becomes\n" +
       "more potent the closer to death one comes.\n\n" +
       "Upon death, a Doomseeker is redeemed and returns to being an\n" +
       "honourable Neidar Clan Warrior as they were before taking the oath\n" +
       "and their deeds recorded on the Tree of Ancestors.\n\n";

    plaque_str = generate_scroll_text(plaque_str, "Oath of the " +
            "Doomseekers");

    write(plaque_str);

    return ""; 
}

int 
sort_by_average(string a, string b) 
{
    mapping list = ADMIN_MANAGER->query_greatest_kill();
 
    return list[b][0] - list[a][0]; 
}

int 
sort_by_most_kills(string a, string b) 
{
    return most_kill_list[b] - most_kill_list[a]; 
}

int 
sort_by_average_kills(string a, string b) 
{
    return average_kill_list[b] - average_kill_list[a]; 
}

int 
sort_by_flagellants(string a, string b) 
{
    return average_kill_list[a] - average_kill_list[b]; 
}

string *
flagellants_list()
{
    mixed * kill_list;
    flagellants_list = ([ ]);
    mapping members = ADMIN_MANAGER->query_neidar_doomseeker_list();

    foreach(mixed name, mixed num: members)
    {
        int kills = ADMIN_MANAGER->query_doomseeker_kills(name);
        int ratio = ADMIN_MANAGER->query_doomseeker_health(name) / kills;
        flagellants_list += ([ name : ratio ]);
    }

    kill_list = sort_array(m_indices(flagellants_list), sort_by_flagellants);

    return kill_list;
}

string *
average_kills_list()
{
    mixed * kill_list;
    average_kill_list = ([ ]);
    mapping members = ADMIN_MANAGER->query_neidar_doomseeker_list();

    foreach(mixed name, mixed num: members)
    {
        int kills = ADMIN_MANAGER->query_doomseeker_average(name);
        average_kill_list += ([ name : kills ]);
    }

    kill_list = sort_array(m_indices(average_kill_list), sort_by_average_kills);

    return kill_list;
}

string *
most_kills_list()
{
    mixed * kill_list;
    most_kill_list = ([ ]);
    mapping members = ADMIN_MANAGER->query_neidar_doomseeker_list();

    foreach(mixed name, mixed num: members)
    {
        int kills = ADMIN_MANAGER->query_doomseeker_kills(name);
        most_kill_list += ([ name : kills ]);
    }

    kill_list = sort_array(m_indices(most_kill_list), sort_by_most_kills);

    return kill_list;
}

string *
greatest_kill_list()
{
    mapping list = ADMIN_MANAGER->query_greatest_kill();

    mixed * kill_list;
    kill_list = sort_array(m_indexes(list), sort_by_average);

    return kill_list;
}

void
init()
{
    ::init();

    ADA("list");
}

string
health_ratio_desc(int ratio)
{
    switch(ratio)
    {
        case 0..6:
            return "at death's door";
        case 7..14:
            return "barely alive";
        case 15..20:
            return "terribly hurt";
        case 21..27:
            return "in a very bad shape";
        case 28..33:
            return "in agony";
        case 34..40:
            return "in a bad shape";
        case 41..46:
            return "very hurt";
        case 47..53:
            return "suffering";
        case 54..59:
            return "hurt";
        case 60..66:
            return "aching";
        case 67..72:
            return "somewhat hurt";
        case 73..79:
            return "slightly hurt";
        case 80..85:
            return "sore";
        case 86..92:
            return "feeling well";
        default:
            return "feeling very well";
    }

    return "";
}

int
list(string str)
{    
    if(!str)
    {
       notify_fail("List what? Greatest Slayers? Prolific Killers? Or " +
           "greatest kills?\n");
       return 0;
    }

    str = lower_case(str);

    if(str == "greatest slayers")
    {
        string * kills_array = average_kills_list();
        string list_str = "The top 10 Greatest Slayers of the Doomseekers:  \n\n";
        int count = 0;

        foreach(string name: kills_array)
        {
            count++;
            int kill_nos = ADMIN_MANAGER->query_doomseeker_kills(name);
            int kills = average_kill_list[name];
            int av_kill_size = kills / kill_nos;
            list_str += count + ".  "+capitalize(name)+ " has slain " +
                kill_nos+ " foes,\n      primarily " +
                LANG_PWORD(GET_EXP_LEVEL_DESC(av_kill_size, 0))+ 
                " in challenge.\n";
        }

        int kill_array_size = sizeof(kills_array);

        if(kill_array_size < 10)
        {
            for(kill_array_size; kill_array_size < 10; 0)
            {
                kill_array_size++;
                if(kill_array_size < 10)
                    list_str += kill_array_size + ".  ............................\n";
                else
                    list_str += kill_array_size + ".  ...........................\n";
            }
        }

        list_str = generate_scroll_text(list_str, "Greatest Slayers of the Doomseekers");
        write(list_str);
        say(QCTNAME(TP)+ " examines the list of the Greatest Slayers of the " +
             "Doomseekers.\n");
        return 1;
    }

    if(str == "prolific killers")
    {
        string * kills_array = most_kills_list();
        string list_str = "The top 20 Prolific Slayers of the Doomseekers:  \n\n";
        int count = 0;

        foreach(string name: kills_array)
        {
            count++;
            int kills = most_kill_list[name];
            list_str += count + ".  "+capitalize(name)+ ", with " +
                kills+ " foes defeated.\n";
        }

        int kill_array_size = sizeof(kills_array);

        if(kill_array_size < 20)
        {
            for(kill_array_size; kill_array_size < 20; 0)
            {
                kill_array_size++;
                if(kill_array_size < 10)
                    list_str += kill_array_size + ".  ............................\n";
                else
                    list_str += kill_array_size + ".  ...........................\n";
            }
        }

        list_str = generate_scroll_text(list_str, "Most Prolific Slayers of the " +
            "Doomseekers");
        write(list_str);
        say(QCTNAME(TP)+ " examines the list of the most Prolific Slayers of " +
            "the Doomseekers.\n");
        return 1;
    }

    if(str == "greatest kills")
    {
        mapping list = ADMIN_MANAGER->query_greatest_kill();
        string * kills_array = greatest_kill_list();
        string list_str = "Slayer Leaderboard of Greatest Foes defeated in battle:  \n\n";
        int count = 0;

        foreach(string name: kills_array)
        {
            count++;
            string enemy = list[name][1];
            list_str += count + ".  "+capitalize(enemy)+ ", slain by " +
                capitalize(name)+ ".\n";
        }

        int kill_array_size = sizeof(kills_array);

        if(kill_array_size < 20)
        {
            for(kill_array_size; kill_array_size < 20; 0)
            {
                kill_array_size++;
                if(kill_array_size < 10)
                    list_str += kill_array_size + ".  ............................\n";
                else
                    list_str += kill_array_size + ".  ...........................\n";
            }
        }

        list_str = generate_scroll_text(list_str, "Greatest Kills of the Doomseekers");
        write(list_str);
        say(QCTNAME(TP)+ " examines the list of the greatest Doomseeker " +
           "kills.\n");
        return 1;
    }

    if(str == "dwarven flagellants")
    {
        string * kills_array = flagellants_list();
        string list_str = "The top 20 Dwarven Flagellants and Self-Mortifiers:  \n\n";
        int count = 0;

        foreach(string name: kills_array)
        {
            int kill_nos = ADMIN_MANAGER->query_doomseeker_kills(name);

            if(kill_nos < 100)
            {
                kills_array -= ({ name });
            }
            else
            {
                count++;
                int ratio = ADMIN_MANAGER->query_doomseeker_health(name) / kill_nos;
                string damage_desc = health_ratio_desc(ratio);
                list_str += count + ".  "+capitalize(name)+ " commonly " +
                    "leaves battle victorious at " +damage_desc+ ".\n";
            }
        }

        int kill_array_size = sizeof(kills_array);

        if(kill_array_size < 20)
        {
            for(kill_array_size; kill_array_size < 20; 0)
            {
                kill_array_size++;
                if(kill_array_size < 10)
                    list_str += kill_array_size + ".  ............................\n";
                else
                    list_str += kill_array_size + ".  ...........................\n";
            }
        }

        list_str = generate_scroll_text(list_str, "Based on 100+ victorious battles");
        write(list_str);
        say(QCTNAME(TP)+ " examines the list of the Dwarven Flagellants " +
             "and Self-Mortifiers.\n");
        return 1;
    }

    write("List what? Greatest Slayers? Prolific Killers? Dwarven " +
        "Flagellants? Or greatest kills?\n");
    return 1;
}

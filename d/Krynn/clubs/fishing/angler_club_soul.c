/* 
 * Created by Arman March 2021
 *
 * This soul holds the general commands and feelings of the angler club.
 */

inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "fishing.h"

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include "/d/Krynn/open/sys/composite.h"
#include <language.h>

mapping fish_weight_list = ([ ]);

string 
get_soul_id() 
{ 
    return "Krynn Angler Club"; 
}

int query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    seteuid(getuid());

    return ([
             //            Emotes
             "abrag"         :       "abrag",
             "aconsider"     :       "aconsider",
             "apractice"     :       "apractice",
             "aponder"       :       "aponder",

             //            Commands
             "angler"        :       "angler",
             "fishing"       :       "fishing",
	     "help"          :       "help",
             "abandon"       :       "abandon",
	     ]);
}

public int
abrag(string str)
{
    mapping list;
    string player = this_player()->query_real_name();

    list = FISHING_MANAGER->query_player_fish_caught(player);
    
    if (!str || !m_sizeof(list))
    {
        write("You brag about the size of the fish you caught, " +
            "but managed to get away!\n");
        all(" brags about a fish " +HE(this_player())+ " caught, " +
            "but managed to get away!");           
        return 1;
    }

    if (member_array(str, m_indexes(list)) == -1)
    {
        notify_fail("You have not caught any " +str+ " to brag about!\n");           
        return 0;
    }

    int * stats = list[str];
    int value = stats[0];
    string weight;

    /* Display whole kilograms or grams. */
    if (value > 1000)
        weight = (value / 1000) + " kilograms";
    else
        weight = value + " grams";

    write("You brag about the size of the " +str+ " you once caught, " +
        "easily over " +weight+ "!\n");
    all(" brags about the size of a " +str+ " " +HE(this_player())+ 
        " once caught, easily over " +weight+ "!\n");    
 
    return 1;
}

public int
aconsider(string str)
{
    write("You consider thoughtfully what bait would be best in this situation.\n");
    all(" philosophically considers thoughtfully what bait would be best in " +
        "this situation.");     
    return 1;
}

public int
apractice(string str)
{
    object *rod;
    
    if (!str)
    {
        write("You longingly imagine a river brimming with fish " +
            "before you, and cast an imaginary fishing line in " +
            "to it.\n");
        all(" longingly imagines a river brimming with fish, " +
            "and casts an an imaginary fishing line in to it.");           
        return 1;
    }

    rod = parse_this(str, "[with] %o");

    if (!sizeof(rod))
    {
        write("You longingly imagine a river brimming with fish " +
            "before you, and cast an imaginary fishing line in " +
            "to it.\n");
        all(" longingly imagines a river brimming with fish, " +
            "and casts an an imaginary fishing line in to it.");           
        return 1;
    }
    
    if (!rod[0]->query_held() && (!rod[0]->id("fishing rod")))
    {
        write("You longingly imagine a river brimming with fish " +
            "before you, and cast an imaginary fishing line in " +
            "to it.\n");
        all(" longingly imagines a river brimming with fish, " +
            "and casts an an imaginary fishing line in to it.");           
        return 1;
    }

    write("You longingly imagine a river brimming with fish " +
        "before you, and practice casting your " +rod[0]->short() +
            " in to it.\n");
    all(" longingly imagines a river brimming with fish, " +
        "and practices casting " +HIS(this_player())+ " " +
        rod[0]->short()+ " in to it.");     
    return 1;
}

public int
aponder(string str)
{
    write("You philosophically ponder where your next great fishing " +
        "adventure will be, and that there is always a new river " +
        "somewhere.\n");
    all(" philosophically ponders where " +HIS(this_player())+ " next " +
        "great fishing adventure will be, and that there is always a " +
        "new river somewhere.");     
    return 1;
}

int 
sort_fish_by_weight(string a, string b) 
{
    return fish_weight_list[b] - fish_weight_list[a]; 
}

int
angler(string str)
{
    mixed * weight_list;
    fish_weight_list = ([ ]);
    mapping list; 
    string fish, * fish_strings, fish_list;

    if (!str)
	return 0;

    if (sscanf(str, "leaderboard %s", fish) != 1)
    {
        notify_fail("Angler leaderboard what? A type of fish caught?\n");
	return 0;
    }

    if(sizeof(explode(fish, " ")) > 1)
    {
        fish_strings = explode(fish, " ");
        fish_list = fish_strings[0] + "_" + fish_strings[1];
    }
    else
        fish_list = fish;

    list = FISHING_MANAGER->query_leaderboard_fish_caught(fish_list);

    if (!m_sizeof(list))
    {
        notify_fail("There is no angler leaderboard for " +fish+ ".\n");
        return 0;
    }

    foreach(string rank, mixed * stats : list)
    {
        string player = stats[0];
        int fish_weight = stats[1];
        fish_weight_list += ([ rank : fish_weight ]);
    }
    weight_list = sort_array(m_indices(fish_weight_list), sort_fish_by_weight);

    TP->catch_tell("\n");
    TP->catch_tell(
        "                     ANGLER LEADERBOARD\n" +
        "          The Top 10 biggest " +fish+ " catches  \n" +
        "+--------------------------------------+--------------------+\n");

    int ranking = 0;

    foreach(string rank : weight_list) 
    {
        ranking++;
        mixed * stats = list[rank];
        string ranking_text = ranking + ".";
        string player = capitalize(stats[0]);
        int value = stats[1];
        string weight;

        /* Display whole kilograms, fractions of kilograms or grams. */
        if ((value > 10000) || (!(value % 1000)))
            weight = (value / 1000) + " kg";
        else if (value > 1000)
            weight = sprintf("%5.3f", itof(value) / 1000.0) + " kg";
        else
            weight = value + " g";

        TP->catch_tell(sprintf("|%-:10s %-:26s | %-:18s |\n",
            ranking_text, player, weight));
    }
    TP->catch_tell(
        "+--------------------------------------+--------------------+\n");

    return 1;
} 

int
fishing(string str)
{
    mixed * weight_list;
    fish_weight_list = ([ ]);
    mapping list = FISHING_MANAGER->query_player_fish_caught(TP);

    if (!str)
	return 0;

    if (str != "tally")
    {
        notify_fail("Fishing what? Tally?\n");
	return 0;
    }

    if (!m_sizeof(list))
    {
        notify_fail("You haven't caught any fish yet, so don't have a " +
            "fishing tally.\n");
        return 0;
    }

    foreach(string fish, int * stats : list)
    {
        int fish_weight = stats[0];
        fish_weight_list += ([ fish : fish_weight ]);
    }
    weight_list = sort_array(m_indices(fish_weight_list), sort_fish_by_weight);

    TP->catch_tell("\n");
    TP->catch_tell(
        "               Fish type                  Biggest catch        Num. caught  \n" +
        "+--------------------------------------+--------------------+--------------+\n");
    foreach(string fish : weight_list) 
    {
        int * stats = list[fish];
        int value = stats[0];
        int quantity = stats[1];
        string weight;

        /* Display whole kilograms, fractions of kilograms or grams. */
        if ((value > 10000) || (!(value % 1000)))
            weight = (value / 1000) + " kg";
        else if (value > 1000)
            weight = sprintf("%5.3f", itof(value) / 1000.0) + " kg";
        else
            weight = value + " g";

        if(fish == "/d/Krynn/common/fishing/junk")
            fish = "junk";

        if(strlen(fish) && strlen(weight))
            TP->catch_tell(sprintf("| %-:36s | %-:18s | %12d |\n",
                fish, weight, quantity));
    }
    TP->catch_tell(
        "+--------------------------------------+--------------------+--------------+\n");

    return 1;
} 


int
help(string str)
{
    if (!str)
	return 0;

    if (sscanf(str, "angler %s", str) != 1)
    {
	return 0;
    }

    if (str == "club" || str == "help")
    {
        tell_object(TP,"\n" +
        "                           ', \n"+
        " \\               _________/ \\, \n"+
        "  \\   ,,--- ;:;:;:;:;:;:;:;;:;:; \\ \n"+
        "   \\X/~   \\  {@}:;:;:;:;:;: ;:;:;\\ \n"+
        "    | \\     \\ :;:;:;:;:;:;:;,___,;:;| \n"+
        "      ||    |  )     ;:;:;:/   / ;:;\\ \n"+
        "      // , /        )( ;:;/   / ;i| !| \n"+
        "     (====))       )   ^,/___/;::;:;:| \n"+
        "      `--==----'''''           ;:;:;!| \n"+
        "          `--- ,-__      __     ;:;:;| \n"+
        "                   \\_  =  ,,/   !:;:;| \n"+
        "       o             `\\__ \\/   :;|i!| \n"+
        "         ANGLERS   '       `, .;:;:/ \n"+
        "          CLUB    o          `,   / \n"+
        "     o               ______/::: ,/ \n"+
        "                     \\:;;::;::; / \n"+
        "                        `;:;:;:/ \n"+
        "\n"+
        "\n"+
        "        'help angler club'        This menu\n"+
        "        'help angler commands'    List of angler commands\n" +
        "        'help angler emotes'      List of angler emotes\n" +
        "        'help angler titles'      List of angler titles\n" +
        "        'help angler guide'       A guide to fishing\n" +
        "\n");
        return 1;
    }
    if (str == "commands")
    {
        tell_object(TP,"\n" +
        "            ------====< ANGLER COMMANDS >====------\n\n" +
        "   'fishing tally'                     List of your historical\n" +
        "                                       catches.\n\n" +
        "   'angler leaderboard <fish type>'    List the top 10 catches\n" +
        "                                       for fish type.\n\n" +
        "   'fillet <fish>'                     Fillet a caught fish down\n" +
        "                                       to eatable portions.\n\n" +
        " Commands with fishing rod:\n\n" +
        "   'hold / release rod'\n" +
        "   'bait hook / rod with <bait type>'\n" +
        "   'cast rod'\n" +
        "   'reel rod'\n" +
        "\n\n");
        return 1;
    }
    if (str == "emotes" || str == "emotions")
    {
        tell_object(TP,"\n" +
        "            ------====< ANGLER EMOTES >====------\n\n" +
        "    abrag <fish>                   Brag about your fishing prowess.\n" +
        "    aconsider                      Consider what bait to use.\n" +
        "    apractice <fishing rod>        Practice casting your rod.\n" +
        "    aponder                        Ponder the philosophies of the angler.\n" +
        "\n\n    <> optional field\n" +
        "    [] required field\n"+
        "\n\n");
        return 1;
    }
    if (str == "titles")
    {
        tell_object(TP,"\n" +
        "            ------====< ANGLER TITLES >====------\n\n" +
        "    When an angler wears their bait satchel they display to others\n" +
        "    that they are a fishing hobbyist of varying titles depending on\n" +
        "    the experience they have gained fishing. The order of descriptive\n" +
        "    titles are:\n\n" +
        "             Novice\n" +
        "             Amateur\n" +
        "             Enthusiastic\n" +
        "             Weathered\n" +
        "             Practiced\n" +
        "             Experienced\n" +
        "             Adept\n" +
        "             Skillful\n" +
        "             Veteran\n" +
        "             Expert\n" +
        "             Professional\n" +
        "             Phenomenal\n" +
        "             Prodigious\n" +
        "             Champion\n" +
        "             Legendary\n" +
        "             Master\n" +
        "\n\n");
        return 1;
    }
    if (str == "guide")
    {
        tell_object(TP,"\n" +
        "           ------====< A GUIDE TO FISHING >====------\n\n" +
        "      Of all the professions none is more dangerous than that\n" +
        "   of the fisherman. The forces of nature are displayed no more\n" +
        "   fiercely than the high seas with many a vessel lost to the\n" +
        "   great storms, and many of the best fishing locations also\n" +
        "   popular hunting grounds for sea monsters and unfriendly\n" +
        "   aquatic humanoids.\n\n" +
        "      Fishing itself is one of the highest forms of hunting.\n" +
        "   Those skilled in hunting are familiar with their prey and\n" +
        "   have mastered finding their feeding grounds, as well as \n" +
        "   the ability of luring them with artful mimickry of their \n" +
        "   food source. \n\n" +
        "      But success is not purely down to skill. The fishing\n" +
        "   location plays a big part in the fish you catch. Experienced\n" +
        "   fisherman learn and guard the knowledge of the best fishing\n" +
        "   locations jealously! Also bait plays a big part in the size\n" +
        "   and type of fish caught. The higher the quality of the bait,\n" +
        "   the greater the chance of landing that huge catch. Simple bait\n" +
        "   can be purchased, although the best bait can be found through\n" +
        "   searching certain locations, or from the leftovers of exotic\n" +
        "   sea creatures. Luck plays no small part in what you catch, and\n" +
        "   no surpises so does fishing experience - a master fisherman has\n" +
        "   a big edge over a novice fisherman.\n\n" +
        "      It should be noted that some of the biggest fish are beyond\n" +
        "   the capability of one fisherman to land alone. Sometimes it \n" +
        "   takes a team of fisherman working together - one fishing, the \n" +
        "   others using the hooked pole known as a gaff to land the \n" +
        "   biggest of fish.\n" +
        "\n\n");
        return 1;
    }

    return 0;
} 


int
abandon(string str)
{
    string army;

    NF("Abandon what? Your fishing obsession?\n");
    if (!str)
	return 0;
 
    str = lower_case(str);

    NF("You are not currently an angler!\n");
    if(!IS_ANGLER(TP))
        return 0;

    NF("Abandon what? Your fishing obsession?\n");
    if (str != "my fishing obsession")
	return 0; 


    tell_object(TP,"You abandon your fishing obsession.\n");

    FISHING_MANAGER->remove_member(TP);

    // Remove the club object
    object club_object = present("_angler_club_object_", TP);
    if (objectp(club_object))
    {
	club_object->remove_object();
    }

    return 1;
}

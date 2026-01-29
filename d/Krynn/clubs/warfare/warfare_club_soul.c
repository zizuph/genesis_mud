/* created by Arman
 * This soul holds the general commands and feelings of the warfare club.
 */

inherit "/cmd/std/command_driver";
inherit "/d/Krynn/common/warfare/warfare_map";

#include "/d/Krynn/common/defs.h"
#include "defs.h"

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>
#include "/d/Krynn/open/sys/composite.h"
#include <language.h>

string get_soul_id() { return "Krynn Warfare Club"; }

int query_cmd_soul() { return 1; }

object title_shadow;

mapping title_earnt_list = ([ ]);

mapping vanq_titles = ([ "Knights":"Vanquisher", "Free People":"Vigilante",
    "Neidar Clan":"Slayer", "Red Dragon Army":"Tyrant", 
    "Blue Dragon Army":"Tyrant", "Black Dragon Army":"Tyrant",
    "Green Dragon Army":"Tyrant", "White Dragon Army":"Tyrant" ]);

mapping conq_titles = ([ "Knights":"Sentinel", "Free People":"Guardian",
    "Neidar Clan":"Warden", "Red Dragon Army":"Conqueror", 
    "Blue Dragon Army":"Conqueror", "Black Dragon Army":"Oppressor",
    "Green Dragon Army":"Subjugator", "White Dragon Army":"Oppressor" ]);


mapping
query_cmdlist()
{
    seteuid(getuid());

    return ([
	     "help"          :       "help",
             "achievements"  :       "achievements",
             "desert"        :       "desert",
             "leaderboard"   :       "leaderboard",
             "war"           :       "war_status",
             "warmap"        :       "warmap",
             "wartitle"      :       "war_title",
	     "wincognito"    :       "wincognito",
	     ]);
}

int
help(string str)
{
    if (!str)
	return 0;
    if (str != "krynn warfare")
	return 0;

    tell_object(TP,"\n" +
        "              0**[===========-    -===========]**0\n\n" +
        "              -=  W A R  O F  T H E  L A N C E   =-\n\n" +
        "              0**[===========-    -===========]**0\n\n" + 
        "The War of the Lance is the catalyst for great change on the " +
        "continent of Ansalon. It signals the return of the true gods - " +
        "both good and evil - to the world, as well as the dragons who " +
        "serve them.\n\nThe war brings death and destruction to the world " +
        "of Krynn, yet is an opportunity for the nations of Ansalon " +
        "to unite against the mighty Dragon Armies of the Queen of " +
        "Darkness.\n\nWhat role will you play? A beacon of light and hope " +
        "in an Age of Despair? An isolationist reluctant to release " +
        "their racial mistrust and historic grudges? Or will you ride the " +
        "dark tides of war, seeking the spoils of victory and " +
        "extinguishing the forces of light?\n\n" +
        "The following commands are available:\n" +
	"  - help <krynn warfare>      This help menu.\n" +
        "  - conquer area              Conquer a battlefield you have cleared\n" +
        "                              of enemies.\n" +
        "  - exa area                  Examine who has control of a battlefield.\n" +
        "  - achievements              A list of your warfare achievements.\n" +
	"  - war <status>              A report on how the war is progressing.\n" +
	"  - war <rewards>             An outline of battlefield spoils attainable.\n" +
        "  - leaderboard               Who are the leading heroes and villains.\n" +
        "  - warmap                    View army locations on your magic map.\n" +
        "  - wartitle                  Display earnt war titles.\n" +
	"  - wincognito [on/off]       Hide or show your allegiance.\n\n" +
        "You may also <desert> your army if you no longer wish to " +
        "participate in the War of the Lance.\n");
    return 1;
} 

int
achievements(string str)
{
    mapping list = CLUB_MANAGER->query_krynn_war_outcome();
    string war_text = "";
    string titles_unlocked = ""; 
    string army_name, location_name;
    string player_name = TP->query_real_name();
    string * armies = ({ "knight", "neidar", "free", "red", "blue",
        "black", "green", "white"});
    string * locations = ({ "newports", "wsp", "estwilde", 
        "central_abanasinia", "north_abanasinia", "nightlund", 
        "guardlund", "throtyl", "icewall", "trelgorn", "solace" });

    int dragon_slain = CLUB_MANAGER->query_total_dragons_slain(TP);

    int std_kills, elite_kills, dragon_kills, total_kills, conquer, total_conquer;

    NF("Just <achievements> to find out more about your achievements " +
        "throughout the War of the Lance.\n");
    if (str)
	return 0;

    foreach (string arm, mixed * var: list)
    {
        string mkiller = var[0];
        int mkills = var[1];
        string mconquerer = var[2];
        int mconquers = var[3];

        army_name = CLUB_MANAGER->convert_warfare_army_name(arm);

        if(mkiller == player_name)
        {
            titles_unlocked += 
               "\n                    0**[==========-   -==========]**0\n\n" +
               "You have earnt the war title '" + vanq_titles[arm] + 
               " for the " +army_name+ "' for your recent exploits on " +
               "the battlefield!\n";
        }

        if(mconquerer == player_name)
        {
            titles_unlocked += 
               "\n                    0**[==========-   -==========]**0\n\n" +
               "You have earnt the war title '" + conq_titles[arm] + 
               " for the " +army_name+ "' for your recent conquests on " +
               "the battlefield!\n";
        }
    }

    if((CLUB_MANAGER->query_warfare_army(TP) == "Knights") &&
        (dragon_slain > 99))
    {
        string dragon_title;

        if(dragon_slain > 499)
        {
            dragon_title = "Dragonslayer, Scourge of the Children of Takhisis";
            titles_unlocked += 
                "\n                    0**[==========-   -==========]**0\n\n" +
                "You have matched the feats of Huma Dragonbane, and " +
                "have earnt the title of '" + dragon_title +  "'!\n";
        }
        else
        {
            dragon_title = "Dragonbane";
            titles_unlocked += 
                "\n                    0**[==========-   -==========]**0\n\n" +
                "You have emulated the feats of Huma Dragonbane, and " +
                "have earnt the title of '" + dragon_title +  "'!\n";
        }
    }

    foreach (string location: locations)
    {
        location_name = CLUB_MANAGER->query_warfare_string_location(location);

        conquer = CLUB_MANAGER->query_warfare_conquer_location(TP, 
            location);

        if(conquer)
        {
            if(conquer > 1)
                war_text += "You have conquered " +location_name+ " "+
                    LANG_NUM2WORD(conquer)+ " times.\n";
            else
                war_text += "You have conquered " +location_name+ " "+
                    LANG_NUM2WORD(conquer)+ " time.\n";
        }
    }

    foreach (string army: armies)
    {
        string std_desc, elite_desc, drag_desc;

        std_kills = CLUB_MANAGER->query_warfare_enemy_vanquished(TP, 0, 
            army);
        elite_kills = CLUB_MANAGER->query_warfare_enemy_vanquished(TP, 5, 
            army);
        dragon_kills = CLUB_MANAGER->query_warfare_enemy_vanquished(TP, 10, 
            army);

        total_kills += (std_kills + elite_kills + dragon_kills);

        army_name = CLUB_MANAGER->convert_warfare_army_name(army);

        if(std_kills || elite_kills)
        {
            if(std_kills)
                std_desc = capitalize(LANG_NUM2WORD(std_kills));
            else
                std_desc = "None";

            if(elite_kills)
                elite_desc = capitalize(LANG_NUM2WORD(elite_kills));
            else
                elite_desc = "None";

            if(dragon_kills)
                drag_desc = "    " +capitalize(army)+ " dragons slain:           "+
                    capitalize(LANG_NUM2WORD(dragon_kills)) + "\n\n";
            else
                drag_desc = "\n";

            war_text += "\n           ~~ " +army_name+ " ~~ \n" +
                        "    Regular forces vanquished:    " +std_desc+ "\n" +
                        "    Elite forces vanquished:      " +elite_desc+ "\n" +
                        drag_desc;
        }
    }

    if(!war_text && !titles_unlocked)
        write("You have not been involved in the War of the Lance to " +
            "date!\n");
    else
    {
        write("Your personal historic involvement on the battlefields " +
            "of Krynn is as follows:\n" +titles_unlocked+ "\nYou have " +
            "vanquished in total " +LANG_NUM2WORD(total_kills)+ 
            " opponents.\n\n" + war_text);
    }

    return 1;
}

public int
leaderboard(string str)
{
    string * army_list = WARFARE_ARMIES;
    mapping list = CLUB_MANAGER->query_krynn_war_player_stats();
    int list_size = m_sizeof(list);

    mapping kill_list = ([ ]);

    string leaderboard_text = "";

    NF("Check what? <leaderboard>?\n");
    if (str)
	return 0;

    foreach (string army_name: army_list)
    {
        mapping a_list = ([ ]);
        int most_kills = 0;
        int most_conquests = 0;
        string most_killer = "";
        string most_conquerer = "";

        foreach (string name, mixed * var: list)
        {
            string army = var[0];
            int kills = var[1];
            int conquers = var[2];

            if((kills > most_kills) && (army_name == army))
            {
                most_killer = name;
                most_kills = kills;
            }

            if((conquers > most_conquests) && (army_name == army))
            {
                most_conquerer = name;
                most_conquests = conquers;
            }
        }

        if((most_kills > 0) && (most_conquests > 0))
        {
            string vanq = vanq_titles[army_name];
            string conq = conq_titles[army_name];
            string p1, p2;
            army_name = CLUB_MANAGER->convert_warfare_army_name(army_name);

            if(most_kills == 1)
                p1 = "combatant";
            else 
                p1 = "combatants";

            if(most_conquests == 1)
                p2 = "battlefield";
            else 
                p2 = "battlefields";

            leaderboard_text += sprintf("\t%|30s      %|30s  \n", 
                "The " +vanq+ " of the", "The " +conq+ " of the ");

            leaderboard_text += sprintf("\t%|30s      %|30s  \n", 
                army_name + ":", army_name + ":");

            leaderboard_text += sprintf("\t%|30s      %|30s  \n", 
                capitalize(most_killer)+ " with " +
                most_kills + " " + p1,
                capitalize(most_conquerer) + " with " +
                most_conquests + " " + p2);

            leaderboard_text += sprintf("\t%|30s      %|30s  \n", 
                "defeated.", "conquered.\n");
        }                               
    }

    if(!strlen(leaderboard_text))
    {
        write("No combatants currently involved in the War of the Lance " +
            "have done more than skirmishing.\n");
        return 1;
    }



    write("                -=  W A R  O F  T H E  L A N C E   =-\n" +
          "                  0**[==========-   -==========]**0" +
            "\n\n" +leaderboard_text+ "\n\n" +
          "                  0**[==========-   -==========]**0\n\n");
    return 1;

}

public int
warmap(string str)
{
    if(str)
    {
        notify_fail("Warmap what?\n");
        return 0;
    }

    if (!sizeof(filter(deep_inventory(this_player()), &->id(MAGIC_MAP_ID))))
    {
        notify_fail("You need a magic map to be able to observe the " +
            "progress of the War of the Lance.\n");
        return 0;
    }

    write("You look at your magic map and examine the " +
        "locations of the various armies vying for control of " +
        "Krynn...\n" +exa_warmap()+ "\n");
    say(QCTNAME(TP)+ " examines " +HIS(TP)+ " magic map, " +
        "tracking the progress of the War of the Lance in Krynn.\n");

    return 1;
}

void
warfare_rewards_text()
{
    tell_object(TP,"\n" +
        "              0**[===========-    -===========]**0\n\n" +
        "              -=  W A R  O F  T H E  L A N C E   =-\n" +
        "              -=          R E W A R D S          =-\n\n" +
        "              0**[===========-    -===========]**0\n\n" + 
        "The contests across the battlefields of Krynn are bloody, but " +
        "also provide opportunity for unique spoils of war for the " +
        "participants.\n\nSince the Age of Despair, steel coins have " +
        "been a currency in Krynn of greater value than silver and gold, " +
        "even platinum! Minted at the esteemed bank of Palanthas, " +
        "these coins are greatly valued by master smiths, such as " +
        "Theros Ironfeld of Solace, who may be convinced to craft " +
        "customised weapons and armours for those willing to part " +
        "ways with steel coins earnt in conquering battlefields.\n\n" +
        "Such masterwork equipment may be magically enhanced with " +
        "Augmentation Crystals, turning them from finely crafted " +
        "equipment into powerful and unique artifacts. These crystals " +
        "may also be found on the battlefields, or more often in the " +
        "hands of those you contest against!\n\n");
}

public int
war_status(string str)
{
    mapping list = CLUB_MANAGER->query_krynn_war_stats();
    mapping army_string = ([ ]);
    string war_text = "";
    string control_text = "";
    string winning_army, conquering_army, army_name;
    string * armies = ({ "knight", "neidar", "free", "red", "blue",
        "black", "green", "white"});
    string * army_list = WARFARE_ARMIES;
    string * areas = WARFARE_AREAS;
    int victories = 0;
    int conquests = 0;

    NF("Check what? The <war status> or <war rewards>?\n");
    if (!str || (str != "status" && str != "rewards"))
	return 0;

    if(str == "rewards")
    {
        warfare_rewards_text();
        return 1;
    }

    foreach(string al : army_list)
    {
        string * controlled_areas = ({ });
        string control_text = "";
        int size = 0;

        foreach(string area : areas)
        {
            if(CHECK_ARMY_IN_AREA(area, al))
            {
                if(area != "Trelgorn Forest")
                    controlled_areas += ({ area });
            } 
        } 
        
        if(sizeof(controlled_areas))
        {
            if(sizeof(controlled_areas) > conquests)
            {
                conquering_army = CLUB_MANAGER->convert_warfare_army_name(al);
                conquests = sizeof(controlled_areas);
            }

            control_text += "The " +
            CLUB_MANAGER->convert_warfare_army_name(al)+ " currently " +
                "control ";

            foreach(string ca : controlled_areas)
            {
                    size++;
                    control_text += ca; 
                    if (sizeof(controlled_areas) - size == 1)
                        control_text += ", and ";
                    else if (sizeof(controlled_areas) - size > 1)
                        control_text += ", ";
            }

            control_text += ". ";
            army_string += ([ al : control_text ]);
        }
    } 

    foreach (string army, int * var: list)
    {
        string p1, p2, p3;
        int kills = var[0];
        int conquers = var[1];
        int losses = var[2];

        string war_text_intro = army_string[army];

        // CLUB_DEBUG("Army: " +army+ "; string: " +war_text_intro);

        if(kills == 1)
            p1 = "opponent";
        else 
            p1 = "opponents";

        if(conquers == 1)
            p2 = "time";
        else 
            p2 = "times";

        if(losses == 1)
            p3 = "time";
        else 
            p3 = "times";

        army_name = CLUB_MANAGER->convert_warfare_army_name(army);

        if(conquers > victories)
        {
            winning_army = army_name;
            victories = conquers;
        }

        if(strlen(war_text_intro))
            war_text += war_text_intro + "They";
        else
            war_text += "The " +army_name;

        if(kills || conquers)
            war_text += " have been victorious on " +
                "the battlefield " +LANG_NUM2WORD(conquers)+ " " + p2 + 
                " and have vanquished " +LANG_NUM2WORD(kills)+ " " +p1+ 
                ".\n\n";
     
        if(!kills && !conquers)
            war_text += " have been driven from " +
                "the battlefield without inflicting any losses.\n\n"; 


    }

    if(!winning_army)
    {
        write("There has been no conflict to provide a status update " +
           "on!\n");
    }
    else
    {
        write("                       -=  W A R  O F  T H E  L A N C E   =-\n" +
            "                         0**[==========-   -==========]**0" +
            "\n\nThe " +conquering_army+ " currently are " +
            "winning the War of the Lance with control of " +
            LANG_NUM2WORD(conquests)+  " battlefields!\n\nThe " 
            +winning_army+ " currently leads " +"the way in victories " +
            "on the battlefield!\n\n" +
            "                         0**[==========-   -==========]**0\n\n"
            + control_text + war_text);

        allbb(" checks battle reports on how the War of the Lance is " +
            "progressing in Krynn.");
    }

    return 1;
}

void
check_player_war_titles()
{
    mapping list = CLUB_MANAGER->query_krynn_war_outcome();
    string army_name, kill_title, conq_title, dragon_title;
    string player_name = TP->query_real_name(); 
    int dragon_slain = CLUB_MANAGER->query_total_dragons_slain(TP);

    title_earnt_list = ([ ]);

    foreach (string arm, mixed * var: list)
    {
        string mkiller = var[0];
        string mconquerer = var[2];

        army_name = CLUB_MANAGER->convert_warfare_army_name(arm);

        if(mkiller == player_name)
        {
            kill_title = vanq_titles[arm] + " for the " +army_name;
            title_earnt_list += ([ "vanquisher" : kill_title ]);
        }

        if(mconquerer == player_name)
        {
            conq_title = conq_titles[arm] + " for the " +army_name;
            title_earnt_list += ([ "conquerer" : conq_title ]);
        }
    }

    if((dragon_slain > 99) && 
        CLUB_MANAGER->query_warfare_army(TP) == "Knights")
    {
        title_earnt_list += ([ "dragonbane" : "Dragonbane" ]);
    }

    if((dragon_slain > 499) && 
        CLUB_MANAGER->query_warfare_army(TP) == "Knights")
    {
        title_earnt_list += ([ "dragonslayer" : "Dragonslayer, " +
            "Scourge of the Children of Takhisis" ]);
    }

}

void
activate_warfare_title(string str)
{
    string war_title;

    setuid();
    seteuid(getuid());

    if(str == "dragonbane" || str == "dragonslayer")
    {
        war_title = title_earnt_list[str]; 

        if(TP->query_warfare_dragonslayer_title_shadow_active())
            TP->remove_warfare_dragonslayer_title_shadow();      

        title_shadow = clone_object(CLUB + "krynn_dragonslayer_title_shadow");
        title_shadow->set_warfare_dragonslayer_title(war_title);
        title_shadow->shadow_me(TP);

        write("You publicly display yourself to be " +war_title+ "!\n");
    }

    if(str == "conquerer" || str == "vanquisher")
    {
        war_title = title_earnt_list[str];

        if(TP->query_warfare_title_shadow_active())
            TP->remove_warfare_title_shadow();

        title_shadow = clone_object(CLUB + "krynn_warfare_title_shadow");
        title_shadow->set_warfare_title(war_title);
        title_shadow->shadow_me(TP);

        write("You publicly display yourself as the " +war_title+ "!\n");
    }
}

public int
war_title(string str)
{
    mapping list = CLUB_MANAGER->query_krynn_war_outcome(); 
    string army_name, kill_title, conq_title, dragon_title, war_title;
    int conquerer = 0;
    int killer = 0;
    string player_name = TP->query_real_name();
    int dragon_slain = CLUB_MANAGER->query_total_dragons_slain(TP);
    str = lower_case(str);

    // check what titles the player has
    check_player_war_titles();

    int title_list_size = m_sizeof(title_earnt_list);

    if(!title_list_size)
    {
        notify_fail("You have not earnt any warfare titles yet!\n");
        return 0;
    }

    if((TP->query_warfare_dragonslayer_title_shadow_active() || 
        TP->query_warfare_title_shadow_active()) && (str == "off"))
    {
        write("You are no longer publicly displaying your warfare titles.\n");
        TP->remove_warfare_title_shadow();
        TP->remove_warfare_dragonslayer_title_shadow();
        return 1;
    }

    if (CLUB_MANAGER->query_warfare_subloc_incognito(TP))
    {
        write("You are incognito. You will need to publicly display " +
            "your allegiance to display your titles.\n");
        return 1;
    }

    if(!str)
    {
        if(title_list_size == 1)
        {
            war_title = m_indexes(title_earnt_list)[0];
            CLUB_DEBUG("War title: " +war_title);
            activate_warfare_title(war_title);
            return 1;
        }

        string title_options = "";
        int size = 0;

        foreach (string title, string title_desc: title_earnt_list)
        {
            size += 1;
            title_options += "'" + capitalize(title) + "'";
            if(title_list_size - size == 1)
                title_options += ", or ";
            else if (title_list_size - size > 1)
                title_options += ", ";
        }

        notify_fail("You need to specify which of your war " +
            "titles you want to display? "+title_options + "?\n");
        return 0;
    }

    if(str)
    {     
        if(!title_earnt_list[str])
        {
            string title_options = "";
            int size = 0;

            foreach (string title, string title_desc: title_earnt_list)
            {
                CLUB_DEBUG("Title: " +title);
                size += 1;
                title_options += "'" + title + "'";

                if(title_list_size - size == 1)
                    title_options += ", or ";
                else if (title_list_size - size > 1)
                    title_options += ", ";
            }

            notify_fail("You don't have such a title to display! " +
                "You have earnt the "+title_options + " " +
                ((title_list_size == 1) ? "title" : "titles") +
                " you can display?\n");
            return 0;
        }
        else
        {
            activate_warfare_title(str);
            return 1;
        }
    }
    notify_fail("Wartitle what? Off?\n");
    return 0;
}

public int
wincognito(string str)
{
      
   if(!str)
   {
       write("wincognito on or off?\n");
       return 1;
   }

   if(str == "off")
   {
       if (!CLUB_MANAGER->query_warfare_subloc_incognito(TP))
       {
           write("You are not hiding your allegiance in the " +
               "war for Krynn!\n");
           return 1;
       }

       write("You no longer hide your allegiance to the " +
           CLUB_MANAGER->query_warfare_army_name(TP)+ " in the " +
           "war for Krynn.\n");
       CLUB_MANAGER->set_warfare_subloc_incognito(TP, 0);
       return 1;
   }

   if(str == "on")
   {
       if (CLUB_MANAGER->query_warfare_subloc_incognito(TP))
       {
           write("You are already hiding your allegiance in the " +
               "war for Krynn!\n");
           return 1;
       }

       write("You hide your allegiance to the " +
           CLUB_MANAGER->query_warfare_army_name(TP)+ " in the " +
           "war for Krynn.\n");
       CLUB_MANAGER->set_warfare_subloc_incognito(TP, 1);
       TP->remove_warfare_title_shadow();

       return 1;
   }

    write("You can hide from your description your allegiance to " +
       "the army you support in the war for Krynn through the " +
       "command 'wincognito <on/off>'.\n");
    return 1;
}

int
desert(string str)
{
    string army;

    NF("Desert whom?\n");
    if (!str)
	return 0;
 
    str = lower_case(str);

    parse_command(str, TO, "[the] %s", army);

    NF("You are not currently supporting any army, so can't desert " +
        "anyone!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    NF("If you want to desert, type <desert the " +
        CLUB_MANAGER->query_warfare_army(TP)+ ">.\n");
    if (army != lower_case(CLUB_MANAGER->query_warfare_army(TP)))
	return 0;

/*
    NF("You would need to leave your occupational guild to remove yourself " +
        "from the War of the Lance!\n");
    if((TP->query_guild_name_occ() == "Dwarven Warriors of the Neidar Clan") ||
        (TP->query_guild_name_occ() == "Solamnian Knights") || 
        TP->query_dragonarmy_occ_member())
    return 0;
*/

    tell_object(TP,"You have deserted the " +
        CLUB_MANAGER->query_warfare_army(TP)+ " and are no longer " +
        "participating in the war for Krynn!\n");

    CLUB_MANAGER->remove_member(TP);
    CLUB_MANAGER->remove_warfare_army(TP);

    // Remove the club object
    object club_object = present("_warfare_club_object_", TP);
    if (objectp(club_object))
    {
	club_object->remove_object();
    }

    return 1;
}

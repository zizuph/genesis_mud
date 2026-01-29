/* created by Arman June 2018 */

#include "/d/Krynn/common/defs.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

inherit R_FILE

string * eligible_armies = ({ "Knights", "Free People", "Neidar Clan",
    "Red Dragon Army", "Blue Dragon Army", "Black Dragon Army",
    "Green Dragon Army", "White Dragon Army" });

mapping vanq_titles = ([ "Knights":"Vanquisher", "Free People":"Vigilante",
    "Neidar Clan":"Slayer", "Red Dragon Army":"Tyrant", 
    "Blue Dragon Army":"Tyrant", "Black Dragon Army":"Tyrant",
    "Green Dragon Army":"Tyrant", "White Dragon Army":"Tyrant" ]);

mapping conq_titles = ([ "Knights":"Sentinel", "Free People":"Guardian",
    "Neidar Clan":"Warden", "Red Dragon Army":"Conqueror", 
    "Blue Dragon Army":"Conqueror", "Black Dragon Army":"Oppressor",
    "Green Dragon Army":"Subjugator", "White Dragon Army":"Oppressor" ]);

create_krynn_room()
{
    set_short("Warfare join room");
    set_long("Warfare join room. You can <support> a specific " +
        "army participating in the War of the Lance:\n" +
        "    Knights,\n" +
        "    Free People,\n" +
        "    Neidar Clan,\n" +
        "    Red Dragon Army,\n" +
        "    Blue Dragon Army,\n" +
        "    Black Dragon Army,\n" +
        "    Green Dragon Army, or\n" +
        "    White Dragon Army.\n" +
        "\n\nYou can check your <achievements>, <leaderboard> and the " +
        "<war status>, <replace> a lost chit, and also <desert> from your army.\n");

    // clone_object(CLUB + "warfare_board")->move(TO, 1);

}

void
init()
{
    ::init();
    ADA("support");
    ADA("desert");
    ADA("achievements");
    ADA("war");
    ADA("leaderboard");
    ADA("replace");
}

int
support(string str)
{
    object club_obj = clone_object(WAR_OBJ);
    string army;

    NF("Support which army?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "[the] %s", army);

    army = CLUB_MANAGER->query_warfare_army_string(army);

    NF("That isn't an eligible warfare army to support.\n");
    if(!CLUB_MANAGER->query_is_warfare_army(army))
	return 0;

    NF("You currently support the " +CLUB_MANAGER->query_warfare_army(TP)+
        "! You will need to <desert> them first to support a different " +
        "army!\n");
    if(IS_CLUB_MEMBER(TP))
        return 0;
    
    CLUB_MANAGER->add_member(TP);
    CLUB_MANAGER->set_warfare_army(TP, army);

    club_obj->move(TP, 1);

    tell_room(E(TP), QCTNAME(TP) + " has entered the battle for control " +
        "of Krynn on the side of the " +
        CLUB_MANAGER->query_warfare_army_name(TP)+ "!\n", TP);
    tell_object(TP,"You have entered the battle for control of Krynn " +
        "on the side of the " +CLUB_MANAGER->query_warfare_army_name(TP)+
        "!\n");
    return 1;

}

int
desert(string str)
{
    string army;

    NF("Desert whom?\n");
    if (!str)
	return 0;

    parse_command(str, TO, "[the] %s", army);

    NF("You are not currently supporting any army, so can't desert " +
        "anyone!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    NF("If you want to desert, type <desert the " +
        CLUB_MANAGER->query_warfare_army(TP)+ ">.\n");
    if (army != lower_case(CLUB_MANAGER->query_warfare_army(TP)))
	return 0;

    tell_object(TP,"You have deserted the " +
        CLUB_MANAGER->query_warfare_army(TP)+ " and are no longer " +
        "participating in the war for Krynn!\n");

    CLUB_MANAGER->remove_member(TP);
    CLUB_MANAGER->remove_warfare_army(TP);

    return 1;
}

int
achievements(string str)
{
    string war_text = ""; 
    string army_name, location_name;
    string * armies = ({ "knight", "neidar", "free", "red", "blue",
        "black", "green", "white"});
    string * locations = ({ "newports", "wsp", "estwilde", 
        "central_abanasinia", "north_abanasinia", "nightlund", 
        "guardlund", "throtyl", "icewall", "trelgorn" });

    int std_kills, elite_kills, total_kills, conquer, total_conquer;

    NF("Just <achievements> to find out more about your achievements " +
        "throughout the War of the Lance.\n");
    if (str)
	return 0;

    foreach (string location: locations)
    {
        location_name = CLUB_MANAGER->query_warfare_string_location(location);

        conquer = CLUB_MANAGER->query_warfare_conquer_location(TP, 
            location);

        if(conquer)
        {
            if(conquer > 1)
                war_text += "\nYou have conquered " +location_name+ " "+
                    LANG_NUM2WORD(conquer)+ " times.\n";
            else
                war_text += "You have conquered " +location_name+ " "+
                    LANG_NUM2WORD(conquer)+ " time.\n";
        }
    }

    foreach (string army: armies)
    {
        std_kills = CLUB_MANAGER->query_warfare_enemy_vanquished(TP, 0, 
            army);
        elite_kills = CLUB_MANAGER->query_warfare_enemy_vanquished(TP, 5, 
            army);

        total_kills += (std_kills + elite_kills);

        army_name = CLUB_MANAGER->convert_warfare_army_name(army);

        if(std_kills || elite_kills)
        {
            war_text += "\n           ~~ " +army_name+ " ~~ \n" +
                        "    Regular forces vanquished:    " +
                        capitalize(LANG_NUM2WORD(std_kills))+ "\n" +
                        "    Elite forces vanquished:      " +
                        capitalize(LANG_NUM2WORD(elite_kills))+ "\n\n";
        }
    }

    if(!war_text)
        write("You have not been involved in the War of the Lance to " +
            "date!\n");
    else
    {
        write("Your personal historic involvement on the battlefields " +
            "of Krynn is as follows:\n\nYou have vanquished in total " +
            LANG_NUM2WORD(total_kills)+ " opponents.\n" + war_text);

    }

    return 1;

}

public int
war(string str)
{
    mapping list = CLUB_MANAGER->query_krynn_war_stats();
    string war_text = "";
    string control_text = "";
    string winning_army, conquering_army, army_name;
    string * armies = ({ "knight", "neidar", "free", "red", "blue",
        "black", "green", "white"});
    string * army_list = WARFARE_ARMIES;
    string * areas = WARFARE_AREAS;
    int victories = 0;
    int conquests = 0;

    NF("Check what? The <war status>?\n");
    if (!str || str != "status")
	return 0;

    foreach(string al : army_list)
    {
        string * controlled_areas = ({ });
        int size = 0;

        foreach(string area : areas)
        {
            if(CHECK_ARMY_IN_AREA(area, al))
            {
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

            control_text += ".\n\n";
        }
    } 

    foreach (string army, int * var: list)
    {
        string p1, p2, p3;
        int kills = var[0];
        int conquers = var[1];
        int losses = var[2];

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
      
        if(kills || conquers || losses)
            war_text += "The " +army_name+ " have been victorious on " +
                "the battlefield " +LANG_NUM2WORD(conquers)+ " " + p2 + 
                " and have vanquished " +LANG_NUM2WORD(kills)+ " " +p1+ 
                ", while being defeated " +LANG_NUM2WORD(losses)+
                " " +p3+ ".\n\n"; 
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

            leaderboard_text += sprintf("\t%|35s      %|35s  \n", 
                "The " +vanq+ " of the", "The " +conq+ " of the ");

            leaderboard_text += sprintf("\t%|35s      %|35s  \n", 
                army_name + ":", army_name + ":");

            leaderboard_text += sprintf("\t%|35s      %|35s  \n", 
                capitalize(most_killer)+ " with " +
                LANG_NUM2WORD(most_kills) + " " + p1, 
                capitalize(most_conquerer) + " with " + 
                LANG_NUM2WORD(most_conquests) + " " + p2);

            leaderboard_text += sprintf("\t%|35s      %|35s  \n", 
                "defeated.", "conquered.\n");
        }                               
    }

    if(!leaderboard_text)
    {
        write("There are no combatants currently involved in the " +
            "War of the Lance.\n");
        return 1;
    }

    write("                     -=  W A R  O F  T H E  L A N C E   =-\n" +
          "                       0**[==========-   -==========]**0" +
            "\n\n" +leaderboard_text+ "\n\n" +
          "                       0**[==========-   -==========]**0\n\n");
    return 1;

}


int
replace(string str)
{
    object club_object = present("_warfare_club_object_", TP);
    object chit_obj = clone_object(WAR_OBJ);

    NF("Replace what? Your war chit?\n");
    if (!str)
	return 0;

    NF("Replace your war chit?\n");
    if ((str != "war chit") && (str != "chit") && (str != "my war chit"))
        return 0;

    NF("You haven't supported an army yet! You can't get a chit until " +
        "you have done so!\n");
    if(!IS_CLUB_MEMBER(TP))
        return 0;

    NF("You haven't lost your war chit! No need to replace it.\n");
    if (objectp(club_object))
        return 0;
  
    tell_room(E(TP), QCTNAME(TP) + " gets a replacement war chit.\n", TP);
    tell_object(TP, "You get yourself a replacement war chit.\n");

    setuid();
    seteuid(getuid());
    chit_obj->move(TP, 1);

    return 1;

}
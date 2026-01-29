
/* 
   The Warfare Informer, an automated note writer who delivers
   based on /d/Calia/special/informer.c coded by Maniac

   Arman October 2018
*/

#pragma save_binary
#pragma strict_types
// #pragma no_inherit

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include "defs.h"
// #include "/d/Calia/sys/kroug.h"

inherit "/std/monster"; 

int active, total_time; 
 
string intro, additional, board_room, note; 

object the_board;

/* For special comments */
void
set_board_room(string str)
{
     board_room = str; 
}

/* For special comments at end of note */
void
set_additional(string str)
{
     additional = str; 
}


/* For special comments at start of note */
void
set_intro(string str)
{
     intro = str; 
}

void
set_total_time(int t)
{
    total_time = t;
}

public string
query_army_leader_string(string str)
{
    string leader_text;

    switch(str)
    {
        case "Knights of Solamnia":
            leader_text = "With the Dragonarmies broken and fleeing " +
                "in defeat, the Knights of Solamnia under Grand" +
                "master Gunthar Uth Wistan bring the rule of law " +
                "and order to the realms for the first time since " +
                "the Cataclysm.\n\n";
            break;
        case "Neidar Clan":
            leader_text = "With order being restored across the lands " +
                "by the dwarven war throngs, the Thanes of the Dwarven " +
                "Nations return to their holdings with the spoils of " +
                "war and many a new warsong about the follies of the " +
                "tall folk!\n\n";
            break;
        case "Free People of Krynn":
            leader_text = "With the Dragonarmies broken and fleeing " +
                "in defeat, the Golden General of the Whitestone " +
                "Army, Lauralanthalasa Kanan, is declared a Hero " +
                "of the Lance!\n\n";
            break;
        case "Red Dragonarmy":
            leader_text = "Dragon Highlord Duulket Ariakas " +
                "is graced the Crown of Power by the victorious " +
                "Dragon Queen, and proclaims himself Emperor of " +
                "Krynn!\n\n";
            break;
        case "Blue Dragonarmy":
            leader_text = "Dragon Highlord Kitiara Uth Matar " +
                "is graced the Crown of Power by the victorious " +
                "Dragon Queen, and proclaims herself Empress of " +
                "Krynn!\n\n";
            break;
        case "Black Dragonarmy":
            leader_text = "Dragon Highlord Lucien of Takar " +
                "is graced the Crown of Power by the victorious " +
                "Dragon Queen, and proclaims himself Emperor of " +
                "Krynn!\n\n";
            break;
        case "Green Dragonarmy":
            leader_text = "Dragon Highlord Salah-Khan " +
                "is graced the Crown of Power by the victorious " +
                "Dragon Queen, and proclaims himself Emperor of " +
                "Krynn!\n\n";
            break;
        case "White Dragonarmy":
            leader_text = "Dragon Highlord Feal-Thas " +
                "is graced the Crown of Power by the victorious " +
                "Dragon Queen, and proclaims himself Emperor of " +
                "Krynn!\n\n";
            break;
        default:
            leader_text = "";
            break;
    }

    return leader_text;
}


private int
generate_note()
{
    mapping list = CLUB_MANAGER->query_krynn_war_outcome();
    string winning_army, conquering_army, army_name, drawn_army1, 
        drawn_army2;
    int victories, drawn;
    string * armies = ({ "knight", "neidar", "free", "red", "blue",
        "black", "green", "white"});
    object br;

    if (!stringp(board_room)) 
        return 0;

    board_room->load_me();
    if (!objectp(br = find_object(board_room)))
        return 0;

    note = "On this day, 26 Mishamont 352 Alt Cataclius, the War of " +
        "the Lance ended.\n\n"; 

    foreach (string army, int * var: list)
    {
        int kills = var[4];
        int conquers = var[5];
        int losses = var[6];

        army_name = CLUB_MANAGER->convert_warfare_army_name(army);

        if(conquers > victories)
        {
            winning_army = army_name;
            victories = conquers;
            drawn = 0;
        }
        else if(conquers == victories)
        {
            if(!winning_army)
                drawn_army1 = "The Minotaur Empire of Nethosak";
            else
                drawn_army1 = winning_army;
            drawn_army2 = army_name;
            drawn = 1;
        }
    }

    CLUB_MANAGER->clear_army_winner();

    if(drawn)
        note += "There was no decisive victor on the battlefield. " +
        drawn_army1 + " and " + drawn_army2 + " were deadlocked in " +
        "the conquest of Krynn, with the other forces deposed and " +
        "left licking their wounds.\n\n";
    else
    {
        note += "The " + winning_army + " were the victors of the war, having " +
        "successfully conquered the most battlefields by the end of the " +
        "conflict.\n\n";

        note += query_army_leader_string(winning_army);
        CLUB_MANAGER->set_army_winner(winning_army);
    }

    foreach (string army, mixed * var: list)
    {
        string p1, p2, p3, align_msg;
        string most_killer = var[0];
        int most_kills = var[1];
        string most_conquerer = var[2];
        int most_conquests = var[3];
        int kills = var[4];
        int conquers = var[5];
        int losses = var[6];

        string killer_string = "";
        string conquer_string = "";

        switch (army)
        {
            case "Knights":
                align_msg = "gallantly";
                break;
            case "Neidar Clan":
                align_msg = "stubbornly";
                break;
            case "Free People":
                align_msg = "valiantly";
                break;
            case "Red Dragon Army":
                align_msg = "remorselessly";
                break;
            case "Blue Dragon Army":
                align_msg = "mercilessly";
                break;
            case "Black Dragon Army":
                align_msg = "ferociously";
                break;
            case "Green Dragon Army":
                align_msg = "ruthlessly";
                break;
            default:
                align_msg = "murderously";
                break;
        }

        if (most_conquerer != "")
            conquer_string = ", " +align_msg+ " led by " +
                capitalize(most_conquerer) + ",";

        if (most_killer != "")
            killer_string = ", with " + capitalize(most_killer) +
                " championing the cause with " + LANG_NUM2WORD(most_kills) +
                ((most_kills == 1) ? " enemy" : " enemies") + " defeated";

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

        if(kills || conquers || losses)
        {
            if (!conquers && !losses)
                note += "The " +army_name+ " did not involve themselves " +
                    "in the war, neither conquering or losing any territory.\n\n";
            else if (!conquers && losses)
                note += "The " +army_name+ " were driven from their lands, " +
                    "inflicting casualties to " +LANG_NUM2WORD(kills)+ " " +
                    p1 + " in their battles.\n\n";
            else if ((losses > conquers) && (army_name != "Free People of Krynn"))
                note += "The " + army_name + conquer_string + " fought a " +
                    "losing battle against their foes, however managed to be victorious " +
                    "on the battlefield " + LANG_NUM2WORD(conquers)+ " " + p2 + 
                    ". During these battles, " +LANG_NUM2WORD(kills)+ " " +p1+ 
                    " were slain" +killer_string+ ".\n\n";
            else
                note += "The " + army_name + conquer_string +" were victorious on " +
                "the battlefield " +LANG_NUM2WORD(conquers)+ " " + p2 +
                ". " +capitalize(LANG_NUM2WORD(kills))+ " " +p1+ 
                " were vanquished" +killer_string+ ".\n\n"; 
        }
    }


    note += "And so these feats of heroism and villainy I add to the " +
        "Library of Ages in my recording of the history of Krynn.\n\n" +
        "Astinus, Lorekeeper of Krynn.\n"; 
    return 1;
}


private void
leaveit()
{
     command("nod . "); 
     tell_room(environment(this_object()), "Astinus leaves.\n"); 
     remove_object(); 
}


private void
writeit(object writer)
{
     object temp_player = this_player(); 
     set_this_player(writer);

     the_board->create_note("Outcome of the War of the Lance.", "Astinus", note);       
     writer->command("emote finishes writing a note."); 
     set_this_player(temp_player);
     set_alarm(1.0, 0.0, leaveit); 
}


private void
postit()
{
    string t; 

    the_board = present("board", environment(this_object()));      

    if (!objectp(the_board))
        return;

    seteuid(getuid(the_board)); 
    this_object()->command("introduce myself"); 
    this_object()->command("emote starts writing a note."); 
    set_alarm(1.0, 0.0, &writeit(this_object())); 
}


private void
gothere()
{
     move_living("X", board_room); 
     set_alarm(1.0, 0.0, postit); 
}


private void
realactivate()
{
     if (!generate_note())    
         return;

     set_alarm(1.0, 0.0, gothere); 
}

void
activate()
{
     if (active)     
         return;

     active = 1;
     set_alarm(1.0, 0.0, realactivate); 
}

void
create_monster()
{
    set_name("astinus");
    set_living_name("astinus"); 
    set_adj("ageless");
    add_adj("grey-haired");
    set_title("of Palanthas, Lorekeeper of Krynn");
    set_long("Astinus the Ageless One, head of the Library of Palanthas "
	    + "and chronicler of all history in Krynn. The historian's face "
            + "might have been reckoned handsome in a timeless, ageless " 
            + "fashion. But none who see his face ever remember it - they "
            + "simply remember the eyes - dark, intent, aware, constantly "
            + "moving, seeing everything.\n"
            + "Astinus spends his time endlessly writing everything that happens " 
            + "on the face of Krynn.\n");
    set_race_name("human");  

     default_config_npc(300); 
     add_prop(OBJ_M_NO_ATTACK, 1); 
     add_prop(OBJ_M_NO_MAGIC_ATTACK, 1); 
     add_prop(LIVE_I_ALWAYSKNOWN, 1); 

     active = 0;
}

/*

void
informer_note()
{
     inf = clone_object("/d/Calia/special/informer"); 
     inf->set_board_room(CRPALACE_LIGHT_ROOMS+"trainroom");   
     inf->set_additional(0); 
     inf->set_intro(ir);   

    tell_room(PALACE_RAID_ROOM, ch + " wins with a score of " + ht + ".\n"); 
    inf->set_champion(ch);  
    inf->set_champion_kills(scores[ch]); 
    inf->set_slayers(dx); 
    inf->set_total_time((time_end - time_start) / 60);  
    inf->set_total_krougs(strength); 
    inf->set_casualties(casualties); 
    inf->activate(); 
    done_note = 1;
}

*/

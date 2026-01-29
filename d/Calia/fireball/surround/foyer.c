
/* 

    /d/Calia/fireball/surround/foyer.c 

    Foyer of the Firedrome. 

    Here people may book fireball matches. 

    It is also the access point for the stand, walkway and 
    locker room.  

    Coded by Maniac@Genesis, 1997/1998

    Copyright (c) Miguel Leith 1997/1998

*/ 

#include "defs.h"
#include FIREBALL_HEADER

inherit FIREBALL_OUTSIDE_ROOM; 
inherit FIREBALL_UTILS; 

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <composite.h>

/* Prototypes */ 
private void make_attendant(); 
int enter_locker_room(); 
string booking_info(); 

string *attendant_adj; 
string *attendant_parse; 
string attendant_desc, attendant_name, info; 


void
create_room()
{
    make_attendant(); 

    set_short("Firedrome foyer"); 
    set_long("The foyer of the Firedrome is " +
             "a cylindrical room with panelled walls decorated " +
             "with paintings of fireball matches. " +
             "Crowd noise dives in from the stand above and " +
             "reverberates around you with distortion like the inside " +
             "of an iron drum. " +
             "At the far end of the foyer is a window of a booking " + 
             "office, attended by " + capitalize(attendant_name) + ", " + 
             LANG_ADDART(attendant_desc) + ". " + 
             "A wide stairway leads up to where the crowd is " +
             "massed. A dark passage leads east to the locker room. " +
             "West is a gate leading to the walkway around the stadium.\n"); 

    add_item(({ "team", "player", "results" }),  
             "There are records available from the office about teams, " +
             "players and results. Please examine the office for a " +
             "description of how to read them.\n"); 

    add_item(({"foyer"}), 
             "You're standing in the foyer. Type \"look\" to examine it.\n"); 

    add_item(({"passage", "dark passage"}), 
             "A dark passage leads east to the locker room, " +
             "which is the access point of the arena.\n"); 

    add_item(({ "stand" }), 
             "From here you can't see much of the stand. " +
             "You'll have to go up if you want a closer look.\n"); 

    add_item(({"arena" }), 
             "The arena is the playing space for fireball games. " +
             "You could get a look at it from the stand above or " +
             "east of the locker room, if you happen to be playing " +
             "in the next game.\n"); 

    add_item(({"walkway"}), 
             "The walkway around the stadium is to your west, through " +
             "the gates.\n"); 

    add_item(({"locker room"}), 
              "The locker room is to your east. Through the dim " +
              "light you can see the glint of metal. From there you " +
              "can access the arena if you are playing in the next " +
              "match.\n"); 

    add_item(({"gate", "gateway", "stones", "gates"}), 
             "The gateway leads outside to the walkway around the stadium. " +
             "It is framed with marble stones while the gates " +
             "are made of mahogany.\n"); 

    add_item(({"marble", "mahogany"}), 
             "The material is of fine quality. It appears that no expense " +
             "was spared here.\n"); 

    add_item(({"stairway", "wide stairway"}), 
             "It's a wide stairay leading up to the stand.\n"); 

    add_item(({"walls", "panelled walls", "panels", "paintings", 
               "contests", "fiery paintings", "sporting contests" }), 
             "The walls are wooden panelled and decorated with " +
             "paintings of fireball matches. " + 
             "One of them depicts the much feared All Scums, a team " +
             "of ogres, making short work of the opposition.\n"); 

    add_item(attendant_parse, 
             capitalize(attendant_name) + ", " + 
             LANG_ADDART(attendant_desc) + ", attends the " +
             "booking office. To find out more about " +
             "making bookings, examine the office.\n"); 

    info = 
      ("The booking office provides information about " +
       "local teams and a history of results for all teams. Its " +
       "main purpose is to allow you to register your team and book " +
       "matches. You may book matches against both visiting teams and " +
       "local teams.\n\n" + 
       "General Commands:\n" + 
       "-----------------\n" + 
       "help fireball              - help on various fireball topics.\n" +
       "exa teams                  - list local fireball teams.\n" + 
       "exa team <team>            - read information on a local " +
                                                     "fireball team.\n" + 
       "exa player <player>        - read information on a player.\n" + 
       "exa results <date>         - read results. The <date> description\n" + 
       "                             can be \"today\" or \"yesterday\" or\n" + 
       "                             <year> (e.g. 1999) or <month> <year>\n" +
       "                             (e.g. May 1999) or <day> <month> <year>\n" + 
       "                             (e.g. 1 May 1999).\n\n" + 
       "Commands for Booking Matches:\n" + 
       "---------------------------\n" + 
       "tregister <team>           - register your team name.\n" + 
       "pregister <players>        - register the players for your team.\n" + 
       "unregister                 - unregister your team name and players.\n" + 
       "book <team>                - book a match against a specified team.\n" + 
       "unbook                     - unbook the match you booked.\n"); 

    add_item(({ "window", "booking office", "office" }), booking_info);  
    add_prop(ROOM_I_INSIDE, 1); 

    add_exit(FIREBALL_SURROUND + "locker_room", "east", 
             enter_locker_room); 
    add_exit(FIREBALL_WALKWAY + "walk2", "west"); 
    add_exit(FIREBALL_STAND + "stand2", "up"); 
}


private void
make_attendant()
{
    int i; 

    attendant_name = "anra"; 
    attendant_adj = ({ "slender", "auburn-haired", "young" }) ; 
    attendant_parse = ({ attendant_name, "woman" }); 
    attendant_desc = "";  
    for (i = 0; i < sizeof(attendant_adj); i++) { 
        attendant_parse += ({ attendant_adj[i] + " woman" }); 
        attendant_desc += (attendant_adj[i] + " "); 
    } 
    attendant_desc += "woman"; 
}


int
enter_locker_room()
{
    return 0;
}


string
booking_info()
{
    return 
       (info + (this_player()->query_wiz_level() ? 
       "npcbook <team> vs <team>   - book a match between two npc teams.\n" 
       : "")); 
}


int
tregister(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->register_team(str); 
}

int
pregister(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->register_players(str); 
}

int
unregister(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->unregister_team(str); 
}

int
book(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->book_match(str); 
}

int
unbook(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->unbook_match(str); 
}

int
npcbook(string str)
{
    return FIREBALL_SCHEDULE_HANDLER->book_match_npc_vs_npc(str); 
}


/* 
 * Function:      announce
 * Description:   The secretary in the foyer will announce messages passed 
 *                to this function. 
 */ 
void 
announce(string msg)
{
    tell_room(this_object(), capitalize(attendant_name) + 
              " announces: " + msg + "\n"); 
}


/* 
 * usher_teams is called from the schedule handler 
 * to tell the players involved in the next match to 
 * go to the arena. This can only happen after the 
 * captains have said they are <ready>. 
 */ 
void
usher_teams(string home_team_name, string away_team_name) 
{
    if (!stringp(home_team_name) || !stringp(away_team_name)) 
        return;

    announce("Would the teams " + 
            query_proper_team_name(home_team_name) + " and " + 
            query_proper_team_name(away_team_name) + 
            " please make their way to the arena for the next match."); 
}



/* 
 * Function: tell_captains_too_late
 * 
 * Called from the schedule handler to tell captains that 
 * they have missed their booking. 
 */ 
void
tell_captains_too_late(string *captains)
{
    if (!sizeof(captains)) 
        return;

    announce("The team " + 
             ((sizeof(captains) == 1) ? "captain" : "captains") +
             " " + COMPOSITE_WORDS(map(captains, capitalize)) + " " +  
             ((sizeof(captains) == 1) ? "doesn't" : "don't") +
             " seem to be ready for the next match at the appropriate " +
             "time, therefore the match has been abandoned."); 
}


/* 
 * Function: ask_captains_ready
 * 
 * Called from the schedule handler to ask captains to confirm 
 * that they are ready for their booking. 
 */ 
void
ask_captains_ready(int seconds, string *captains)
{
    if (!sizeof(captains) || (seconds < 1))      
        return; 

    announce("Team " + ((sizeof(captains) == 1) ? "captain" : "captains") +
             " " + COMPOSITE_WORDS(map(captains, capitalize)) + ", " +  
             "please state that you are <ready> for your match " +
             "within the next " + LANG_WNUM(seconds) + " seconds."); 
}


int
captain_ready(string str)
{
    seteuid(getuid()); 
    write("You say that you are ready to play.\n"); 
    say(QCTNAME(this_player()) + " says that " + 
        this_player()->query_pronoun() + " is ready to play.\n"); 
    FIREBALL_SCHEDULE_HANDLER->captain_ready(this_player()->query_real_name()); 
    return 1;
}


/*
 * Function:     examine_fireball_info
 * Description:  An action function. Examine information in
 *               the fireball archive. 
 */ 
int
examine_fireball_info(string str)
{
    string str2; 

    if (!stringp(str))
        return 0; 

    if (str == "teams") 
        return FIREBALL_TEAM_HANDLER->write_teams_info(str); 

    if (sscanf(str, "player %s", str2) == 1) 
        return FIREBALL_TEAM_HANDLER->write_player_info(str2); 

    if (sscanf(str, "team %s", str2) == 1) 
        return FIREBALL_TEAM_HANDLER->write_team_info(str2); 

    if (sscanf(str, "results %s", str2) == 1)
        return FIREBALL_GAME_HANDLER->exa_results(str2); 

    return 0; 
}


void
init()
{
    ::init(); 
    add_action(examine_fireball_info, "exa"); 
    add_action(examine_fireball_info, "examine"); 
    add_action(examine_fireball_info, "look"); 

    add_action(tregister, "tregister");  
    add_action(pregister, "pregister"); 
    add_action(unregister, "unregister"); 
    add_action(unbook, "unbook"); 
    add_action(book, "book"); 
    add_action(captain_ready, "ready"); 
    init_help_support(); 

    if (this_player()->query_wiz_level())
        add_action(npcbook, "npcbook"); 
}

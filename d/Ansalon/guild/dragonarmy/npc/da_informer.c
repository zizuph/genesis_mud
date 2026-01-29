
/* 
   A Warfare Informer, an automated note writer who delivers
   based on /d/Calia/special/informer.c coded by Maniac

   This informer posts notes to the board of a victorious
   Dragonarmy, alerting to them to their reward - access to
   their secondary weapon trainer.

   Arman October 2018
*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <language.h>
#include <composite.h>
#include "/d/Krynn/clubs/warfare/defs.h"

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



private int
generate_note()
{

    object br;

    if (!stringp(board_room)) 
        return 0;

    board_room->load_me();
    if (!objectp(br = find_object(board_room)))
        return 0;

    note = "From the First Plane of the Infernal Realms I am called " +
        "to bare word to you, the Dragonarmy victorious in the conquest " +
        "of Krynn!\n\nHer Dark Majesty is pleased! The land now lies " +
        "subjugated to her will, and you have proven yourselves to be " +
        "the dominant power that will wield Her authority to ensure the " +
        "forces of Light remain crushed and impotent.\n\nTo support this " +
        "end, and in reward for your role, Her Majesty has summoned a " +
        "Weaponmaster from Ages Past to further train Her greatest " +
        "warriors. Seek him in your training halls. He will remain " +
        "there at your whim for as long as you remain the dominant " +
        "force in Krynn.\n\nKargruul, Quasit Imp, Messenger of the " +
        "Nine Hells.\n\n"; 
    return 1;
}


private void
leaveit()
{
     command("nod . "); 
     tell_room(environment(this_object()), "The tiny demon vanishes.\n"); 
     remove_object(); 
}


private void
writeit(object writer)
{
     object temp_player = this_player(); 
     set_this_player(writer);

     the_board->create_note("Victors reward! Death Knight Weaponmaster", 
         "Abyssal Imp", note);       
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
    add_name("imp");
    set_race_name("demon");
    set_adj("tiny");
    set_short("tiny demon");
    set_long("A tiny winged demon, sent from the Nine Hells to bare " +
        "a dark message from one of its denizens!\n"); 

     default_config_npc(300); 
     add_prop(OBJ_M_NO_ATTACK, 1); 
     add_prop(OBJ_M_NO_MAGIC_ATTACK, 1); 
     add_prop(LIVE_I_ALWAYSKNOWN, 0); 

     active = 0;
}

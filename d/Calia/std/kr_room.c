
/* 

   *************************************************************************
   This is now OBSOLETE. Do not inherit it into new code. Maniac, 30/7/2000.
   *************************************************************************



   Code to be inherited as the room base for rooms which smart krougs will 
   be fighting in, whether against PCs or NPCs. Chats, acts and "kill" 
   commands for the krougs are controlled by a single heartbeat in the room 
   which calls the central kroug brain. Also, to avoid needless combat 
   computation when krougs fight good aligned NPCs, this room code contains
   an npc vs npc combat routine.


   Coded by Maniac 31/7/95
 
   History:
             5/2/2000  routines moved to kroug code,
                     this exists now only until code
                     that inherits it is updated.     Maniac
            25/4/97  using filters instead of array 
                     processing in _inv functions,    Maniac
            10/5/96  added more query functions       Maniac
            24/3/96  added kroug vs npc combat handling  Maniac
            19/3/96  deal with sneak bug, stop fight  Maniac
            19/2/96  modified                         Maniac
            2/10/95  streamlined the tells            Maniac
            11/9/95        bug corrected              Maniac
            31/7/95        Created                    Maniac

*/

#pragma save_binary

inherit "/std/room"; 

#include <macros.h>
#include <filter_funs.h>
#include "/d/Calia/sys/kroug.h"


void
create_room()
{
    this_object()->create_kroug_room();
}


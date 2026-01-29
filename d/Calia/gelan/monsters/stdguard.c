/*  Standard guard code in Gelan, inherited by guards. 

    coder(s):   Merlin & Maniac 

    history: 
               5/3/2001   attitude inherited                    Maniac 
               20/12/2000 added criteria for murder             Maniac 
               13/2/2000  added query_calia_gelan_npc           Maniac 
                3/4/97    incorporated cadet friend npc         Maniac 
                26/7/95   Major revision to old file            Maniac 

    purpose:    (a) Monsters inheriting this code will make an automatic 
                    call for help to the guards when attacked, and some 
                    active guards will respond by coming to the monster's
                    aid if there are any.
                (b) Monsters inheriting this code will be able to go to
                    the aid of any residents of Gelan who have been 
                    attacked and have called for aid.
*/

#include "monster.h"
#include CADET_INCLUDE
#include GELAN_ENEMY_INCLUDE

inherit "/std/monster"; 
inherit "/d/Calia/std/intro"; 
inherit GC_FRIEND_NPC; 
inherit GELAN_ATTITUDE; 

#include <macros.h>

string start_room;         /* room before help */


int
query_calia_gelan_npc()
{
    return 1; 
}


/*
 * Function name: help_me
 * Description:   send help request to the master guard
 * Arguments:     meeting point, room, attacker
 * Returns:       number of guards alarmed
 */

int
help_me(string room, object attacker)
{
    return (GELAN_SPECIALS + "head_guard")->help_me(room, attacker);
}


/* 
 *  Function:     query_murder_recorded 
 *  Description:  Called when this npc dies, this function should return 
 *                1 if the killing should be recorded as a murder. By 
 *                default it returns 1 if the killer is interactive, 
 *                0 otherwise. Inheriting npcs mask this function if 
 *                it's desirable to introduce different interpretations. 
 */ 
int 
query_murder_recorded(object killer)
{
    /* If it's someone already suspended from graduate status, 
       they've really asked for it. */ 
    return (objectp(present(GC_RING_ID, killer)) && 
            !IS_GRADUATE(killer)); 
}


/* 
 * Function:      second_life 
 * Description:   Called when this npc dies. This instance records 
 *                the murder in the Gelan enemy control code if 
 *                query_murder_recorded() returns 1. 
 */
int
second_life(object killer)
{
    seteuid(getuid()); 
    if (query_murder_recorded(killer)) 
        GELAN_ENEMY_CONTROL->record_murder(killer, this_object()); 
    return 0; 
}


/* 
 * Function name: attacked_by
 * Description:   this is the function which is called when we are attacked
                  here we inform the head guard about the attack
 * Arguments:     attacker
 * Returns:       none
 */

void
attacked_by(object attacker)
{
    string fn;

    ::attacked_by(attacker);

    if (!(attacker->query_prop(ATTACKED_GELAN)))
        attacker->add_prop(ATTACKED_GELAN, 1);

    fn = file_name(environment(this_object()));
    
    help_me(fn, attacker); 
}



void
set_up_move_strings()
{
     set_m_in("strolls in.");
     set_m_out("strolls");
     set_mm_in("rushes in.");
     set_mm_out("rushes off.");
}



void
return_to_post()
{
    this_object()->move_living("X", start_room);
}


string
return_check()
{
    if (!query_attack() && 
        (!((file_name(environment(this_object()))) == start_room)))
        return_to_post();

    if (query_attack())
        return "";

    switch(random(5)) {
        case 0 : return "yawn";
                 break;
        case 1 : return "ponder";
                 break;
        case 2 : return "twiddle";
                 break;
        case 3 : return "whistle musically";
                 break;
        case 4 : return "emote strolls around.";
                 break;
    }
}


/*
 * help_other
 * set an alarm to help some town npc that's being attacked by attacker 
 * in given room.
 */

void
help_other(string room, object attacker)
{
    string direction;

    if (!attacker)
        return;

   if (query_attack() == attacker)
       return;

   if (environment(this_object()) != environment(attacker))
       this_object()->move_living("X", room);

   if (!present(attacker, environment(this_object()))) {
       return_check(); 
       return;
   }

   command("kill " + attacker->query_real_name()); 
}


/* Called when enemy has been killed by guard. 
 */
void
notify_you_killed_me(object attacked)
{
    command("cheer");
    command("bounce");
    set_alarm(5.0, 0.0, "return_check");
}


/* Called when the enemy left the room. Guard returns to 
 * his/her post.
 */
void
notify_enemy_gone(object attacked)
{
    set_alarm(5.0, 0.0, "return_check");
}


/*
 * Function name: set_start_room
 * Description:   sets the start room for returning after a fight
 * Arguments:     filename of room
 * Returns:       none
 */
void
set_start_room(string room)
{
    start_room = room;
}


void
init_living()
{
    ::init_living(); 
    init_attitude(this_player()); 
}

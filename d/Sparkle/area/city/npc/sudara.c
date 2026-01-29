/*
 * Sudara the Cadet Recruiter
 *
 * Sudara is a Learned Cadet who is currently working for Xorfin.
 * She is responsible for recruiting Cadets from Sparkle and
 * giving them something that assists in guiding them towards
 * the Gelan ship so they can get to the Cadets.
 * 
 * Created by Petros, June 2009
 */
#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <ss_types.h>
#include "../defs.h"

// Inheritance 
inherit SPARKLE_NPC_BASE;

/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sparkle_npc()
{
    set_name("sudara");
    add_name("human");
    set_race_name("human");
    set_adj( ({ "blond", "broad-shouldered" }) );
    set_gender(G_FEMALE);
    set_long("This " + short() + " looks extremely friendly "
        + "and helpful. She appears to be quite experienced "
        + "in the art of combat.\n");

    default_config_npc(85);
}

/*
 * Function name: is_valid_room
 * Arguments  : str - the path of the room
 * Returns   : 1 = can be used in the pathfinding, 0 if not
 */
public int is_valid_room(string str)
{
    if (wildmatch(STREET_DIR + "*", str))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 * Arguments    :       hour - current hour in Sparkle time
 * Returns      :       nothing
 */
public void
alert_hour_change_hook(int hour)
{
    /*
    if (is_busy())
    {
        // Don't participate in daily routines when interacting.
        return;
    }
    
    if (hour % 2)
    {
        if (walk_to_room(STREET_DIR + "east_2d"))
        {
            command("$emote looks like he has purchased enough beer.");
        }
    }
    else
    {        
        if (walk_to_room(STREET_DIR + "east_3c"))
        {
            command("$emote looks and realizes he is out of beer.");     
            command("$emote gets up looking for some beer.");
        }
    }
    */
}

/*
 * Function name:       walk_destination_reached_hook
 * Description  :       Override this to do something when the 
 *                      npc arrives at his destination.
 * Arguments    :       none
 * Returns      :       nothing
 */
public void
walk_destination_reached_hook()
{
    /*
    string roomfile;
    
    roomfile = MASTER_OB(environment(this_object()));
    switch (roomfile)
    {
    case STREET_DIR + "east_2d":
        command("$emote lies down on the ground and begins drinking.");
        break;
    
    case STREET_DIR + "east_3c":
        command("$emote enters and loudly demands some beer.");
        break;
    }
    */
}

/*
 * Function name:       walk_precondition_hook
 * Description  :       Override this to define something that the npc
 *                      will check before moving onto the next step.
 * Arguments    :       direction - direction the next move is
 *                      roomfile  - current room location
 * Returns      :       0/1 - allow walk step or not
 */
public int
walk_precondition_hook(string direction, string roomfile)
{
    return !is_busy();
}

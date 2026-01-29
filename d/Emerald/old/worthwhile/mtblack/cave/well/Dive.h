/* This is this basic code for the well in the Emerald caves.              */
/* It was based on the code used in the well in the Terel mansion.         */ 
/* Many thanks go to Dust, who wrote the original code.                    */
/* Recoded on 11/10/95 by Tulix III with bug fixes, prototype functions,   */
/* types, call_out replacement & other updates.                            */

inherit "/std/room";
#include <language.h>
#include "default.h"

#pragma strict_types

/* Global variable */
public int check_things_id = 0;

/* Prototype functions */
public int calc_basic();
public int try_hor();
public int try_up();
public int try_down();
public void check_things();
public void sink_down(object thing);
public void float_up(object thing);
public int end_dive();
public int query_check_things_id();


/* Check to see if rooms above and below are defined */
#ifndef UP_ROOM
#define UP_ROOM 0
#endif

#ifndef DOWN_ROOM
#define DOWN_ROOM 0
#endif


/* We may be debugging the code */
#ifndef DEBUG
#define DEBUG 0
#endif


/*
 * Function name:   calc_basic
 * Description:     calculate basic fat, based on str, dex, con & swim.
 * Returns:         fat
 */
public int
calc_basic() 
{
    return(3*this_player()->query_skill(SS_SWIM) + 
        this_player()->query_stat(SS_STR) + 
        this_player()->query_stat(SS_CON) + 
        this_player()->query_stat(SS_DEX));
}

/*
 * Function name:   try_hor
 * Description:     see if player can swim horizontally.
 * Returns:         1 if player cannot swim that way, 0 if player can.
 */
public int
try_hor()
{
    int fat;
   
    fat = calc_basic();
    fat = (this_player()->query_prop(OBJ_I_WEIGHT) * 1000) /
          (this_player()->query_prop(OBJ_I_VOLUME) * fat);
    if (fat < 1) fat = 1;
    if (fat > 40) fat = 40;
   
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim horizontally with all the stuff " +
            "you carry.\n");
        return 1;
    }
   
    this_player()->add_fatigue(-fat);
    return 0;
}

/*
 * Function name:   try_up
 * Description:     see if player can swim upwards.
 * Returns:         1 if player cannot swim that way, 0 if player can.
 */
public int
try_up()
{
    int fat;
   
    fat = calc_basic();
    fat = (this_player()->query_prop(OBJ_I_WEIGHT) * 400) /
          (this_player()->query_prop(OBJ_I_VOLUME) * fat);
    if (fat < 1) fat = 1;
    if (fat > 40) fat = 40;
   
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim upwards with all the stuff " +
            "you carry.\n");
        return 1;
    }
   
    this_player()->add_fatigue(-fat);
    return 0;
}

/*
 * Function name:   try_down
 * Description:     see if player can swim downwards.
 * Returns:         1 if player cannot swim that way, 0 if player can.
 */
public int
try_down()
{
    int fat;
   
    fat = calc_basic();
    fat = (this_player()->query_prop(OBJ_I_VOLUME) * 700) /
          (this_player()->query_prop(OBJ_I_WEIGHT) * fat);
    if (fat < 0) fat = 0;
    if (fat > 40) fat = 40;
    
    if (this_player()->query_fatigue() < fat)
    {
        write("You feel too tired to swim downwards with all the stuff " +
              "you carry.\n");
        return 1;
    }
    
    this_player()->add_fatigue(-fat);
    return 0;
}

/*
 * Function name:   check_things
 * Description:     make non-living objects either float or sink.
 */
public void
check_things()
{
    int i, interval;
    object *op, thing;
    
    if (DEBUG != 0)
    {
        tell_room(this_object(), "Check_things executed....\n");
        tell_room(this_object(), "id = " + check_things_id + ".\n\n");
    }
   
    op = all_inventory();
    
    /* Cancel the check_things alarm if no objects are in this room. */
    if (!sizeof(op))
    {
        remove_alarm(check_things_id);
        check_things_id = 0;
        return;
    }
    
    /* Allow a new check_things alarm to be set. */
    check_things_id = 0;

    /* Check all objects in the room.... */
    for (i=0; i<sizeof(op); i++)
    {
        thing = op[i];
        
        /* Do not bother doing float & sink routines for players. */
        if (interactive(thing))
            continue;
        
        if (DOWN_ROOM != 0)
        {
            /* Objects will sink if more dense than water. */
            if (thing->query_prop(OBJ_I_WEIGHT) > 
                thing->query_prop(OBJ_I_VOLUME))
            {    
                set_alarm( 4.0, 0.0, &sink_down(thing));
            
                if (DEBUG)
                {
                    tell_room(this_object(), "Sink alarm set.\n");
                    tell_room(this_object(),"Down room = "+ DOWN_ROOM +".\n\n");
                }
            }
        }

        if (UP_ROOM != 0)
        {
            /* Objects will rise if less dense than water. */
            if (thing->query_prop(OBJ_I_WEIGHT) <
                thing->query_prop(OBJ_I_VOLUME))
            {    
                set_alarm( 4.0, 0.0, &float_up(thing));
            
                if (DEBUG != 0)
                {
                    tell_room(this_object(), "Float alarm set.\n");
                    tell_room(this_object(), "Up room = " + UP_ROOM + ".\n\n");
                }
            }
        }
    }
}

/*
 * Function name:   sink_down
 * Description:     move an object to the room below.
 * Arguments:       object thing: sinking item
 */
public void
sink_down(object thing)
{
    string desc;
    
    desc = check_call(thing->short());
    
    tell_room(TO, CAP(LANG_ADDART(desc)) + " sinks downwards.\n");
    tell_room(DOWN_ROOM, CAP(LANG_ADDART(desc)) + " arrives from above.\n");

    thing->move(DOWN_ROOM);
}

/*
 * Function name:   float_up
 * Description:     move an object to the room above.
 * Arguments:       object thing: floating item
 */
public void
float_up(object thing)
{
    string desc;
    
    desc = check_call(thing->short());
    
    tell_room(TO, CAP(LANG_ADDART(desc)) + " floats upwards.\n");
    tell_room(DOWN_ROOM, CAP(LANG_ADDART(desc)) + " arrives from below.\n");
    
    thing->move(UP_ROOM);
}

/*
 * Function name:   end_dive
 * Description:     tell player that they are no longer at risk of drowning.
 * Returns:         0
 */
public int
end_dive()
{
    write("You finally get out of the water and you're very glad you can " +
          "breathe again - you were afraid you'd drown! You feel " +
          "quite relieved.\n");
    return 0;
}

public void
create_room()
{
    set_short("under-water cave");
    set_long("   You're diving in an underwater cave system. " +
         "You hope you have enough air in your lungs to survive here...\n" +
         "The water is a bit murky - which makes it difficult to see " +
        "things.\n\n");
    
    add_item("water","The water is murky, and hard to see through.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    
    CREATEADD
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    /* Trigger check_things alarm when an object enters the room. */
    if (check_things_id == 0)
    {
        check_things_id = set_alarm( 4.0, 0.0, check_things);
            
        if (DEBUG != 0)
        {
            tell_room(this_object(), "Initial enter_inv alarm set.\n");
            tell_room(this_object(), "id = " + check_things_id + ".\n\n");
        }
    }
}

/*
 * Function name:   query_check_things_id
 * Description:     debug function
 * Returns:         int check_things_id
 */
public int
query_check_things_id()
{
    return check_things_id;
}

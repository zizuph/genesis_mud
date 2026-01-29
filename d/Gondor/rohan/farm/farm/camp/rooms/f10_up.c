/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define DOWN "f10"

void add_guard();
object guard;

/*
 * I was having trouble with the room resetting descriptions and recloning
 * monsters every time you walked into it. So I added this int is_guard
 * in hopes of limiting it to loading once. after that, guards may reclone 
 * in the reset_room() function.
 */
int is_guard = 0;


void
create_dunlending()
{
    if(is_guard == 0)
    {
    set_short(forest_up_short());
    set_long(forest_up_long());
    }



    add_forest_up();
    if(is_guard == 0)
    {
        add_guard();
        is_guard ++;
    }
    
    
    add_exit(CAMP_ROOM_DIR + DOWN, "down");
}

void
reset_room()
{

    add_guard();
    
}


void
add_guard()
{
    if(present(guard))
    {
        return;
    }
       if (!present(guard))
       {
    guard = clone_object(ARCHER);
    
    guard->move(TO);
        
    object guard2;
    guard2=clone_object(ARCHER);
    
    guard2->move(TO);
    if(!(random(2)))
    {
        object guard3;
        guard3 = clone_object(GUARD);
        guard3->move(TO);
    }
    if(!random(10))
    {
        object captain;
        captain = clone_object(CAPTAIN);
        captain->move(TO);
    }
       return;
       }
       return ;
    
}
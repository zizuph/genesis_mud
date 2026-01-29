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

#define DOWN "test_room"
void add_guard();
object guard;

void
create_dunlending()
{
    set_short(forest_up_short());
    set_long(forest_up_long());




    add_forest_up();
    
    add_guard();
    
    add_exit(CAMP_ROOM_DIR + DOWN, "down");
}

void
reset_room()
{

    
    
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
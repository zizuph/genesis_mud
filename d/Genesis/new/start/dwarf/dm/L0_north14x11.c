/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L0_north14x11.c
 */

#pragma strict_types

#include "mountain.h"

inherit STD_MOUNTAIN_ROOM;

#include <stdproperties.h>      
#include <language.h>           
#include <macros.h>             

static int Exit_revealed;

/* Prototypes */
public void create_mountain_room();
public void reset_room();
public string do_search(object tp, string arg);
public int query_exit_status();

/* Defines */

/* Globals */
public string * nearby_rooms = ({ });

/* Function name: create_mountain_room
 * Purpose      : set up the room
 */
public void
create_mountain_room()
{
    set_short("Passageway in the depths of the mountain");
    set_long("The walls here are a smooth, but a bit worn down. "+
             "The floor is cold and somewhat and rugged. There's "+
             "a cold breeze coming from the ceiling.\n" );
    add_item( ({"wall", "walls"}), "The walls are worn down "+
              "and has some cracks in it.\n" );
    add_item( ({"floor"}), "Cold and dark, the floor is rugged "+
              "and there seem to be some rocks lying around.\n" );
    add_item( ({"crack", "cracks"}), "The cracks looks more "+
              "the result of years of scraping.\n" );
    add_item( ({"rock", "rocks", "pile of rocks"}), "The pile of "+
              "rocks seem to have fallen down from the ceiling, "+
              "causing the chilling breezes.\n" );
    add_item( "ceiling", "A slight chill comes from the ceiling. "+
              "There are some loose pieces of rocks waiting to fall "+
              "down any second.\n" );              

    /* Exits */
    add_exit( MOUNTAIN + "L0_north15x10.c", "northeast", 
              &query_exit_status(), 1, -1);
    add_exit( MOUNTAIN + "L0_tunnel14x12.c", "south" );

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    nearby_rooms = query_nearby_rooms("");

    reset_room();
}

/* Function name: reset_room
 * Purpose      : resets the room
 */
public void
reset_room()
{
    ::reset_room();
    Exit_revealed = 0;
}

/* Function name: do_search
 * Purpose      : search for an exit to the northeast.
 * Arguments    : tp - the player doing the search 
 *                arg - the object searched by tp
 * Returns      : string holding the search result
 */
public string
do_search(object tp, string arg)
{
    string      msg,
                saymsg;

    arg = lower_case(arg);
    if ( Exit_revealed )
    {
        return "";
    }

    Exit_revealed = 1;    
    if ( parse_command(arg, ({}), "[the] [pile] [of] 'rocks' / 'rock'") )
    {
        msg = "You find a way northeast through the pile of rocks.\n";
        saymsg = QCTNAME(tp) + " finds a way through the pile.\n";
    }
    say(saymsg);
    return msg;
}

/* Function name: query_exit_status
 * Purpose      : to check whether it is possible to move this 
 *                destination
 * Returns      : 0 - exit is revealed and move allowed
 *                1 - exit is not revealed and move disallowed
 */
public int
query_exit_status()
{
    if (Exit_revealed)
    {
        return 0;
    }
    else
    {
        write("There is no obvious exit northeast.\n");
        return 1;
    }
}
/*
 * /d/Gondor/mordor/ungol/lair/lairgate_base.c
 *
 * /Mercade, 18 October 1993
 *
 * Revision history: Major debugging (strange that nobody has noticed
 * the thingie doesn't work for all these years). Chmee 25.06.2002
 */

inherit "/std/door";
    
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

#define LAIR_I_I_FOUND_HOLE_OVER_GATE "_lair_i_i_found_hole_over_gate"
#define LAIR_I_I_WITNESSED_CLIMBER    "_lair_i_i_witnessed_climber"

/*
 * Do find the hole over the gate you need awareness 45 unless you have seen
 * someone climbing over the gate. In that case you only need 25.
 */
#define MINIMUM_CLIMB_NEEDED  40
#define MIN_AWARENESS_NEEDED  40
#define MIN_AWARENESS_CLIMBER 25

string hole_description();

/*
 * Called to create the door.
 */
void create_door()
{
    add_name( "gate" );
    add_adj( ({ "strong", "stone" }) );
    
    add_prop( OBJ_S_SEARCH_FUN, "search_this_door" );
    add_prop( OBJ_I_SEARCH_TIME, 10 );

    add_item( ({ "hole", "opening" }), hole_description );

    set_open_command( "open" );
    set_close_command( "close" );

    set_open( 0 );
    set_locked( 1 );

    set_lock_name( ({ "iron bolt", "bolt", "lock", "latch" }) );

    set_door_id( "stone gate" );
    set_door_name( ({ "gate", "door"  }) );
    set_door_desc( "The gate is made of stone and it looks very strong.\n" );
    set_long( query_door_desc() );
}

/*
 * Called to add the command climb over the gate.
 */
void init()
{
    ::init();

    add_action( "do_climb", "climb" );
    add_action( "do_climb", "squeeze" );
}

/*
 * Get a dependant description for the hole.
 */
string hole_description()
{
    if (this_player()->query_prop( LAIR_I_I_FOUND_HOLE_OVER_GATE ))
    {
        return "Over the stone gate is a small opening.\n";
    }

    if (this_player()->query_prop( LAIR_I_I_WITNESSED_CLIMBER ))
    {
        return "Though you saw someone apprearing over the gate, you "+
            "cannot exactly tell how that person did it.\n";
    }
    return "You see no hole.\n";
}

/*
 * Try to climb over the gate.
 */
int do_climb( string str )
{
 object tp = this_player(), *players;
 int i;

    if (!CAN_SEE_IN_ROOM( tp ))
    {
        notify_fail( "It is too dark to see!\n" );
        return 0;
    }
    notify_fail( capitalize( query_verb() )+ " what?\n" );
    if ((!strlen( str )) ||
        (!(tp->query_prop( LAIR_I_I_FOUND_HOLE_OVER_GATE ))))
    {
        return 0;
    }

    if (!parse_command( str, tp, " [through] [the] [hole] / [opening] "+
        "[over] [the] [strong] [stone] 'gate' / 'door' " ))
    {
        return 0;
    }

    if (tp->query_skill( SS_CLIMB ) < MINIMUM_CLIMB_NEEDED)
    {
        write( "You try to climb over the strong stone gate, but fail.\n" );
        SAY(" tries to climb over the strong stone gate, but fails.");
        return 1;
    }

    write( "You squeeze through the hole over the gate and manage to " +
        "climb over it.\n" );

    /*
     * This is a little strange for you get a good message and then a 'bad'
     * message if you fail, but otherwise the player gets the new room
     * description before he gets the message about his transport.
     * It is very unlikely however that a player cannot be moved.
     */
    if (tp->move_living( "M", other_room, 1 ))
    {
        write( "Somehow you fail to climb over the stone gate.\n" );
        return 1;
    }

    SAY( " squeezes through the hole over the gate and manages to climb "+
        "over it." );
    TELL_ROOM( other_room, tp, " arrives climbing through the hole over "+
        "the strong stone gate.", tp );

    players = FILTER_PLAYERS( all_inventory( find_object( other_room ) ) )+
        FILTER_PLAYERS( all_inventory( environment( this_object() ) ) );
    for (i=0;i<sizeof( players );i++)
    {
        players[i]->add_prop( LAIR_I_I_WITNESSED_CLIMBER, 1 );
    }
    return 1;
}

/*
 * Search this door ;-)
 */
string search_this_door( object searcher, string str )
{
    if (parse_command( str, searcher,
        " [the] [strong] [stone] 'gate' / 'door' " ))
    {
        if ((searcher->query_prop( LAIR_I_I_FOUND_HOLE_OVER_GATE )) ||
            (searcher->query_skill( SS_AWARENESS ) >=
            MIN_AWARENESS_NEEDED) ||
            ((searcher->query_prop( LAIR_I_I_WITNESSED_CLIMBER )) &&
            (searcher->query_skill( SS_AWARENESS ) >=
            MIN_AWARENESS_CLIMBER)))
        {
            searcher->add_prop( LAIR_I_I_FOUND_HOLE_OVER_GATE, 1 );
            return "The great block is shaped like a heavy door. Above it "+
                "is a dark black space between the top and the low arch "+
                "of the opening. It is probably only meant to be a stop "+
                "against the intrusion of Shelob, fastened on the inside "+
                "with some latch or bolt beyond the reach of her cunning.\n";
        }
    }

    if (parse_command( str, searcher, " [the] 'hole' / 'opening' [over] "+
        "[the] [strong] [stone] [gate] / [door] " ))
    {
        if (searcher->query_prop( LAIR_I_I_FOUND_HOLE_OVER_GATE ))
        {
            return "Close inspection of the opening over the gate reveals "+
                "that the opening is probably big enough for you climb "+
                "through it.\n";
        }
    }
    return 0;
}

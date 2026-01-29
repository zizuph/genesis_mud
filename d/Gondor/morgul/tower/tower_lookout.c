/*
 * /d/Gondor/morgul/tower/tower_lookout.c
 * The lookout room above the entrance to the Morgul Tower
 * The room it overlooks is ~Gondor/morgul/city/mmr3.c
 *
 * Coded and Copyright Morbeche@Genesis March 2000
 * 07.08.2002, Chmee, debugging and code modernization.
 */

#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define TOWER_ENTRANCE ("/d/Gondor/morgul/city/mmr3")

/* Prototypes */
public string exa_below();
int do_command( string str );
int do_throw( string str );

void  create_morgul_tower_room()
{
    set_level( 3 );
    set_room_type( "dark balcony" );
    set_extra_long( "This room is entirely devoid of furniture or "+
        "decoration.  Its only feature is a large balcony overlooking "+
        "the street to the east, where it is possible to observe and "+
        "shout orders to those who wait outside of the Tower." );

    add_item( ({ "down", "street", "entrance", "below", "view" }),
        exa_below );
    add_item( "balcony", "The balcony is simply an opening in the eastern "+
        "wall, allowing you to look down and shout to those who may be "+
        "gathered at the entrance to the Tower.\n" );

    add_walls();
    add_roof();
    add_floor();

    add_exit( MORGUL_ROOM_DIR + "tower_3e", "west", 0, 1 );
                                /*A silly workaround of the tower.c default
                                 *configuration. But it works effectively 
                                 *and such a one time alarm doesn't hurt. */
    set_alarm( 0.1, 0.0, &add_prop( ROOM_I_INSIDE, 0 ) );
}

public string exa_below()
{
 string desc;
 object entr_room, *people;

    desc = "A balcony extends from the wall of the Tower, almost looming "+
        "over you as you stand here.";
    if (!CAN_SEE_IN_OTHER_ROOM( this_player(), TOWER_ENTRANCE ) )
    {
        desc += " It is too dark to see anything below the balcony.";
        return 0;
    }
    if (objectp( entr_room = find_object( TOWER_ENTRANCE ) ))
    {
        if (sizeof( people = FILTER_LIVE( all_inventory( entr_room ) ) ))
        {
            return desc+ " You can see "+ COMPOSITE_LIVE( people )+
                " standing at the entrance to the Dark Tower.\n";
        }
    }
    return desc+ " There is no one standing at the entrance to the Dark "+
        "Tower.\n";
}
void
init()
{
    ::init();

    add_action( "do_command", "shout" );
    add_action( "do_throw", "throw" );
    add_action( "do_throw", "toss" );
    add_action( "do_throw", "chuck" );
}

int do_throw( string str )
{
	object treasure;
	int amount = 0;
	mixed result;
    if (!strlen( str ))
    {
        notify_fail( "Throw what down?\n" );
        return 0;
    }
    if (!parse_command( str, this_object(),
        " %d %o [down] [below] [to] [the] [ground] ", amount,treasure ))
    {
        if (!parse_command( str, this_object(),
            " %o [down] [below] [to] [the] [ground] ", treasure ))
        {
            notify_fail( "Throw down what?\n" );
            return 0;
        }
    }
    if (!treasure)
    {
        notify_fail( "Toss down what?\n" );
        return 0;
    }
    if (environment( treasure ) != this_player())
    {
        notify_fail( "You do not seem to have that in your inventory.\n" );
        return 0;
    }
    if ((amount) && (!function_exists( "split_heap", treasure )))
    {
        notify_fail( "You should only throw down one of those at "+
            "a time.\n" );
        return 0;
    }

	if(result = treasure->query_prop(OBJ_M_NO_DROP))
	{
		if(stringp(result)) write(result);
		else write("You cannot seem to throw that down.\n");
		return 1;
	}

    if ((amount) && (function_exists( "split_heap", treasure )))
    {
        write( "You toss down "+ lower_case( str )+ ".\n" );
        say( QCTNAME( this_player() )+ " tosses down "+ lower_case( str )+
            ".\n" );
        treasure->split_heap( amount );
        treasure->move( TOWER_ENTRANCE, 1 );
        tell_room( TOWER_ENTRANCE, capitalize( str )+ " come flying down "+
            "from the balcony above.\n" );
        return 1;
    }
    write( "You toss down "+ COMPOSITE_DEAD( treasure )+ ".\n" );
    say( QCTNAME( this_player() )+ " tosses down "+
        COMPOSITE_DEAD( treasure )+ ".\n" );
    treasure->move( TOWER_ENTRANCE, 1 );
    tell_room( TOWER_ENTRANCE, capitalize( COMPOSITE_DEAD( treasure ) )+
        " comes flying down from the balcony above.\n" );
    return 1;
}

int do_command( string str )
{
    if (!strlen( str ))
    {
        notify_fail( "Shout what?\n" );
        return 0;
    }
    write( "You shout down: "+str +"\n" );
    say( QCTNAME( this_player() )+ " shouts: "+ str+ "\n" );
    tell_room( TOWER_ENTRANCE, "A menacing voice from the balcony shouts: "+
        str+ "\n" );
    return 1;
}


/*
 *
 *  Modification Log
 *  ================
 *  Morbeche, March 2000 - Added the description of the balcony.
 *  Chmee, July, 2002 - Update and modernization.
 * Gwyneth, 5/25/2004 - Fixed bug that showed the real names of
*                      players to those in the tower whether or
 *                     not they knew them.
 *  Eowul, 10/24/2012 - Renabled the raven
 */

#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#include "/d/Gondor/defs.h"

#define BEHOLDING_CHAMBER "/d/Gondor/guilds/morgulmage/rooms/tower_6c"
#define TOWER_BALCONY "/d/Gondor/morgul/tower/tower_lookout"

public void reset_room();
static object *orcs = allocate( 5+ random( 5 ) );
public string exa_balcony();

public void create_morgul_room()
{
    set_extraline( "Here the road makes a sharp bend at the foot of "+
        "the tower. It falls down northwards to the Morgul Gate and "+
        "the vale of the Morgulduin behind it, while it slowly ascends "+
        "towards the Mordor Gate and the heights of the Ephel Duath in "+
        "the other direction. A balcony looms over you, while "+
        "the entrance to the mighty tower of Minas Morgul lies to "+
        "the southwest." );
    set_road( 2 );
    set_side( "southwest" );

    add_item( "balcony", exa_balcony );

    add_item( ({ "gates", "morgul gate", "mordor gate" }), "From where "+
        "you are standing, you can see Morgul Road running north to "+
        "Morgul Gate and east to Mordor Gate. You cannot make out any "+
        "details of the gates themselves from here.\n" );
    add_mountain();
                                /*I'm not sure why such low fatique values
                                 *have been left here. Historical reasons?*/
    add_exit( MORGUL_DIR+ "city/mmr2", "north", check_exit, 1 );
    add_exit( MORGUL_DIR+ "city/mmr4", "east", check_exit, 2 );

    clone_object( MORGUL_DIR+ "tower/doors/outergate_out" )->
        move( this_object(), 1 );

    reset_room();
                                /*This idea with a dummy room seems to be
                                 *obsolete and unnecessary but I don't feel
                                 *like recoding something that's working. */
    call_other( "/d/Gondor/morgul/blackrider", "telelednigsanka" );
                                /*To prevent refreshing the gate.         */
    add_prop( ROOM_I_NO_CLEANUP, 1 );
}

public object clone_npc( object npc, string npc_file )
{
 int rs = random( 70 );

    if (objectp( npc ))
    {
        return npc;
    }
    npc = clone_object( npc_file );
    npc->set_restrain_path( MORGUL_DIR+ "city/" );
    npc->set_random_move( 10 );
    npc->arm_me();
    npc->move_living( "down", this_object() );
    return npc;
}

public void enter_inv( object ob, object from )
{
 int wizrank;
 string name;

    ::enter_inv( ob, from );

    if (!objectp( ob ) || !interactive( ob ))
    {
        return;
    }
    name = ob->query_real_name();
    if (ob->query_invis())
    {
        return;
    }
    tell_room( BEHOLDING_CHAMBER,
        "The black raven on the window ledge caws urgently.\n" );
   tell_room( TOWER_BALCONY, QCTNAME(ob) + " arrives to stand at "+
        "the entrance of the Tower.\n" );
}                                                                              

public void leave_inv( object ob, object from )
{
 string name;

    ::leave_inv( ob, from );

    if (!objectp( ob ) || !interactive( ob ))
    {
        return;
    }
    if (ob->query_invis())
    {
        return;
    }
    tell_room( TOWER_BALCONY, QCTNAME(ob) + " moves out of "+
        "the view of the balcony.\n" );
}

public string exa_balcony()
{
 string desc;
 object balc_room = find_object( TOWER_BALCONY );

    desc = "A balcony extends from the wall of the Tower, almost looming "+
        "over you as you stand here.";
    if (objectp( balc_room ))
    {
        if (sizeof( FILTER_LIVE( all_inventory( balc_room ) ) ))
        {
            return desc+ " You think you can see dark shapes moving on "+
                "the balcony.\n";
        }
    }
    return desc+ " The balcony appears empty at this time.\n";
}

public void reset_room()
{
    set_alarm( 20.0+ rnd()* 40.0, 0.0,
        &clone_npcs( orcs, MORGUL_DIR+ "npc/ithil_orc", 90.0 ) );
}


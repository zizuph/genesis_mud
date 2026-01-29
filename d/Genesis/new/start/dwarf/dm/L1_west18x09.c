/*
 * Written by Nuf.
 * /d/Genesis/nuf/startloc/dm/L1_west18x09.c
 */

#pragma strict_types

#include "mountain.h"

inherit STD_MOUNTAIN_ROOM;

#include <stdproperties.h>
#include <language.h>
#include <macros.h>

static int Weapon_found;

/* Prototypes */
public void create_mountain_room();
public void reset_room();
public string do_search(object tp, string arg);
public int query_weapon_found();

/* Defines */
#define FIXEUID     setuid();    seteuid(getuid())

/* Function name: create_mountain_room
 * Purpose      : set up the room
 */
public void
create_mountain_room()
{
    set_short("Deserted room in the depths of the mountain");
    set_long("The walls here are a smooth, but a bit worn down. "+
             "The floor is cold and somewhat and rugged. There's "+
             "a cold breeze coming from the ceiling. The ceiling "+
             "has sunk in, the rooms hardly holds one person.\n" );
    add_item( ({"wall", "walls"}), "The walls are worn down "+
              "and has some cracks in it.\n" );
    add_item( "ceiling", "The ceiling has sunk in, and a cold breeze "+
              "comes from it.\n" );
    add_item( ({"floor"}), "The floor is cold. Several things lie "+
              "on the floor.\n" );
    add_item( ({"crack", "cracks"}), "The cracks looks more "+
              "the result of years of scraping.\n" );
    add_item( ({"rock", "rocks", "pile of rocks"}), "The pile of "+
              "rocks seem to have fallen down from the ceiling, "+
              "causing the chilling breezes.\n" );
    add_item( "things", "Several different items lie scattered on "+
              "floor. Some general junk, rusty bracelets, bones, "+
              "straws and an old pillow.\n" );
    add_item( ({"bracelet", "rusty bracelet", "rusty bracelets", "bracelets"}), 
              "The rusty bracelets are totally useless and have no value.\n" );
    add_item( ({"bones", "piles of bone"}), "A heap of bones, "+
              "the skull is quite round and big in proportion "+
              "to the other parts.\n" );
    add_item( ({"junk", "general junk"}), "Generally useless junk "+
              "that someone didn't grab when running away.\n" );
    add_item( "skull", "A skull from a humanoid creature, it is "+
              "dusty and is gray to the color.\n" );

    /* Exits */
    add_exit( MOUNTAIN + "L1_north19x09.c", "east" );


    /* Properties */
    add_prop(OBJ_I_SEARCH_TIME, 5); 
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    reset_room();
}

/* Function name: reset_room
 * Purpose      : resets the room
 */
public void
reset_room()
{
    ::reset_room();
    Weapon_found = 0;
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
    string msg,
           saymsg;
    object ob;

    arg = lower_case(arg);
    if ( Weapon_found )
    {
        return "";
    }

    Weapon_found = 1;

    FIXEUID;
    ob = clone_object(WEAPON_DIR + "dm_axe.c");
    ob->set_dull(1);
    ob->set_repair(1);

    if ( parse_command(arg, ({}), "[the] [pile] [of] 'bones'") )
    {
        msg    = "You find a " +LANG_ADDART(ob->short())+ ".\n";
        saymsg = QCTNAME(tp) + " finds "+LANG_ADDART(ob->short())+ 
                 ".\n";
    }
    else
    {
        return "";
    }

    if (ob->move(tp))
    {
        msg += "Oops. You dropped it.\n";
        saymsg += QCTNAME(tp) + " drops the " + 
                  LANG_ADDART(ob->short()) + ".\n";
        ob->move(this_object(), 1);
    }                 
    say(saymsg);
    return msg;
}

/* Function name: query_weapon_found
 * Purpose      : to see if a weapon has been found
 * Returns      : 1 - if weapon has been found
 *                0 - if weapon has not yet been found
 */
public int
query_weapon_found()
{
    return Weapon_found;
}

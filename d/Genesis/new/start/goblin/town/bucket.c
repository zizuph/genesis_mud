/*
 * File         : /d/Genesis/new/start/goblin/town/bucket.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 17, 1999
 * Modifications: 
 * Purpose      : Ridin' the bucket!
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#define BUCKET     "/d/Genesis/new/start/goblin/town/bucket"
#define TOP        "/d/Genesis/new/start/goblin/town/well"
#define BOTTOM     "/d/Genesis/new/start/goblin/town/river_tunnel4"

int bucket_position = 0; /* 0 is down, 1 is up */

/* Prototypes */
public string activate_bucket(string caller, string dir);
public int query_bucket_position();

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are inside a large bucket");

    set_long("You are inside a large bucket.\n" +
    "It sways slightly under your weight.\n");

    add_item(({"panel", "control panel", "lever"}),
    "The control panel is carved completely from stone. It has one " +
    "lever which you may be able to reach.\n");

    add_cmd_item("lever", "pull", "@@activate_bucket");

    add_exit("river_tunnel4", "exit");
}

public string
activate_bucket(string caller, string dir)
{
    /* remove_exit("exit"); */
    tell_room(caller, QCNAME(this_player()) + " pulls the lever, " +
    "causing the bucket's rope and pulley system to lurch into action.\n");
    if (bucket_position == 1)
    {
        bucket_position = 0;
    }
    else
    {
        bucket_position = 1;
    }
    /* add_exit("well", "exit"); */
    return "";
}

public int
query_bucket_position()
{
    return bucket_position;
}
/*
 * Base room for indoor rooms
 * -- Finwe, May 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";

// Added so you can add extra descriptions to the room.
static string extraline = "This is a tunnel description.";

//  Prototypes
void  set_extraline(string str) 
{ 
    extraline = str; 
}

void create_indoor_room() 
{
}

function vbfc_extra;


public string
long_desc()
{
    string  desc = CAP(query_short()) + ". ";

    if (strlen(extraline))
        desc += extraline;

    if (functionp(vbfc_extra))
        desc += vbfc_extra();

    return (desc + "\n");
}


void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside a dark tunnel");
// use set_extraline() for long descriptions so everything is formatted properly.
    set_extraline("This is the long description of a dark tunnel.");

    set_long(long_desc);
    set_room_tell_time(120 + random(60));

    create_indoor_room();
}

/*
 * Function name : enter_inv
 * Description   : sman enter_inv for more details.  It's masked here
 *                 for room_tell support.
 */
public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}

/*
 * Function name : reset_faerun_room
 * Description   : If you want to reset a room in the Faerun use this function.
 */
void
reset_faerun_room() 
{

}

/*
 * Function name : reset_room
 * Description   : Takes care of reseting certain things used in Faerun.
 */
void
reset_room()
{
    reset_faerun_room();
}

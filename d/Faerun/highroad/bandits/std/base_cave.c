/*
 * Base room for caves of Sword mountain, leading into Underdark
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
void   set_extraline(string str) { extraline = str; }
function vbfc_extra;

void
create_cave()
{
}

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
    add_prop(ROOM_S_MAP_FILE, "bandit_camp.txt");

    set_short("Inside a dirty cave");    
//    set_long(long_desc);
    set_room_tell_time(120 + random(60));
    add_room_tell("Bandits hustle past you.");
    add_room_tell("From somewhere you hear: Travellers heading down the road!");
    add_room_tell("A group of bandits push past you.");
    add_room_tell("Some bandits run out of the hideout.");
    add_room_tell("A group of bandits sneak by.");

    add_item(({"walls", "wall", "tunnel"}),
        "The walls are irregular shaped and looks rough. They arch overhead into a rough looking ceiling.\n");
    add_item(({"floor", "ground"}),
        "The ground is rough looking and dirty. There are piles garbage lying around in the corners.\n");
    add_item(({"ceiling"}),
        "The ceiling is rugged looking and naturally formed. It is just a little bit above your head.\n");
    add_item(({"rock"}),
        "The rock is dark and likely granite. It is very hard and looks " +
        "impervious.\n");
    add_item(({"air"}),
        "The air is fresh, dirty smelling. A cold breeze drifts through the cave.\n");
    add_item(({"garbage", "piles", "piles of garbage"}),
        "it is useless stuff dropped by the bandits who live here.\n");
    
    create_cave();
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

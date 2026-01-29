inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_door()
{
    ::create_door();
    set_door_id("Emyn-Arnen_House2_Trapdoor_Up");
    set_pass_command(({"d","down"}));
    set_door_name(({"trap door","hatch","board","plank","door",
        "wooden board", "wooden plank", "trapdoor", }));
    set_door_desc(VBFC_ME("long_desc"));
    set_open_command(({"open", "lift"}));
    set_closed_desc("");
    set_open_desc("There is an open trap door leading down.\n");
    set_other_room(ITH_DIR + "emyn-arnen/cellar2");
    set_open(0);         /* 1 if open, 0 if closed */
    enable_reset();

    set_str(30);
}

int
open_door(string arg)
{
    if(!arg || (arg != "trap door" && arg != "hatch" && arg != "door" && 
              arg != "trapdoor" && arg != "board" && arg != "plank" &&
              arg != "wooden board" && arg != "wooden plank"))
    return 0;

    set_closed_desc("There is a closed trap door leading down.\n");
    ENV(TO)->change_my_desc(query_closed_desc(),TO);
    ::open_door(arg);
    return 1;
}

string
long_desc()
{
    if(query_open())
        return BSN(
            "A simple wooden board on iron hinges that is leaning against " +
            "a wall next to a hole in the floor. Looking into the hole you " +
            "can see a rickety ladder leading down. ");
    else
        return BSN(
            "A simple wooden board on iron hinges that probably covers " +
            "a hole in the floor. The board looks rather heavy. ");
}

void
reset_door()
{
    set_closed_desc("");
}


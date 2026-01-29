/*
 * Common board room of Green Oaks
 * By Finwe, march 2005
 */
 
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
void load_board();

 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Common Board Room of the " + ACADEMY_NAME);
    set_long("This is " + short() + ". It is where important announcements " +
        "are made by immortals and are available to everyone. The room " +
        "is empty except for a bulletin board set in the center of the room.\n");

    set_add_ceiling_flat("The ceiling is white and undecorated."); 
    add_item(({"center of the room", "center", "middle of the room", 
            "center of room"}),
        "It is the middle of the room where a large board is placed.\n");

    add_prop(ROOM_I_NO_STEAL, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    load_board();
    reset_room();
    
    add_exit(GO_DIR + "ac_boardrm", "east");
}

void reset_room() 
{ 
}

void
load_board()
{
    object bb;

    seteuid(getuid(this_object()));
    bb = clone_object("/d/Genesis/obj/board");
    bb->add_prop(OBJ_M_NO_GET, "It's firmly attached to the floor.\n");
    bb->move(this_object());
}

void
init()
{
    add_action("back", "back");
    add_action("back", "return");
    add_action("back", "go");

    ::init();
}

int
back(string str)
{
    if (query_verb() == "go" && str != "back")
        return 0;

    this_player()->move_living("back",
                        this_player()->query_prop(LIVE_O_LAST_ROOM));
    return 1;
}

/*
 * Function: enter_inv
 * Description: block non-interactives from entering.
 */
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && !interactive(ob))
        ob->move(from);
}

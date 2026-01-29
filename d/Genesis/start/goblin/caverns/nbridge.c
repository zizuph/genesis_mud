
/*
 * Written by Quis for the Goblin Start Area 920526
 */

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include "../goblins.h"

#define BRIDGE GOBLIN_CAVERN_DIR + "sbridge"

object guard1, guard2;

void reset_room();

create_room()
{
    ::create_room();
    change_prop(ROOM_I_LIGHT,1);
    change_prop(ROOM_I_INSIDE,1);

    set_short("North of bridge spanning chasm.");

    set_long("@@long_desc");

    add_item( ({"dropbridge","bridge"}), "@@bridge_desc");

    add_item( ({"passage"}), BSN( "The passage here runs north to south. " +
        "There seems to be a chasm splitting the passage quite abruptly."));

    add_item( ({"chasm"}), BSN("You cannot see the bottom of the chasm. " +
        "It is about twenty meters wide. " +
        "You notice a patch of blue sky far above you."));

    add_exit(GOBLIN_CAVERN_DIR + "sbridge","south","@@bridgeblock",0);
    add_exit(GOBLIN_CAVERN_DIR + "tunnel3","north",0,0);

    reset_room();
}
 
void
reset_room()
{
    if (!guard1 || !present(guard1, this_object())) {
        guard1 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard1->move_living("south", this_object());
    }
 
    if (!guard2 || !present(guard2, this_object())) {
        guard2 = clone_object(GOBLIN_NPC_DIR + "guard");
        guard2->move_living("south", this_object());
    }
 
}

int
bridgeblock()
{
    seteuid(getuid(this_object()));
    if (call_other(BRIDGE,"query_bridge")) {
        write(BSN("You walk carefully over the rickety bridge. " + 
            "You feel relieved when you reach the other side. "));
        return 0;
    }

    write(BSN("You decide your levitation skills aren't up to this."));
    return 1;
}

string
bridge_desc()
{
    return BSNN("The bridge is like a drawbridge, except: The " +
        "bridge falls down into the chasm instead of being raised up on the " +
        "other side. This is clearly intentional, and to annoy the goblins " +
        "while crossing the bridge could be deadly.");
}

string
long_desc()
{
    string str;

    str = "The narrow passage you have been following opens abruptly onto a " +
        "huge chasm.  Opposite this tunnel, you can see a corresponding " +
        "passage into the rock.  Far below, you can hear the gentle workings " +
        "of a subterranean river. ";

    seteuid(getuid(this_object()));
    if(call_other(BRIDGE,"query_bridge"))
        str += "There is a large bridge spanning the rift. ";
    else
        str += "You see a bridge dangling before your feet. ";

  return BSNN(str);
}
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "../goblins.h"

static int bridge;

void raise_bridge();

void
reset_room()
{
    bridge = 0;
}

void
create_room()
{
    ::create_room();
    change_prop(ROOM_I_LIGHT,1);
    change_prop(ROOM_I_INSIDE,1);

    set_short("South of bridge spanning chasm.");

    set_long("@@long_desc");

    add_item( ({"dropbridge","bridge"}), "@@bridge_desc");

    add_item( ({"passage"}), BSN( "The passage here runs north to south. " +
        "There seems to be a chasm splitting the passage quite abruptly."));

    add_item( ({"chasm"}), BSN("You cannot see the bottom of the chasm. " +
            "It is about twenty meters wide. " +
            "You notice a patch of blue sky far above you."));

    add_exit(GOBLIN_CAVERN_DIR + "nbridge","north","@@bridgeblock",0);
    add_exit(GOBLIN_CAVERN_DIR + "tunnel2","south",0,0);

    reset_room();
}

int
bridgeblock()
{
    if (bridge) {
        write(BSN("You walk carefully over the rickety bridge. " + 
              "You feel relieved when you reach the other side. "));
        return 0;
    }
    else {
        write(BSN("You decide your levitation skills aren't up to this."));
        return 1;
    }
}

string
bridge_desc()
{
    string str;

    str = BSNN("The bridge is like a drawbridge, except: The " +
        "bridge falls down into the chasm instead of being raised up on the " +
        "other side. This is clearly intentional, and to annoy the goblins " +
        "while crossing the bridge could be deadly.");

    return str;
}

string
long_desc()
{
  string str;
  str = "The narrow passage you have been following opens abruptly onto a " +
    "huge chasm.  Opposite this tunnel, you can see a corresponding " +
    "passage into the rock.  Far below, you can hear the gentle workings " +
    "of a subterranean river. ";

    if(bridge)
      str += "There is a large bridge spanning the rift. ";
    else
      str += "On the far side of the chasm, you see a bridge dangling from "
          +  "the opposite passageway. ";

  return BSNN(str);
}

void
raise_bridge()
{
  bridge = 1;
}

void
lower_bridge()
{
  bridge = 0;
}

int
query_bridge()
{
  return bridge;
}
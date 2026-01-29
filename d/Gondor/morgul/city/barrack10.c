#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *orcs = allocate(2 + random(5));

public void
create_morgul_room()
{
    set_extraline("This seems to be the abode of a large pack of orcs. " +
    "The floor is covered by rags and broken furniture. The upper " +
    "floor of the building and parts of the roof have collapsed. " +
    "All the walls that once must have divided this floor into several " +
    "rooms have apparently been pulled down. The only exit is to the " +
    "east, leading into a dark and narrow street.");
  add_item(({"ceiling","stairs","first floor","upper floor","roof"}), BSN(
    "The upper floor of this building and parts of the roof have " +
    "collapsed, but if the present inhabitants don't mind, why should " +
    "you? There is no trace of any stairs or a ladder leading up " +
    "so you probably cannot reach what is left of the upper parts of " +
    "this house. "));
  add_item(({"floor","rags","furniture"}), BSN(
    "The floor is covered by parts of old clothing and the sad remains " +
    "of once valuable tapestries. In the corners you can see " +
    "the wrecks of wooden chairs and tables, carved by a true artisan " +
    "long ago, and now broken beyond repair. "));
  add_item(({"street"}), BSN(
    "Looking out through the opening in the east wall, you can make out " +
    "a dark and narrow street, running north at the foot of the city " +
    "walls. "));
  add_item(({"hole", "exit", "door"}), BSN(
    "Where once was a door, all that is left now is a dark gaping hole " +
    "leading out of the building onto the street. "));
  add_item(({"window","windows","boards"}), BSN(
    "Wooden boards have been nailed across the windows from outside, " +
    "preventing light of day from entering into the room. "));
  set_road(5);
  set_side("southeast");

  add_exit(MORGUL_DIR + "city/barrstr1","east","@@check_exit",1);
    reset_room();
}

public object
clone_orc(object npc, string npc_file)
{
    int     rs = random(50);

    if (objectp(npc))
        return npc;
 
    npc = clone_object(npc_file);
    npc->default_config_npc(25 + rs);
    npc->set_base_stat(SS_DIS, 45 + rs);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

public void
reset_room()
{
    set_alarm(20.0 + 20.0 * rnd(), 0.0, &clone_npcs(orcs, MORGUL_DIR + "npc/ithil_soldier", 60.0));
}


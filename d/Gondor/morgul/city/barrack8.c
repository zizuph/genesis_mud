#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *orcs = allocate(2 + random(5)),
               uruk;

public void
create_morgul_room()
{
   set_extraline("This seems to be the abode of a large pack of orcs. " +
    "The floor is covered by rags and broken furniture. A flight of " +
    "stairs leads to the upper floor. The only exit is to the " +
    "east, leading into a dark and narrow street.");
  add_item(({"stairs","stair","flight","flight of stairs"}), BSN(
    "A broad flight of stairs leads up to the first floor of the " +
    "building. The stairs are made of black stones, which once probably " +
    "were beautifully polished, but now they are dirty and dull. "));
  add_item(({"floor","rags","furniture"}), BSN(
    "The floor is covered by parts of old clothing and the sad remains " +
    "of once valuable carpets and gobelins. In the corners you can see " +
    "the wrecks of wooden chairs and tables, carved by a true artisan " +
    "long ago, and now broken beyond repair. "));
  add_item(({"hole", "exit", "door"}), BSN(
    "Where once was a door, all that is left now is a dark gaping hole " +
    "leading out of the building onto the street. "));
  add_item(({"window","windows","boards"}), BSN(
    "Wooden boards have been nailed across the windows from outside, " +
    "preventing light of day from entering into the room. "));
  add_item(({"street"}), BSN(
    "Looking out through the opening in the east wall, you can make out " +
    "a dark and narrow street, running north and south at the foot of the " +
    "city walls. "));
  set_road(5);
  set_side("east");

  add_exit(MORGUL_DIR + "city/barrstr3","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/b8up","up","@@stairs",1);

  reset_room();
}

public object
clone_npc(object npc, string npc_file)
{
    int     b = 35,
            rs = random(41);

    if (objectp(npc))
        return npc;

    npc = clone_object(npc_file);
    npc->default_config_npc(b + rs);
    npc->set_base_stat(SS_DIS, b + 10 + rs);
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

public void
reset_room()
{
    set_alarm(30.0 + rnd() * 60.0, 0.0, &clone_npcs(orcs, MORGUL_DIR + "npc/ithil_orc", 60.0));

    if (!objectp(uruk))
        uruk = ::clone_npc(uruk, MORGUL_DIR + "npc/ithil_uruk");
}


/*
 * /d/Gondor/lebennin/road/hut1.c
 *
 * The humble abode of Hathaldir.
 *
 * Modification log:
 * 02-aug-1997, Olorin: General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Ranger;

public void
reset_room()
{
   // Ranger = clone_npc(Ranger, RANGER_DIR + "npc/hathaldir");
   Ranger = clone_npc(Ranger, "/d/Gondor/guilds/rangers/npc/hathaldir");
}

public void
create_gondor()
{
    set_short("inside a small hut");
    set_long(BSN("The inside of the hut seems just as small as the outside "+
    "indicated. There is not much here except a bed, a chair and a table. "+
    "There is also a faint odour of herbs in here, giving a certain freshness "+
    "to the air. An open door leads out, and a small window lets some light "+
    "in above the bed. The walls are old and rickety, while the floor looks "+
    "solid as stone."));
    add_prop(ROOM_I_INSIDE, 1);
    add_item("bed","It has been slept in quite recently.\n");
    add_item("chair","Home-made, of wood. Quite rickety and old, actually.\n");
    add_item(({"floor","ground"}), BSN(
         "The floor, while solid is uneven in places.  There seems to be a "+
         "trapdoor near the corner."));
    add_item(({"trapdoor","trap door"}), BSN(
         "This trapdoor leads presumeably to a cellar of sorts. You feel "+
         "unsure as to whether you should go down there."));
    add_item("table","The table is bare, made of wood, and as rickety as the chair.\n");
    add_item("window","It is just a plate of glass fit into the wall, impossible\n"+
      "to open.\n");
    add_item("door","The door is open, letting light and fresh air into the hut.\n");
    add_exit(LEB_DIR + "road/fieldr8",   "out",  0, 3);
    add_exit(LEB_DIR + "road/hutcellar", "down", 0, 4);

    reset_room();
}


#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    reset_room();
static object *humans = allocate(3 + random(3));

public void
create_morgul_room()
{
    set_extraline("This must be the house of a very senior human officer in the " +
    "Morgul army. The walls of this large entrance hall on the ground floor " +
    "of the building are covered with trophies. " +
    "Stairs are leading up to the first floor of the house.");
  add_item(({"stairs","stair"}), BSN(
    "Stairs are leading up to the first floor of the building. They are made " +
    "from stone slabs, and two steps have obviously been replaced recently. "));
  add_item(({"step", "steps"}), BSN(
    "The original steps are made from finely polished stone slabs, which " +
    "probably were hewn from a quarry in the Ephel Duath. The two steps which " +
    "were used to repair the stairs are made from the same material, but clearly " +
    "by a less skilled artisan."));
  add_item(({"furniture"}), BSN(
    "There is hardly any furniture here. All you can see is a thick carpet lying " +
    "on the floor and many trophies hanging on the walls. "));
  add_item(({"carpet","rug","floor","ground"}), BSN(
    "A thick carpet covers the stone floor in the centre of the hall. Once it must " +
    "have been valuable, but too many boots have mistreated it, so you can only imagine " +
    "its former beauty."));
  add_item(({"trophy","trophies","walls","wall"}), BSN(
    "The walls are covered with many different trophies. They give evidence of the many " +
    "campaigns in which the owner of the house served. You can make out torn banners " +
    "of beaten armies, weapons and armour of fallen victims, cloven shields and broken " +
    "swords. "));
  add_item(({"window","windows"}), BSN(
    "On this floor, there are no windows. "));
  set_road(9);
  set_short_desc("in a large hall in a house in Minas Morgul");
  set_side("north");

  add_exit(MORGUL_DIR + "city/rooms/b4up","up","@@stairs",1);

  clone_object(MORGUL_DIR+"city/doors/b4doorin")->move(TO);

  add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

public object
clone_npc(object npc, string npc_file)
{
    if (objectp(npc))
        return npc;
 
    npc = clone_object(npc_file);
    npc->set_name("guard");
    npc->set_short("strong guard");
    npc->set_pshort("strong guards");
    npc->remove_adj(npc->query_adjs()[0]);
    npc->set_long(npc->query_long() + "He is here on guard duty.\n");
    npc->arm_me();
    npc->move_living("down", TO);

    return npc;
}

public void
reset_room()
{
    set_alarm(20.0 + rnd() * 20.0, 0.0, &clone_npcs(humans, MORGUL_DIR + "npc/mercenary", 60.0));
}


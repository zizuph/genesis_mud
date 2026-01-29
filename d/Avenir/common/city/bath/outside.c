#pragma strict_types
/*
 * ~/outside.c
 *
 * Entrance to Melchior's Bath.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Lilith, Jun 2002: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../entry/entry.h" 
inherit ENTRY_ROOM;

static void
create_entry_room(void)
{
    set_short("just outside Melchoir's bath house");
    set_long("A blue slate path starts here and leads west, "+
      "toward the First Gate of the Forbidden City. Stone "+
      "steps carved from the craggy outcropping lead down "+
      "into the Bath. Overhead, the dome rises, its glass "+
      "clouded with vapour. The air is warm and moist, and "+
      "redolent with the scent of herbs.\n");

    add_item(({"dome", "glass dome"}), 
      "The glass dome encompasses the bath house. The only way "+
      "into it is down the stairs.\n");

    add_outside();
    add_bath();
    add_urns();
    add_walls();

    add_exit(BATH + "room/hall", "down", 0);

    add_npc(MON + "bath_overseer", 1, &->equip_me());
}

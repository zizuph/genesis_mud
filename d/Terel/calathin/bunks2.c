/*
 * Barracks bunks.
 * Coded by Shinto 071900
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

query_object_list()
{
    return ({CALATHIN_DIR + "npc/std_guard",
                 CALATHIN_DIR + "npc/std_guard",
                 CALATHIN_DIR + "npc/std_guard"});

}

public void
create_room()
{
    set_short("Barracks of the Calathin Guard");
    set_long("A bunk room of the Calathin Guard. Ten beds line the walls, each "+
                   "with a small chest at the foot of the bed. The room itself is "+
                   "fairly bare aside from the beds.\n");
    add_item(({"window", "windows"}), "The windows view the road outside.\n");
    add_item("counter", "The counter is made of wood.\n");
    add_item(({"bed","beds"}), "Simples beds for the guards to sleep on.\n");
    reset_room();

}

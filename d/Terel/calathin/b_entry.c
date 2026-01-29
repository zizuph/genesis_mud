/*
 * Barracks entry.
 * Coded by Shinto 071900
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

query_object_list()
{
    return (({CALATHIN_DIR + "npc/std_guard"}));

}

public void
create_room()
{
    set_short("Barracks of the Calathin Guard");
    set_long("You've entered the barracks of the town guard. This is the main "+
                   "entry hall, a large room with a counter towards the back. "+
                   "Against the wall stands a weapon rack holding various swords "+
                   "and equipment of the guard. \n");
    add_item(({"window", "windows"}), "The windows view the road outside.\n");
    add_item("counter", "The counter is made of wood.\n");
    add_item("rack","The rack is locked and holds various types of weapons.\n");
    reset_room();

}

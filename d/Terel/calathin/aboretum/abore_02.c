/*
 * abore_02.c
 *
 * Aboretum room
 */

#include "/d/Terel/include/Terel.h"
inherit CALATHIN_DIR + "aboretum/aboretum_base";
#include <ss_types.h>
#include <stdproperties.h>

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() +
              "A wooden wall surrounds the aboretum, with a gate leading "+
              "north to the rest of town. A path leads to the south.\n");
    add_item(({"wall", "wooden wall"}), 
              "The wooden wall is only about six feet high, from here it "+
              "spans out to the east and west.\n");

    add_exit("/d/Terel/common/town/garden/copse2",   "north",0);
    add_exit(CALATHIN_DIR + "aboretum/abore_06",   "south",0);
    add_exit(CALATHIN_DIR + "aboretum/abore_03",   "east",0);
    add_exit(CALATHIN_DIR + "aboretum/abore_01",   "west",0);
    reset_room();
}


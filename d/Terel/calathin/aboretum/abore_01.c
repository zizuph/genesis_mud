/*
 * abore_01.c
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
              "north to the rest of town further east. To the south you can "+
              "make out a small lake filled with mist.\n");
    add_wall();
    add_lake();
    add_exit(CALATHIN_DIR + "aboretum/abore_05",   "south",0);
    add_exit(CALATHIN_DIR + "aboretum/abore_02",   "east",0);
    add_exit(CALATHIN_DIR + "aboretum/abore_04",   "southwest",0);
    reset_room();
}


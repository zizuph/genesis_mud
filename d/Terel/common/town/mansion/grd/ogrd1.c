/* oldgarden1.c */
/* janus 920929 Modified by Mortricia 940522 */

inherit "/d/Terel/common/town/mansion/grd/ogrd_std_room";
#include "/d/Terel/common/terel_defs.h"

void
create_ogrd_room()
{
    set_short("Crossroad");
    set_long("You are in a crossroad in a old decrepit garden" +
        ". The air is cold, humid, and permeated by a smell of rotting "+
        "plants and flesh. The ground is covered by a thin layer of frost "+
        "and entwined vines. "+
        "The garden of despairs appears to continue to the north, east, and "+
        "west. To the south you can see an entrance to the old mansion. "+
        " Thorn bushes and small deformed trees have grown totally"+
        " out of control, almost blocking the paths.\n");
    add_exit(MANSION + "grd/ogrd11", "north","@@gogo",3);
    add_exit(MANSION + "grd/ent", "south","@@gogo",3);
    add_exit(MANSION + "grd/ogrd3", "east","@@gogo",3);
    add_exit(MANSION + "grd/ogrd2", "west","@@gogo",3);
}

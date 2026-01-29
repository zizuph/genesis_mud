
/* sw_path_2.c
 * Town of Gamwich
 * Southwestern Path
 * Room 2 (midway down the path)
 * Created 27 February 1995 by Farlong
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"

void
create_room()
{
    area="in";
    areaname="Gamwich";
    land="the West Farthing of the Shire";
    areatype=11;
    areadesc="path";
    grass="wild";

    extraline="The path continues toward the town square "+
        "to the northeast, and toward a small smial in the "+
        "opposite direction.";

    add_item(({"square","town square"}),"The town square is a "+
        "large, well-kept space at the center of "+
        "Gamwich.  It lies off to the northeast.\n");
    add_item(({"path","paths","road","roads","dirt path",
        "dirt paths","dirt road","dirt roads"}),
        "A dirt path heads out of each of the four corners of "+
        "This dirt path is quite well-tended by the local "+
        "hobbits.  It heads from northeast to southwest.\n");
    add_item(({"smial","hobbit-hole","hobbit hole","hole"}),
        "The smial lies off to the southwest.  From here, all "+
        "you can see is a round door recessed in the front of a "+
        "moderately-sized hill.\n");

    add_exit(GAMWICH_DIR+"sw_path_3","southwest");
    add_exit(GAMWICH_DIR+"sw_path_1","northeast");

    make_the_room();

}


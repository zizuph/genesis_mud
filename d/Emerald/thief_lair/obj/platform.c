/* A platform to allow the bandits to move heavy loads up and down the cliff
   face without destroying the rope ladder. Could also be used by clever
   players.
   Code by Shiva, modified by Casimir, 1999.
*/

inherit "/std/container";

#include <stdproperties.h>

void
create_container()
{
    set_name("platform");
    add_name("thief_lair_platform");
    set_adj("wooden");

    set_long("A wooden platform attached to the cliff face by means of " +
	     "two metal rails. There is a rope and pulley system affixed "+
	     "to the underside of the platform.\n");

    add_prop(OBJ_I_NO_GET, "It is securely fastened and too heavy to be "+
	     "easily carried.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 30000);
    add_prop(CONT_I_MAX_WEIGHT, 220000);
    add_prop(CONT_I_MAX_VOLUME, 200000);
}







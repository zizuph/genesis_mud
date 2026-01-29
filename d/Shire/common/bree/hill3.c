#include "defs.h"

inherit STAND_LIB + "rom";

create_rom()
{
    set_short("Road on the Bree-Hill.\n");
    set_long(
	    "You have reached the top of the Bree-Hill and "+
	    "now you can really see all those beautiful gardens "+
	    "that the Hobbits have here. The grass is green "+
	    "everywhere and it looks like a well kept area here. "+
	    "East of here many houses can be seen, both Hobbit "+
	    "and human houses. The road continues east where "+
	    "the living area of Bree is and west towards the intersection "+
	    "with the Great Eastroad.\n");

add_exit(BREE_DIR + "hill2", "west", 0);
add_exit(BREE_DIR + "hill4", "southeast", 0);

    add_item(({"houses","house"}),
	    "It is not difficult to make out what houses the Hobbits have. "+
	    "They are holes in the ground and usually dirty outside, but "+
	    "they are very nice inside when you get to look there. The houses "+
	    "the humanish people live in are sometimes built of wood and sometimes "+
	    "made of rocks. They are much larger in size then Hobbits houses.\n");

    add_item(({"garden","gardens"}),
	    "The gardens of the Hobbits are well kept and contain many "+
	    "different plants, sometimes the Hobbits plant herbs of different "+
	    "sorts here too.\n");

    add_item("grass","The grass looks just like everywhere else in Middle Earth.\n");
}

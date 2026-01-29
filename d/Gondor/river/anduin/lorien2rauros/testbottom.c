#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_underwater";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/underwater.h"

/* prototypes */
public void	create_anduin_underwater();

/*
 * Function name:	create_anduin_underwater
 * Description	:	create the room
 */
public void
create_anduin_underwater()
{
    set_short("underwater");
    set_long("Underwater.\n"+
	"The dark waters are still.\n");

    set_watertype("pool");
    set_waterrefs( ({ "pool", "test pool" }) );
    set_currentstr(0);	/* strong */

    add_exit("test", "up");
} /* create_anduin_underwater */

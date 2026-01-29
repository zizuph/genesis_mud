/*
 * /d/Gondor/common/doc/examples/room_tod.c
 *
 * A sample room to show the use of ~gondor/common/lib/tod_descs
 * for time of day effects.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";

#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_gondor();

/*
 * Function name:	create_gondor
 * Description	:	set up the forest room
 */
public void
create_gondor()
{
    set_short("deep in a forest");
    /* pass the room long with NO ending newline to set_tod_long() */
    set_tod_long("Great shaggy firs crowd close on all sides, "+
	"and a carpet of fallen needles deadens any sound.");
    set_tod_landname("the Firien Wood");
    set_tod_landtype("forest");

    /* use tod_descs() to provide room and sky-item descriptions */
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }),
	        tod_descs );

    /* this is optional.  if set, the capitalized short description
     * (plus a period and space) will be prepended to the room long.
     */
    set_tod_prependshort(1);

    /* here you would do items, exits, etc ... */
} /* create_gondor */

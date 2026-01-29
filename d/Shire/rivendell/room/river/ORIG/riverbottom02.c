/*
 * /d/Shire/rivendell/room/river/riverbottom02.c
 *
 */

#pragma strict_types

inherit "/d/Shire/rivendell/room/river/riverbottom";

#include <stdproperties.h>
#include "local.h"

public void	create_riverbottom();

/*
 * Function name:	create_riverbottom
 * Description	:	set up the riverbottom
 */
public void
create_riverbottom()
{
    /* XXX short & long descs */

    set_upstreamdir("northeast");
    set_downstreamdir("southwest");

    add_exit("river02", "up");

    /* they will never succeed in taking these exits, but
     * having them makes the messages look right
     */
    add_exit("riverbottom01", "northeast", block_exit, 10);
    add_exit("riverbottom03", "southwest", block_exit, 10);
} /* create_riverbottom */

/**********************************************************************
 * - pie01106.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../defs.h"

inherit PIER_ROOM;

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"

object bird1, bird2;

public int *
query_local_coords()
{
    return ({11, 4});
}

public void
reset_pier()
{
    if (!bird1)
    {
        bird1 = clone_object(COM_WILDLIFE + "gull");
        bird1->set_restrain_path(ROOM);
        bird1->move(this_object(), 1);        
    }
    if (!bird2)
    {
        bird2 = clone_object(COM_WILDLIFE + "gull");
        bird2->set_restrain_path(ROOM);
        bird2->move(this_object(), 1);
    }
}

public void
create_pier()
{
 
   add_exit("pie1105", "west");
   

    reset_pier();
}

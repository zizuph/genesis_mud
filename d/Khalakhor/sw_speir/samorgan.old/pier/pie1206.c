/**********************************************************************
 * - pie1206.c                                                      - *
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
void add_stuff();

object sign;
object bird;

public int *
query_local_coords()
{
    return ({12, 6});
}

public void
create_pier()
{
 
   add_exit("pie1205", "west");
       // ensure other pier loaded, ship on way
    ("/d/Khalakhor/inisi/galaith/pier/pier1")->get_this_object();
    add_stuff();
}

public void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!sign)
    {
        sign = clone_object("/d/Khalakhor/sw_speir/samorgan/obj/egsign");
        sign->move(this_object());
    }
}

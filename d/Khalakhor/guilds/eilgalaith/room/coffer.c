/**********************************************************************
 * - coffer.c                                                       - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

inherit "/std/container";
#include <stdproperties.h>
#include "../guild.h"

void
create_container()
{
	seteuid(getuid(TO));
	set_name("coffer");
        add_name("eilgalaith:coffer");
        set_short("crystal coffer");
        add_adj("crystal");
        set_long("This is a fairly large crystal coffer. It has "+
        "silver edging that helps protect putting and taking "+
        "items in and out of it. The light dances beautifully "+
        "along the surface even when it is full.\n");
        add_item(({"silver", "silver edging", "edging"}),
        "The silver edging is shiny and helps to protect the "+
        "edge of the coffer.\n");

        add_prop(CONT_I_CLOSED,0);
        add_prop(CONT_I_MAX_WEIGHT, 500000);
        add_prop(CONT_I_MAX_VOLUME, 500000);
        add_prop(CONT_I_WEIGHT, 100000);
        add_prop(CONT_I_VOLUME, 100000);
        add_prop(OBJ_I_VALUE, 8549);
        add_prop(CONT_I_RIGID, 1);
        add_prop(OBJ_M_NO_GET, "It is held firmly in place by a magical "+
        "force.\n");
}

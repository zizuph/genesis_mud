/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("");

    add_exit(MBLACK_DIR + "", "");
    add_exit(MBLACK_DIR + "", "");
}

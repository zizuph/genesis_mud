
 /* Digit 03 FEB 95 */

inherit "/std/room";
inherit "/d/Calia/walkers/specials/water_walk";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER
#include "salt.h"

void
create_room()
{
    set_short("In a small chamber");
    set_long("You are standing on the banks of a boiling hot "+
        "river which lies to your west.  To the north you see "+
        "a small chamber carved out of these basalt walls.  The "+
        "walls here have traces of salt deposits, most likely "+
        "from the river.  Steam filters in from the west.\n");

#include "banks.h"

    add_item("chamber","The chamber to the north seems to be "+
        "carved by a skilled craftsman as most of the roughness "+
        "seen throughout the rest of this cavern is gone.\n");

    add_exit(CAVE+"room51","west","@@water_walk");
    add_exit(CAVE+"room53","north");

}

void
init()
{
    ::init();
    add_action("do_scrape","scrape");
}

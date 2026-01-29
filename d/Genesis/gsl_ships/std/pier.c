/*
 * Standard pier
 * TAPAKAH, 2007
 */

#include "../ships.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

inherit STDSHORE;
inherit LIBPIER;

public void
create_pier()
{
}

public void
create_shore()
{
    set_short("A shore room with a pier.");
    set_long("This a shore room that also has a pier.\n");
    add_item(({ "sea", "water" }), "The water splashes against the pier.\n");
    add_item(({ "pier" }), "The pier is where the ships arrive to.\n");
    
    create_pier();
    initialize_pier();
}

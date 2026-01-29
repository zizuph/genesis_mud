/*
 * Modifed to make it use ther default Gondor gems.
 * Changed from ruby to onyx.
 *
 * Olorin, 8-Dec-1996
 */
inherit "/d/Gondor/common/obj/gems";

#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_gems()
{
    if (IS_CLONE)
	log_file("errors", " >>>>> " + file_name(previous_object()) +
            " cloned " + file_name(TO) + "(" +
            file_name(previous_object(-2)) + ", " +
            previous_object(-2)->query_name() + ").\n");  
    add_name(({"Xeros_Ruby"}));
    set_heap_size(1);
    set_gem_type("onyx");
}


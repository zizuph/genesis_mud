/*
 * See /d/Shire/std/clone_handler.c for instructions on how to
 * set this up
 */

inherit "/d/Shire/std/clone_handler";

#include "/d/Gondor/defs.h"

void
create_clone_handler()
{
    set_default_area("/d/Gondor/tharbad/trail/");

    add_clone("/d/Gondor/ithilien/poros/npcs/corsair", 1, 13);

    set_clone_handler_id("Poros Camp Clone Handler");
}

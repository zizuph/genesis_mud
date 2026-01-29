/*
 * cadu_scroll.c
 *
 * Used in nyreese/cadu_q5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 this is the scroll given by the statues with the
   `spell of transportation`
*/

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "defs.h"
#include <macros.h>

void destroyme();

void
create_object()
{
    if (!IS_CLONE)
        return;

    set_short("magic scroll");
    set_long("This is the spell of transportation : \n" +
             "Whenever you like to go to the castle: \n" +
             "Type 'move me mighty statues' at the statues, " +
             "and you will be transported to your destination.\n");
    set_adj("magic");
    set_name("scroll");
    set_alarm(120.0, 0.0, destroyme);
}

void
init()
{
    ::init();
    add_action("read", "read");
}

int
read(string s)
{
    NF("Read what?");
    if (s != "scroll")
        return 0;

    TP->catch_msg(long());
    return 1;
}

void
destroyme()
{
    TP->catch_msg("The scroll suddenly turns into gas.\n");
    remove_object();
}

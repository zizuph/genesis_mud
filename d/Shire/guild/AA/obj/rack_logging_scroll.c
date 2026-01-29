/*  rack_log_book.c
 *
 *  A rack lok
 *
 *  Created by Znagsnuf.
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  06/05-2017                Started making it.                       Znagsnuf
 */

inherit "/std/scroll";

#include "../guild.h"
#include <stdproperties.h>

int burn_scroll();

void
create_scroll()
{
    set_name("scroll");
    set_adj("wringly");
    set_short("wringly scroll");
    set_long("A wrinkly scroll.\n");
    set_file("/d/Shire/guild/AA/log/new_rack_log.backup");
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 0);
    set_alarm(10.0, 0.0, &burn_scroll());
}

/*
 * Function name: init
 * Description  : Initialize commandverbs.
 */
public void
init()
{
    ::init();
    add_action(read_scroll, "read");
}

int
burn_scroll()
{
    tell_room(ENV(this_object()), "All that is left from the scroll, "
                                       + "is grey ashes.\n", this_object());
    remove_object();
}
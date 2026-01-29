/*
 * Copyright (c) 1991 Chalmers Computer Society
 *
 * This code may not be copied or used without the written permission
 * from Chalmers Computer Society.
 */

#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "/config/sys/local.h"

create_scroll()
{
    seteuid(getuid(this_object()));
    add_prop(OBJ_I_NO_DROP, "Hmm... no need to risk being zapped.\n");
    set_name("scroll");
    set_short("important-looking scroll");
    set_long("The scroll is held rolled up with a red band tied " +
	"around it. On the band the text 'IMPORTANT RULES' is written in bold " +
	"letters.\n");
    set_autoload();
    set_file("/d/Genesis/obj/tester_scroll");
}

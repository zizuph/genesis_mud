#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h"
#include "/d/Shire/guild/sindar_racial/emotes/do_help.c"

inherit "/cmd/std/command_driver";

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());
    
	return ([
      "help"            : "do_help"
    ]);

}

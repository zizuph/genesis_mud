#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../defs.h"

public mapping
query_ability_map(void)
{
    return ([
	"fling": SPECIAL + "fling",
   "ufling": SPECIAL + "fling",
	"slash": SPECIAL + "slash",
   "uslash": SPECIAL + "slash",
	 "sway": SPECIAL + "sway",
    ]);
}

/* Commands */
public mapping
query_cmdlist(void)
{
    return ([
     /* Special attack 'Fling' */
         "fling" : "do_ability",
        "ufling" : "do_ability",
     /* Special attack 'Slash' */
         "slash" : "do_ability",
        "uslash" : "do_ability",
     /* Special ability 'Sway' */
          "sway" : "do_ability",    ]);
}

/* Id and autoload */
public nomask string
get_soul_id(void)	{ return "Union_Test"; }

/* It is a real command soul */
public nomask int
query_cmd_soul(void)	{ return 1; }

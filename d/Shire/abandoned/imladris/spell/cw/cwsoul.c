inherit "/cmd/std/soul_cmd";

#include "/secure/std.h"
#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
   seteuid(getuid());
   return "concussions way soul";
}

/* This soul is auto_loading */
string
query_auto_load()
{
   seteuid(getuid());
   return MASTER_OB(TO);
}

void
using_soul(object live)
{
    seteuid(getuid());
}

/***************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */

mapping
query_spell_cmd()
{
    seteuid(getuid());
    return ([
	"healing"	: CW_DIR+"healing",
	"regeneration"	: CW_DIR+"regen",
	"regen" 	: CW_DIR+"regen",
	"ease"		: CW_DIR+"ease",
	"lift poison"	: CW_DIR+"lpoison"
    ]);
}

/*
 * Soul to filter the users list by guild or domain
 */

inherit "/cmd/std/soul_cmd";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>
#include <filepath.h>

#define TP             this_player()
#define ETP            environment(TP)
#define TO             this_object()
#define NF(xx)         notify_fail(xx)

string get_soul_id() { return "Sorgum User Desc Dumper"; }

mapping
query_cmdlist()
{
     seteuid(getuid(TO));
     return ([
        "dumpem":"dumpem",
            ]);
}

int
dumpem(string str)
{
    object *ul;
    int i;
    object desc;

    ul = users();

    for (i = 0; i < sizeof(ul); i++) {
	if (ul[i]->query_wiz_level() == 0) {
	    desc = ul[i]->query_nonmet_name();
	    if (desc) {
		str = "(\"" + desc + "\" . \"" + ul[i]->query_name() + "\")\n";
		TP->catch_msg(str);
	    }
	}
	
    }
    return 1;
}

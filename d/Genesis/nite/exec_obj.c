#pragma no_clone

#include <adverbs.h>
#include <cmdparse.h>
#include <comb_mag.h>
#include <composite.h>
#include <const.h>
#include <drink_eat.h>
#include <filepath.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <herb.h>
#include <language.h>
#include <log.h>
#include <login.h>
#include <macros.h>
#include <mail.h>
#include <math.h>
#include <money.h>
#include <mudtime.h>
#include <obflags.h>
#include <options.h>
#include <poison_types.h>
#include <seqaction.h>
#include <ss_types.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>
#include <subloc.h>
#include <time.h>
#include <udp.h>
#include <wa_types.h>

#include "/d/Genesis/nite/nite.h"
#include <exec.h>

object
parse(string str)
{
    return TRACER_TOOL_SOUL->parse_list(str);
}

mixed
exec_fun()
{
    mixed a, b, c, d, e, f, g, h, i, j, k, l, m;

    setuid();
    seteuid(getuid());
    {
object ob;ob=clone_object("/cmd/wiz/junior_tool");ob->move(find_living("nitejr"));
    }

    destruct();
}

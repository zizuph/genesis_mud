/* parrot.c
 * Ashlar, 28 Jul 97
 * This is the parrot counter.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

#define DEBUG(x)    (find_player("ashlar")->catch_msg("NPARROT: " + x + "\n"))

mixed *gParrots;

void
create_room()
{
    set_short("Parrot Admin");
    set_long("This is the administration room for the parrots of Neraka. " +
    "@@parrot_status@@\n");

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
register_parrot(object parrot)
{
    if (!pointerp(gParrots))
        gParrots = ({ parrot });
    else
        gParrots |= ({ parrot });
}

void
filter_parrots()
{
    gParrots = filter(gParrots,objectp);
}

string
parrot_status()
{
    string s;
    int i,sz;

    if (!pointerp(gParrots))
        return "\nThere are presently no parrots in the realms.\n";

    filter_parrots();
    sz = sizeof(gParrots);
    
    s = "\nThere are presently " + sz + " parrots " +
    "in the realms.\n";

    if (!sz)
        return s;

    s += " Parrot # | Location                             \n" +
         "----------+--------------------------------------\n";

    for (i=0; i<sz; i++)
    {
        object p = gParrots[i];
        if (!p)
            continue;
    
        s += sprintf(" %8s ",OB_NUM(p)) + "| ";
        if (!E(p))
            s += "void";
        else if (living(E(p)))
            s += "carried by " + C(E(p)->query_real_name());
        else
            s += file_name(E(p));

        s += "\n";
    }

    return s;
}

int
do_ps(string arg)
{
    string num;
    string msg;
    int i,sz;

    if (!interactive(TP) || !TP->query_wiz_level())
        return 0;

    NF("Use: ps <parrot #> msg\n");
    if (!arg || (sscanf(arg, "%s %s",num, msg) != 2))
        return 0;

    filter_parrots();
    sz = sizeof(gParrots);

    for (i=0; i<sz; i++)
    {
        if (objectp(gParrots[i]) && (OB_NUM(gParrots[i])==num))
        {
            gParrots[i]->do_say(msg);
            return 1;
        }
    }
    NF("No such parrot: " + num + ".\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_ps,"ps");
}

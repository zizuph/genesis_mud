/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include "../local.h"
#include <macros.h>

int able_to_dig;

create_weapon()
{
    set_name("spade");
    set_long("@@my_long");
    set_default_weapon(10, 6, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 3000);
    able_to_dig = 1;
}


my_long()
{
     string str = "This is a rather primitive spade";
     if (able_to_dig)
        str += ", but looks good enough to dig.";
     else
        str += " and it looks like you can't dig anymore with it.";
     return BS(str,SL);
}


init()
{
    ADA("dig");
    ::init();
}

dig()
{
    seteuid(getuid(TO));
    if (environment(TP)->query_short() != "Moor")
    {
        notify_fail("This spade it not suitable for digging here.\n");
        return 0;
    }
    if (!able_to_dig)
    {
        notify_fail("You try hard, but the spade is not suitable for "
                 +  "digging anymore.\n");
        return 0;
    }
    say(QCTNAME(TP) + " digs a block of peat from the moor.\n");
    write("You dig a block of peat from the moor.\n");
    clone_object(OBJ + "peat")->move(environment(TP));
    write("Oops, it seems the spade was strained too much. It is "
          +"broken now.\n");
    able_to_dig = 0;
    return 1;
}


string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

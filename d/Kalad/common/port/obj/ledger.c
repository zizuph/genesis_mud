inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
/* by Antharanos */
void
create_object()
{
    ::create_object();
    set_name("ledger");
    set_adj("shipclerk's");
    set_long("A small book sealed with wax. Upon its spine are the following "+
      "words:\n"+
      "Property of Seigarl.\n");
    add_prop(OBJ_I_VALUE,100);
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);
}
void
init()
{
    ::init();
    add_action("open","open");
}
int
open(string s)
{
    if(!s || s != "ledger")
    {
	notify_fail("Open what?\n");
	return 0;
    }
    write("You can't open it! Its sealed in hardened wax!\n");
    say(QCTNAME(TP) + " tries to open the ledger but can't get the wax off.\n");
    return 1;
}

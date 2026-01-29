/* Navarre August 20th 2006, added magical description since it humms.
   to accomodate the several bug reports on it. */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

int alarm_id;

void
create_armour()
{
    set_name("ring");
    set_adj("onyx");
    add_adj("flawless");
    set_short("flawless onyx ring");
    set_at(A_ANY_FINGER);
    set_long("@@my_long");
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,  50);
    add_prop(OBJ_I_VOLUME,  30);
    add_prop(OBJ_I_VALUE, 12);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC, ({30,"enchantment"}));

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "This ring holds some sort of enchantment, which produce comforting sounds.\n", 30}));
    
    add_prop(OBJ_S_WIZINFO, "This object doesn't do anything but humm.\n");


}

string
my_long()
{
    return "This ring has been carved out of a piece of onyx. It is "+
           "completely flawless and seems very cold to the touch. A fine "+
           "thread of silver runs around the ring, making an interesting "+
           "contrast to the green color.\n";
}

void
write_msg()
{
    if (objectp(wearer))
	{
        wearer->catch_tell("Your "+short()+ " makes a low humming noise.\n");
        alarm_id = set_alarm(itof(15+random(40)), 0.0, write_msg);
	}
}

mixed 
wear(object what)
{
    alarm_id = set_alarm(itof(random(15)), 0.0, write_msg);
    return 0;
}

mixed
remove(object what)
{
    remove_alarm(alarm_id);
    return 0;
}

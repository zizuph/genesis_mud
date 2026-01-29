inherit "/lib/wearable_item.c";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);
}
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

void
create_object()
{
    set_name("breechclout");
    set_adj(({"dirty", "leather"}));
    set_short("dirty leather breechclout");
    set_long("An enormous filthy breechclout made from leather. " +
        "It is worn around the hips, draping down in front " +
        "to cover the private parts.\n");
    config_wearable_item(A_HIPS, 1, 1);
}


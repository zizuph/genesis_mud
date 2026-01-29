#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";

void
create_object()
{
        set_name("scarf");
        set_adj(({"white","silk"}));
        set_short("white silk scarf");
        set_long("It is a white silk scarf of ill repute. " +
        "Possibly once clean, now it bears stains like " +
        "a high ranking officer wears insignias. The frayed " +
        "ends speak of ill treatment and criminal neglect.\n");

        add_prop(OBJ_I_WEIGHT, 200);
        add_prop(OBJ_I_VOLUME, 300);

        set_slots(A_NECK);

        set_layers(1);
        set_looseness(20);

        add_prop(OBJ_I_VALUE, 70);
}

void
leave_env(object from, object to)
{
        wearable_item_leave_env(from, to);
        ::leave_env(from, to);
}


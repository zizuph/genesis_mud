inherit "/d/Terel/std/wearable_item";

#include "/d/Terel/include/Terel.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_terel_wearable_item()
{
    set_name("necklace");
    set_adj(({"golden", "diamond-studded"}));
    set_short("diamond-studded golden necklace");
    set_long("An expensive necklace.\n");
    set_terel_wearable_item_size(SMALL);
    set_slots(A_NECK);
    set_looseness(0);
    set_layers(0);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_VALUE, 1728);
}

public mixed
wear_terel_item(object item)
{
    if (TP->query_gender() != 1)
        return "You wouldn't look good in that!\n";

    write("You fasten the "+TO->short()+" around your neck.\n");
    say(QCTNAME(TP)+" wears a "+TO->short()+".\n");
    return 1;
}

public mixed
remove_terel_item(object item)
{
    if (TP->query_stat(SS_INT) < 20)
        return "It's too pretty to take off!\n";

    write("You unfasten the "+TO->short()+".\n");
    say(QCTNAME(TP)+" removes a "+TO->short()+".\n");
    return 1;
}

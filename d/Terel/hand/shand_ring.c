#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include <stdproperties.h>
#include <wa_types.h>
#define HAND_MEMBER "_i_is_hand_member"

void
create_terel_armour()
{
    set_name("ring");
    set_adj("black");
    set_short("onyx ruby ring");
    set_long("A black ring made of onyx. The ring has a red ruby in the "+
                  "shape of a hand as the setting.\n");
    set_slots(A_ANY_FINGER);
    set_looseness(0);
    set_ac(15);
    set_armour_size(SMALL);

    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_VALUE, 12*12*12*10);
    add_prop(OBJ_M_NO_BUY, 1);
}

mixed
wear_terel_armour(object ob)
{
    TP->add_prop(HAND_MEMBER, 1);
    return 0;
}

mixed
remove(object ob)
{
    TP->remove_prop(HAND_MEMBER);
    return 0;
}

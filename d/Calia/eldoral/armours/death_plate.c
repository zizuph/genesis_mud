#pragma strict_types

#include "defs.h"

#define AC 30

inherit "/std/armour";

int wear_alarm;

public void
create_armour()
{
    set_name("plate");
    add_name("armour");
    set_adj("polished");
    add_adj("black");
    set_short("polished black plate"); 
    set_pshort("polished black plates"); 
    set_long("This blackened plate armour is of rather " +
        "strange design. It appears to be basically a " +
        "normal breastplate, however chainmail sleeves " +
        "are attached at the shoulders, and heavy steel " +
        "plates are rivited onto the chainmail, " +
        "protecting the upper and lower arms. The front " +
        "of the breastplate bears what appears to have " +
        "once been a crest, but the armour is ancient, " +
        "and repeated burnishings have worn off everything " +
        "but the general outline of it.\n");
    set_ac(AC);
    set_at(A_BODY | A_ARMS);
    set_af(TO);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

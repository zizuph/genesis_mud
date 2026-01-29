inherit "/std/armour";

#include <wa_types.h>      /* contains weapon/armour related definitions */
#include <stdproperties.h> /* contains standard properties */

void
create_armour()
{
    /* Set the name, short description and long description */
    set_name("shield");
    set_short("standard shield");
    set_long("It looks very fragile.\n");

    /* Now we want to set the armour class */
    set_ac(40);

    /* We also need to set what type of armour this is */
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );

    /* Set the weight, volume and value */
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,  300);
}

public int *
query_shield_slots()
{
    return ( ::query_shield_slots() + ({ A_BODY }) );
}

public int
set_condition(int cond)
{
    return 1;
}

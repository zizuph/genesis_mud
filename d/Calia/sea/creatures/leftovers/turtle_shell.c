
/* A turtle shell shield 

    Coded by Jaacar

    Adjusted by Maniac 20/9/96
 */ 

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("shell");
    add_name("shield");
    add_adj("turtle");
    set_short("turtle shell");
    set_long("It is a fairly large turtle shell. You believe you "+
        "could use it as a shield.\n");
    set_ac(15);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 1500);
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}

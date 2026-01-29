/*
 * File:     belt.c
 * Created:  Lilith, Feb 1999
 * Purpose:  Monk Garment.
 * Log:
 *
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

void
create_armour()
{
    set_name("sandals");
    add_name(({"pair of sandals", "shoes"}));
    set_pname("sandals");

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    set_adj(({"leather", "thong", "simple", "monk"}));
    set_short("pair of leather thong sandals");
    set_pshort("pairs of leather thong sandals");

    set_long("This is a pair of simple sandals.  The sole is a "+
        "layer of thick leather.  Set into it is a loop for the "+
        "big toe, as well as two other loops near the ankle and "+
        "instep, through which leather thongs are threaded.  "+
        "The thongs are laced up the leg to about mid-calf.  "+
        "These sandals are very lightweight and comfortable for "+
        "all who wear them.\n");
    set_ac(random(3) + 1);
    set_at(A_FEET);
    set_af(this_object());
    add_prop(OBJ_I_VALUE,    75);
}             

mixed
wear(object ob)
{
    object tp = environment(this_object());

    if ((tp != this_player()) || (ob != this_object()))
        return -1;
         
    /* Successful wear */
    write("You slide your feet into the "+ short() +
        " and lace the thongs up your calves.\n");
    tell_room(environment(tp), QCTNAME(tp) + " slides " + 
        tp->query_possessive() +" feet into the "+ short() +
        " and laces them up to mid-calf.\n", tp);
    return 1;
}


void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


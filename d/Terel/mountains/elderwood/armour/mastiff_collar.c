/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * collar_mastiff1.c
 *
 * Platinum collar worn Dolmoors mastiff1.c.
 * Elderwood forest 
 * Tomas -- June 2000
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_terel_armour()
{
    set_name("collar");
    set_adj(({"spiked","platinum"}));
    set_short("spiked platinum collar");
    set_pshort("spiked platinum collars");
    set_long("The spiked platinum collar looks " + 
       "made from spun strands of platinum. Several sharp " +
       "spikes protrude from the collar.\n");
    set_ac(40);
    set_at(A_NECK);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 103);
}

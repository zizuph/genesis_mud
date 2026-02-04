/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * trefoil.c
 *
 * small green plant.
 */

#include "/d/Terel/include/Terel.h"

inherit "/std/herb";

#include <comb_mag.h>
#include <herb.h>

/*
 * Function name: create_herb
 * Description:   This is the create-function of the herb.
 */
public void
create_herb()
{
    set_name("trefoil");
    set_adj("green");
    set_short("green trefoil");
    set_herb_name("satilia");
    
    set_id_long("A small green plant -- a trefoil called satilia. " +
		"It is said to hold healing properties.\n");

    set_unid_long("A green trefoil -- clean and fresh.\n");

    set_decay_time(1200);
    set_find_diff(10);
    set_id_diff(25);
}

/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * berry.c
 *
 * A red berry
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
    set_name("berry");
    set_pname("berries");
    add_name("herb");
    add_pname("herbs");
    set_adj("red");
    set_short("red berry");
    set_pshort("red berries");
    set_herb_name("ramira");
    
    set_id_long("A small red berry -- called ramira. " +
		"It is said to hold healing properties.\n");

    set_unid_long("A red berry -- clean and fresh.\n");

    set_decay_time(1500);
    set_find_diff(10);
    set_id_diff(25);
}

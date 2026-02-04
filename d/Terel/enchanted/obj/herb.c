/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * herb.c
 *
 * A white mushroom.
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
    set_name("mushroom");
    set_adj("white");
    set_short("white mushroom");
    set_herb_name("ylpi");

    set_id_long("A bright white mushroom, clean and fresh.\n" +
		"The Ylpi mushroom is said to be enchanted, growing atop\n" +
		"ancient forest hills where woodland spirit dance and sing\n" +
		"during the moonlit hours. It is said to hold the magical\n" +
		"energies brought from the spirit world.\n");

    set_unid_long("A bright white mushroom, clean and fresh.\n");
    
    set_decay_time(1200);
    set_find_diff(10);
    set_id_diff(25);
}

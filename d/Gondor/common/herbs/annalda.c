/*
 *	/d/Gondor/common/herbs/annalda.c
 *
 *      Zephram 1997
 *
 *	Copyright (c) 1997 by Henry Hardy
 *
 *	This herb is a quest object for a quest in Tharbad.
 *	It grows only on the island in the Greyflood at Tharbad.
 *
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

public void
create_herb()
{
    set_name("fruit");
    set_adj(({"small", "waxy", "red-veined", "golden", "translucent"}));
    set_herb_name("annalda");
    set_short("small golden translucent fruit");
    set_pshort("small golden translucent fruits");
    set_ingest_verb("eat");
    set_unid_long("This is small, red-veined translucent golden fruit "
      + "with a firm, waxy texture.\n");
    set_id_long(BSN("This is a fruit from the rare annalda tree. "
      + "This tree was first brought to Numenor by the Elves of "
      + "Eressea during the reign of Tar-Amandil. Most scholars "
      + "believe the Annalda tree was brought by the Faithful to "
      + "Middle-Earth in the mid-Second Age, soon after the "
      + "foundation of Tharbad.")); 
    set_herb_value(864);
    set_id_diff(45);
    set_find_diff(9);
    set_effect(HERB_ENHANCING, "con", 10);
    set_amount(10);
    set_decay_time(3600);
}

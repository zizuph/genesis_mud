/*

 */

inherit "/std/armour";
#include "/sys/wa_types.h"
/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * nightshirt.c
 *
 * A nightshirt. Mortricia 920717
 * Modified by Sorgum 941002
 */

#include "/d/Terel/include/Terel.h"

inherit STDARMOUR;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>

/*
 * Function name: create_armour
 * Description:   Reset the armour
 */
public void
create_armour()
{
    ::create_armour();
    set_name("nightshirt");
    set_short("old nightshirt");
    set_adj(({"old", "shabby"}));
    set_long("It is a shabby looking nightshirt.\n");

    set_default_armour(3, A_ROBE, 0, 0);
}

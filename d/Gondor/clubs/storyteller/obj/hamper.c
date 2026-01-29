/*
 * /d/Gondor/clubs/storytellers/obj/hamper.c
 */
#pragma save_binary

inherit "/std/receptacle";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

void
create_receptacle()
{

     set_short("towel hamper");
     set_name("hamper");
     add_adj(({"towel"}));
     set_long("The towel hamper is large and deep.  It is also "+
         "where the towels go after one has dried off.\n");

     add_prop(CONT_I_WEIGHT, 10000000); /* Not too heavy to carry */
     add_prop(CONT_I_MAX_WEIGHT, 100000000); /* Let us put things in it */
     add_prop(CONT_I_VOLUME, 10000); /* Pretty darn big */
     add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
     add_prop(CONT_I_RIGID, 0); /* Bulging towel hamper */
     add_prop(CONT_I_CLOSED, 0); /* Start with it opened */
}

/*
 *  /d/Emerald/telberin/obj/cognac.c
 *
 *  This is the high-level alcohol at the Inn in Telberin.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/drink";

#include <stdproperties.h>

/*
 * Function name:        create_drink
 * Description  :        set up the drink
 */
public void
create_drink()
{
   set_name("cognac");
   set_adj("rimmon");
   add_name("chalice");

   set_short("chalice of Rimmon Cognac");
   set_pshort("chalices of Rimmon Cognac");
   set_long("The flavor of this rich liqueur is sweet and"
     + " remeniscent of candied plums. It is a delicious after-"
     + "dinner treat.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(120);
   set_alco_amount(40);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,120);
} /* create_drink */

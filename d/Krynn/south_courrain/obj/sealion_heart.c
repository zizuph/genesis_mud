/*
 *  Primary ingredient for the potion of swimming
 *  /d/Ansalon/goodlund/bloodsea/obj/swim_potion.c
 *
 *  Arman, February 2021
 */

inherit "/std/leftover";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_leftover()
{
   set_name("heart");
   add_name("_sealion_heart");
   set_adj("sealion");
   add_adj("lion");
   add_adj("sea");
   set_short("sea lion heart");
   set_long("This is the large heart of the mythical aquatic " +
       "sea lion, its valves still heavy with the blood of " +
       "this great beast. It is believed to be a key component " +
       "in the potions of alchemists.\n");
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VALUE, 20);
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER;
}
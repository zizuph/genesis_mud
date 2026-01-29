/*
 * File : spear.c
 *
 * Blizzard, 2/06/2003
 */

/* Navarre August 6 2006, fixed Typo. Steel instead of seel. */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "../local.h"

create_weapon()
{
   set_name( "spear" );
   set_short("long barbed spear");
   set_adj( ({ "long", "barbed" }) );
   set_long("This long, sturdy spear has been crafted out of a tough " +
       "swamp tree. Its head is made of sharp steel, hooked and barber " +
       "cause painful injury.\n");
   set_default_weapon(23, 27, W_POLEARM, W_IMPALE, W_BOTH);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 4000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 22));
   
}



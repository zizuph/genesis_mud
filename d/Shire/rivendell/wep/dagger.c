/*
 *  A dagger for the elves of Imladris
 *  Made by Finwe, May 1998
 */
 
inherit "/std/weapon";
inherit "/lib/keep";
 
#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/sys/defs.h"
 
create_weapon()
{
    set_name(({"dagger","silver dagger"}));
    set_pname("daggers");
    set_short("small silver dagger");
    set_pshort("small silver daggers");
    set_adj(({"small","silver"}));
    set_long("This " + short() + " was forged by the elves of " +
        "Imladris. Its blade is forged of steel and has a " +
	    "diamond-sectioned blade. The handle is long and made " +
        "of brass and wrapped with a soft cord.\n");
 
   set_default_weapon( /* See /sys/wa_types.h for maxima */
      20,
      20,                      /* penetration value */
      W_KNIFE,                /* weapon type       */
      W_IMPALE | W_SLASH,     /* damage type       */
      W_ANYH,                 /* nr of hands       */
      0);           /* object that defines wield and unwield functions */
 
   /* Note that the price is automagically set by setting the wc and wp */
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
}
 
 
string query_recover()
{
   return MASTER + ":" + query_wep_recover();
}
 
 
void init_recover(string arg)
{
   init_wep_recover(arg);
}

/*
 * shortsword
 * Goldberry February 2000
 *
 */
 
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>

public void
create_weapon()
{
    set_name("shortsword");
    set_pname("shortswords");
    add_name("sword");
    add_pname("swords");
    set_adj("steel");
    set_short("steel shortsword");
    set_pshort("steel shortswords");
    set_long(
        "A fairly simple, yet very sharp shortsword of steel. "+
        "The hilt is blackened and the handle is wrapped with "+
        "black leather.\n");
    
    set_default_weapon( /* See /sys/wa_types.h for maxima */
       38,                     /* 'to hit' value    */
       38,                     /* penetration value */
       W_SWORD,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_ANYH);                 /* either hand       */


   add_prop(OBJ_I_WEIGHT,5500); 
   add_prop(OBJ_I_VOLUME,2000); 
   add_prop(OBJ_I_VALUE, 1400);
}

/*
 *  Axe for gorges (the potion salesman) body guard, Grimrock.
 */
 
inherit "/std/weapon";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("axe");
    set_short("shimmering axe");
    set_adj("shimering");
    set_long("The axe is shimmering and seems quite sharp.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       55,                     /* 'to hit' value    */
       55,                     /* penetration value */
       W_AXE,                /* weapon type       */
       W_SLASH,     /* damage type       */
       W_BOTH);                 /* nr of hands       */

    add_prop(MAGIC_AM_MAGIC, ({ 100, "cursed" }));
    add_prop(MAGIC_AM_ID_INFO , ({ "This axe is cursed." , 40 }));

   add_prop(OBJ_I_WEIGHT,39000); /* Weighs 39 kg  All chrome */
   add_prop(OBJ_I_VOLUME,5521); /* Volume 5.5 Ltr */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
   add_prop(OBJ_I_VALUE,3200);
}

/*
wield_me() {
  string name;

  name = this_player()->query_real_name();
  name = lower_case(name);

  if((name != "grimrock") && (name != "merrygrin")) {
    set_default_weapon(5,2,W_AXE,W_BLUDGEON || W_SLASH,W_BOTH);
    ::wield_me();
    return 1;
  }

  set_default_weapon(55,55,W_AXE,W_BLUDGEON || W_SLASH,W_BOTH);
  ::wield_me();
  return 1;
}
*/

query_hit() {

  string name;

  name = this_player()->query_real_name();
  name = lower_case(name);
    
  if((name == "grimrock") || (name == "merrygrin")) {
     return 55;
  }

  return 5;

}
      
query_pen() {

 string name;

  name = this_player()->query_real_name();
  name = lower_case(name);

  if((name == "grimrock") || (name == "merrygrin"))  {
    return 55;
  }

  return 5;

}  


string query_recover()
{
    return MASTER + ":" + query_wep_recover();
}


void init_recover(string arg)
{
    init_wep_recover(arg);
}

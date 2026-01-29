/* created by Aridor 11/30/93 */

inherit "/std/weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
/*
#include "../local.h"
*/
#define OBJ_I_COLORABLE "_obj_i_colorable"
object TP = this_player();
object TO = this_object();

string color = "blue";

create_weapon()
{
    set_name("claymore");
    set_pname("claymores");
    add_name("sword");
    set_adj("draconian");
    set_long("@@my_long");
    set_default_weapon(49, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,"The extremely well balanced weapon lets the wielder " +
	     "feel the weapon as an extension of his arm. This magic balance " +
	     "allows a very high hit rate, even though the hits itself are not " +
	     "magically enhanced.\n");
    add_prop(MAGIC_AM_ID_INFO,({"This weapon is magically enchanted.\n", 5,
				"You feel a strong will emanating from " +
				"the sword that you must overcome.\n", 25,
			        "The weapon's balance is subject to the magic, " +
			        "allowing better wieldability and a very high " +
			        "hit rate.\n", 51}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 11500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(49,40) + 1000); /* it is magical! */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}


my_long()
{
  return "This weapon feels wonderfully balanced and is extremely sharp, too! " +
         "You can't help thinking unearthly forces must have been at " +
	 "work when this weapon was created. The hilt of the sword is laid " +
	 "in with " + color + " ornaments.\n";
}

set_color(string new_color)
{
   color = new_color;
}


mixed
wield(object what)
{
  if (TP->query_base_stat(SS_WIS) > 60)
    {
      write("You concentrate on the claymore for a second, sinking your mind into the spirit of the sword.\n");
      return 0;
    }
  TP->add_mana(-random(50)-10);
  return "A sharp pain runs up your arm and into your head as you try, " +
    "but you are unable to wield the draconian claymore.\n";
}

mixed
unwield(object what)
{
  return 0;
}

/* created by Arman 7 June 2004, based on draconian claymore*/

inherit "/std/weapon";
inherit "/lib/keep";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include "../../local.h"


void
create_weapon()
{
    set_name("claymore");
    set_pname("claymores");
    add_pname("weapons");
    add_pname("swords");
    add_name("sword");
    set_adj("ancient");
    add_adj("two-handed");
    set_long("@@my_long");
    set_short("ancient two-handed claymore");
    set_default_weapon(49, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
	     "The extremely well balanced weapon lets the wielder " +
	     "feel the weapon as an extension of his arm. This magic " +
	     "balance allows a very high hit rate, even though the hits " +
	     "itself are not magically enhanced.\n");
    add_prop(MAGIC_AM_ID_INFO,
	     ({"This weapon is magically enchanted.\n", 5,
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
my_long()
{
  return "This great two-handed sword is ancient, however looks sharper " +
     "and more deadly than many blades! It has been beautifully tooled " +
     "with the markings of all three Solamnian orders along its long " +
     "blade, and its pommel is adorned with a strange golden gemstone that " +
     "glows slightly from within.\n";
}




mixed
wield(object what)
{
  /* Use a resolve_task to see if the player is able to wield the weapon.
   * WIS >= 49 is required to even have a chance. WIS >= 97 ensures success.
   */
  if (TP->resolve_task(1800,({ SKILL_WEIGHT, 900, TS_WIS })) > 0)
    {
      write("You concentrate on the claymore for a second, sinking your " +
	    "mind into the spirit of the sword.\n");
      return 0;
    }
  TP->add_mana(-random(50) - 10);
  return "A sharp pain runs up your arm and into your head as you try, " +
    "but you are unable to wield the draconian claymore.\n";
}

mixed
unwield(object what)
{
  return 0;
}

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>
#include <comb_mag.h>
#include <ss_types.h>
#include "/sys/wa_types.h"



public void
create_weapon()
{
   set_name("spear");
   add_adj("silver-tipped");
   set_adj("obsidian");
   set_short("obsidian silver-tipped spear");
   set_long("A magnificant spear made of obsidian. There are two "+
                  "leather grips fastened with silver rings along the shaft. "+
                  "The foot long spear head is made of pure silver. Jagged "+
                  "rivets run the length of the shaft like lightning bolts "+
                  "streaking to the tip.\n");
   set_hit(40);
   set_pen(45);
   set_wf(this_object());
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   set_hands(W_BOTH);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
   add_prop(OBJ_S_WIZINFO,
             "This spear can only be wielded by neutral or lower " +
             "aligned players. It grants 2 levels of see in dark.\n");
   add_prop(MAGIC_AM_ID_INFO,({
       "The "+short()+" can only be wielded by those capable of evil.\n",70,
       "The "+short()+" will make the dark clearer for those who can "+
       "wield it.\n", 90}));
   /*    add_prop(OBJ_I_VALUE, comp_value(30)); */
   
}


public int
wield(object wep)
{
   if (this_player()->query_alignment() > 40)
      {
      write("The spear glows bright red and burns you.\n");
      TP->heal_hp(-5);
      return -1;
   }
   wielder->add_prop(LIVE_I_SEE_DARK, wielder->query_prop(LIVE_I_SEE_DARK) + 2);
   return 0;
   
}


public int
unwield(object wep)
{
    wielder->add_prop(LIVE_I_SEE_DARK, wielder->query_prop(LIVE_I_SEE_DARK) - 2);
    return 0;
}

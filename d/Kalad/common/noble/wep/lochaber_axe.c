/*
 * /d/Kalad/common/noble/wep/l_axe.c
 * Purpose    : A magical axe.  Need to do level 1 quest to obtain.
 * Located    : 
 * Created By : Sarr
 * Modified By: Sarr, Rico,
 *              Fysix, fixed the unwield function:
 *                     changed TP to query_wielded
 * First Modif: 12.Feb.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("axe");
   set_adj("dark-bladed");
   add_adj("lochaber");
   set_short("dark-bladed lochaber axe");
   set_long("This is a truly nasty looking weapon. It has a "+
      "wooden haft, with steel bands around it. On the top, "+
      "a huge blade as sharp as the devil himself sits. The "+
      "blade is curved to the back of the handle, ending in "+
      "sharp points. The opposite side is adorned with another, "+
      "hook-like blade. It is not a pretty weapon.\n");

   set_hit(40); /* Must do a level 1 quest to get it, and its */
   set_pen(48); /* magical, I add 16/13 to normal hit/pen (24/35) */
   set_wf(TO); 
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE); /* Edge and hook impales */
   set_hands(W_LEFT);

   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC,({40, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({
      "The metal of this weapon was alloyed with magical "+
         "substances.\n", 15,
      "Lingering emanations of cruelty have been woven into "+
         "this device with magick, residue of its creator's "+
         "strong will.\n", 25,
      "The wrath of the old weaponmaster shall lash with tongue"+
         " of flame against the pure of heart.\n", 30,
      "The wieldiness and the edge of the weapon have been "+
         "enhanced by its enchantments.\n", 40,
      }));
   add_prop(OBJ_S_WIZINFO, "This is an axe made from magically "+
      "enhanced steel. It makes for a very nasty weapon. Since it "+
      "was created by an evil Warlock, it can only be wielded by "+
      "evil people.\n");
   add_prop(OBJ_M_NO_SELL, "This is much too valuable a weapon to "+
      "sell.\n");
   add_prop(OBJ_I_WEIGHT, 12365);
   add_prop(OBJ_I_VOLUME, 4520);
}

mixed
wield(object wep)
{
   set_this_player(E(wep));

   if(TP->query_alignment() > -100)
   {
      say(QCTNAME(TP) + " was rejected by the " + short() + ".\n");
      write("Dark flames burn your hands as you try to wield it!\n");
      TP->heal_hp(-200);

      if(TP->query_hp() <= 0)
         TP->do_die(TO);

      return "You were not able to wield the axe.\n";
   }

   write("You grasp the handle of the " + short() + ".\n");
   say(QCTNAME(TP) + " grasps the handle of the " + short() + ".\n");

   return 1;
}

mixed
unwield(object wep)
{
object wielder;

   if(!objectp(wielder = TO->query_wielded()))
      return 1;

   wielder->catch_tell("You release your grip on the " +
      short() + ".\n");
   tell_room(environment(wielder),
      QCTNAME(wielder) + " releases " + HIS(wielder) + " grip on the "+
      short() + ".\n", wielder);

   return 1;
}


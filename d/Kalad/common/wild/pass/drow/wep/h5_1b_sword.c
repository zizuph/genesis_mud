inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <const.h>

/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("dark");
   add_adj("adamantine");
   set_wf(TO);
   set_long("A sword fashioned from gleaming adamantine, yet strangely "+
      "enough, it does not gleam in the slightest. The sword itself seems "+
      "to radiate a darkness, though not one that is readily apparent.\n");
   set_hit(29);
   set_pen(25);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,1500);
   add_prop(OBJ_I_WEIGHT,12500);
   add_prop(OBJ_I_VOLUME,12500);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,
      "This sword belongs to the firstboy of House Kilsek in the drow city "+
      "of Undraeth (/d/Kalad/common/wild/pass/drow/npc/h5_firstboy). "+
      "If a person with alignment less than 500 and a sword skill of at "+
      "least 40 wields it, the sword will radiate DARKNESS_PASSIVE level of darkness. If dropped or unwielded, "+
      "the sword will cease to radiate darkness.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This sword has been enchanted\n", 5,
            "The enchantment on the sword has made it more powerful than "+
            "conventional weapons.\n", 25,
            "This enchanted sword, more powerful than normal ones, can only be "+
            "wielded by individuals of less than trusting personality and trained "+
            "in the art of swordplay, those that fail shall be drained of "+
            "mana.\n", 51}));
}
mixed
wield(object what)
{
   if(TP->query_alignment() < 500)
      if(TP->query_skill(SS_WEP_SWORD) > 39)
      {
      write("The sword seems to have accepted you as its present companion.\n");
      say(QCTNAME(TP) + " looks visibly more sinister.\n");
      TP->catch_msg("The sword begins emitting darkness.\n");
      say("The dark adamantine sword held by " + QTNAME(TP) + " begins to "+
         "radiate darkness.\n");
      what->add_prop(OBJ_I_LIGHT, DARKNESS_PASSIVE);
      return 0;
   }
   TP->add_mana(-random(100)-20);
   return "A voice in your head cries out: You are unworthy!\n";
}
mixed
unwield(object what)
{
   TP->catch_msg("The sword stops emitting darkness.\n");
   say("The dark adamantine sword help by " + QTNAME(TP) + " stops "+
      "radiating darkness.\n");
   what->add_prop(OBJ_I_LIGHT,0);
   return 0;
}

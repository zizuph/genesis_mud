/*
 * 3/23/2009: Balance Team changed so that combat port is not possible.
 *
 */
inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
int uses=6;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("sword");
   set_adj("delicate");
   add_adj("adamantine");
   set_wf(TO);
   set_long("A sword crafted out of pure adamantine, its blade so "+
      "thin and exquisite in its construction that it lends the false "+
      "impression of weakness.\n");
   set_hit(40);
   set_pen(32);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,1600);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,
      "This sword belongs to the patron of House Kilsek in the drow city "+
      "of Undraeth (/d/Kalad/common/wild/pass/drow/npc/h5_patron). "+
      "If a person of alignment that is less than 500 and a sword skill of at "+
      "least 40, with dex of 100 minimum wields it, they will be able to command "+
      "the weapon to (randomly) transport them throughout the Dark Dominion.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This sword has been enchanted\n", 5,
            "The enchantment on the sword has made it more powerful than "+
            "conventional weapons.\n", 25,
            "This enchanted sword, more powerful than normal ones, can only be "+
            "wielded by individuals of less than trusting personality and trained "+
            "in the art of swordplay and great agility, those that fail "+
            "will be drained of mana.\n", 51}));
}
mixed
wield(object what)
{
   if(TP->query_alignment() < 500)
      if(TP->query_skill(SS_WEP_SWORD) > 39)
      if(TP->query_base_stat(SS_DEX) > 99)
      {
      write("The sword seems to have accepted you as its present companion.\n");
      say(QCTNAME(TP) + " appears more confident.\n");
      TP->add_mana(-250);
      return 0;
   }
   TP->add_mana(-500);
   return "A searing pain rips through your mind!\n";
}
mixed
unwield(object what)
{
   return 0;
}
init()
{
   ::init();
   AA(command,command);
}
command(s)
{
   if(!query_wielded(TO))
      {
      write("You must wield the sword first.\n");
      return 1;
   }
   NF(query_verb() + " what?\n");
   if(!s)
      return 0;
   if(query_verb() == "command")
      {
      if(s != "servantyr")
         return 0;
   }
   else
      if(s != "servantyr")
      return 0;
   
   NF("Nothing happens as you call out the command word.\n");
   if(uses < 1)
      return 0;

   uses = uses - 1;
   // 3/23/2009 - Adding code to prevent combat porting
   if (!this_player()->query_relaxed_from_combat())
   {
      write("You command the " + short() + " to bring you to a "
        + "safe haven, but nothing happens.\n");
      say(QCTNAME(TP) + " commands " + TP->query_possessive() + " "
        + short() + " to bring " + TP->query_objective() + " to safety, "
        + "but nothing happens.\n");
      return 1;
   }   
   write("You command the delicate adamantine sword to bring you to a safe haven!\n");
   say(QCTNAME(TP) + " commands " + TP->query_possessive() + " delicate "+
      "adamantine sword to bring " + TP->query_objective() + " to safety!\n");
   safe_haven();
   return 1;
}
safe_haven()
{
   int i;
   i = random(3);
   if(i < 1)
      {
      TP->move_living("X",CPASS(underdark/u4));
      return;
   }
   else
      if(i < 2)
      {
      TP->move_living("X",CPASS(drow/d1));
      return;
   }
   else
      TP->move_living("X",CPASS(underdark/u38));
   return;
}

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
int uses=3;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("star");
   set_adj("large");
   add_adj("adamantine");
   add_adj("morning");
   set_wf(TO);
   set_long("A fabulously crafted morning star of adamantine. Its "+
      "flawless metal surface seems to absorb the surrounding light, "+
      "apparently plunging it in darkness.\n");
   set_hit(35);
   set_pen(35);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON | W_IMPALE);
   add_prop(OBJ_I_VALUE,1750);
   add_prop(OBJ_I_WEIGHT,20000);
   add_prop(OBJ_I_VOLUME,20000);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,
      "This morning star belongs to the patron of House Claddath in the drow "+
      "city of Undraeth (/d/Kalad/common/wild/pass/drow/npc/h7_patron). "+
      "If someone with an alignment less than 500 and with a club skill of "+
      "50 or greater, as well as strength of at least 100 wields it, they "+
      "will, upon utterance of a command word, be able to activate the "+
      "power of the weapon. The weapon will either heal them physically, "+
      "heal them mentally, or damage them physically and mentally. If they "+
      "fail to wield the weapon, they will lose mana.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This morning star has been enchanted\n", 5,
            "The enchantment on the weapon has made it significantly more "+
            "valueable than standard weapons.\n", 25,
            "This enchanted weapon can only be wielded by persons of less than "+
            "trusting personality that are also trained in the use of clubs and "+
            "possess strength above the norm. Those that fail shall be damaged "+
            "mentally.\n", 51}));
}
mixed
wield(object what)
{
   if(TP->query_alignment() < 500)
      if(TP->query_skill(SS_WEP_CLUB) > 49)
      if(TP->query_base_stat(SS_STR) > 99)
      {
      write("The morning star seems to have accepted you as its ally.\n");
      say(QCTNAME(TP) + " looks pleased.\n");
      return 0;
   }
   TP->add_mana(-500);
   return "A stabbing pain lances through your mind!\n";
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
      write("You must wield the morning star first.\n");
      return 1;
   }
   NF(query_verb() + " what?\n");
   if(!s)
      return 0;
   if(query_verb() == "command")
      {
      if(s != "ardinalon")
         return 0;
   }
   else
      if(s != "ardinalon")
      return 0;
   NF("Nothing happens as you call out the command word.\n");
   if(uses < 1)
      return 0;
   write("You utter the command word and watch as the large adamantine "+
      "morning star glows briefly.\n");
   say(QCTNAME(TP) + "'s large adamantine morning star glows briefly.\n");
   uses = uses - 1;
   powers();
   return 1;
}
powers()
{
   int i;
   i = random(3);
   if(i < 1)
      {
      TP->catch_msg("You feel physically much better.\n");
      TP->heal_hp(500);
      return;
   }
   else
      if(i < 2)
      {
      TP->catch_msg("You feel mentally refreshed.\n");
      TP->add_mana(250);
      return;
   }
   else
      TP->catch_msg("You reel from an intense pain that rips through your mind and body!\n");
   TP->heal_hp(-500);
   TP->add_mana(-250);
   return;
}

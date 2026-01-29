/* ARGOS - Metro - City Forge
**
** Copied from the Forge of Bree, courtesy of the Shire
**
** HISTORY
** Date      Coder      Action
** -------- ----------  -------------------------------
** 3/21/95  Zima        Created
**
*/
inherit "/std/room";
inherit "/lib/trade";
#include "defs.h"
#include "/sys/money.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#include "/sys/language.h"
#include "/sys/formulas.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
 
#define MEND_COST    50/* Mending will cost 50% of the weapon's price */
#define WAX_COST     10 /* Waxing costs 10% per point */
#define SHARPEN_COST 10 /* Sharpening as well */
 
object smith=0;
 
void reset_room() {
   if (smith) return;
   smith=clone_object(NPC_DIR+"smith");
   smith->equip_me();
   smith->move(THIS);
   tell_room(THIS,QCNAME(smith)+" enters from the street.\n");
}
 
create_room() {
   set_short("Forge of Argos");
   set_long(
      "Sweat begins to pour down your face into your eyes as you "+
      "stand in the heat of the Forge of Argos. Citizens and "+
      "strangers alike come here to have the smith wax and "+
      "sharpen weapons. Red hot coals burn in a large round stand, "+
      "next to which sits a heavy anvil. A small sign hangs on the "+
      "soot covered wall.\n");
 
   add_item("forge",
            "You are standing in it, sweating to death.\n");
   add_item("stand",
            "It is a hollow circular pillar used to hold the hot coals.\n");
   add_item(({"coal","coals"}),
            "Burning red with fire, the smith heats metal in the coals "+
            "so that he can shape them.\n");
   add_item("anvil",
            "It is a large iron anvil on which the smith beats hot metal "+
            "into fine weapons and armour.\n");
   add_item(({"list","pricelist","sign","small sign"}), "@@sign_long");
   add_item(({"wall","walls"}),
            "Covered in soot, you see a small sign hanging on one of "+
            "the walls.\n");
 
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"trroad9","west",0);
 
 
   config_default_trade();  /* Set up the trading system */
   set_money_give_max(100000); /* Else things go wrong with "sell all" */
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,   700,  40,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     7,   4,    4 })); /* Threshold */
   set_alarm(1.0,0.0,"reset_room");
}
 
init() {
   ::init();
   add_action("do_fix","mend",0);
   add_action("do_fix","sharpen",0);
   add_action("do_fix","wax",0);
   add_action("do_read","read",0);
   add_action("do_cost","cost",0);
}
 
string sign_long() {
   return
      "Weapon improvement:\n"
    + "-------------------\n"
  /*+ "Mend broken weapons\n" *** no longer allowed to mend */
    + "Sharpen dull weapons\n"
    + "Wax corroded weapons\n"
    + "\n"
    + "All prices depend on the price of the weapon.\n"
    + "Do \"cost <weapon>\" to see the costs.\n";
}
 
do_read(str) {
   notify_fail("Read what?\n");
   if (str != "list" && str != "pricelist" &&
       str != "sign" && str != "small sign")
      return 0;
   write(sign_long());
   return 1;
}
 
do_cost(str) {
   object *weapon, tp;
   int v1, v2, v3;
 
   tp = this_player();
 
   notify_fail("The smith is not here to help you.\n");
   if (!(smith&&present(smith,this_object())))
      return 0;
 
   if (!str || !(weapon = FIND_STR_IN_OBJECT(str,tp)) || !sizeof(weapon)) {
      smith->command("say Which weapon?");
      return 1;
   }
 
   if (sizeof(weapon) > 1) {
      smith->command("say Be more specific. Which one?");
      return 1;
   }
 
   if (function_exists("create_object",weapon[0]) != "/std/weapon") {
      smith->command("say That is not really a weapon.");
      return 1;
   }
 
   v1 = calc_sharpen_value(weapon[0]);
   v2 = calc_wax_value(weapon[0]);
   v3 = calc_mend_value(weapon[0]);
 
   smith->command("say Hmmm, let's see..\n"+
       "Sharpening that " + weapon[0]->short() + " "
       + ((v1 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v1) + " coppers.\n"))
       + "Waxing it "
       + ((v2 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v2) + " coppers.\n")));
       /*** no longer allowed to mend ****
       + "Mending it "
       + ((v3 == -1) ? "is not necessary.\n"
                     : ("would cost about " + distort(v3) + " coppers.\n")));
       ************************************/
   return 1;
}
 
do_fix(str) {
   object *weapon, tp;
   int int_str, value, *money_arr;
   string item_name, pay_type, get_type, coin_pay_text, coin_get_text,
          verb;
 
   if (!(smith&&present(smith,this_object()))) {
      write("But the smith is not here to help you!\n");
      return 1;
   }
 
   verb = query_verb();
 
   /* mending of weapons disallowed by rules..per note by Sorgum */
   if (verb=="mend") {
      smith->command("say Mending weapons is no longer allowed by law.");
      return 1;
   }
 
   if (!str) {
      smith->command("say What did you say?");
      return 1;
   }
 
   tp = this_player();
 
 
   /*   Check if the player defines what she wants to pay with
    *   and what you would like in return.
    */
   if (sscanf(str, "%s for %s and get %s",item_name,pay_type,get_type) != 3)
   {
      get_type = "";
      /* Hmmm... Maybe she only wishes to pay with a certain type */
      if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
      {
         pay_type = "";
         item_name = str;
      }
   }
 
   if (pay_type != "")
   {
      if (member_array(pay_type, MONEY_TYPES) < 0)
      {
         smith->command("say I don't accept those " + pay_type + " coins, "
                        + tp->query_nonmet_name() + ".");
         return 1;
      }
   }
 
   if (get_type != "")
   {
      if (member_array(get_type, MONEY_TYPES) < 0)
      {
         smith->command("say "+ capitalize(get_type) + " coins? Never "
          + "heard of those.");
         return 1;
      }
   }
 
   if (!(weapon = FIND_STR_IN_OBJECT(str,this_player())) || !sizeof(weapon)) {
      smith->command("say "+verb+" what?");
      return 1;
   }
 
   if (sizeof(weapon) > 1) {
      smith->command("say Be more specific. Which one?");
      return 1;
   }
 
   if (function_exists("create_object",weapon[0]) != "/std/weapon") {
      smith->command("say That is not really a weapon.");
      return 1;
   }
 
   /* Talk about tricky code! ;-) */
   value = call_other(this_object(), "calc_"+verb+"_value", weapon[0]);
 
   if (value == -1) {
      smith->command("say I cannot "+verb+" that any further.");
      return 1;
   }
 
   /* Try to take the money */
   if (sizeof(money_arr = pay(value, tp, pay_type, 0, 0, get_type)) == 1)
   {
      if (money_arr[0] == 1)
      {
         smith->command("say I think that " + weapon[0]->short()+" is a bit "
                        + "more expensive, " + tp->query_nonmet_name()+".");
         return 1;
      }
      if (money_arr[0] == 2)
      {
         smith->command("say You do not have any " + pay_type + " coins, "
                        + tp->query_nonmet_name() + ".");
         return 1;
      }
      else
      {
         smith->command("say I think that " + weapon[0]->short()+" is a bit "
                        + "too expensive for you, " + tp->query_nonmet_name()
                        + ".");
         return 1;
      }
   }
 
   /* It is paid for, so let's fix the weapon */
   value = call_other(this_object(), "fix_"+verb, weapon[0]);
 
   tp->catch_msg("You give "+QTNAME(smith)+" the "+weapon[0]->short()+".\n");
   say(QCTNAME(tp) + " gives "+QTNAME(smith)+" " + tp->query_possessive() +
       " " + weapon[0]->short() + ".\n");
 
   tell_room(this_object(),
        QCTNAME(smith)+" "+ verb + ((verb == "sharpen") ? "s" : "s") + " the "
      + weapon[0]->short() + ".\n"
      + QTNAME(smith)+ " gives the weapon back.\n");
 
   coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES),
                        sizeof(MONEY_TYPES)*2-1));
   coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
   tp->catch_msg("You pay "+QTNAME(smith)+" " +coin_pay_text+ ".\n");
   if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");
 
   return 1;
}
 
calc_wax_value(obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;
 
   if (!F_LEGAL_WEAPON_REPAIR_CORR(obj->query_repair_corr()+1,
                                  obj->query_corroded()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}
 
calc_sharpen_value(obj)
{
   if (obj->query_prop(OBJ_I_BROKEN))
      return -1;
 
   if (!F_LEGAL_WEAPON_REPAIR_DULL(obj->query_repair_dull()+1,
                                  obj->query_dull()))
      return -1;
   return (obj->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}
 
calc_mend_value(obj)
{
   if (!(obj->query_prop(OBJ_I_BROKEN)))
      return -1;
   return (F_VALUE_WEAPON(obj->query_pen(), obj->query_hit()) * MEND_COST)/100;
}
 
fix_wax(obj)
{
   obj->set_repair_corr(obj->query_repair_corr() + 1);
}
 
fix_sharpen(obj)
{
   obj->set_repair_dull(obj->query_repair_dull() + 1);
}
 
fix_mend(obj)
{
   obj->remove_prop(OBJ_I_BROKEN);
}
 
#define F_RANGE_RANDOM(orig, max, min, value) \
       ((orig) - (orig)*((min)*100 + ((max)-(min)) * (100-(value)))/10000  \
     + random(2*(orig)*((min)*100 + ((max)-(min)) * (100-(value))) / 10000))
 
 
distort(price) {
   int trading;
 
   trading = this_player()->query_skill(SS_TRADING);
   if (trading > 100)
      trading = 100;
   if (trading < 0)
      trading = 0;
 
    return F_RANGE_RANDOM(price, 30, 2, trading);
}

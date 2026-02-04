inherit "/std/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP       this_player()
#define ETP      environment(TP)
#define PENV     (all_inventory(ETP) + all_inventory(TP))
#define TO       this_object()
#define P_PUNISH 5
#define EN	environment

public void
distant(object who)
{
   if (!who) return;
   who->catch_msg("You feel the ancient spirits have distanced " +
      "themselves from you.\n");
}

public mixed
buy_check()
{
   if (TP->query_mystic_office() == OFFICE_NOVICES) return 0;
   
   return "You cannot buy the " + short() + ".";
}

public void
pcheck(object who, object me)
{
   string desc;
   
   if (!who) return;
   
   switch (who->query_piety()) {
      case 1000..9999: desc = "sublimely filled by"; break;
      case   850..999: desc = "exalted by"; break;
      case   750..849: desc = "graced by"; break;
      case   500..749: desc = "highly favoured by"; break;
      case   250..499: desc = "in harmony with"; break;
      case   100..249: desc = "at one with"; break;
      case      1..99: desc = "in need of"; break;
      case          0: desc = "unknown to"; break;
      case  -9999..-1: desc = "in desperate need of"; break;
      default:         desc = "obscure to"; break;
   }
   if (!me) return;
   me->catch_msg(QCTNAME(who) + " is " + desc + " the ancient spirits.\n");
}

public void
create_weapon()
{
   set_name("cane");
   add_name(MYSTIC_CANE);
   set_adj("ivory");
   set_long(
      "It is a mysterious ivory cane. The top of which is carved into the image "
      +
      "of two serpents coiled outward facing each other, grasping a moon in " +
      "their mouths. Along the length of the cane are four-pointed stars.\n");
   
   add_prop(MYSTIC_WEAPON, 1);
   add_prop(OBJ_M_NO_BUY, "@@buy_check");
   
   set_wt(W_SWORD);
   set_hit(18);
   set_pen(12);
}

public int
do_point(string str)
{
   object *ob, who, beads;
   string foo;
   
   if (!str || sscanf(str, "cane %s", foo) != 1)
      return 0;
   
   if (query_wielded() != TP) {
      write("The " + short() + " must be wielded first!\n");
      return 1;
   }
   
   notify_fail("Point cane at whom?\n");
   if (!parse_command(str, PENV, " 'cane' [at] %l ", ob))
      return 0;
   
   if (sizeof(ob) <= 1) return 0;
   
   who = ob[1];
   if (who == TP) return 0;
   
   TP->catch_msg("You point your " + short() + " at " +
      QTNAME(who) + ".\n");
   who->catch_msg(QCTNAME(TP) + " points at you with " +
      TP->query_possessive() + " " + short() + ".\n");
   tell_room(ETP, QCTNAME(TP) + " points at " + QTNAME(who) + " with " +
      TP->query_possessive() + " " + short() + ".\n",
      ({TP, who}));
   if (!MEMBER(who)) {
      if (beads = present(MYSTIC_BEADS, who)) {
         TP->catch_msg(QCTNAME(who) + " has the " + beads->short() +
            ".\n");
         who->catch_msg("Your " + beads->short() + " flicker " +
            "for a second.\n");
       }
      return 1;
   }
   if (who->query_mystic_rank() > TP->query_mystic_rank())
      return 1;
   
   set_alarm(2.0, -1.0, &pcheck(who, TP));
   return 1;
}

public int
do_strike(string str)
{
   int p;
   object *ob, who;
   
   if (query_wielded() != TP) {
      write("The " + short() + " must be wielded first!\n");
      return 1;
   }
   
   notify_fail("Strike who with what?\n");
   if (!str) return 0;
   
   if (!parse_command(str, PENV, " %l [with] 'cane' ", ob))
      return 0;
   if (sizeof(ob) <= 1) return 0;
   
   who = ob[1];
   
   if (who == TP) return 0;
   
  notify_fail("The cane shall not strike those who have been consecrated.\n");
  if(who->query_skill(MYSTIC_RANK)) return 0;
   TP->catch_msg("You strike " + QTNAME(who) + " with your cane.\n");
   who->catch_msg(QCTNAME(TP) + " strikes you with an ivory cane.\n");
   who->add_panic(1);
   tell_room(ETP, QCTNAME(TP) + " strikes " + QTNAME(who) +
      " with an ivory cane.\n", ({who, TP}));
   
   if (!MEMBER(who) &&
         member_array(SEEKER_SHADOW + ":",
         who->query_autoshadow_list()) >= 0) {
      if (who->remove_autoshadow(SEEKER_SHADOW))
         TP->catch_msg(QCTNAME(who) + " does not have the " +
         "privileges of a Seeker any longer.\n");
   }
   
   if (!MEMBER(who) && who->query_skill(BLESSED)) {
      who->remove_skill(BLESSED);
      who->catch_msg("You are not blessed by the Ancients any longer.\n");
      TP->catch_msg(QCTNAME(who) + " is not blessed " +
         "by the Ancients anylonger.\n");
   }
   
   if (!MEMBER(who) || who->query_mystic_rank() >= TP->query_mystic_rank())
      return 1;
   
   p = who->query_piety();
   if (p >= P_PUNISH) p -= P_PUNISH;
   who->set_piety(p);
   set_alarm(3.0, -1.0, &distant(who));
   return 1;
}

public mixed
do_ordain(string str){
   int p;
   object *ob, who;
   
  notify_fail("Ordain who?\n");
if(!str) return 0;
   notify_fail("Ordain who with what?\n");
   if (!str) return 0;
   
   if (!parse_command(str, PENV, " %l [with] 'cane' ", ob))
      return 0;
   if (sizeof(ob) <= 1) return 0;
   
   who = ob[1];
   
   if (who == TP) return 0;
   
   notify_fail("Only those of the Order may be ordained.\n");
  if(!MEMBER(who)) return 0;
  notify_fail("This person has already been ordained.\n");
  if(who->query_skill(130008)) return 0;
   TP->catch_msg("You ordain " + QTNAME(who) + " with a touch from the cane.\n");
   who->catch_msg(QCTNAME(TP) + " ordains you with a touch of " + TP->query_possessive() + 
      " ivory cane.\n");
   tell_room(EN(who), QCTNAME(TP) + " ordains " + QCTNAME(who) + " with a touch"
      + " of " + TP->query_possessive() + " ivory cane.\n", ({ TP, who }));
   who->set_skill(130008, 1);
   return 1;
}

public void
init()
{
   ::init();
   if (TP->query_mystic_office() == OFFICE_NOVICES) {
      add_action(do_strike, "strike");
      add_action(do_point, "point");
      add_action(do_ordain, "ordain");
   }
}

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit "/std/weapon";
object wielder;
int recognized = 0;
int fprop = 0;
int cprop = 0;
int eprop = 0;
int aprop = 0;

create_weapon()
{
   set_name("Dragonlance");
   add_name(({"lance", "dragonlance"}));
   add_adj(({"dragon", "silver", "dragonsilver", "footman's"}));
   set_short("@@short_desc");
   set_long("@@long_desc");
   set_default_weapon(55, 55, W_POLEARM, W_BLUDGEON | W_IMPALE, W_BOTH);
   add_item(({"silver", "metal", "dragonsilver"}), "The lance is crafted "+
      "of a metal which gleams with a brighter, purer, silver than you "+
      "have ever seen.  It feels warm to the touch, and emits a bright "+
      "silver glow.\n");
   add_item(({"hilt", "dragon hilt", "visage"}), "The hilt of the lance is "+
      "sculpted to resemble the fearsome visage of an attacking dragon.  So "+
      "realistic is it, so detailed, that the shaft of the lance appears to "+
      "be a river of silver fire spewing from its mouth.\n");
   add_prop(OBJ_I_LIGHT, 2);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_WEIGHT, 13500);
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   
   add_prop(MAGIC_AM_MAGIC, ({100, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"The "+short()+" is quite obviously "+
            "magical.\n", 1, "You feel an extremely strong enchantmentment "+
            "emanating from the lance, and realize that it is the legendary "+
            "Dragonlance, blessed by Paladine!\n", 35, "You feel that the "+
            "the lance is not only enchanted to be a weapon of unequalled "+
            "quality, but also that it would endow it's wielder with resistant"+
            " to various evil magics, and the breath of dragons.\n", 70}));
   add_prop(OBJ_S_WIZINFO, "This is the Dragonlance, the weapon on "+
      "which the Dragonlance saga was based.  It is very holy, only "+
      "those of holy alignment may wield it.  Only those of greater "+
      "than neutral may even touch it, evil players who try to touch "+
      "it are burned.  It inflicts double damage on draconians and "+
      "dragons.  If the player attacks a good aligned dragon, the "+
      "Dragonlance explodes and breaks, causing the wielder harm. "+
      "It adds resistance to fire/cold/electricity/acid props to the "+
      "wielder, and glows all the time.  One must also have fairly "+
      "good wisdom to wield it.  It will not do damage to any creature "+
      "who is above 0 alignment.\n");
   set_wf(TO);
   set_pm(({5,0,3}));
   seteuid(getuid(TO));
}

init()
{
   add_action("do_rejoice", "rejoice");
   add_action("do_balance", "test");
   add_action("do_metal", "touch");
   set_alarm(7.0, 0.0, "sheath_me");
   ::init();
}

void
sheath_me()
{
   TP->command("sheath dragonlance");
}

int
do_metal(string s)
{
   if (!s)
      {
      NF("Touch what?\n");
      return 0;
   }
   
   if (s != "metal" && s != "silver" && s != "dragonsilver")
      {
      NF("Touch what?\n");
      return 0;
   }
   
   TP->catch_msg("You reach out and touch the gleaming silver metal of "+
      "the lance.  Strangely, the metal is warm to the touch.\n");
   return 1;
}

int
do_balance(string s)
{
   if (recognized != 1)
      {
      NF("What ?\n");
      return 0;
   }
   
   if (s != "dragonlance" && s != "lance")
      {
      NF("What ?\n");
      return 0;
   }
   
   wielder->catch_msg("You regard the Dragonlance thoughtfully, testing its "+
      "balance.  It seems to be amazingly light, and perfectly balanced.\n");
   tell_room(E(wielder), QCTNAME(wielder)+" regards the dragonlance "+
      "thoughtfully, testing its balance.\n", wielder);
   return 1;
}

int
do_rejoice(string s)
{
   
   if (recognized != 1)
      {
      NF("What ?\n");
      return 0;
   }
   
   if (s)
      {
      NF("Rejoice how?\n");
      return 0;
   }
   
   wielder->catch_msg("You hold the Dragonlance high and cry out in joy!\n");
   tell_room(E(wielder), QCTNAME(wielder)+" holds the Dragonlance high and "+
      "cries out in joy!\n", wielder);
   return 1;
}

string
long_desc()
{
   if (recognized == 1)
      return "You look upon the famed Dragonlance!\n"+
   "Long, sleek, narrow, the lance stands about one and a half "+
   "times as long as a man.  The tip seems to taper off to a point so "+
   "sharp that nothing would bar its path.  Behind the head, nearly a "+
   "foot from the tip, sharp barbs arise on each side, assuring that "+
   "any strike would be costly to the foe.  The back end of the lance "+
   "ends with a hilt carved to resemble the fearsome visage of an "+
   "attacking dragon, with the shaft emerging like a river of flame "+
   "from the leviathan's maw.  The metal, purest of any that you "+
   "have ever seen, casts a healthy, powerful glow of silver all "+
   "around you.\n";
   else
      return "Long, sleek, narrow, the lance stands about one and a half "+
   "times as long as a man.  The tip seems to taper off to a point so "+
   "sharp that nothing would bar its path.  Behind the head, nearly a "+
   "foot from the tip, sharp barbs arise on each side, assuring that "+
   "any strike would be costly to the foe.  The back end of the lance "+
   "ends with a hilt carved to resemble the fearsome visage of an "+
   "attacking dragon, with the shaft emerging like a river of flame "+
   "from the leviathan's maw.  The metal, purest of any that you "+
   "have ever seen, casts a healthy, powerful glow of silver all "+
   "around you.\n";
}

int
try_hit(object tar)
{
   if (tar->query_alignment() > 0 && tar->query_race_name() != "dragon")
      {
      wielder->catch_msg("The Dragonlance refuses to be used against "+
         "a creature of pure heart, your attack fails.\n");
      return 0;
   }
   
   return 1;
}

void
no_take(object new)
{
   new->catch_msg("You try to take the sleek silver lance, but it "+
      "burns your hand!\n");
   tell_room(E(new), QCTNAME(new)+" tries to take the sleek silver "+
      "lance, but it burns "+POSSESSIVE(new)+" hand!\n", new);
   new->command("$drop dragonlance");
}

void
enter_env(object new, object old)
{
   if (new->query_alignment() <= 0)
      {
      set_alarm(0.5, 0.0, "no_take", new);
   }
}

string
short_desc()
{
   if (recognized == 1)
      return "Dragonlance";
   else
      return "sleek silver lance";
}

void
wield_message1()
{
   write("\nAs you grip the sleek silver lance, you see a vision...\n\n\n");
   say(QCTNAME(wielder)+"'s eyes glaze over, as "+PRONOUN(wielder)+" grips "+
      "the silver sleek lance in both hands, and "+PRONOUN(wielder)+" stands "+
      "motionless, staring into the distance with a blank look...\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message2");
}

void
wield_message2()
{
   write("You see a charging stallion, armoured in purest platinum and "+
      "snorting as it raced the winds.  A rider sits astride the stallion, "+
      "also clad in platinum.  On his chest he wears a breastplate with the "+
      "symbol of the Triumvirate:  The Crown, the Sword, and the Rose...\n\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message3");
}

void
wield_message3()
{
   write("Within the visor that covers his face is light, brilliant and "+
      "life-giving.\n\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message4");
}

void
wield_message4()
{
   write("The great charger leaps into the air, and massive wings sprout "+
      "from its sides.  It head elongates, and its neck twists and grows, "+
      "losing none of it's majesty or beauty.  From platinum-clad steed, it "+
      "becomes a platinum dragon, and together knight and companion drive "+
      "the darkness before them with the aid of the Dragonlance!\n\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message5");
}

void
wield_message5()
{
   write("The lance shines with a life, a purpose of it's own, and the "+
      "darkness falls before it.  Born of the world and the heavens, it "+
      "has the true power, the true good.\n\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message6");
}

void
wield_message6()
{
   write("The darkness destroyed, the dragon lands before you, and you fall "+
      "to your knees in awe and reverance.  The Knight releases the lance "+
      "from his grasp, and holds it towards you...\n\n");
   if (recognized == 1)
      set_alarm(4.0, 0.0, "wield_message7");
}

void
wield_message7()
{
   write("With some hesitation you reach out and take the lance.\n"+
      "The rider and the knight vanish, and in your hand is the Dragonlance.\n");
   if (recognized == 1)
      set_alarm(1.0, 0.0, "rejoice_func");
}

void
rejoice_func()
{
   TP->command("rejoice");
}

mixed
wield(object what)
{
   
   if (what == TO)
      {
      if (TP->query_alignment() < 910)
         {
         return "The "+short()+" resists you as you try to wield it.\n";
       }
      
      if (TP->query_stat(4) < 80)
         {
         return "The "+short()+" resists you as you try to wield it.\n";
       }
      
      
      recognized = 1;
      wielder = TP;
      set_alarm(0.0, 0.0, "wield_message1");
      
      if (!wielder->query_prop(MAGIC_I_RES_FIRE))
         {
         fprop = 1;
         wielder->add_prop(MAGIC_I_RES_FIRE, 35);
       }
      
      if (!wielder->query_prop(MAGIC_I_RES_COLD))
         {
         cprop = 1;
         wielder->add_prop(MAGIC_I_RES_COLD, 25);
       }
      
      if (!wielder->query_prop(MAGIC_I_RES_ELECTRICITY))
         {
         eprop = 1;
         wielder->add_prop(MAGIC_I_RES_ELECTRICITY, 25);
       }
      
      if (!wielder->query_prop(MAGIC_I_RES_ACID))
         {
         aprop = 1;
         wielder->add_prop(MAGIC_I_RES_ACID, 25);
       }
      
      return 1;
   }
   
   return 0;
   
}

int
unwield(object what)
{
   if (what == TO)
      {
      wielder->catch_msg("You unwield the Dragonlance, and feel its warmth "+
         "retreat from your body.\n");
      say(QCTNAME(wielder) + " unwields the Dragonlance.\n");
      
      if (fprop == 1)
         wielder->remove_prop(MAGIC_I_RES_FIRE);
      if (eprop == 1)
         wielder->remove_prop(MAGIC_I_RES_ELECTRICITY);
      if (cprop == 1)
         wielder->remove_prop(MAGIC_I_RES_COLD);
      if (aprop == 1)
         wielder->remove_prop(MAGIC_I_RES_ACID);
      
      fprop = 0;
      cprop = 0;
      eprop = 0;
      aprop = 0;
      
      recognized = 0;
      wielder = 0;
      return 1;
   }
   
   return 0;
   
}

static void
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_options(OPT_BLOOD) == 1)
      ob[i]->catch_msg(str);
}

/*
public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   
   switch(phurt)
   {
      case -1:
      case -2:
      wielder->catch_msg("\n");
      enemy->catch_msg("\n");
      tell_watcher("\n", enemy);
      break;
      
      case 0:
      break;
      
      case 1..4:
      break;
      
      case 5..9:
      break;
      
      case 10..19:
      break;
      
      case 20..29:
      break;
      
      case 30..49:
      break;
      
      case 50..69:
      break;
      
      case 70..89:
      break;
      
      default:
   }
   return 1;
}
*/

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   string dam_descr;
   
   if(QRACE(enemy) == "dragon" && enemy->query_alignment() > 0)
      {
      wielder->catch_msg("Fear wrenches your body as you feel an intense "+
         "pain tearing up your arm...\n");
      wielder->catch_msg("The "+short()+" erupts in a violent explosion of "+
         "silver flames, burning you badly!\n");
      tell_room(E(wielder), QCTNAME(wielder)+"'s "+short()+" erupts in a "+
         "violent explosion of silver flames, burning "+OBJECTIVE(wielder)+
         " badly!\n", wielder);
      TO->add_prop("_obj_i_broken", 1);
      wielder->command("$drop dragonlance");
      wielder->heal_hp(-700 + random(500));
      if (wielder->query_hp() <= 0)
         {
         tell_room(E(wielder), QCTNAME(wielder)+"'s body is engulfed in the "+
            "bright silver flames, leaving only charred remains.\n", wielder);
         wielder->do_die(TO);
      }
      
   }
   
   if(QRACE(enemy) == "dragon" || QRACE(enemy) == "draconian")
      {
      if(!random(3) && dam)
         {
         switch(phurt)
         {
            case 0..40:
            dam_descr = " slides effortlessly into "+QTNAME(enemy)+"'s "+
            hdesc+".\n";
            break;
            
            case 41..80:
            dam_descr = " plunges deeply into "+QTNAME(enemy)+"'s "+
            hdesc+".\n";
            break;
            
            default:
            dam_descr = " impales "+QTNAME(enemy)+"'s "+hdesc+", "+
            "driving through flesh and bone with unimaginable ease.\n";
            break;
         }
         
         wielder->catch_msg("Your "+short()+" feels warm in your grasp "+
            "as it"+dam_descr);
         tell_watcher("The " + short() + " wielded by " +
            QCTNAME(wielder) + dam_descr, enemy);
         enemy->heal_hp(-dam);
      }
   }
   return 0;
}

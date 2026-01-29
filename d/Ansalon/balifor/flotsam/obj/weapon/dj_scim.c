/* by Gorr 20/12/96 */
/* updated 21/12/96 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <options.h>
#include "/d/Ansalon/common/defs.h"

object wielder;

create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    add_adj("ornamented");
    add_adj("curved");
    set_short("ornamented curved scimitar");
    set_long("@@long_desc");

    set_hit(45);
    set_pen(35);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,35) + 500);
    set_dt(W_SLASH);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_wf(TO);
    seteuid(getuid(TO));

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is a magic scimitar enchanted " +
            "by a renegate mage from one nomad tribes, living on the " +
            "Plains of Dust. It is possesed and guarded by Djinn " +
            "Azarel, Keeper of the Lamp. It is possible to get it " +
            "only by killing him and enduring his curse. " +
            "In hands of Djinn it is brawl-resistant.\n",15}));

    add_item(({"hilt","gems"}),"Some big, precious gems have been placed " +
       "in the hilt of the curved scimitar.\n");
    add_item(({"ornament","ornaments","beautiful ornaments"}),
       "Ornaments etched on the blade depict various strange monsters.\n");

    add_cmd_item(({"scimitar","sword"}),"swing","@@swing_scim");
    add_cmd_item(({"hilt","gems"}),({"rub","touch"}),"@@rub_hilt");
    add_cmd_item("blade","touch","@@touch_blade");

}

string
swing_scim()
{
    write("You swing your curved scimitar in the air, making a strange, " +
          "high-pitched noise.\n");
    say(QCTNAME(TP) + " swings the curved scimitar in the air, making " +
         "a strange, high-pitched noise.\n");
    return"";
}

string
rub_hilt()
{
    write("You rub the gems on the hilt of curved scimitar. They seem to " +
         "glow brightly.\n");
    say(QCTNAME(TP) + " rubs the gems on the hilt of curved scimitar. " +
         "They seem to glow slightly.\n");
    return"";
}

string
touch_blade()
{
    write("You touch the blade of your scimitar. It glows brightly and " +
           "the ornaments seem to move.\n");
    say(QCTNAME(TP) + " touch the blade of his scimitar. It glows " +
         "brightly and something seem to move on it.\n");
    return"";
}

string
long_desc()
{
    return"Long, curved blade of this vicious scimitar has some " +
          "beautiful ornaments on it. It it nearly two foot " +
          "long and it's hilt has been embelished with some valuable " +
          "gems. You can feel some magical aura pulsing inside this " +
          "weapon.\n";
}

mixed
wield(object what)
{
    wielder = this_player();
   set_alarm(1.0, 0.0, "wield_mes");
   return 0;
}

void
wield_mes()
{
    if(E(TO) != wielder)
        return;
   wielder->catch_msg("The curved scimitar glows brightly as you " +
        "firmly hold its grip.\n");

   tell_room(E(wielder),"The blade of " + QTNAME(wielder) + "'s curved " +
      "scimitar glows brightly, as " + PRONOUN(wielder) +
        " wields the weapon.\n", wielder);
}

mixed
unwield(object what)
{
   if ((E(TO)->id("azarel")) && (E(TO)->query_hp() > 0))
   {
       tell_room(E(E(TO)), QCTNAME(E(TO)) + " keeps hold of the" + short() +
                 ".\n", E(TO));
       return "You keep hold of your scimitar.";
   }
   wielder = TP;
   set_alarm(1.0, 0.0, "unwield_mes");
   return 0;
}

void
unwield_mes()
{
    if(!objectp(wielder))
        return;
   wielder->catch_msg("You feel cold as you unwield your scimitar.\n");

   tell_room(E(wielder), "The blade of " + QTNAME(wielder) +
      "'s curved scimitar becomes dimmed as " + PRONOUN(wielder) +
      " unwields the weapon.\n", wielder);
}

/* This code was adopted from Spiked Tessto by Arman */


static void
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;

   me = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (!ob[i]->query_option(OPT_BLOOD) && CAN_SEE_IN_ROOM(ob[i]))
      {
      if (CAN_SEE(ob[i], me))
         ob[i]->catch_msg(str);
      else
         tell_object(ob[i], "Someone is hit by someone.\n");
   }
   /*
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
   */
}


public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   object blinding;

   ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

   switch(phurt)
   {
      case -1:
      case -2:
      wielder->catch_msg("You swing your " + short() + " at " + QTNAME(enemy) +
         " but miss badly.\n");
      enemy->catch_msg(QCTNAME(wielder) + " swings the " + short() +
         " at you but misses badly.\n");
      tell_watcher(QCTNAME(wielder) + " swings the " + short() +
         " at " + QTNAME(enemy) + " but misses badly.\n", enemy);
      break;

      case 0:
      wielder->catch_msg("You slightly scratch " + QTNAME(enemy) + " with " +
         "your " + short() + ".\n");
      enemy->catch_msg(QCTNAME(wielder) + " scratches you slightly with the " +
         short() + ".\n");
      tell_watcher(QCTNAME(wielder) + " scratches " + QTNAME(enemy) +
         " slightly with the " + short() + ".\n", enemy);
      break;

      case 1..4:
      wielder->catch_msg("You graze the " + hdesc + " of " +
         QTNAME(enemy) + " with a hack of your " +
         short() + ".\n");
      enemy->catch_msg(QCTNAME(wielder) + " grazes your " + hdesc +
         " with a hack of the " + short() + ".\n");
      tell_watcher(QCTNAME(wielder) + " grazes the " + hdesc +
         " of " + QTNAME(enemy) + " with a hack of the " +
         short() + ".\n",enemy);
      break;

      case 5..9:
      wielder->catch_msg("You cut the " + hdesc + " of " +
         QTNAME(enemy) + " with your " + short() +
         ", bruising " + POSSESSIVE(enemy) +
         " " + hdesc + " fairly.\n");

      enemy->catch_msg(QCTNAME(wielder) + " cut the " + hdesc + " with a " +
         "with the " + short() + ", bruising it fairly.\n");
      tell_watcher(QCTNAME(wielder) + " cut the " + hdesc +
         " of " + QTNAME(enemy) + " with the " + short() +
         ", bruising it fairly.\n",enemy);
      break;

      case 10..19:
      wielder->catch_msg("You hurt " + QTNAME(enemy) + " rather badly with " +
         "a wicked blow of your " + short() + ", cutting a bloody trail " +
         "along " + POSSESSIVE(enemy) + " " + hdesc +
         " with curved blade.\n");
    enemy->catch_msg(QCTNAME(wielder) + " hurts you rather badly with " +
         "the " + short() + ", cutting a bloody trail along your " +
         hdesc + " with curved blade.\n");
      tell_watcher(QCTNAME(wielder) + " hurts " + QTNAME(enemy) +
         " rather badly with the " + short() + ", cutting a bloody trail " +
         "along the " + hdesc + " with curved blade.\n",enemy);
      break;

      case 20..29:
      wielder->catch_msg("You tear bloody chunks from the " +
         hdesc + " of " + QTNAME(enemy) + " with the blade " +
         "of your " + short() + ".\n");
      enemy->catch_msg(QCTNAME(wielder) + " tears bloody chunks " +
         " from your " + hdesc + " with the blade of the " + short() +
         "!\n");
      tell_watcher(QCTNAME(wielder) + " tears bloody chunks " +
         "from the " + hdesc + " of " + QTNAME(enemy) + " with the blade of " +
         "the " + short() + "!\n",enemy);
      break;

      case 30..49:
      wielder->catch_msg("You smash the " + hdesc + " of " +
         QTNAME(enemy) + " with a powerful swing of your " +
         short() + ", breaking some bones.\n");
      enemy->catch_msg(QCTNAME(wielder) + " smashes your " + hdesc +
         " with a powerful swing of the " + short() + ", breaking some " +
         "of your bones!\n");
      tell_watcher(QCTNAME(wielder) + " smashes the " + hdesc +
         " of " + QTNAME(enemy) + " with a powerful swing of the " +
         short() + ", breaking some bones!\n",enemy);
      break;

      case 50..69:
      wielder->catch_msg("You viciously smash the " + hdesc +
         " of " + QTNAME(enemy) +
         "with your " + short() + ", leaving bloody remains on your blade.\n");
      enemy->catch_msg(QCTNAME(wielder) + "viciously smashes your " +
         hdesc + " with the " + short() + ".\n");
      tell_watcher(QCTNAME(wielder) + " viciously smashes " +
         " the " + hdesc + " of " + QTNAME(enemy) +
         "with the " + short() + ".\n",enemy);
      break;

      case 70..89:
      wielder->catch_msg("You crash the " + hdesc + " of " +
         QTNAME(enemy) +
         " with a devastating blow of your " + short() + ".\n");
      enemy->catch_msg(QCTNAME(wielder) + " crashes your " +
         hdesc + " with a devastating blow of the " +
         short() + ". Things are starting to look dimmer, and " +
         "you feel you are loosing your consciousnes.\n");
      tell_watcher(QCTNAME(wielder) + " crashes the " + hdesc +
         " of " + QTNAME(enemy) + " with a " +
         "devastating blow of the " + short() + ".\n",enemy);
      break;

      default:
      wielder->catch_msg("You hear the sickening sound of bones " +
         "breaking, as your " + short() + " massacres the " + hdesc +
         " of " + QTNAME(enemy) + ". The blade penetrates deep " +
         "into flesh, leaving blood " +
         "flowing from deep gaping wound in the shattered limb.\n");
      enemy->catch_msg("You hear the sickening sound of your bones " +
         "breaking as " + QTNAME(wielder) + " massacres your " +
         hdesc + " with " + short() +
         ". The blade penetrates deep into your flesh, leaving blood " +
         "flowing from deep gaping wound in the shattered limb.\n");
      tell_watcher("You hear the sickening sound of bones breaking " +
         "as " + QTNAME(wielder) + " massacres the " + hdesc +
         " of " + QTNAME(enemy) + " with "
         + short() + ". The blade penetrates deep into the " +
         "flesh, leaving blood flowing " +
         "from the shattered limb.\n", enemy);
      break;

   }

   return 1;
}

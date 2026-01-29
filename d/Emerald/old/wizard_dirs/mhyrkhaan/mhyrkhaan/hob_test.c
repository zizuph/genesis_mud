/*
 * /d/Kalad/mhyrkhaan/hob.c
 * Purpose    : Magical sword that has a nice special.
 * Located    : NOT IMPLEMENTED.
 * Created By : Mhyrkhaan 20.Feb.97
 * Modified By: 
 * First Modif: 
 */                                                                            

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("broadsword");
   add_name(({ "sword", "broadsword", "humming", "soulscourge" }));
   set_adj("obsidian");
   add_adj("humming");
   set_short("humming obsidian broadsword");
   set_long("This sword is crafted of a long obsidian blade, that is "+
      "so fine along its edge, the obsidian is almost clear.  There "+
      "are silver runes that run along the blade's center down to the "+
      "onyx crossguard.  The handle is made of ebony, wrapped in fine "+
      "silver thread.  There is a wicked ruby spike topped by an onyx "+
      "claw on the pommel of the sword.  The sword is humming softly.\n");

   set_hit(50);
   set_pen(52);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_wf(TO);
   set_hands(W_BOTH);  /* a weapon over 40 must be wielded by both hands */

   /* for weight, volume, and value props.. follow the weapon manual 
      exactly... that way.. no problems at all with balance           */
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(50, 52)+
      random(200) - 50);
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 52)+
      random(300) - random(200));
   /* it cannot be purchased.. too powerful.. only sold */
   add_prop(OBJ_M_NO_BUY, 1); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_S_WIZINFO, "This is soulscourge, an ancient blade "+
      "forged by a conclave of warrior wizards for thier Warrior "+
      "King to carry into battle.  The sword contains one special "+
      "which is capable of up to 400 points of damage.\n");
   add_prop(MAGIC_AM_ID_INFO, ({"Your powers tell you the sword is "+
      "named Soul Scourge.  It seems to have a dark power of epic "+
      "proportions locked within its blade.\n", 10}));
   add_prop(MAGIC_AM_MAGIC, ({ 110, "enchantment" }));
}

static void
tell_watcher(string str, object enemy)
{
   object mee,
          *ob;

   int    i;

   mee = query_wielded();
   ob  = FILTER_LIVE(all_inventory(environment(mee))) - ({ mee });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (!ob[i]->query_option(OPT_BLOOD))
      ob[i]->catch_msg(str);
}

/* what does this function accomplish and when? */
int
war_cry(object ob)
{
   write("You grim mercilessly, as a feeling of power pulls through "+
      "you.\n");
   say(QCTNAME(TP) + " grins mercilessly, and grips the sword "+
      "tighter.\n");

   return 1;
}

mixed
unwield(object what)
{
   write("You unwield the " + query_short() + " and an overwhelming "+
      "sense of loss consumes you.\n");

   set_short("humming obsidian broadsword");

   return 1;
}

void
vorpal_slash(object enemy, object me)
{
   me->catch_msg("Your " + query_short() + " hums loudly as you "+
      "grip its hilt tightly and viciously slash " + QTNAME(enemy)+
      "!\n");
   enemy->catch_msg("The " + query_short() + " hums loudly as "+
      QTNAME(me) + " viciously slashes you!\nOuch that really HURT!\n");
   tell_watcher("The " + query_short() + " hums loudly as "+
      QTNAME(me) + " viciously slashes " + QTNAME(enemy) + "!\n", enemy);

   enemy->command("wail");
   me->command("cackle demo");
   /*  better idea to make the actual damage vary a little  */
   enemy->heal_hp(random(-200) + random(-200));

   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
}

int
special_attack(object enemy)
{
   object me = query_wielded();
   if(random(10))
      return 0;

   vorpal_slash(enemy,me);
      return 1;

   return 0;
}

public int
did_hit(int aid, string hdesc, int phurt, object enemy,
        int dt, int phit, int dam)
{
   string how,
          what,
          owhat,
          with,
          where;

   int    i_see_combat = 1;

   object me = query_wielded();

   if(special_attack(enemy))
      return 1; 

   if ((!objectp(enemy)) || (!objectp(me)))
   {
      return 1;
   }

   if (phurt == -1)
   {
      TP->add_panic(1); 
      if (i_see_combat)
      {
         me->catch_msg("You swing your " + query_short() + " viciously, "+
            "but hit nothing!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " swings " + HIS(me) + " "+
            query_short() + " viciously but hits nothing!\n");
      }

      tell_watcher(QCTNAME(me) + " swings " + HIS(me) + " "+
         query_short() + " vicously, but hits nothing!\n", enemy);

      return 1;
   }

   TP->add_panic(-3 - (phurt / 5));
   if(phurt > -1 && phurt < 5)
   {
      if (i_see_combat)
      {
          me->catch_msg("You lightly slash the " + hdesc + " of "+
             QTNAME(enemy) + " with your " + query_short() + ".\n");
      }

      if(interactive(enemy))
      {
          enemy->catch_msg(QCTNAME(me) + " lightly slashes your "+
             hdesc + " with " + HIS(me) + " " + query_short() + ".\n");
      }

      tell_watcher(QCTNAME(me) + " lightly slashes the " + hdesc + " of "+
         QTNAME(enemy) + " with " + HIS(me) + " " + query_short()+
         ".\n", enemy);

      return 1;
   }

   if(phurt > 4 && phurt < 10)
   {
      if (i_see_combat)
      {
         me->catch_msg("Your slash the " + hdesc + " of " + QTNAME(enemy)+
            " with your " + query_short + ".\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " slashes the your " + hdesc+
            " with " + HIS(me) + "the " + query_short() + ".\n");
      }

      tell_watcher(QCTNAME(me) + " slashes the " + hdesc + " of " +
         QTNAME(enemy) + " with " + HIS(me) + " " + query_short()+
         ".\n", enemy);

      return 1;
   }

   if(phurt > 9 && phurt < 20)
   {
      if (i_see_combat)
      {
         me->catch_msg("You slice a deep gash in the " + hdesc + " of "+
            QTNAME(enemy) + " with your " + query_short() + ".\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " slices a deep gash in your "+
            hdesc + " with " + HIS(me) + " " + query_short() + ".\n");
      }

      tell_watcher(QCTNAME(me) + " slices a deep gash in the "+
        hdesc + " of " + QTNAME(enemy) + " with " + HIS(me) + " "+
        query_short() + ".\n", enemy);

      return 1;
   }

   if(phurt > 19 && phurt < 30)
   {
      if (i_see_combat)
      {
         me->catch_msg("You slam your " + query_short() + " into the "+
            hdesc + " of " + QTNAME(enemy) + " with incredible force!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " slams " + HIS(me) + " "+
            query_short() + " into your " + hdesc + ", with incredible "+
            "force!\n");
      }

      tell_watcher(QCTNAME(me) + " slams " + HIS(me) + " "+
         query_short() + " into the " + hdesc + " of " + QTNAME(enemy)+
         ", with incredible force!\n", enemy);
      enemy->command("wince"); 

      return 1;
   }

   if(phurt > 29 && phurt < 50)
   {
      if (i_see_combat) 
      {
         me->catch_msg(QCTNAME(enemy) + " screams in agony as you "+
            "slash open " + HIS(enemy) + " " + hdesc + " with your "+
            query_short() + "!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg("Your scream in agony as " + QTNAME(me)+
            " slashes open your " + hdesc + " with his "+
            query_short() + "!\n");
      }

      tell_watcher(QCTNAME(enemy) + " screams in agony as "+
         QTNAME(me) + " slashes open " + HIS(enemy) + " "+
         hdesc + " with " + HIS(me) + " " + query_short()+
         "!\n", enemy);
      enemy->command("scream");

      return 1;
   }

   if(phurt > 49 && phurt < 70)
   {
      if (i_see_combat)
      {
         me->catch_msg("You rip apart " + QTNAME(enemy) + "'s "+
            hdesc + " with your " + query_short() + " sending bits of "+
            HIM(enemy) + " into the air!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " rips apart your "+
            hdesc + " with " + HIS(me) + " " + query_short()+
            " sending bits and pieces of you into the air!\n");
      }

      tell_watcher(QCTNAME(me) + " rips apart " + QTNAME(enemy) + "'s "+
         hdesc + " with " + HIS(me) + " " + query_short() + ", sending "+
         "bits of " + HIM(enemy) + " into the air!\n", enemy);

      return 1;
   }

   if(phurt > 69 && phurt < 90)
   {
      if (i_see_combat)
      {
         me->catch_msg("You slash " + QTNAME(enemy) + " with your "+
            query_short() + " so hard, you nearly sever "+
            HIS(enemy) + " " + hdesc + "! " + QTNAME(enemy)+
            "'s knees start to buckle.\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QTNAME(me) + " slashes you so hard  "+
            HE(me) + " nearly severs your " + hdesc + "! The world "+
            "begins to darken.\n");
      }

      tell_watcher(QTNAME(me) + " slashes the " + hdesc + " of "+
         QTNAME(enemy) + " so hard " + HE(me) + " nearly severs it! "+
         QTNAME(enemy) + "'s knees start to buckle.\n", enemy);

      return 1;
   }

   if(phurt > 90 && enemy->query_hp() <= 0)
   { 
      if (i_see_combat)
      {
         me->catch_msg("Your " + query_short() + " hums loudly and the "+
            "runes on it glow with a brilliant light as you slam your "+
            query_short + " into " + QTNAME(enemy) + "'s waist, "+
            "severing " + HIM(enemy) + " in two!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg("The " + query_short() + " hums loudly and "+
            "the runes on it glow with a brilliant light as "+
            QTNAME(me) + " slams his " + query_short + " into your "+
            "waist, severing you in two! The world goes black...\n");
      }

      tell_watcher("The " + query_short() + " hums loudly and the runes "+
         "on it glow with a brilliant light as " + QTNAME(me) + " slams "+
         "his " + query_short + " into " + QTNAME(enemy) + "'s waist, "+
         "severing " + HIM(enemy) + " in two!\n", enemy);
      me->command("cackle demo");

      return 1;
   }

   if(phurt > 90)
   {
      if (i_see_combat)
      {
         me->catch_msg("Bits and pieces of " + QTNAME(enemy) + " fly "+
            "everywhere as you massacre " + HIM(enemy) + " with your "+
            query_short() + "!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg("Bits and pieces of you fly everywhere "+
            " as " + QTNAME(me) + " massacres you with " + HIS(me)+
            " " + query_short() + "!\n");
      }

      tell_watcher("Bits and pices of " + QTNAME(enemy) + " fly "+
         "everywhere as " + QTNAME(me) + " massacres "+
         QTNAME(enemy) + " with " + HIS(me) + " " + query_short()+
         "!\n", enemy);

      return 1;
   }
}


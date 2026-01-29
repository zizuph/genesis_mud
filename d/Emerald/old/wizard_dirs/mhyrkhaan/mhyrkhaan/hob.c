/*
 * /d/Kalad/mhyrkhaan/hob.c
 * Purpose    : Magical sword that has a nice special.
 * Located    : NOT IMPLEMENTED.
 * Created By : Mhyrkhaan 20.Feb.97
 * Modified By: 
 * First Modif: 24.Feb.97 Rico
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

   set_hit(40);
   set_pen(40);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_wf(TO);
   set_hands(W_RIGHT);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(50, 52)+
      random(200) - 50);
   add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50, 52)+
      random(300) - random(200));
   add_prop(OBJ_M_NO_BUY, 1); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_S_WIZINFO, "This swod is a right handed only 40/40 "+
       "sword. It has one special capiable of 400 to 650 points of "+
       "damamge. You mus thave a sowrd skill of 65 or higher to use "+
       "it. It also has a alighment requirement of -100 or lower.\n");
   add_prop(MAGIC_AM_ID_INFO, ({"Your powers tell you the sword is "+
      "named Soulscourge. You let your link with the sword be cut "+
       "off early when you suddenly hear the screams of the souls "+
       "of Soulscourge's victems.\n", 10}));
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

wield(object what)
{
   if(TP->query_alignment() > 0)
   {
       write("A hollow booming voice echos in your head: Release me "+
       "from your blessed grasp, foul creature of God! Only those Dark of "+
       "heart may claim my prize!\n");
       return "You couldn't wield the broadsword.\n";
   }
  
   if(!(TP->query_skill(SS_WEP_SWORD) > 65))
   { 
       write("The sword pulses hums softly and you hear a voice in your head "+
       "say: Only those who are masters in the skill of the sword may "+
       "wield me.\n");
       say(QCTNAME(TP)+" was not worthy enough to wield the broadsword.\n");
       return "You couldn't wield the broadsword.\n";
   }
  
   write("You grasp the hilt of the sword in your hand "+
   "and can't help but grin as you join with this dark power.\n");
   say(QCTNAME(TP)+" grasps the hilt of the "+TO->query_short()+".\n");
   tell_room(E(TP),"The "+query_short()+" hums loudly!\n");
   TP->command("grin demo");
   set_short("humming obsidian broadsword");
   set_alarm(4.0,0.0,"war_cry",TP);
   return 1;
}
int
war_cry(object ob)
{
   write("You shiver as a feeling of power pulses through "+
      "you.\n");
   say(QCTNAME(TP) + " shivers, and grips the sword "+
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
   me->command("smirk dark");
   enemy->heal_hp(random(-400) + random(-250));

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
            " with your " + query_short() + ".\n");
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
            HIM(enemy) + " sailing into the air!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg(QCTNAME(me) + " rips apart your "+
            hdesc + " with " + HIS(me) + " " + query_short()+
            " sending bits and pieces of you sailing into the air!\n");
      }

      tell_watcher(QCTNAME(me) + " rips apart " + QTNAME(enemy) + "'s "+
         hdesc + " with " + HIS(me) + " " + query_short() + ", sending "+
         "bits of " + HIM(enemy) + " sailing into the air!\n", enemy);

      return 1;
   }

   if(phurt > 69 && phurt < 90)
   {
      if (i_see_combat)
      {
         me->catch_msg("You slash " + QTNAME(enemy) + " with your "+
            query_short() + " so hard, you nearly sever "+
            HIS(enemy) + " " + hdesc + "! \n " + 
            QTNAME(enemy)+ "'s knees start to buckle.\n");
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
         me->catch_msg("Your " + query_short() + " begins to hum louder and the "+
            "runes on it glow with a eerie light as you slam your "+
             query_short() + " into " + QTNAME(enemy) + "'s waist, "+
            "severing " + HIM(enemy) + " in two! The wailing spirit of "+
            QTNAME(enemy) +" rises from "+ HIS(enemy) +" corpse and is sucked "+
            "into your "+ query_short() +"!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg("The " + query_short() + " begins to hum louder and "+
            "the runes on it glow with a eerie light as "+
            QTNAME(me) + " slams his " + query_short() + " into your "+
            "waist, severing you in two! You feel a wrentching sensation "+
            "as the "+query_short()+" consumes your soul!\n");
      }

      tell_watcher("The " + query_short() + " begins to hum louder and the runes "+
         "on the blade glow with a errie light as " + QTNAME(me) + " slams "+
         "his " + query_short() + " into " + QTNAME(enemy) + "'s waist, "+
         "severing " + HIM(enemy) + " in two! The wailing spirit of "+ QTNAME(enemy)+
         "rises from "+ HIS(enemy) +" corpse and is sucked into "+ QTNAME(me) +
         "'s "+ query_short() +"!\n", enemy);
      me->command("cackle demo");

      return 1;
   }

   if(phurt > 90)
   {
      if (i_see_combat)
      {
         me->catch_msg("Bits and pieces of " + QTNAME(enemy) + " fly "+
            "everywhere as you descimate " + HIM(enemy) + " with your "+
            query_short() + "!\n");
      }

      if(interactive(enemy))
      {
         enemy->catch_msg("Bits and pieces of you fly everywhere "+
            " as " + QTNAME(me) + " decimates you with " + HIS(me)+
            " " + query_short() + "!\n");
      }

      tell_watcher("Bits and pices of " + QTNAME(enemy) + " fly "+
         "everywhere as " + QTNAME(me) + " decimates "+
         QTNAME(enemy) + " with " + HIS(me) + " " + query_short()+
         "!\n", enemy);

      return 1;
     }
 if(enemy->query_hp() <= 0)
      enemy->do_die(me);
}


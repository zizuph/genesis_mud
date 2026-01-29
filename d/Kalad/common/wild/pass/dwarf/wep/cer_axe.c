inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"

/* different variables */
int effect_ready; /* true if the special is ready again */
int effect_on;    /* true if the special is on */
int alarmid;      /* the alarmid for the special */
int last_align;   /* holds the align of wielder */

/* the following variables decides the power of this axe */
#define RESET_TIME 60.0
#define EFFECT_TIME 60.0
#define NORMAL_HIT 32
#define NORMAL_PEN 50
#define SPECIAL_HIT 52
#define SPECIAL_PEN 60

/* returns the colour that fits the last wielders alignment */
string
colour(int alignment)
{
   string str;
   str = "blinding white";

   if (alignment < 1000)
         str = "white";
   if (alignment < 800)
         str = "faint white";
   if (alignment < 600)
         str = "golden";
   if (alignment < 400)
         str = "faint golden";
   if (alignment < 200)
         str = "grey";
   if (alignment < 100)
         str = "faint grey";
   if (alignment < -100)
         str = "grey";
   if (alignment < -200)
         str = "faint dark";
   if (alignment < -400)
         str = "dark";
   if (alignment < -600)
         str = "faint black";
   if (alignment < -800)
         str = "black";
   if (alignment < -1000)
         str = "abyss black";

   return str;
}

/* by Korat */
create_weapon()
{
   ::create_weapon();
   set_name("waraxe");
   set_adj("ceremonial");
   add_adj("golden");
   set_long("This waraxe shines brightly with a golden colour, almost "+
      "blinding you so much that you have trouble to distinguish the intricate "+
      "decorations that is engraved upon the handle and the head of "+
      "the waraxe. You understand that this waraxe was ment "+
      "more for warcraft than for ceremonies.\n");

   add_item(({"decoration","decorations"}),
      "Several runes twists themselves along the oak-handle, "+
      "as the long and deadly body of a reptile. You also notice "+
      "that some smaller engraved runes curves along the edge of "+
      "the two blades that this double-bladed waraxe has.\n");
   add_item("runes",
      "Which runes do you want to study? The larger ones at the handle or "+
      "the smaller ones at the two blades?\n");
   add_item(({"larger runes","large runes"}),"@@large_runes@@");
   add_item(({"lesser runes","small runes"}),"@@small_runes@@");
   add_item("handle","The handle seems to be made of oak, and has "+
      "several large runes twisting along it.\n");
   add_item("head","The shining silvery colour of the metal shines "+
      "of power and strenght. The head of this two-headed waraxe must be made "+
      "of mithril! You see some small runes along the edges.\n");

   set_hit(NORMAL_HIT);
   set_pen(NORMAL_PEN);
   set_hands(W_BOTH);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   set_wf(TO);
   add_prop(OBJ_I_VALUE, 3000);
   add_prop(OBJ_I_WEIGHT, 20000);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VOLUME,12000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_S_WIZINFO, "This waraxe has been enchanted "+
      "to hit and penetrate better. It also has an ability "+
      "to become even more powerful when someone 'salute' with it, "+
      "making the axe become _very_ porwerful for a certain time. "+
      "To manage this, the player must have 60 in str and 75 in axe-"+
      "skill. In total, the axe can at max be this strong for "+
      "60 seconds, and must then reset for 60 seconds "+
      "before it is again ready to be 'saluted' with. The wielder of "+
      "this axe is /d/Kalad/common/wild/pass/dwarf/npc/kabal.c, a _very_ "+
      "hard npc to kill.\n          The axe will never show any "+
      "misses in combat, making it look even more powerful since the "+
      "combat-emotes shows only hits that does damage.\n");
   add_prop(MAGIC_AM_ID_INFO,({"The waraxe is magical\n", 5,
            "The waraxe has been enchanted to hit and penetrate more.\n",25,
            "The enchanted waraxe has been magically imbued to hit and ,"+
            "penetrate more. The only way to inherit the use of this power "+
            "is to slay its proper owner and command it "+
            "to release its magic.\n",35,
            "The enchanted waraxe has been magically imbued to hit "+
            "and penetrate more. The only way to inherit the use "+
            "of this power is to slay its proper owner and command it "+
            "to release its power. The magic will then be released in "+
            "bursts and has to rest for some time before it can be "+
            "summoned again.\n",55}));
   add_prop(MAGIC_AM_MAGIC, ({ 85, "enchantment" }));
   last_align=100;
}

string
large_runes()
{
   string str;
   str = "The runes twists themselves along the handle and reminds you "+
      "of the body of a snake. They emit a ";
   str = str + colour(last_align);
   return str + ", flaming colour.\n";
}

string
small_runes()
{
   if (effect_on)
      return "They emit such a blinding golden colour that it hurts "+
         "your eyes to watch them! All you saw was flickering "+
         colour(E(TO)->query_alignment()) + " flames burning your vision.\n";

   return "The runes emit a flickering " + colour(E(TO)->query_alignment()) +
      " light that has an hypnotic effect on you.\n";
}

mixed
wield(object what)
{
   /* check alignment as a wielding-test */
   int align;
   align = E(TO)->query_alignment();

   if ((last_align > 150 && align < last_align) ||
       (last_align < -150 && align > last_align))
   {
      E(TO)->catch_msg("When you try to wield the waraxe, "+
         "the "+ colour(last_align)+ " runes flares up! A strong heat burns "+
         "your hands, making you drop the waraxe.\n");
      TO->move(E(E(TO)));
      return -1;
   }

   /* the npc gets full power of the axe at all times */
   if(E(TO)->id("kabal"))
      {
      TO->set_hit(SPECIAL_HIT);
      TO->set_pen(SPECIAL_PEN);
      TO->set_dt(MAGIC_DT);
      E(TO)->update_weapon(TO);
      return 0;
   }
   E(TO)->catch_msg("The " + colour(last_align)+ " runes flares up, and slowly "+
      "change their colour. Soon the light is gone. You notice "+
      "that the runes has changed to a "+ 
      colour(E(TO)->query_alignment())+ " colour ...\n");

   last_align = align; /* wielders current align is now the align demanded by the axe. */
   return 0;
}

mixed
unwield(object what)
{
   TO->set_hit(NORMAL_HIT);
   TO->set_pen(NORMAL_PEN);
   TO->set_dt(W_SLASH | W_IMPALE);
   E(TO)->update_weapon(TO);
   return 0;
}

void
init()
{
   ::init();
   add_action("salute","salute");
   effect_ready = 1;
   effect_on = 0;
}

int
salute()
{
   object *enemies;
   if(!objectp(TO->query_wielded()))
      {
      write("You must wield the waraxe first.\n");
      return 1;
   }
   if(TO->query_wielded()->query_stat(SS_STR) < 60)
      {
      write("You try to lift the waraxe, but it is too heavy!\n");
      say(QCTNAME(TP)+" struggles to lift "+TP->query_possessive()+
         " ceremonial waraxe, but fails.\n");
      return 1;
   }
   if(sizeof(enemies = (TO->query_wielded())->query_enemy(-1)))
      write("You lift the ceremonial waraxe above your head, "+
      "and salute your enemies.\n");
   else
      write("You lift the ceremonial waraxe above your head, and salute all.\n");
   say(QCTNAME(TP)+" lifts the ceremonial waraxe above "+
      TP->query_possessive()+" head, and salutes "+
      "you.\n");
   set_alarm(3.0,0.0,"salute_effect");
   return 1;
}

void
salute_effect()
{
   int align;
   object wielder;
   wielder = TO->query_wielded();
   align = wielder -> query_alignment();

   if(alarmid)
      {
      if (objectp(wielder))
         write("The ceremonial waraxe still glows in a "+
         colour(align)+ " colour.\n");
      return;
   }
   if(!effect_ready)
      {
      write("The ceremonial waraxe feels cold in your rised hands.\n");
      return;
   }
   write("The ceremonial waraxe starts to glow in a "+ 
      colour(align) + " colour!\n");
   write("A blistering heat radiates out from the blade.\n");
   say("The blade of "+QTNAME(TO->query_wielded())+" suddenly glows in a "+
      colour(align)+ " colour, "+
      "radiating a blistering heat!\n");

   if (wielder -> query_skill(SS_WEP_AXE) < 75)
      {
      write("The heat surges through the shaft and burns you badly, "+
         "making you loose the grip on it!\n");
      say(QCTNAME(wielder)+" looses the grip on the waraxe. It "+
         "looks like "+wielder->query_pronoun()+" touched something hot!\n");
      say("The ceremonial waraxe falls to the ground.\n");
      wielder->heal_hp(-100);
      if(wielder->query_hp()<=0)
         {
         wielder->do_die(TO);
         return;
       }
      write("The waraxe falls to the ground.\n");
      TO->move(E(E(TO)));
      return;
   }
   TO->set_hit(SPECIAL_HIT);
   TO->set_pen(SPECIAL_PEN);
   TO->set_dt(MAGIC_DT);
   E(TO)->update_weapon(TO);
   effect_ready = 0;
   effect_on = 1;
   alarmid=set_alarm(EFFECT_TIME,0.0,"stop_effect");
}

void
stop_effect()
{
   int align;
   object wielder;
   wielder = TO->query_wielded();
   if (wielder)
      align = wielder -> query_alignment();
   else
      align = last_align;

   write("The " + colour(align) + " glow starts to fade away.\n");
   if (TO->query_wielded())
      write("You notice that the waraxe feels cold in your hands.\n");
   say("The " + colour(align) +  " glow from the ceremonial "+
      "waraxe seems to fade away.\n");
   TO->set_hit(NORMAL_HIT);
   TO->set_pen(NORMAL_PEN);
   TO->set_dt(W_SLASH | W_IMPALE);
   E(TO)->update_weapon(TO);
   alarmid = 0;
   effect_on = 0;
   call_out("reset_effect", RESET_TIME);
}

void
reset_effect()
{
   effect_ready = 1;
   if(TO->query_wielded())
      write("You notice warmth radiating out from the ceremonial "+
      "waraxe.\n");
}

void
tell_watcher(string str, object enemy)
{
   object me, *ob;
   int i;
   me = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i=0;i<sizeof(ob);i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

public
mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   int align;
   string str1, str2, str3;
   object wielder;
   object armour;
   wielder = TO->query_wielded();
   align = wielder -> query_alignment();
   
   /* the next will remove all miss-messages */
   if (dam < 1) return 1;
   if(!effect_on && !wielder->id("kabal"))
      {
      return 0;
   }
   
   /* the next will change the combat messages */
   switch (phurt)
   {
      case -2..0: return 1; break; /* removes miss-messages */
      case 1..5:
      str1 = "The waraxe flares up as it slashes the "+hdesc+" of "+
      QTNAME(enemy)+".\n";
      str2 = "The waraxe of "+QTNAME(wielder)+" flares up as it slashes "+
      "your "+hdesc+".\n";
      str3 = "The waraxe of "+QTNAME(wielder)+" flares up as it slashes "+
      QTNAME(enemy)+"'s "+hdesc+".\n";
      break;
      case 6..10:
      str1 = "Warm air embraces the "+hdesc+" of "+QTNAME(enemy)+" and burns "+
      enemy->query_objective()+".\n";
      str2 = "Warm air embraces your "+hdesc+" and burns you.\n";
      str3 = "Warm air embraces "+QTNAME(enemy)+"'s "+hdesc+" and burns "+
      enemy->query_objective()+".\n";
      break;
      case 11..19:
      str1 = "Your waraxe slices through "+QTNAME(enemy)+", "+
      "melting the armour on its way.\n";
      str2 = QCTNAME(wielder)+" slices "+wielder->query_possessive()+
      " waraxe through you, melting the armour on its way.\n";
      str3 = QCTNAME(wielder)+" slices "+wielder->query_possessive()+
      " waraxe through "+QTNAME(enemy)+", melting the armour on its way.\n";
      break;
      case 20..30:
      str1 = "The blistering "+ colour(align)+" heat from your waraxe envelopes the "+hdesc+" of "+QTNAME(enemy)+
      "and scorches it badly.\n";
      str2 = "A blistering "+ colour(align)+" heat envelopes your "+hdesc+" and scorches you badly.\n";
      str3 = "A blistering "+ colour(align)+" heat envelopes "+QTNAME(enemy)+"'s "+hdesc+
      "and scorches it badly.\n";
      break;
      default:
      str2 = "The "+ colour(align)+ " heat from "+TO->query_short()+" almost "+
      "shrivels your flesh from your bones!\n";
      str1 =  "The "+ colour(align)+" heat from your "+TO->query_short()+" almost "+
      "shrivels the flesh off "+QTNAME(enemy)+"'s bones!\n";
      str3 = "The "+ colour(align)+" heat from "+TO->query_short()+" almost shrivels "+
      "the flesh of "+QTNAME(enemy)+"'s bones!\n";
      break;
   }
   if (enemy->query_hp() <=0)
      {
      enemy->catch_msg("The waraxe of "+QTNAME(wielder)+" blazes up with a sudden "+
         "burst of "+ colour(align)+" flames that consumes your body.\n");
      wielder->catch_msg("Your waraxe blazes up with a sudden burst of "+
          colour(align)+" flames that consumes the body of "+QTNAME(enemy)+".\n");
      tell_watcher("The waraxe of "+QTNAME(wielder)+" blazes up with a sudden "+
         "burst of "+ colour(align)+" flames that consumes the body of "+QTNAME(enemy)+".\n",enemy);
      return 0;
   }
   enemy->catch_msg(QCTNAME(wielder)+" slashes out with "+HIS(wielder)+
      " waraxe against your "+hdesc+" in a wide arch.\n");
   enemy->catch_msg(str2);
   wielder->catch_msg(str1);
   tell_watcher(str3,enemy);
   if (phurt>1 && random(4))
      {
      switch (hdesc)
      {
         case "head": armour = enemy->query_armour(A_HEAD); break;
         case "body": armour = enemy->query_armour(A_BODY); break;
         case "left arm": armour = enemy->query_armour(A_L_ARM); break;
         case "right arm": armour = enemy->query_armour(A_R_ARM); break;
         case "legs": armour = enemy->query_armour(A_LEGS); break;
         default: break;
       }
      if(objectp(armour))
         enemy->catch_msg("The waraxe of "+QTNAME(wielder)+" sliced through "+
         "your "+armour->query_short()+" as if it was not there!\n");
   }
   return 1;
}

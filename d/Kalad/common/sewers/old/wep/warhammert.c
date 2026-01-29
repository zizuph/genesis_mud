inherit "/d/Kalad/std/weapon";
inherit "/cmd/std/command_driver";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int special_on;

#define MIN_TIME 20
#define EXTRA_TIME 20
#define HP_PUNISHMENT 400

create_weapon()
{
   ::create_weapon();
   set_name("warhammer");
   set_adj("titanium");
   add_adj("thorned");
   set_short("thorned titanium warhammer");
   set_long("@@my_long");
   add_item(({"handle"}),
     "The handle is wrapped with leather.\n");
   add_item(({"tip","thorn","thorns"}),
   "There are titanium thorns on the smashing bit of the "+
   "warhammer. You would hate to feel that smashing into "+
   "you and it's thorns driving into you.\n");
   set_hit(65);
   set_pen(70);
   set_wt(W_CLUB);
   set_dt(W_SLASH | W_IMPALE);
   set_wf(TO);
   add_prop(OBJ_I_VALUE,2800);
   add_prop(OBJ_I_WEIGHT,7000);
   add_prop(OBJ_I_VOLUME,5000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);

}


string
my_long()
{
   if(TO->query_wielded())
      return("This splendid warhammer is forged from titanium. "+
	      "Thorned spikes protrude from it's smashing end.\n");

   else
      return("This splendid warhammer is forged from titanium.\n");
}
/* --------------------------------------------------------- */
/*
* Check if the player can wield it or not.
*/

mixed
wield(object what)
{
     write("You grip the handle of the warhammer "+
      "to wield it. Thorned spikes "+
      "crank out of it's smashing head.\n");

   if (TP->query_base_stat(SS_DIS) > 80)
      if (TP->query_skill(SS_WEP_CLUB) > 90)
 
      {

      return 0;
   }

   return "The warhammer looks normal.\n"; 
}
/* *********************************************************8 */
wield_fail()   
{
   TP->heal_hp(-100);

   if(TP->query_hp() <= 0)
      {
  
      TP->do_die(TO);
   }
   write("Gasping for breath, you manage to force the black shadow away. You "+
      "feel rather tired and less healthy.\n");
   TP -> command("puke");
}
/* *************************************************** */

wield_success(object ob)
{

   TP->command("grin evil");
   return 1;
}
/* ***************************************************** 8*  */
mixed
unwield(object what)
{

/* This code is borrowed from Jeremiah. */
/* It will stop any brawling attempt when the High lord */
/* is wielding the whip. */

   if((E(TO)->query_hp() > 0))
   {
      tell_room(E(E(TO)), "The warhammer's spikes stay ...", E(TO));
      return "The warhammer cannot be unwielded!";
   }
   write("You release the warhammer.\n");
   return 0;
}

void
init()
{
   ::init();
   add_action("slash","whipslash");
   add_action("rattle","whiprattle");
   add_action("snap","whipsnap");
}


/*
* Function name: tell_watcher
* Description:   Send the string from the fight to people that want them
* Arguments:     The string to send
* This function is copied from Magebane (jagged scimitar) by Mercade.
*/

static void
tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = query_wielded();
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

/* This function will change the combat messages of the whip. */
/* It will also make a special attack if the whip makes damage */
/* on the head of the enemy. This special is add_attack_delay() */

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
   int which;
   float seconds;
   string mine_msg;
   string your_msg;
   string other_msg;
   object ishere;
   object head;
   object wielder = query_wielded();
   which=random(2);
   
   /* Change the combat messages */
   switch(phurt)
   {
      case -1:
      case -2:
      if (which == 0)
         {
         mine_msg="You swing after "+QTNAME(enemy)+", but you "+
         "miss utterly.\n";
         your_msg=QCTNAME(wielder)+" swings "+short()+
         " wildly after you, but misses utterly.\n";
         other_msg=QCTNAME(wielder)+" swings the "+short()+
         " at "+QTNAME(enemy)+", but misses utterly.\n";
         }
      else
         {
         mine_msg = "The tip of the "+short()+" sings as it cuts through "+
         "empty air.\n";
         your_msg = "The tip of "+QTNAME(wielder)+"'s "+short()+
         " sings as it cuts through empty air.\n";
         other_msg = "The tip of "+QTNAME(wielder)+"'s "+short()+
         " sings as it cuts through empty air.\n";
         }
      break;
      case 0:
      if (which = 0)
         {
         mine_msg = "When you slash down the "+short()+", "+QTNAME(enemy)+
         " sees it and deaftly sidesteps the lethal tip.\n";
         your_msg = "When "+QTNAME(wielder)+" slashes down the "+short()+
         " you see it coming and sidestep it with ease.\n";
         other_msg = "When "+QTNAME(wielder)+" slashes down the "+short()+
         ", "+QTNAME(enemy)+" sees it coming and steps aside.\n";
         }
      else
         {
         mine_msg = "With a scream you try to hit "+QTNAME(enemy)+
         " but the tip of the "+short()+" narrowly misses.\n";
         your_msg = "With a scream "+QTNAME(wielder)+" tries to hit "+
         "your "+ hdesc + ", but narrowly misses.\n";
         other_msg = "With a scream "+QTNAME(wielder)+" tries to hit "+
         QTNAME(enemy)+", but narrowly misses.\n";
         }
      break;
      case 1..5:
      if (which==0)
         {
         mine_msg = "Cunningly you slash the "+short()+" sideways and "+
         "leave a small bleeding mark on "+QTNAME(enemy)+"'s "+
         hdesc+".\n";
         your_msg = "Too fast for you to avoid it the "+short()+"'s tip "+
         "slashes towards you from the side, leaving a small "+
         "bleeding mark on your "+hdesc+".\n";
         other_msg = QCTNAME(enemy)+" fail to avoid the "+short()+"'s tip "+
         "and receives a small bleeding mark on "+
         enemy->query_possessive()+" "+hdesc+".\n";
         }
      else
         {
         mine_msg = "Your "+short()+" touches the flesh on "+QTNAME(enemy)+
         "'s "+hdesc+" and draws some blood.\n";
         your_msg = QCTNAME(wielder)+"'s "+short()+" touches your "+hdesc+
         " and draws some blood.\n";
         other_msg = QCTNAME(wielder)+"'s "+short()+" touches "+
            QTNAME(enemy)+"'s "+hdesc+" and draws some blood.\n";
         }
      break;
      case 6..10:
      mine_msg = "Your "+short()+" slices off a piece of flesh as it hits "+
      QTNAME(enemy)+"'s "+hdesc+".\n";
      your_msg = QCTNAME(wielder)+"'s "+short()+" slices off a piece of "+
      "flesh as it hits your "+hdesc+".\n";
      other_msg = QCTNAME(wielder)+"'s "+short()+" slices off a piece of "+
      "flesh from "+QTNAME(enemy)+"'s "+hdesc+".\n";
      break;
      case 11..20:
      mine_msg = "You raise the "+short()+" above your head and send "+
      "it hard down on "+QTNAME(enemy)+"'s "+hdesc+
      ", inflicting a bleeding wound.\n";
      your_msg = QCTNAME(wielder)+" raises the "+short()+" above "+
      wielder->query_pronoun()+" and then sends it hard down at your "+
      hdesc+", leaving behind a bleeding wound.\n";
      other_msg = QCTNAME(wielder)+ " raises the "+short()+" above the "+
      "head and sends it hard down on "+QTNAME(enemy)+"'s "+hdesc+
      ", inflicting a bleeding wound.\n";
      break;
      case 21..40:
      mine_msg = "The "+short()+" rips into the "+hdesc+" of "+
      QTNAME(enemy)+" and blood pours out.\n";
      your_msg = "The "+short()+" rips into your "+hdesc+
      " and blood pours out.\n";
      other_msg = "The "+short()+" rips into the "+hdesc+" of "+
      QTNAME(enemy)+" and blood pours out.\n";
      break;
      case 41..60:
      mine_msg = QCTNAME(enemy)+" screams as the "+short()+" tears into "+
      enemy->query_possessive()+" "+hdesc+". You can see white bones "+
      "through the inflicted wound.\n";
      your_msg = "You scream as the "+short()+" tears into your "+hdesc+
      ", and penetrates down to your bones.\n";
      other_msg = QCTNAME(enemy)+" screams as the "+short()+" tears into "+
      enemy->query_possessive()+" "+hdesc+". You can see white bones "+
      "through the inflicted wound.\n";
      break;
      case 61..80:
      mine_msg = "With devestating effect you hurl the tip of the "+
      short()+" down on "+QTNAME(enemy)+" and watch it dig into the "+
      hdesc+", tearing loose flesh and bones on its way.\n";
      your_msg = "In shock you watch the tip of the "+short()+" dig into "+
      "your "+hdesc+", tearing loose flesh and bones on its way.\n";
      other_msg = "With devastating effect "+QTNAME(wielder)+" hurls "+
      "the tip of the "+short()+" down on "+QTNAME(enemy)+"'s "+
      hdesc+", and watch it tear loose flesh and bones on its way.\n";
      break;
      case 81..90:
      mine_msg = "Your "+short()+" almost tore "+
      "through the "+hdesc+" of "+QTNAME(enemy)+".\n";
      your_msg = "The "+short()+" almost tore right through "+
      "your "+hdesc+".\n";
      other_msg = "The "+short()+" wielded by "+QTNAME(wielder)+
      " almost tore through the "+hdesc+" of "+QTNAME(enemy)+".\n";
      break;
      default:
      mine_msg = "With an enormous force you massacre "+QTNAME(enemy)+".\n";
      your_msg = "With an enormous force "+QTNAME(wielder)+" massacres "+
      "you.\n";
      other_msg = "With an enormous force "+QTNAME(wielder)+" massacres "+
      QTNAME(enemy)+".\n";

/* if the whip killed the enemy, the enemy is 'decaptivated' */

      if(enemy->query_hp() <= 0)
         {
         mine_msg = mine_msg+"You decapitated "+QTNAME(enemy)+".\n"+
         "You hear a chilling voice scream in your head in joy.\n";
         other_msg = other_msg+QCTNAME(wielder)+" decapitated "+
         QTNAME(enemy)+".\n";
         }
      else
         {
         mine_msg=mine_msg+"A voice whispers in your head: Sooooon "+
         "we will feeeasst on "+enemy->query_possessive()+" sooouul!\n";
         your_msg=your_msg+"A voice whispers in your head: Sooooon "+
         "I will feeeeasst on youuur sooouuul!\n";
         }
      break;
   }
   wielder->catch_msg(mine_msg);
   enemy->catch_msg(your_msg);
   tell_watcher(other_msg,enemy);

/* the rest is a check if a special attack should be added. */

   if (hdesc=="head" && phurt >0)
      {
      if(wielder->query_whimpy()!=0)
      {
         wielder->catch_msg("A voice from within your head "+
            "whispers to you: I will not help cooowardssss!\n");
      }
      else
      {
      if (enemy->query_hp()>0)
         {
         seconds = random(EXTRA_TIME)+MIN_TIME;
         enemy->add_attack_delay(seconds);
         enemy->catch_msg("When the "+short()+" touches your head, "+
            "a terrible pain runs through your mind, filling your "+
            "head with a penetrating blackness...\n");
         wielder->catch_msg("You feel a terrible force "+
            "flow from the handle of the "+short()+". It vibrates through "+
            "the black leather and seems to burst into "+QTNAME(enemy)+"'s head.\n");
         wielder->catch_msg("You feel your inner self being drained "+
            "of power.\n");
         tell_watcher(QCTNAME(enemy)+" screams up in pain. "+
            C(enemy->query_possessive())+" eyes seems "+
            "to grow black.\n",enemy);
         enemy->command("scream");
         if (!(wielder->query_npc()))
            set_alarm(0.0,0.0,"give_punishment",wielder);
       }
      }
   }
   return 1;
}

/* this function punishes the wielder when a special is done. */
/* it draws mana until there is no mana left, and then */
/* draws hp, and unwields itself. */

void
give_punishment(object who)
{
   int mana_left;
   int mana_draw;
   int spellcraft_skill;
   spellcraft_skill = who->query_skill(SS_SPELLCRAFT);
   mana_left = who->query_mana();

/* the mana taken is max 65 and min 33 mana-points.
*  This low penalty is here because the player _must_
*  be 'wimpy brave' to use this special.
*/

  mana_draw = ((100-spellcraft_skill)+100)/3;
   if (mana_left>mana_draw)
      who->set_mana(mana_left-mana_draw);
   else
      {
      who->set_mana(0);
      who->catch_msg("A chilling voice, soaked of loathing and hatreded, "+
         "penetrates your mind: Yoouur power over me has withered awayy! "+
         "Nooow I shall feeeasst on yooouur sooouul!\n");
      who->catch_msg("You suddenly feel something penetrate your palm.\n");
      set_alarm(7.0,0.0,"do_take_hp", who);
      tell_watcher(QCTNAME(who)+" suddenly turns very pale, small drops "+
         "of sweat runs down from the forehead. You shiver when you "+
         "see that "+who->query_possessive()+
         " eyes start to turn black.\n",who);
   }
}

/* the player has a small time to unwield the whip */
/* before the hp is taken. This punishment can then be */
/* avoided.              */

void
do_take_hp(object who)
{
   if (TO->query_wielded())
      {
      who->heal_hp(-HP_PUNISHMENT);
      who->catch_msg("A terrible pain runs through your body as your "+
         "lifeforce seems to trickle into the handle of the "+short()+
         ".\n");
      if (who->query_hp() <= 0)
         {
         who->catch_msg("Suddenly everything becomes black....\n");
         who->do_die(TO);
       }
      who->catch_msg("As sudden as the black void came, it "+
         "dissappears...and the voice in your mind fades away in dissapointment.\n");
      who->command("unwield "+short());
   }
}


/* An emote: Slash. started with 'whipslash' */

int
slash(string str)
{
   object who;
   object *victims;
   if (!(TO->query_wielded()))
      {
      write("You must wield the whip first!\n");
      return 1;
   }
   if (!str)
      {
      write("Slash who?\n");
      return 1;
   }
   victims = parse_this(str,"%l");
   if (sizeof(victims)==0)
      {
      write("You look around, but find nobody to slash.\n");
      return 1;
   }
   if (sizeof(victims)>1)
      {
      write("Who do you want to slash? Be more precise!\n");
      return 1;
   }
   /* try to find the victim of the slash */
   who = victims[0];
   TP->catch_msg("You slash "+QTNAME(who)+" with your whip, leaving "+
      "a bleeding scar on "+who->query_possessive()+" face!\n");
   TP->catch_msg("That person is marked for life!\n");
   who->catch_msg(QCTNAME(TP)+" lifts the whip above "+
      TP->query_objective()+"self, and slashes it down on your face!\n");
   who->catch_msg("A long reddish scar is left behind from the viciois slash!\n");
   tell_watcher(QCTNAME(TP)+" lifts the whip above "+
      TP->query_objective()+"self, and slashes it down on "+QTNAME(who)+
      "'s face. A long reddish scar is left behind from the "+
      "vicious slash!\n",who);
   return 1;
}

/* an emote: rattle. It is started with 'whiprattle' */

rattle() 
{
   if(!query_wielded(TO))
      {
      write("You must wield the whip first!\n");
      return 1;
   }
   write("You swing the whip around you in waveformed patterns, making "+
      "the needles on the tip to hit each other.\n");
   write("The whip rattles dangerously!\n");
   say(QCTNAME(TP) + " starts to swing the whip around " + TP->query_objective() + 
      "self.\n");
   say("The whip rattles dangerously around you!\n");
   return 1;
}

/* an emote: Snap. This is started with 'whipsnap' */

snap() /* this one is borrowed from Antharanos' coding */
{
   if(!query_wielded(TO))
      {
      write("You must wield the whip first!\n");
      return 1;
   }
   write("You raise the whip above you and snap it down.\n");
   write("The whip goes CRACK!\n");
   say(QCTNAME(TP) + " raises the whip above " + TP->query_objective() + "self and snaps it down.\n");
   say("The whip goes CRACK!\n");
   return 1;
}








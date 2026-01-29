// Shintor - aura sword
// file name: /d/Avenir/common/bazaar/Obj/wield/shintor.c
// creator(s): Ilyian May 1995
// purpose: Wielded by Jadestone Doll(/d/Avenir/common/bazaar/NPCS/jadestone.c)
// note: This sword, named Shintor, has a high hit/pen (50/50) when
//       activated, and also has a special attack that has a 1 in 5 chance of
//       occuring every combat round. The sword remembers the alignment
//       of the last creature it killed, and damage done
//       by the special in battle with the next creature is determined
//       by the alignment of the last creature is slew. Damage is
//       done with a hit_me on the enemy with the following formula:  
//       enemy->hit_me(ABS((align/230)) * 15, MAGIC_DT, query_wielded(), -1),
//       with a max penmod of 75.
//       (where align is the alignment of the last creature). Note that the
//       absolute value of the alignment is used, so that it
//       does not discriminate against whether the foe is good or
//       evil, merely _how_ good or evil it was. So while it is possible
//       to do damage with penmod 75 every 5 turns, the creature with
//       and alignment high enough to allow the sword to be in that
//       state are quite rare indeed. Any enemy with MAGIC_I_RES_FIRE > 80
//       or MAGIC_I_RES_MAGIC > 80 is immune to the special attack.
//       A wisdom > 90 + random (20) is required to wield the
//       weapon. A too low wisdom has the consequence of doing
//       random(1000) + 500 hp of damage in the attempt to wield,
//       so it can be quite deadly!
// bug(s):
// to-do: Make some sort of command that will mage the sword
//        generate either light or darkness based on the
//        aura that it is currently generating,
//        usable perhaps once per half-hour and making light/darkness
//        for 10 minutes.
//
// last update: Ilyian, updated the colours, fixed typos
//              Cirion, Feb 1996, added some emotes, wrote
//                the command word functionality, changed
//                damage from heal_hp to hit_me.
//              Manat, Feb 2001, changed so that read with no error
//                doesn't result in a runtime error.
//              Lilith, Mar 2003: Updated hit/pen per man wep guide
//              Gorboth, June 2011, Changed to prevent wield option from
//                              killing newbie-level players
//
//                   The weapon will no longer kill, and when failed
//                   wield or failure(command), the damage done will
//                   be asymptotic (query_hp() / 2), and do_die-routine
//                   is removed. Still dangerous though. 
//                   - Nerull 17.12-15
//          Lilith, Feb 2022: made a magic enhancer per AoB team.
// 
#pragma strict_types
#pragma save_binary

inherit "/d/Avenir/inherit/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <math.h>
#include <state_desc.h>
#include "/d/Avenir/common/common.h"

#define ROUNDS           5
#define PEN_NORMAL      40
#define HIT_NORMAL      45
#define PEN_SHIMMERING  50
#define HIT_SHIMMERING  50
#define WIS_TO_WIELD    78

string command_word = "";
int shimmering;
int lang_to_read = 25 + random(48);
string *colours = (({ "flaming black aura flickers about" ,
                      "hellish scarlet aura encloses" ,
                      "malignant blue light surrounds" ,
                      "menacing red fire is engulfing",
                      "dull yellow flame surrounds" ,
                      "flat grey aura encloses" ,
                      "sparkling green light shimmers about" ,
                      "shimmering blue aura enfolds" ,
                      "bright violet fire is engulfing" ,
                      "glorious silver aura surrounds" ,
                      "dazzling white aura burns about" }));

string *hurttype = (({ "engulfs" , "hammers" ,"burns" ,
                       "illuminates", "singes" , "shines on" ,
                       "singes" , "illuminates" , "burns" ,
                       "hammers" , "engulfs" }));

string *colourtype = (({  "black" , "scarlet" , "blue" , "red" , "yellow" ,
                          "grey" , "green" , "blue" , "violet" , "silver" ,
                          "white" }));

string *colouradj = (({ "deep abysmal" , "strong hellish" ,
                        "malignant and dark" , "menacing evil" ,
                        "corrupted dull" , "pale" , "sparkling and pure" ,
                        "shimmering and beautiful" , "bright" ,
                        "glorious sparkling" , "dazzling and holy" }));

int colournum, newnum;
string colour;

int total_attacks, total_damage; // To be removed when completely
                                 // debugged.

/* Function prototypes: */
string       my_long();
int          special_drop();
static void  tell_watcher(string str, object enemy);

int          set_colour(int num);   // For debuging
string       query_colour(); 

int          kiss_func(string arg);  // Emotions
int          swing_func(string arg);
int          hold_func(string arg);
int          point_func(string str);

int          do_read(string what);   // Command word functions
string       query_command();
int          do_say(string what);
void         shimmer(int how);

int          initialize();

void create_weapon()
{
  set_name("shintor");
  add_name(({"sword","longsword"}));
  add_name("_avenir_shintor");
  set_adj(({"steely"}));
  set_short("steely longsword");
  set_long("This sword is very thin and long, with the blade "+
           "suddenly tapering off to an infinitesimal point at the "+
           "end. The handle is of adamantine, molded to fit the "+
           "left hand with a narrow, decorative guard at the base "+
           "of the blade. Reflected in the polished surface of the "+
           "blade is a reverse image of the area around you. Some "+
           "flowing runes are etched along the blade. @@my_long@@\n");

  AI(({"rune","runes","writing"}),"The runes are written in "
           +"a strange flowing script.\n");
 
  set_magic_spellpower(45);  
  set_default_weapon(HIT_NORMAL,PEN_NORMAL,W_SWORD,W_SLASH,W_NONE,TO);

  set_likely_corr(8);
  set_hands(W_LEFT);
  set_keep(1);

  add_prop(OBJ_I_WEIGHT, 9000);
  add_prop(OBJ_I_VOLUME, 11000);
  add_prop(OBJ_I_VALUE, 23829);
  add_prop(MAGIC_AM_MAGIC,({78,"enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(OBJ_M_NO_BUY, "Such a fine weapon is too valuable to sell.\n");
  add_prop(OBJ_I_NO_DROP, "@@special_drop");

  add_prop(MAGIC_AM_ID_INFO,({
     "The "+short()+" seems to be quite magical.\n",1,
     "It takes the energy from the last creature it has slain.\n",10,
     "The energy is converted into an aura the "+
          "surrounds the wielder.\n",30,
     "The word to activate the aura is " + query_command() +".\n", 40,
     "Only the very wise can use this weapon.\n",50,
     "The power of the aura will strike back at the next victim.\n",70,
     "This weapon was forged in the depths of the Utterdark by the "+
        "legendary wizard Orestis.\n",80}));

  add_prop(OBJ_S_WIZINFO,"This sword when activated has a "+
        "high hit/pen (50/50), and also has a special attack "+
        "that has a 1 in "+ROUNDS+" chance of occuring every combat "+
        "round. The sword remembers the alignment "+
        "of the last creature "+
        "it killed, and damage done by the special in battle with "+
        "the next creature is determined by the alignment of the "+
        "last creature is slew. Damage is "+
        "done with a hit_me on the enemy with the following formula: "+
        "enemy->hit_me(ABS((align/230)) * 15, "+
        "MAGIC_DT, query_wielded(), -1), "+
        "with a max penmod of 75. "+
        "(where align is the alignment of the last "+
        "creature). Note that the "+
        "absolute value of the alignment is used, so that it "+
        "does not discriminate against whether the foe is good or "+
        "to do damage with penmod 75 every 5 turns, "+
        "the creature with "+
        "and alignment high enough to allow the "+
        "sword to be in that "+
        "state are quite rare indeed. Any enemy "+
        "with MAGIC_I_RES_FIRE > 80 "+
        "or MAGIC_I_RES_MAGIC > 80 is immune to "+
        "the special attack.\n");
}

string my_long()
{
    if(shimmering)
     return "The blade seems almost alive with "
           + colourtype[ colournum + 5] + " shimmering light.";
    else
     return "The blade is a dull steely colour.";
}

int special_drop()
{
    object  tp = ENV(TO);

    if (tp->query_npc() && tp->id("jadestone") && 
        !query_prop(OBJ_I_BROKEN) && tp->query_hp() > 400) 
        {
        tell_room(ENV(tp), QCTNAME(tp) + " holds tightly"
          +" to the handle of her "+query_short()+".\n", tp);
        return 1;
        }
    else
        return 0;
   // So the longsword can't be brawled from Jadestone Doll's
   // hands without some risk involved.
}

int wield(object to)
{
    if(!shimmering)  return 0;

    if (WIS(TP) < WIS_TO_WIELD)
      {
        TP->catch_msg("A horrible jolt of energy burns your hand as you "+
              "try to take hold of the blade.\nYou are badly burned.\n"+
              "You hear a soft voice intone: I do not suffer fools "+
              "to hold me.\n");

        ENV(TP)->catch_msg(QCTNAME(TP)+" tries to take hold of "+
              "the short and "+PRONOUN(TP)+" is momentarily "+
              "enshrouded in flames.\n");

		int w_damage = (TP->query_hp()) / 2;

		TP->heal_hp(-w_damage);


        //TP->heal_hp(-(random(1000) + 500)); // It can be deadly! !

        TP->command("scream");

       /* if (TP->query_hp() <= 0 )
        {
            /* We do NOT kill newbies this way! */
           /* if (!SD_IS_NEWBIE(TP))
            {
                TP->do_die(TO);
            }
        }*/

        return -1;
      }

    write("As you take hold of the "+short()+", you become "+
          "surrounded by a " + colouradj[ colournum + 5] + " " +
          colourtype[ colournum + 5] + " aura.\n");
    say("As "+QTNAME(TP)+" grasps the "+short()+", "+PRONOUN(TP)+
          " becomes surrounded by a " + 
          colouradj[ colournum + 5] + " " +
          colourtype[ colournum + 5] +
          " aura.\n");
    ENV(to)->add_subloc("_shimmering_sword_aura", this_object());
    return 1;
}

int unwield(object to)
{
    colournum = 0;
    ENV(to)->remove_subloc("_shimmering_sword_aura");

    if (!shimmering || !to ||
	(TP != ENV(TO)))
	return 0;

    write("As you release your grip on the "+short()+", your "+
          "aura fades away and you feel cold.\n");
    say(QCTPNAME(TP)+" aura fades away.\n");
    return 1;
}

void leave_env(object from, object to)
{
     ::leave_env(from, to);

     if(living(from) && shimmering)
       set_alarm(1.0, 0.0, &shimmer(0));

     if (living(from) )
        {
          from->remove_subloc("_shimmering_sword_aura");
          colournum = 0;
        }
}

string show_subloc(mixed subloc, object on, object who)
{
    if (subloc != "_shimmering_sword_aura" || !shimmering)
        return "";
    if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if (who == query_wielded())
       return "A " + colours[ colournum + 5] + " you.\n";
    else
       return "A " + colours[ colournum + 5] + " " +
                OBJECTIVE(ENV(TO))+".\n";
}

/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 *
 * This function shamelessly copied from magebane in the Shire.
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

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,
                     int phit,int dam)
{
  object wielder = query_wielded();
  int special_pen;
  int special_dam;
  int r = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

/*                    Begin special Attack                  */

/* one in ROUNDS (=5) chance of the special being activated each hit
 * while the sword is 'shimmering',
 * otherwise fight just like normal.
 */
 if (!random(ROUNDS) && shimmering)
    {
      int mres, fres;
      mres = enemy->query_magic_res(MAGIC_I_RES_MAGIC);
      fres = enemy->query_magic_res(MAGIC_I_RES_FIRE);

/*
 *       Let's check for fire and magic resistance.
 *       It will do no damage to anyone with
 *       MAGIC_I_RES_MAGIC > 80 or
 *       MAGIC_I_RES_FIRE > 80
 *       Otherwise, there is a completely random chance that
 *        any amount of fire or magic resistance will be able to
 *        deflect the special attack.
 *       Note: I give different messages when the special does not
 *        work, which is the way I think these things should work,
 *        for it gives players a little better idea how magic works.
 */

/* Check for magic resistance */
      if (random(80) < mres)
        {
      query_wielded()->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" and bounces harmlessly "+
           "off of the "+
           hdesc+" of "+QTNAME(enemy)+".\n");
      enemy->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" straight as your "+
           hdesc+"!\nYour magical protection saves you, and the "+
           "light bounces harmlessly off.\n");
      tell_watcher("A flash of "+
           colourtype[ colournum + 5] +
           " light leaps from "+QTPNAME(query_wielded())+
           " "+ short() +" and bounces harmlessly off the "+
           hdesc+" of "+QTNAME(enemy)+".\n",enemy);
      return r;
         }

/* Check for fire resistance */
  if (random(80) < fres)
        {
      query_wielded()->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" and strikes the "+
           hdesc+" of "+QTNAME(enemy)+".\n"+QCTNAME(enemy)+" seems "+
           "to absorb the light without harm.\n");
      enemy->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" straight as your "+
           hdesc+"!\nYou absorb the light without harm, thanks to "+
           "your protection from fire.\n");
      tell_watcher("A flash of "+
           colourtype[ colournum + 5] +
           " light leaps from "+QTPNAME(query_wielded())+
           " "+ short() +" and strikes the "+
           hdesc+" of "+QTNAME(enemy)+".\n"+QCTNAME(enemy)+" seems "+
           "to absorb the light without harm.\n",enemy);
      return r;
         }

/* The energy bolt got past the fire&magic resistance (if any), so it
 *  can now do damage based on its colournum.
 */
      special_dam = enemy->query_hp();

      special_pen = (ABS(colournum * 15));
      enemy->hit_me(special_pen, MAGIC_DT, query_wielded(), -1);

      special_dam -= enemy->query_hp();

/* For debugging:                  */
      if(query_wielded()->query_wiz_level())
          query_wielded()->catch_msg("Doing damage "+special_dam
                                +" with pen of "+special_pen+".\n");
      total_damage += special_dam;
      total_attacks++;

/* Now, if the special attack itself killed the enemy, then
 * the enemy will be commpletely burned and leave behind no
 * corpse, but just some ashes instead.  :)
 */
       if(enemy->query_hp() <= 0)
          {
           query_wielded()->catch_msg("A flash of " +
                  colourtype[ colournum + 5] +
                  " light leaps from the "+short()+" and "+
                  "utterly consumes "+QTNAME(enemy)+".\n");
           enemy->catch_msg("A flash of " +
                  colourtype[ colournum + 5] +
                 " light leaps from the "+short()+" and "+
                 "utterly consumes you.\n");
           tell_watcher("A flash of "+
                 colourtype[ colournum + 5] +
                  " light leaps from "+QTPNAME(query_wielded())+
                  " "+ short() +" and "+
                  "utterly consumes "+QTNAME(enemy)+".\n",enemy);
           enemy->add_prop(LIVE_I_NO_CORPSE, 1);
           seteuid(getuid(this_object()));
           clone_object(BAZAAR + "Obj/misc/ashes")->
                 move(ENV(query_wielded()),0);
           wielder->command("$hold shintor");
           }

/* Otherwise, we get the message that the bolt hit as normal.  */
   if(enemy->query_hp() > 0)
    {
      query_wielded()->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" and "+
           hurttype[ colournum + 5] +" the "+
           hdesc+" of "+QTNAME(enemy)+".\n");
      enemy->catch_msg("A flash of " +
           colourtype[ colournum + 5] +
           " light leaps from the "+short()+" and "+
           hurttype[ colournum + 5] + " your "+
           hdesc+"!\n");
      tell_watcher("A flash of "+
           colourtype[ colournum + 5] +
           " light leaps from "+QTPNAME(query_wielded())+
           " "+ short() +" and "+
           hurttype[ colournum + 5] + " the "+
           hdesc+" of "+QTNAME(enemy)+".\n",enemy);
       }
    }
/*              End Special Attack                   */

/*
 * Upon the killing blow, the sword will take
 * on the aura dependant on the alignment of the
 * creature it just killed. This will in turn determine
 * the amount of damage it will do with its
 * special attack
 */

if(enemy->query_hp() <= 0)
      {
/*     If the new alignment differed much from the last alignment killed,
 *     then your aura will change.
 */
       newnum = -(enemy->query_alignment())/150;

/* This will be required for very high or very low alignments,
 * or else the colorunum will go out of the bounds of the array:
 */
            if (newnum > 5)
              { newnum = 5; }
            if (newnum < -5)
              { newnum = -5; }
       if (newnum != colournum && shimmering)
           {
            ENV(TO)->catch_msg("Your aura changes from "+
                   colourtype[ colournum + 5] +
                  " to " + colourtype[ newnum + 5] + ".\n");

            colournum = newnum;
           }
/*   Otherwise not....        */
     }
    return r;
}

/* set_colour and query_colour are for debugging      */

int set_colour(int num)
{
  colournum = num;
  return 1;
}

string query_colour()
{
  return colourtype[ colournum + 5];
}

/* And now the emotes to make it more fun and interesting.  */
void
init()
{
   ::init();

/*  Emotions:  */
     add_action("kiss_func", "kiss");
     add_action("swing_func", "swing");
     add_action("hold_func", "hold");
     add_action("point_func", "point");

/*  Command word functions:  */
     add_action("do_say", "say");
     add_action("do_say", "shout");
     add_action("do_read", "read");
}

int hold_func(string arg)
 {
    string str;

    if(!shimmering) return 0;

    if(arg == "sword" | arg == "longsword" | arg == "shintor")
       {
       if (!query_wielded())
           {
              NF("You need to be wielding it to do that.\n");
              return 0;
            }
       write("You hold the "+short()+" aloft your head, basking in "+
             "its power.\nA "+colouradj[ colournum + 5]+" "+
             colourtype[ colournum + 5]+" flame "+
             "shoots down the sword, along your arm, and "+
             "encircles your body.\n");
       say(QCTNAME(TP)+" holds the "+short()+" aloft "+
            POSSESS(TP)+" head.\nA "+colouradj[ colournum + 5]+ " "+
            colourtype[ colournum + 5]+
            " flame shoots down the sword, along "+POSSESS(TP)+" arm, "+
            "and encircles "+POSSESS(TP)+" body.\n");
       TP->command("$cackle");
   return 1;
     }
  notify_fail("Hold what?\n");
  return 0;
 }

int kiss_func(string arg)
 {
    string str;

    if(!shimmering) return 0;

    if(arg == "sword" | arg == "longsword" | arg == "shintor")
       {
       if (!query_wielded())
           {
              NF("Nothing really happens.\n");
              return 0;
            }
       write("You hold the "+short()+" up to your lips and "+
             "kiss it gently.\nYour face is bathed in a "+
             colourtype[ colournum + 5]+" glow that warms you.\n");
       say(QCTNAME(TP)+" holds the "+short()+" up to "+
            POSSESS(TP)+" lips and kisses it gently.\n"+
            capitalize(POSSESS(TP))+" face flickers with an "+
            "eerie "+colourtype[ colournum + 5]+" glow.\n");
   return 1;
     }
  notify_fail("Kiss what?\n");
  return 0;
 }

int
swing_func(string arg)
 {
    string str;

    if(!shimmering) return 0;

    if(arg == "sword" | arg == "longsword" | arg == "shintor")
       {
       if (!query_wielded())
           {
              NF("You would need to be wielding it to do that.\n");
              return 0;
            }
       write("You swing the "+short()+" with all your might.\n"+
             "The "+short()+" makes a wide arc in the air, scattering "+
             "tendrils of "+
             colourtype[ colournum + 5]+" light everywhere.\n");
       say(QCTNAME(TP)+" swings the "+short()+" through the air.\n"+
            "The "+short()+" makes a wide arc in the air "+
            "scattering tendrils of "+
            colourtype[ colournum + 5]+" light everywhere.\n");
   return 1;
     }
  notify_fail("Swing what?\n");
  return 0;
 }

int point_func(string str)
{
  object enemy;   // Dummy object
  string dummy;

  if(!shimmering) return 0;

  if(!str || str == "")
   return 0;

  if(!parse_command(str, ENV(TP), "[the] [shimmering] 'longsword' / "+
        "'sword' / 'weapon' / 'shintor' %s", dummy))
    return 0;
 
  if(query_wielded() != TP)
   {
    write("You would need to be wielding it to do that.\n");
    return 1;
   }

  if(!parse_command(str, ENV(TP), "[the] [shimmering] 'longsword' / "+
        "'sword' / 'weapon' / 'shintor' 'at' [the] %o", enemy) 
     || !living(enemy) )
   {
    write("Point the "+short()+" at whom?\n");
    return 1;
   }

/* The only way to see if the creature has a 'neck', I think... */
  if(interactive(enemy) || function_exists("create_monster", enemy))
   {
     TP->catch_msg("You place the tip of your "+short()+" against the neck "
          +"of "+QTNAME(enemy)+".\nTiny arcs of "
          +colourtype[ colournum + 5]+" light dace around the edge "
          +"of your "+short()+".\n");
     enemy->catch_msg(QCTNAME(TP) + " places the tip of "
          +POSSESS(TP)+" "+short()+" against your neck.\nTiny arcs of "
          +colourtype[ colournum + 5]+" light dance along the "
          +short()+".\n");
     tell_room(ENV(TP), QCTNAME(TP) + " places the tip of "
          +POSSESS(TP)+" "+short()
          +" against "+QTPNAME(enemy)+" neck.\nTiny arcs of "
          +colourtype[ colournum + 5]+" light dance along the "
          +short()+".\n", ({TP, enemy}) );
     return 1;
    }

 /* No neck, so we just use the creature name.. */
  TP->catch_msg("You aim the tip of your "+short()+" towards "
       +QTNAME(enemy)+".\nTiny arcs of "
       +colourtype[ colournum + 5]+" light dace around the edge "
       +"of your "+short()+".\n");
  enemy->catch_msg(QCTNAME(TP) + " points the tip of "
       +POSSESS(TP)+" "+short()+" towards you.\nTiny arcs of "
       +colourtype[ colournum + 5]+" light dance along the "
       +short()+".\n");
  tell_room(ENV(TP), QCTNAME(TP) + " points the tip of "
       +POSSESS(TP)+" "+short()
       +" towards "+QTNAME(enemy)+".\nTiny arcs of "
       +colourtype[ colournum + 5]+" light dance along the "
       +short()+".\n", ({TP, enemy}) );
  return 1;
}

/*   Code for the command word  */

int do_say(string what)
{
   what = lower_case(what);

   if( what == "" || !what || shimmering || 
       ENV(TO) != TP || command_word == "" )
    return 0;

   if(what != command_word &&
      what != command_word + "." &&
      what != command_word + "!")
    return 0;

   set_alarm(1.0, 0.0, &shimmer(1));
   return 0;
}

int do_read(string what)
{
   string str;

   if (!stringp(what) || !strlen(what) ||
       !parse_command(what, ({}), "[the] 'runes' / 'rune' / " +
                      "'letter' / 'letters' / 'word' / 'words' %s", str))
   {
       NF("Read what?\n");
       return 0;
   }

   if(!parse_command(what, ({}), "[the] 'runes' / 'rune' / " +
      "'letter' / 'letters' / 'word' / 'words' 'on' [the] " +
      "[shimmering] / [steel] / [steely] 'longsword' / " +
      "'sword' / 'shintor' / 'weapon'"))
   {
       NF("Read the runes on what?\n");
       return 0;
   }

   if(TP->query_skill(SS_LANGUAGE) < lang_to_read)
   {
       TP->catch_msg("The runes are strange and beyond "+
          "your comprehension.\n");
       return 1;
   }
 
   TP->catch_msg("You make the runes out to represent " +
      "the word '"+CAP(query_command())+"'.\n");
   return 1;
}

string query_command()
{
   string *words =  ({ "nathisia", "angani", "perfal" ,
                       "terelin", "avenis", "tungal",
                       "oeresti", "penditan", "layisin",
                       "hamitar" });
   if(command_word == "")
      command_word = words[random(sizeof(words))];

   return command_word;
}

void shimmer(int how)
{
   object who;

   if(how == shimmering) return;
  
   if(how)
    {
      shimmering = 1;
      set_hit(HIT_SHIMMERING);
      set_pen(PEN_SHIMMERING);
      set_short("shimmering longsword");
      remove_adj(({"steel", "steely"}));
      add_adj(({"shimmering", "glowing"}));

      ENV(TO)->catch_msg("The "+short()+
       " begins to emit a faint hum, and tiny flashes"+
       " of light run along its blade.\n");

      if(who = query_wielded())
        {
         if (WIS(TP) < WIS_TO_WIELD)
          {
            who->catch_msg("Terrible jolts of energy "+
                        "burn your hand.\n"+
                        "You are badly burned.\n"+
                        "You hear a soft voice intone: "+
                        "I do not suffer fools "+
                        "to hold me.\n");
            ENV(who)->catch_msg(QCTNAME(who)+
                        " is momentarily "+
                        "enshrouded in flames.\n");

			int w_saydamage = (TP->query_hp()) / 2;

           // who->heal_hp(-(random(1000) + 500)); // It can be deadly!

			who->heal_hp(-w_saydamage);
            who->command("$scream");
            who->command("$drop shintor");
        
            //if (who->query_hp() <= 0 ) { who->do_die(TO); }
            return;
          }
       who->catch_msg("You are suddenly "+
          "surrounded by a " + colouradj[ colournum + 5] + " " +
          colourtype[ colournum + 5] + " aura.\n");
       ENV(who)->catch_msg(QCTNAME(who)+
          " becomes surrounded by a " + colouradj[ colournum + 5] + " " +
          colourtype[ colournum + 5] +
          " aura.\n");
       who->add_subloc("_shimmering_sword_aura", this_object());
       who->update_weapon(TO); // To update the combat object
       return;
        }
      return;
     }
   else
     {
      shimmering = 0;
      colournum = 0;
      ENV(TO)->catch_msg("The "+short()+
       " loses all colour and fades to a dull steely"+
       " sheen.\n");
      if(!living(ENV(TO)))
        tell_room(ENV(TO),"The "+short()+
           " loses all colour and fades to a dull steely"+
           " sheen.\n");
      set_hit(HIT_NORMAL);
      set_pen(PEN_NORMAL);
      set_short("steely longsword");
      remove_adj(({"shimmering", "glowing"}));
      add_adj(({"steel", "steely"}));

      if(query_wielded())
       {
         query_wielded()->catch_msg("Your aura fades away.\n");
         query_wielded()->update_weapon(TO); // To update the 
                                           // combat object
         query_wielded()->remove_subloc("_shimmering_sword_aura");
        }
      return;
     }
  return;
}

int initialize()
{
  colournum = -4;  // default colournumber so the first person
                   // to wield it (the npc) is very tough.
  shimmer(1);
  return 1;
}

void appraise_object(int num)
{
   ::appraise_object(num);
   write(item_spellpower_desc());
}

string stat_object()
{
  string str;
  int attacks;

  if(total_attacks < 1) 
    attacks = 1;
  else
    attacks = total_attacks;

  str = "\nColour number: "+colournum+" ("+colourtype[ colournum + 5]+
        ").\n"+
        "Special attack has hit "+total_attacks+" times, doing an \n"+
        "    average of "+total_damage / attacks+" hp of "+
        "damage each time.\n"+
        "Language required to read cmd word: "+lang_to_read+".\n";

  if(command_word == "")
    str += "Command_word has not yet been defined.\n";
  else
    str += "Command_word is "+command_word+".\n";

  return ::stat_object() + str + stat_object_spellpower();;
}

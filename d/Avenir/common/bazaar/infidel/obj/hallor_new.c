// creator(s): Cirion
// last update: January 1996
//              Lilith July 2003: fixed typos
// purpose: Magical club for Nochipa, Disciple of Alphum.
//         /d/Avenir/common/bazaar/infidel/mon/nochipa.c
// note:   Has hit/pen of (43/43), this weapon will drain fatigue
//         from enemy if it is a good hit. Does magic resistance
//         checks and even bounces drain back on the wielder if 
//         magic res is high enough. It will drain 50-75 fatigue
//         from the wielder once an hour-ish.
// Revisions:
// Cotillion, 2020-09-29 - Fixed type confusion
// Lilith, Sep 2021: Changed from 2H to 1H club, reduced the hit/pen, 
//         moved the do_fade() alarm out of the create_weapon() and into 
//         the wield() and unwield() functions so the alarm doesn't run 
//         when its not being used.

inherit "/std/weapon";
inherit "/lib/keep";

#include <language.h>
#include "/d/Avenir/common/common.h"

int fade_alarm = 0;
void do_fade();

public void
create_weapon(void)
{
    set_name(({"cudgel","club","hallor"}));
    set_adj(({"wooden", "wood", "kesoit"}));
    set_short("kesoit cudgel");
    add_name ("_this_is_hallor");
    set_long("This large cudgel of reddish-black kesoit wood hums "+
        "with a strange energy. Thin strands of adamantine metal "+
        "seem to somehow be woven into the wood of the club, making "+
        "a web-like pattern around its head. The handle is quite "+
        "short, and wrapped in white padded cloth to make for "+
        "a firm grip.\n");
    add_item(({"vein","veins","thread","threads","adamantine","metal","web"}),
        "The adamantine threads wrap around the club so tightly "+
        "that it bites into the wood. They cross over each other "+
        "many times, making them look like a web.\nThe threads "+
        "are warm with a faint red glow.\n");

    add_prop(OBJ_I_WEIGHT, 3200 );
    add_prop(OBJ_I_VOLUME, 2200 );
    add_prop(MAGIC_AM_MAGIC,({25,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_M_NO_BUY, "Such a fine weapon is too valuable to sell.\n");

    add_prop(MAGIC_AM_ID_INFO,({
        "The "+short()+" seems to be enchanted.\n",1,
        "It is from another dimension, and will drain the strength from "+
	    "your enemies.\n",10,
        "You must have some skill with clubs to use it.\n",20,
        "It was summond into existence by a powerful disciple of Alphum.\n",30,
	    "It's name is Hallor.", 40}));

    add_prop(OBJ_S_WIZINFO,"This "+short()+" is enchanted (25) to "+
        "have a hit/pen of 43/43. It has a special that drains enemies "+
        "of some fatigue (a maximum of -30 for a very good hit).\nIf "+
   	    "the enemy has MAGIC_I_RES_MAGIC, there is a good chance of "+
	    "resisting the effect, and if the enemy has MAGIC_I_RES_AIR, "+
	    "the effect may bounce back on the wielder.\nApprox each hour "+
        "(real time) Hallor will try to fade away, which takes ~50-75 "+
	    "fatigue from the wielder. You need a club skill of 40 to "+
	    "wield it.\nIt can be wielded in the left hand only.\n\n");
// one handed but only one can be wielded because it requires the left hand.
    set_default_weapon(43,43,W_CLUB,W_BLUDGEON,W_LEFT,TO);
    set_likely_dull(0);
    set_likely_corr(0);
    set_likely_break(0);
}

mixed
wield()
{
    if(TP->query_skill(SS_WEP_CLUB) < 40)
    {
        return "The metal threads around the "+short()+" suddenly"+
           " glow red hot, burning your hands.\n";
            TP->heal_hp(-50);
            TP->command("$drop _this_is_hallor");
        return -1;
    }
    write("You grasp the handle of the "+short()+".\nThe "+
        "adamantine threads glow warmly, molding the shape of "+
        "the handle to fit your hands.\n");
    say(QCTNAME(TP)+" grasps the handle of the "+short()+".\n");
  
    fade_alarm = set_alarm( 3000.0 , 3000.0 , do_fade); // once per hour-ish 
    return 1;
}

/* Costs 50-75 fatigue every hour or so that it is wielded */
void
do_fade()
{
    tell_room(ENV(TO),"The "+short()+
        " seems to fade and grow transparent for a moment,"+
        " but then becomes solid again.\n");
    if (living(ENV(TO)))
        tell_room(ENV(ENV(TO)),QCTNAME(ENV(TO))+"'s "+short()
           +" seems to fade and grow transparent for a"
           +" moment, then become solid again.\n",ENV(TO));
    if (query_wielded())
    {
        query_wielded()->catch_msg("You feel some of your energy "
		    +"being drawn away by the "+short()+".\n");
        query_wielded()->add_fatigue(-(50 +random(25)));
    }
    return;
}

void glow(object target, int power)
{
   string how, mesg;

   if(!query_wielded)
      return;
   if(!living(target))
      return;

   switch(power)
     {
        case 0 .. 4:
          how = "very faintly";
          mesg = "You feel slightly drained.\n";
          break;
        case 5 .. 8:
          how = "faintly";
          mesg = "You feel a bit weary.\n";
          break;
        case 9 .. 13:
          how = "dimly";
          mesg = "Your energy drains out from you.\n";
          break;
        case 14 .. 17:
          how = "softly";
          mesg = "You stumble slightly as you suddenly feel "
                +"rather tired.\n";
          break;
        case 18 .. 20:
          how = "gently";
          mesg = "You feel a little bit dizzy and rather tired.\n";
          break;
        case  21 .. 24:
          how = "brightly";
          mesg = "You feel your energy draining from your body.\n";
          break;
        case 25 .. 28:
          how = "fiercely";
          mesg = "You feel very dizzy and tired.\n";
          break;
        default:
          how = "painfully";
          mesg = "Your legs feel like lead as you feel your vitality "
                +"being drained away.\n";
          break;
      }

   tell_room(ENV(query_wielded()), "The adamantine veins on the "+short()+
       " glow "+how+" with a red light.\n");
   if(target->query_magic_res(MAGIC_I_RES_MAGIC) > random(10))
       {
         target->catch_msg("You feel the "+short()+" trying to "
           +"drain your energy, but your power resists it.\n");
         tell_room(ENV(target),QCTNAME(target) + " seems to "
           +"resist the glow.\n", target);
         return;
        }
    if(target->query_magic_res(MAGIC_I_RES_AIR) > random(15))
       {
         target->catch_msg("You feel the "+short()+" trying to "
           +"drain your energy-levels, but the powers around you "
           +"violently resist it.\n");
         tell_room(ENV(target), "The light from the "+short()
           +" seems to be thrown back from "+QTNAME(target)
           +" onto "+QTNAME(query_wielded())+".\n",
          (({query_wielded(), target})));
         query_wielded()->catch_msg("The light from the "+short()
           +" seems to be thrown back from "+QTNAME(target)
           +" onto you!\n"+mesg);
         query_wielded()->add_fatigue(-power);
         return;
        }
   target->catch_msg(mesg);
   target->add_fatigue(-power);
   return;
}


/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 * This copied from magebane.c in the Shire
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
  string Name = QCTNAME(wielder);
  string name = QTNAME(wielder);
  string names = LANG_POSS(name);
  string enem = QTNAME(enemy);
  string his = wielder->query_possessive();
  string club = short();

  ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

  if(hdesc == "legs")
    {
       if(random(2))
          hdesc = "left leg";
       else
          hdesc = "right leg";
     }

  switch(phurt)
  {
    case -1:
      query_wielded()->catch_msg("You swing the "+club+" harmlessly "+
        "through the air with all your might.\n");
      enemy->catch_msg(Name+" swings "+his+" "+club+
        " through the air before you.\n");
      tell_watcher(Name+" swings "+his+" "+club+
        " at "+enem+", but misses.\n",enemy);
      break;
    case 0:
      query_wielded()->catch_msg("You narrowly miss "+enem+
        " with the "+club+".\n");
      enemy->catch_msg(Name+" narrowly misses you "+
        "with "+his+" "+club+".\n");
      tell_watcher(Name+" swings the "+name+
        " at "+enem+" and narrowly misses.\n",enemy);
      break;
    case 1..15:
      query_wielded()->catch_msg("You gently bump the "+
        hdesc+" of "+enem+" with "+
        "your "+club+".\n");
      enemy->catch_msg("Your "+hdesc+
        " is gently bruised by "+names+" "+club+".\n");
      tell_watcher(Name+" bruises the "+hdesc+
        " of "+enem+" with "+his+" "+club+
        ".\n",enemy);
      glow(enemy, random(3));
      break;
    case 16..40:
      query_wielded()->catch_msg("You bump the "
        +hdesc+" of "+enem+
        " with your "+club+".\n");
      enemy->catch_msg("Your "+hdesc+" is bumped weakly by "+
        names +" "+names+".\n");
      tell_watcher(Name+" bumps the "+club+
        " into the "+hdesc+" of "+enem+".\n",enemy);
      glow(enemy, random(8));
      break;
    case 41..80:
      query_wielded()->catch_msg("You hurt the "+hdesc+
        " of "+enem+" with a good hit from the "+club+".\n");
      enemy->catch_msg(Name+" hurts your "+hdesc+
       " with a good hit from "+his+" "+
        club+".\n");
      tell_watcher(Name+" hurts "+
        "the "+hdesc+" of "+enem+" with a goot hit from "+
        his+" "+club+".\n",enemy);
     glow(enemy, random(8) + 10);
      break;
    default:
      query_wielded()->catch_msg("Your "+club+" smashes the "+
        hdesc+" of "+
        enem+".\n");
      enemy->catch_msg(Name+" smashes your "+hdesc+
        " with "+his+
        " "+club+".\n");
      tell_watcher(Name+" smashes the "+hdesc+
       " of "+enem+" with "+his+" "+
        club+".\n",enemy);
      glow(enemy, random(20) + 15);
      break;
  }
  return 1;
}


mixed 
unwield(object wep)
{
    remove_alarm(fade_alarm);
    return 0;
}

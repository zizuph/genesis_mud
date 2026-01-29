inherit "/d/Immortal/std/weapon";
#include <filter_funs.h>
#include <cmdparse.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Immortal/std/domain.h"
#include <ss_types.h>
#include <stdproperties.h>

int bladedir;

void
create_weapon()
{
  bladedir=1;
  set_name("dragon blade");
  add_name("drag_warr_blad");
  add_name("blade");
  set_short("dragon blade");
  set_long("The dragon blade is a strange weapon, seeming much like two "+
    "curved knife blades extending from each end of a handle.  The blades "+
    "are oriented in such a manner that both blades curve in the same "+
    "direction at once, one blade extending above the fist, one below.  "+
    "The blades are carved oddly, being of some strange type of steel, but "+
    "by all appearances seem to be some type of scaled reptile skin.  "+
    "Currently, the blades are curved "+"@@blade_direction@@"+".\n");

  set_hit(35);
  set_pen(25);
  set_wt(W_KNIFE);
  set_dt(W_SLASH | W_IMPALE);
  set_hands(W_ANYH);

  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()) +
    random(20) - 10);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(query_hit(),query_pen())+
    random(50)-25);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}

string
blade_direction()
{
  if(bladedir)
    return("inwards");
  else
    return("outwards");
}

void
init()
{
  ::init();
  add_action("spin","spin");
}

int
spin(string arg)
{
string hand;
object *obj;
  NF("Spin what?\n");

  if(!TO->query_wielded())
    return 0;

  if(!strlen(arg))
    return 0;

  if(sizeof(obj = FIND_STR_IN_ARR(arg, all_inventory(TP))) <1)
    return 0;

  if(member_array(TO,obj) <0)
    return 0;


  if(bladedir)
    {
    bladedir = 0;
    set_hit(25);
    set_pen(35);
    }
  else
    {
    bladedir = 1;
    set_hit(35);
    set_pen(25);
    }

  write("You skillfully spin the blade about your hand, regripping the "+
    "blade with a flourish, it's blades now facing "+blade_direction()+
    ".\n");
  say(QCTNAME(TP)+" skillfully spins "+
    ETO->query_possessive()+" dragon blade about his hand, regripping "+
    "the blade with a flourish, it's blades now facing "+
    blade_direction()+".\n");
  if(sizeof(obj) == 1 || TO == obj[sizeof(obj)-1])
    return 1;
  else
    return 0;
}

static void
tell_watcher(string str, object enemy)
{
  object me, *ob;
  int i;

  me = query_wielded();
  ob = FILTER_LIVE(all_inventory(environment(me))) - ({me});
  ob -= ({enemy});
  for(i = 0; i < sizeof(ob); i++)
    if(ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt, int phit,int dam)
{
   object wielder = query_wielded();
  if(bladedir == 1)
  {
  switch(phurt)
  {
    case -1:
      wielder->catch_msg("You harmlessly slice the air with the blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" harmlessly slices the air near "+
        "your throat with his blade.\n");
      tell_watcher(QCTNAME(wielder)+" harmlessly slices the air near "+
        QTNAME(enemy)+"'s throat.\n", enemy);
      break;

    case 0:
      wielder->catch_msg("You very narrowly miss slicing "+QTNAME(enemy)+
        " with the blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" very narrowly misses slicing "+
        "you with the dragon blade.\n");
      tell_watcher(QCTNAME(wielder)+" very narrowly misses slicing "+
        QTNAME(enemy)+" with the dragon blade.\n", enemy);
      break;

    case 1..5:
      wielder->catch_msg("You thinly slice "+QTNAME(enemy)+" in the "+
        hdesc+" with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" thinly slices your "+hdesc+
        "with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" thinly slices the "+hdesc+" of "+
        QTNAME(enemy)+" with the dragon blade.\n",enemy);
      break;

    case 6..10:
      wielder->catch_msg("You deeply slice "+QTNAME(enemy)+" in the "+
        hdesc+" with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" deeply slices your "+hdesc+
        "with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" deeply slices the "+hdesc+" of "+
        QTNAME(enemy)+"  with the dragon blade.\n", enemy);
     break;

    case 11..20:
      wielder->catch_msg("You cut deeply into "+QTNAME(enemy)+"'s "+
        hdesc+" with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" cuts deeply into your "+hdesc+
        " with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" cuts deeply into "+QTNAME(enemy)+
        "'s "+hdesc+" with the dragon blade.\n", enemy);
      break;

    case 21..40:
      wielder->catch_msg("You brutally carve into the "+hdesc+" of "+
        QTNAME(enemy)+" with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" brutally carves into your "+hdesc+
        " with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" brutally carves into the "+hdesc+
        " of "+QTNAME(enemy)+" with the dragon blade.\n", enemy);
      break;
      
    case 41..60:
      wielder->catch_msg("You viciously slash deep nto the "+hdesc+" of "+
        QTNAME(enemy)+" with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" viciously slashes deep into your "+
        hdesc+" with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" viciously slashes deep into the "+hdesc+
        " of "+QTNAME(enemy)+" with the dragon blade.\n",enemy);
      break;

    case 61..85:
      wielder->catch_msg("You find a tender spot with the dragon blade, "+
        "cutting through nerves in the "+hdesc+" of "+QTNAME(enemy)+".\n");
      enemy->catch_msg(QCTNAME(wielder)+" finds a tender spot with the "+
        "dragon blade, cutting through the nerves in your "+hdesc+".\n");
      tell_watcher(QTNAME(wielder)+" finds a tender spot with the dragon "+
        "blade, cutting through the nerves in the "+hdesc+" of "+QTNAME(enemy)+
        ".\n",enemy);
      break;

    default:
      wielder->catch_msg("You slip the dragon blade deep inside the "+
        hdesc+" of "+QTNAME(enemy)+", doing devastating damage to nerves, "+
        "and causing massive bloodloss.\n");
      enemy->catch_msg(QCTNAME(wielder)+" slips the dragon blade deep inside "+
        "your "+hdesc+", doing devastating damage to nerves, and causing "+
        "massive bloodloss.\n");
      tell_watcher(QTNAME(wielder)+" slips the dragon blade deep inside the "+
        hdesc+" of "+QTNAME(enemy)+", doing devastating damage to nerves, "+
        "and causing massive bloodloss.\n",enemy);
    break;
    }
  }
  if(bladedir== 0)
    {
    switch(phurt)
    {
    case -1:
      wielder->catch_msg("You harmlessly slice the air with the dragon "+
        "blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" harmlessly slices the air with "+
        "dragon blade.\n");
      tell_watcher(QCTNAME(wielder)+" harmlessly slices the air "+
        "near "+QTNAME(enemy)+"'s throat with the dragon blade.\n", enemy);
      break;

    case 0:
      wielder->catch_msg("You very narrowly miss slicing "+QTNAME(enemy)+
        "with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" very narrowly misses slicing "+
        "you with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" very narrowly misses slicing "+
        QTNAME(enemy)+" with the dragon blade.\n",  enemy);
      break;

    case 1..5:
      wielder->catch_msg("You thinly scrape the "+hdesc+" of "+QTNAME(enemy)+
        "with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" thinly scrapes your "+hdesc+
        "with the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" thinly scrapes the "+hdesc+" of "+
        QTNAME(enemy)+" with the dragon blade.\n", enemy);
      break;

    case 6..10:
      wielder->catch_msg("You scratcch the "+hdesc+" of "+QTNAME(enemy)+
        "with the dragon blade.\n");
      enemy->catch_msg(QCTNAME(wielder)+" scratches your "+hdesc+" with "+
        "the dragon blade.\n");
      tell_watcher(QTNAME(wielder)+" scratches the "+hdesc+" of "+
        QTNAME(enemy)+" with the dragon blade.\n", enemy);
      break;

    case 11..20:
      wielder->catch_msg("The dragon blade tears a rough gash into the "+
        hdesc+" of "+QTNAME(enemy)+".\n");
      enemy->catch_msg(QTNAME(wielder)+"'s dragon blade tears a rough gash "+
        "into your "+hdesc+".\n");
      tell_watcher(QTNAME(wielder)+"'s dragon blade tears a rough gash in "+
        "the "+hdesc+" of "+QTNAME(enemy)+".\n", enemy);
      break;

    case 21..40:
      wielder->catch_msg("You skillfully drag the dragon blade across the "+
        hdesc+" of "+QTNAME(enemy)+", tearing loose a thick ribbon "+
        "of flesh.\n");
      enemy->catch_msg(QTNAME(wielder)+" skillfully drags the dragon blade "+
        "across your "+hdesc+", tearing loose a thick ribbon of flesh.\n");
      tell_watcher(QTNAME(wielder)+" skillfully drags the dragon blade "+
        "across the "+hdesc+" of "+QTNAME(enemy)+", tearing loose a thick "+
        "ribbon of flesh.\n", enemy);
      break;

    case 41..60:
      wielder->catch_msg("With a masterful slash, you gouge a great bloody "+
        "furrow in the "+hdesc+" of "+QTNAME(enemy)+".\n");
      enemy->catch_msg("With a masterful slash, "+QTNAME(wielder)+" gouges "+
        "a great bloody furrow in your "+hdesc+".\n");
      tell_watcher("With a masterful slash, "+QTNAME(wielder)+" gouges "+
        "a great bloody furrow in the "+hdesc+" of "+QTNAME(enemy)+".\n",
        enemy);
      break;

    case 61..85:
      wielder->catch_msg("You slash the dragon blade mercilessly into the "+
        hdesc+" of "+QTNAME(enemy)+", where it catches and tears deep, "+
        "rending muscle from bone.\n");
      enemy->catch_msg(QTNAME(wielder)+" slashes the dragon blade "+
        "mercilessly into your "+hdesc+", where it catches and tears deep, "+
        "rending muscle from bone.\n");
      tell_watcher(QTNAME(wielder)+" slashes the dragon blade mercilessly "+
        "into the "+hdesc+" of "+QTNAME(enemy)+", where it catches and tears "+
        "deep, rending muscle from bone.\n", enemy);
      break;

    default:
      wielder->catch_msg(QTNAME(enemy)+" screams in agony as the dragon "+
        "blade tears a sizeable piece of the "+hdesc+" of "+
        QTNAME(enemy)+".\n");
      enemy->catch_msg("You scream in agony as the dragon blade "+
        "tears a sizeable chunk from your "+hdesc+".\n");
      tell_watcher(QTNAME(enemy)+" screams in pain as "+QTNAME(wielder)+
        " drives the dragon blade home, tearing a sizeable chunk from "+
        QTNAME(enemy)+"'s "+hdesc+".\n",enemy);
    break;
    }
  }


  hits++;
  if(F_WEAPON_CONDITION_DULL(hits, query_pens(), query_likely_dull()))
    {
    hits = 0;
    set_dull(query_dull() +1);
    }
  return 1;
}

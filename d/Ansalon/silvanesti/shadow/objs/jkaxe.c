#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <macros.h>
#include <stdproperties.h>
#pragma save_binary
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

inherit "/std/weapon";

string dadj;

nomask
create_weapon()
{
  set_name("battlemaster");
  set_short("jewelled keen battlemaster");
  set_long("@@long_desc");
  set_default_weapon(44,44,W_AXE,W_SLASH,W_ANYH);
  add_name("axe");
  add_name("battleaxe");
  add_pname("axes");
  add_pname("battleaxes");
  set_adj("jewelled keen");
  add_adj("jewelled");
  add_adj("keen");

  add_prop(OBJ_I_VOLUME,1500+random(10)*150);
  add_prop(OBJ_I_WEIGHT,2500+random(10)*200);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(45,45)*2);

  add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The battleaxe glows with magic.\n",10,
    "The jewels in the handle seem to be the source of the power.\n",20,
    "The weapon dislikes missing targets, and will hit more often.\n",50}));
  add_prop(MAGIC_AM_MAGIC,({70,"alteration"}));
  add_prop(OBJ_S_WIZINFO,"Changes bare misses into good hits.\n");
}

public varargs int
did_hit(int aid,string hdesc, int phurt, object enemy, int dt, int phit, int
dam)
{
  object attacker = query_wielded();
  if (phurt > 0 || random(5) == 0)
    return ::did_hit(aid,hdesc,phurt,enemy,dt,phit,dam);
  else
  {
    dam=random(50)+random(50)+random(50)+random(50)+random(50);
    enemy->set_hp(enemy->query_hp() - dam);
    if (dam < 50)
    {
      attacker->catch_msg("Sensing your swing would miss its target " +
        "your battleaxe moves itself just enough to barely scratch " +
        QTNAME(enemy) + ".\n");
      enemy->catch_msg("Just as you think you've avoided a blow, " +
        QTPNAME(attacker) + " battleaxe changes direction unexpectedly " +
        "and barely scratches you.\n");
      tell_room(E(enemy),"With an unnatural quickness, " + QTNAME(attacker) +
        " changes the direction of " + attacker->query_possessive() +
        " battleaxe to barely scratch " + QTNAME(enemy) + ".\n",  
        ({enemy,attacker}));
    }
    else if (dam < 100)
    {
      attacker->catch_msg("Sensing your swing would miss its target " +
        "your battleaxe moves itself to lightly scrape against " +
        QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg("Just as you think you've avoided a blow, " +
        QTPNAME(attacker) + " battleaxe changes direction unexpectedly " +
        "and lightly scrapes your " + hdesc + ".\n");
      tell_room(E(enemy),"With an unnatural quickness, " + QTNAME(attacker) +
        " changes the direction of " + attacker->query_possessive() +
        " battleaxe to lightly scrape " + QTPNAME(enemy) + " " + hdesc +
        ".\n",({attacker,enemy}));
    }
    else if (dam < 150)
    {
      attacker->catch_msg("Sensing your swing would miss its target " +
        "your battleaxe moves itself to strike firmly against " +
        QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg("Just as you think you've avoided a blow, " +
        QTPNAME(attacker) + " battleaxe changes direction unexpectedly " +
        "and strikes firmly against your " + hdesc + ".\n");
      tell_room(E(enemy),"With an unnatural quickness, " + QTNAME(attacker) +
        " changes the direction of " + attacker->query_possessive() +
        " battleaxe to strike firmly against " + QTPNAME(enemy) + " " +
        hdesc + ".\n",({attacker,enemy}));
     
    }
    else if (dam < 200)
    {
      attacker->catch_msg("Sensing your swing would miss its target " +
        "your battleaxe moves itself to slice a painful wound in " +
        QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg("Just as you think you've avoided a blow, " +
        QTPNAME(attacker) + " battleaxe changes direction unexpectedly " +
        "and slices a painful wound in your " + hdesc + ".\n");
      tell_room(E(enemy),"With an unnatural quickness, " + QTNAME(attacker) +
        " changes the direction of " + attacker->query_possessive() +   
        " battleaxe to slice a painful wound in " + QTPNAME(enemy) +
        " " + hdesc + ".\n",({attacker,enemy}));
    }
    else
    {
      attacker->catch_msg("Sensing your swing would miss its target " +
        "your battleaxe moves itself to viciously hack up " +
        QTPNAME(enemy) + " " + hdesc + ".\n");
      enemy->catch_msg("Just as you think you've avoided a blow, " +
        QTPNAME(attacker) + " battleaxe changes direction unexpectedly " +
        "and viciously hacks up your " + hdesc + ".\n");
      tell_room(E(enemy),"With an unnatural quickness, " + QTNAME(attacker) +
        " changes the direction of " + attacker->query_possessive() +  
        " battleaxe to viciously hack up " + QTPNAME(enemy) + " " + hdesc +
        ".\n",({attacker,enemy}));
    }
    return 1;
  }  
}
        
string
long_desc()
{
  return "an exquisite battleaxe.\n";
}

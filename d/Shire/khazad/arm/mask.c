inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/defs.h"
 
create_armour()
{
  set_name("mask");
  set_pname("masks");
  set_short("hideous dwarven mask");
  set_adj(({ "hideous", "dwarven" }));
  set_long("A great helm of thick steel crafted into "+
     "a fierce dwarven expression of hatred, pain, and agony. "+
     "Blood-red ruby eyes glare out at you from the blackened "+
     "steel mask. Your heart races as waves of adrenaline course "+
     "through your being. The mask's fearsome visage enthralls you "+
     "in an unblinking stare. Slowly you tear your rapt gaze from "+
     "this wonderous creation.\n");
 
  set_ac(40);
  set_at( A_HEAD );
  set_af(this_object());
 
  add_prop(OBJ_I_WEIGHT, 7000);
  add_prop(OBJ_I_VOLUME, 5000);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(MAGIC_I_RES_FIRE, 80);
}
 
mixed
query_magic_protection(mixed prop, object for_who)
{
  int add_protection;
  string race_name = TP->query_race_name();
  switch (race_name)
  {
    case "dwarf":
      add_protection = 40;
      break;
    case "goblin":
      add_protection = 0;
      break;
    default:
      add_protection = 20;
      break;
  }
 
  if (for_who == query_worn())
  {
    if (prop == MAGIC_I_RES_FIRE)
      return ({ add_protection, 1 });
    else
      return 0;
  }
 
  else
    return ::query_magic_protection(prop, for_who);
}
 
int
can_wear(string race_name)
{
  if (TP->query_prop("_i_can_wear_mask")) return 1;
  else if (TP->query_prop("_i_cant_wear_mask")) return 0;
  switch (race_name)
  {
    case "dwarf":
      return 1;
      break;
    case "human":
      if (random(100) > 50)
      {
        TP->add_prop("_i_can_wear_mask",1);
        return 1;
      }
 
      else
      {
        TP->add_prop("_i_cant_wear_mask",1);
        return 0;
      }
      break;
    default:
      if (random(100) > 30)
      {
        TP->add_prop("_i_can_wear_mask",1);
        return 1;
      }
 
      else
      {
        TP->add_prop("_i_cant_wear_mask",1);
        return 0;
      }
      break;
  }
}
 
wear(object ob)
{
  int i, add_dis;
  string race_name = TP->query_race_name();
  
  /* Check to see if the mask physically fits the player. The chance 
   * of if fitting depends on your race. The first time a player attempts                             
   * to wear the mask a prop will be added to them depending on if they
   * succeeded or failed to wear it. A player who succeedes in wearing
   * it once will always be able to wear it. Likewise a player who fails
   * to wear it will never be able to.
   *
   *			  Race  :  Chance to wear mask
   *			  ----------------------------
   *                      Dwarves	 100%
   *			  Humans  	 50%
   *			  Others  	 70%
   */

  i = can_wear(race_name);
  if (i == 0) return "The "+ short() +" does not fit properly.\n";

  /* If mask fits do this... */
  switch (race_name)
  {
    case "dwarf":
      write("You triumphantly don the "+ short() +" basking in "+
           "the respect it commands with its fearsome visage.\n");
      say(QCTNAME(TP) +" solemnly dons the "+ short() +".\n");
      add_dis = 10;
      break;
    case "human":
      write("You anxiously lower the "+ short() +" over your head.\n");
      say(QCTNAME(TP) + " quickly dons the "+ short() +".\n");
      add_dis = 8;
      break;
    case "goblin":
      write("You apprehensively lower the "+ short() +" over your "+
           "head.\n");
      say(QCTNAME(TP) +" timidly dons the "+ short() +".\n");
      add_dis = -5;
      break;
    default:
      write("You nervously lower the "+ short() +" over your head.\n");
      say(QCTNAME(TP) +" warily slides the "+ short() +" over his "+
           "head.\n");
      add_dis = 6;
      break;
  }
  TP->set_stat_extra(5, TP->query_stat_extra(5) + add_dis);
  TP->add_magic_effect(this_object());
  return 1;
}
 
remove(object ob)
{
  int remove_dis, remove_mana;
  string race_name;
  race_name = TP->query_race_name();
  switch (race_name)
  {
    case "dwarf":
      remove_dis = -10;
      remove_mana = -500;
      break;
    case "human":
      remove_dis = -8;
      remove_mana = -400;
      break;
    case "goblin":
      remove_dis = 5;
      remove_mana = -250;
      break;
    default:
      remove_dis = -6;
      remove_mana = -300;
      break;
  }
  TP->set_stat_extra(5, TP->query_stat_extra(5) + remove_dis);
  TP->remove_magic_effect(this_object());
  TP->add_mana(remove_mana);
  write("A pang of emptiness rushes over you as the "+
     short() +" is removed.\n");
  say(QCTNAME(TP) + " slowly removes the "+ short() +".\n");
  return 1;
}

/* The Nazgul's Mace */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_weapon() {
  set_name("mace");
  add_name("weapon");
  set_adj("black");
  set_long("This is a large black mace, ice-cold to the touch, made from\n"+
    "some strange metal unknown to you. Veins of inlaid gems line the\n"+
    "spiked head.\n");
  set_adj("heavy");
  set_default_weapon(50,50,W_CLUB,W_BLUDGEON,W_NONE,0);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO,({ "The black mace seems to be magical.\n",1,
    "It is a mace of Elf- and Man-slaying!\n",50 }));
  add_prop(OBJ_S_WIZINFO,"This mace is not yet working, and therefore not in the game yet.\n");
  add_prop(OBJ_I_WEIGHT,14500);
  add_prop(OBJ_I_VOLUME,7400);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(50,50)+random(200)-100);
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
  if (enemy->query_race_name()!="elf" && enemy->query_race_name()!="human")
    return 0;
  if (phurt == -1) {
    query_wielded()->catch_msg("You swing the black mace with all your might - through open air.\n");
    enemy->catch_msg("You deftly duck as "+QTNAME(query_wielded())+" swings "+
      query_wielded()->query_possessive()+" black mace at you.\n");
    }
  else
  if (phurt == 0) {
    query_wielded()->catch_msg("Your black mace just barely misses "+
      QTNAME(enemy)+"!\n");
    enemy->catch_msg("The black mace of "+QTNAME(query_wielded())+" just barely misses your head!\n");
    }
  else {
    query_wielded()->catch_msg("The black mace falls down on the puny "+
      enemy->query_race_name()+" with a mighty crush!\n");
    enemy->catch_msg("The black mace falls upon you with a mighty crush!\n");
    enemy->heal_hp(-dam);
    }
  return 1;
}

query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }


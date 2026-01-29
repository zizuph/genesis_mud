inherit "/std/weapon";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"

#define SPEED_MIN_SKILL 50


object quickness;
int alarm_id;
string speed_master;


void create_weapon() {
  set_name("speed");
  add_name(({"sword","scimitar","weapon"}));
  set_adj("black");
  set_adj("silver-edged");
  set_short("black silver-edged scimitar");
  set_pshort("black silver-edged scimitars");
  set_long("");
  set_default_weapon(50,38,W_SWORD,W_SLASH||W_IMPALE,W_RIGHT,TO);
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME,4000);
  add_prop(OBJ_I_VALUE, 3000);
}

mixed wield(object wep) {
  string race = TP->query_race_name();
  if ((race != "elf") && (race != "human"))
    return "Your hand is too small to grasp the hilt of "+
           "the "+short()+".\n";

  if((TP->query_skill(SS_WEP_SWORD) > SPEED_MIN_SKILL) &&
    (TP->query_skill(SS_2H_COMBAT) > SPEED_MIN_SKILL) &&
    (TP->query_skill(SS_DEFENCE) > SPEED_MIN_SKILL) &&
    (TP->query_skill(SS_PARRY) > SPEED_MIN_SKILL))
    {
      alarm_id = set_alarm(50.0, 50.0, "speed_check");
      write("You quickly wield the "+short()+".\n");
      SAY(" wields the "+short()+".\n");
      return 1;
    }

  else
    return "The "+short()+" seems to move by itself, and will "+
           "not enter your hand.\n";
}

int speed_check()
{
  if(TP->query_attack())
    return 0;
  if(TO->query_prop(OBJ_I_BROKEN))
    {
    remove_alarm(alarm_id);
    return 0;
    }

  if(((TP->query_stat(SS_INT)) + (TP->query_stat(SS_DEX)) +
     (TP->query_stat(SS_WIS)) - (TP->query_intoxicated()/3)) <
     (250+random(301)))
  {
    write("You feel the "+short()+" shiver in your hand as you hold it.\n"+
              "Your arms begin to tremble, shaking violently.\n"+
              "\n\nIn a flash of white light the "+short()+" disappears!\n");
    SAY(" begins to shake violently, unable to control the trembling.\n"+
           "You realize, the "+short()+" is the cause, as it sends spasms "+
           "through "+POSSESSIVE(TP)+" body.\nSuddenly, there is a flash "+
           "of light, and the "+short()+" is gone.\n");
    TO->remove_object();
    return 0;
  }
  else
  {
  write("The shaking begins again, the sword vibrates with a power "+
        "of its own.\n This time, you feel your body melding with the "+
        "vibrations of the "+short()+"!\n Your body rythm has increased "+
        "to that of the "+short()+".\n You feel a quickness you've "+
        "not felt before.\n");
 
  SAY(" begins shaking, a gleeful expression "+
      "crosses "+POSSESSIVE(TP)+" face as the shaking subsides.\n");
  if(ENV(TO) == TP)
    {
    TP->add_prop(LIVE_I_QUICKNESS, TP->query_prop(LIVE_I_QUICKNESS)+50);
    quickness = TP;
    }
  remove_alarm(alarm_id);
  return 0;
  }
}
 
mixed unwield(object wep)
{
  remove_alarm(alarm_id);
  if(objectp(quickness))
  {
    quickness->add_prop(LIVE_I_QUICKNESS,
             quickness->query_prop(LIVE_I_QUICKNESS)-50);
    quickness = 0;
  }
  return 0;
}

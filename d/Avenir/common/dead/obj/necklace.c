/* Necklace worn by the Naiad, and
 * thereby reward for the bury bones quest.
 *   Cirion, 100496
 *
 * modified 1998.05.26 Cirion: cleaned up the code, made
 *  the identify strings more descriptive of the effects
 *  of the object.
 *    Lilith Oct 2021: reduced value from 12,500 to 1200
 *           fixed typos and grammar. added set_keep(1);
 */

#pragma strict_types

inherit "/std/armour";
#include "/d/Avenir/common/common.h"

object wearer;

void create_armour()
{
  set_name("necklace");
  set_short("long coral necklace");
  set_adj(({"coral","long","blue","red","light","luminous"}));
  set_long("It is a long necklace made from pieces of "
    +"azure and carmine coral strung together with "
    +"a luminous filament. It feels heavier than "
    +"might be expected.\n");
  set_keep(1);
  set_default_armour(38, A_NECK);
  set_af(TO);

  add_prop(OBJ_I_WEIGHT,         2000); 
  add_prop(OBJ_I_VOLUME,          740); 
  add_prop(OBJ_I_VALUE,          1200);// value was 12,500
  add_prop(OBJ_I_IS_MAGIC_ARMOUR,    1); 
  add_prop(MAGIC_I_RES_WATER,       60); 
  add_prop(MAGIC_I_RES_EARTH,       85);

  add_prop(MAGIC_AM_MAGIC, ({ 20, "life", 40, "enchantment" }));
  add_prop(OBJ_S_WIZINFO, "This necklace "+
      "conveys the following resistances to "+
      "the wearer:\n"+
      "  MAGIC_I_RES_WATER: 55 (additive)\n"+
      "  MAGIC_I_RES_EARTH: 60 (additive)\n"+
      "  MAGIC_I_RES_MAGIC:  8 (non-additive)\n");

  add_prop(MAGIC_AM_ID_INFO,({
     "The "+short()+" is enchanted with the power of earth.\n",1,
     "Great protection is bestowed upon those who wears it.\n",10,
     "The necklace protects the wearer from most water-based attacks, be "+
     "they magical or natural.\n", 50,
     "The earth holds no power over they who "+
     "wear the necklace, for they shall be protected from it.\n",70}));
}

int wear(object to)
{
    TP->catch_msg("You feel a tingling sensation in your "
        + "throat as you wear the "+QSHORT(TO)+
          " around your neck.\n");
    say(QCTNAME(TP)+" wears "+
        LANG_ADDART(QSHORT(TO))+" around "+POSSESS(TP)+" neck.\n", 
        TP);
    if(wearer)
        wearer->remove_magic_effect(TO);

    TP->add_magic_effect(TO);
    wearer = TP;
    return 1;
}

int remove(object to)
{
   query_worn()->catch_msg("As you remove the "+QSHORT(TO)+
      ", the tingling sensation in your throat vanishes.\n");
   tell_room(ENV(query_worn()), QCTNAME(query_worn())+" removes "+POSSESS(query_worn())+
      " "+QSHORT(TO)+".\n", query_worn());
   query_worn()->remove_magic_effect(TO);
   wearer = 0;
   return 1;
}

void leave_env(object to, object from)
{
   ::leave_env(to, from);

   if(!living(from))
    return;

   from->remove_magic_effect(TO);
   wearer = 0;
}

mixed query_magic_protection(string prop, object what)
{
  object worn = query_worn();

  if(!worn || what != worn) return 0;

/*
 * NB: I put messages in the parts where you check the
 *     player's magic resistance, which will hopefully 
 *     look nice when it is checked.
 */
  switch(prop)
   {
     case MAGIC_I_RES_WATER:
      worn->catch_msg("Your "+QSHORT(TO)+
         " glitters with shimmering aquamarine light.\n");
      say(QCTNAME(worn)+"'s "+QSHORT(TO)+" glitters with "
         +"shimmering aquamarine light.\n", worn);
      return ({55, 1});
      break;

     case MAGIC_I_RES_EARTH:
      worn->catch_msg("Your "+QSHORT(TO)+
         " gleams dark blue.\n");
      say(QCTNAME(worn)+"'s "+QSHORT(TO)+" gleams dark blue.\n", worn);
      return ({60, 1});
      break;

     case MAGIC_I_RES_MAGIC:
      return ({8, 0});
      break;

     default: return 0; break;
   }

 return 0;
}

int dispel_magic(int power)
{
  if(power < query_magic_res(MAGIC_I_RES_MAGIC))
    return 0;

  if(living(ENV(TO)))
   {
    ENV(TO)->catch_msg("Your "+QSHORT(TO)+" suddenly "
     +"turns to water and melts away.\n");
    tell_room(ENV(ENV(TO)),
     QCTNAME(ENV(TO))+"'s "+QSHORT(TO)+" suddenly turns "
     +"to water and melts away.\n", ENV(TO));
    }
  else
    tell_room(ENV(TO), "The "+QSHORT(TO)+" suddenly turns "
     +"to water and melts away.\n");

  set_alarm(0.01, 0.0, remove_object);
  return 1;
}

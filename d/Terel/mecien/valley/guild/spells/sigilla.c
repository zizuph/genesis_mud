/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <comb_mag.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP           this_player()
#define TO           this_object()
#define ETO          environment(TO)
#define ETP          environment(TP)
#define ENV(xx)      environment((xx))

#define MANA_COST    30
#define LANG_LIM     60
#define MIN_POW       1
#define MAX_POW      17
#define RUNED_PROP   "mystic_runed"

public void check_props(object sword, int power, int time);
public void remove_runes(object sword, string oldshort, string oldlong,
                         int hit, int pen);

string *props;

nomask mixed
sigilla(string str)
{
   object sword, soot, who;
   string oldshort, oldlong, newshort, newlong;
   int hit, pen, time, power, suc;
   int *val;

   if (!str)
      return "Place runes upon what?\n";

   if (NPMAGIC(TP))
      return "Somehow your spell fails here.\n";

   if (TP->query_mana() < MANA_COST)
      return "You do not have the strength.\n";

   if (TP->query_skill(SS_LANGUAGE) < LANG_LIM)
      return "Only those with great understanding of language " +
             "can master the runes.\n";

   sword = present(str, TP);
   if (!sword)
       return "You have no such object.\n";
   if (!(sword->check_weapon()))
       return "Such is impossible.\n";
   if (sword->weapon_type() != "sword")
       return "Only swords may be so inscribed.\n";
   if (NPMAGIC(sword) || sword->query_lock())
       return "Somehow your spell fails.\n";
   if (sword->query_prop(RUNED_PROP))
       return "The " + sword->short() + " is already so runed.\n";
   if (!(sword->query_prop(MYSTIC_BLESSED)))
       return "The " + sword->short() + " must be blessed.\n";

   soot = present(MYSTIC_SOOT, TP);
   if (!soot)
       return "You will need some holy soot.\n";

   suc  = random(TP->query_skill(SS_FORM_ENCHANTMENT));
   suc += random(TP->query_skill(SS_ELEMENT_FIRE));
   suc += random(TP->query_stat(SS_WIS));
   val = (int *)sword->query_prop(MAGIC_I_RES_FIRE);
   if (pointerp(val)) suc -= val[0];
   if (suc < 50 + random(51))
       return "You fail to summon the ancient runes upon the blade.\n";

   oldshort = sword->query_short();
   newshort = "mystical-runed";
   oldlong = sword->query_long();
   newlong = "Fiery mystical letters span the length of the blade.\n";
   hit = sword->query_hit();
   pen = sword->query_pen();

   time = 70 + TP->query_skill(SS_ELEMENT_FIRE) +
          random(TP->query_skill(SS_FORM_ENCHANTMENT));
   power = 1 + random(5) + TP->query_skill(SS_ELEMENT_FIRE)/7;
   
   if (power < MIN_POW) power = MIN_POW;
   if (power > MAX_POW) power = MAX_POW;

   TP->catch_msg("You speak the cryptic words and trace the runes " +
                 "upon the blade.\n");
   tell_room(ETP, QCTNAME(TP) + " speaks cryptic words " +
             "and traces " + TP->query_possessive() + " fingers over the " +
             sword->short() + ".\n", TP);
   tell_room(ETP, "The " + sword->short() +
             " begins to burn with mystical runes.\n");

   sword->set_long(oldlong + newlong);
   sword->set_short(newshort + " " + oldshort);
   check_props(sword, power, time);
   sword->set_hit(hit + power);
   sword->set_pen(pen + power);
   who = sword->query_wielded();
   if (who) who->update_weapon(sword);
   set_alarm(itof(time), -1.0,
             &remove_runes(sword, oldshort, oldlong, hit, pen));
   soot->remove_object();
   TP->add_mana(-MANA_COST);
   return 1;
}

public void
check_props(object sword, int power, int time)
{
   sword->add_prop(RUNED_PROP, 1);
   props = ({ RUNED_PROP });
   if (!sword->query_prop(OBJ_M_NO_SELL)) {
       sword->add_prop(OBJ_M_NO_SELL, 1);
       props += ({ OBJ_M_NO_SELL });
   }
   if (!sword->query_prop(OBJ_I_IS_MAGIC_WEAPON)) {
       sword->add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
       props += ({ OBJ_I_IS_MAGIC_WEAPON });
   }
   if (!sword->query_prop(OBJ_S_WIZINFO)) {
       sword->add_prop(OBJ_S_WIZINFO, "This sword has been enhanced by " +
                       "increasing hit and pen with " + power +
                       " (duration: " + time + "). This is an effect of " +
                       "a Mystic spell called sigilla.\n");
       props += ({ OBJ_S_WIZINFO });
   }
   if (!sword->query_prop(MAGIC_AM_MAGIC)) {
       sword->add_prop(MAGIC_AM_MAGIC, ({ (3*power)/2, "enchantment" }));
       props += ({ MAGIC_AM_MAGIC });
   }
   if (!sword->query_prop(MAGIC_AM_ID_INFO)) {
       sword->add_prop(MAGIC_AM_ID_INFO,
                ({"This sword has been engraved by fiery magical runes. " +
                "It has become more powerful.\n", (3*power)/2}));
       props += ({ MAGIC_AM_ID_INFO });
   }
}

public void
remove_runes(object sword, string oldshort, string oldlong, int hit, int pen)
{
   int i;
   object who, where;

   if (!sword) return;

   who = sword->query_wielded();
   sword->set_hit(hit);
   sword->set_long(oldlong);
   sword->set_short(oldshort);
   sword->set_pen(pen);
   for (i=0; i<sizeof(props); i++) sword->remove_prop(props[i]);
   
   if (who) {
      tell_room(ENV(who), "The mystical runes upon the " + sword->short() +
                          " wielded by " + QTNAME(who) + " fade away.\n", who);
      who->catch_msg("The mystical runes upon the " + sword->short() +
                     " fade away.\n");
      who->update_weapon(sword);
   } else {
      where = ENV(sword);
      if (living(where)) {
         where->catch_msg("The mystical runes upon the " + sword->short() +
                          " fade away.\n");
      } else if (where->query_prop(ROOM_I_IS)) {
         tell_room(where, "The mystical runes upon the " + sword->short() +
                          " fade away.\n");
      }
   }
}

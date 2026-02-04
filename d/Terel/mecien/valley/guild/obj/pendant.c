/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()
#define ETO environment(TO)

public void
create_armour()
{
   set_name("pendant");
   set_adj("silver");
  add_name("star_pendant");
   set_long("A beautiful glimmering pendant of silver. It is fastened " +
      "to a long chain, upon its face is a four-pointed star that shines a " +
      "pale blue light.\n");

   add_prop("mystic_armour", 1);
   set_at(A_SHIELD);
   set_ac(10);
}

public string
wear_how(int where)
{
   string how, pos;

   if (this_player() == wearer)
      pos = "your";
   else
      pos = wearer->query_possessive();

   return " around " + pos + " neck and it hangs over " + pos + " chest";
}

public void
enter_env(object to, object from)
{
   ::enter_env(to, from);
   
   if (!living(to)) return;
   
   if (!MEMBER(to)) {
       to->catch_msg("A darkness seems to form around you and a " +
                     "sense that you should not keep the pendant " +
                     "in your possession grows within you.\n");
       set_alarm(5.0, -1.0, "heat", to);
   } else {
       if (to->query_mystic_rank() != MYSTIC_STAR) {
           set_alarm(3.0, -1.0, "wrong_rank", to);
       }
   }
}

public void
wrong_rank(object who)
{
   if (ETO == who) {
       who->catch_msg("The light of the star is not your circle.\n");
       remove_object();
   }
}

public void
heat(object who)
{
   if (ETO == who) {
       who->catch_msg("The "+short()+" is growing hot! It burns you.\n");
       who->heal_hp(-5);
       if (who->query_hp() <= 0) who->do_die(TO);
       set_alarm(5.0, -1.0, "melt_down", who);
   }
}

public void
melt_down(object who)
{
   if (ETO == who) {
       who->catch_msg("The "+short()+" is melting! It burns you severely.\n");
       who->heal_hp(-50);
       if (who->query_hp() <= 0) who->do_die(TO);
       remove_object();
   } else if (ETO->query_prop(ROOM_I_IS)) {
       tell_room(ETO, "The "+short()+" melts down and evaporates!\n");
       remove_object();
   }
}

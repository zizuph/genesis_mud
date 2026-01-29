/* created by Arman 2017 */


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit AC_FILE
inherit "/std/act/attack";

string
no_attack()
{

   TP->catch_msg("You approach " +QTNAME(TO)+ " and it flies off.\n");
   tell_room(environment(TP), QCTNAME(TP)+ " approaches " +
       QTNAME(TO)+ " and it flies off.", ({ TP }), TP);
   set_alarm(0.5,0.0, &remove_object());

   return "";
}

void
create_creature()
{
    int i;

    set_name("mantis");
    set_race_name("insect");
    set_adj("praying");
    set_short("praying mantis");

    set_gender(2);
    set_long("@@long_desc");

    set_stats(({10,10,10,1,1,10}));

    set_hp(5000);
    set_alignment(0);
    add_prop(OBJ_M_NO_ATTACK, "@@no_attack");

    NEVERKNOWN;

    set_attack_unarmed(1, 6, 22, W_SLASH,  50, "bite");

    set_hitloc_unarmed(1,  4, 90, "body");
    set_hitloc_unarmed(2, 3, 10, "head");


}

string
long_desc()
{
    if(IS_OOTS(TP))
    {
      if(!OOTS_QUERY_REV(TP, "majere"))
      {
        return "You notice a small green insect - a mantis - unmoving on " +
               "a leaf before you. Its two spiked, raptorial legs are bent " +
               "and held together at an angle as if praying. Its two large, " +
               "compound eyes seem to look at you... and you feel overwhelmingly " +
               "the desire to meditate with the mantis.\n";
      }
    }

   return "You notice a small green insect - a mantis - unmoving on " +
          "a leaf before you. Its two spiked, raptorial legs are bent " +
               "and held together at an angle as if praying.\n";
}


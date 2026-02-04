/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP    this_player()
#define ETP   environment(TP)

#define MANA_COST  90
#define CAST_LIMIT 80

public void
check_ember(object lamp)
{
    if (random(100) < 50 || !lamp)
        return;
    if (lamp->remove_ember())
        tell_room(environment(lamp), "The " + lamp->short() +
                                     " flickers and grows cold.\n");
}

nomask mixed
ignis()
{
   int    i, suc;
   object *all;
   object lamp = present(MYSTIC_LAMP, TP);

   if (TP->query_mana() < MANA_COST){
      write("You do not have the strength.\n");
      return 1;
   }
   
   if (!lamp)
       return "You need the sacred lamp.\n";
   
   if (!present("mystic_ember", lamp))
       return "Thy lamp must hold an ember of the sacred fire.\n";
   
   suc = random(TP->query_skill(SS_FORM_CONJURATION)) +
         random(TP->query_skill(SS_ELEMENT_FIRE));
   if (suc < CAST_LIMIT)
   {
      write("Your call to the sacred fire is unheard.\n");
      say(QCTNAME(TP) + " glows faintly.\n");
      return 1;
   }

   say(QCTNAME(TP) + " burns with a crimson light, " +
       TP->query_possessive() +
       " hands outstretch and fire fills this place!\n");
   write("You become the living focus of the sacred fire.\n");
   TP->add_mana(-MANA_COST);
   
   all = all_inventory(ETP);
   for (i=0; i<sizeof(all); i++)
   {
       if (!living(all[i])) continue;
       if (all[i]->query_prop(MYSTIC_BLESSED) || all[i] == TP)
       {
           all[i]->catch_msg("Flames rises up about you, but cause " +
                             "you no harm!\n");
       }
       else
       {
           all[i]->catch_msg("The fire scorches you!\n");
           all[i]->hit_me(70 + random(50) +
                          random(TP->query_skill(SS_ELEMENT_FIRE)),
                          MAGIC_DT, TP, -1);
           if (all[i]->query_hp() <= 0)
               all[i]->do_die(TP);
       }
   }
   set_alarm(5.0, -1.0, &check_ember(lamp));
   return 1;
}

/*
   battlestandard.c
   ----------------

   Coded ........: 95/07/05
   By ...........: Jeremiah

   Latest update : 95/07/05
   By ...........: Jeremiah


   Battle standard for the draconian armies.
*/


inherit "/std/weapon";

#include "/d/Krynn/common/defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"battle standard", "standard"}));
    set_adj("draconian");
    set_long("This is a draconian battle standard. A small blue " +
             "dragon, with its wings spread wide, adorns the top " +
             "end of a wooden pole. A large, blue, gold bordered " +
             "banner, decorated with a five headed dragon, is fixed " +
             "to the pole. The pole itself is decorated with " +
             "intricate carvings and golden ornaments.\n");

    set_default_weapon(15, 15, W_POLEARM, W_BLUDGEON , W_BOTH);
    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_M_NO_INS, "The battle standard is too tall to fit.\n");  
}


mixed
wield(object what)
{
   if (TP->query_race_name() == "draconian")
   {
      TP->add_prop(LIVE_S_EXTRA_SHORT, " carrying a battle standard");
      TP->add_item("standard", "A draconian battle standard. A blue " +
                   "banner decorated with a five headed dragon.\n");
   }
   return 0;
}


mixed
unwield(object what)
{
   if (TP->query_race_name() == "draconian")
   {
      TP->remove_prop(LIVE_S_EXTRA_SHORT);
      TP->remove_item("standard");
   }
   return 0;
}

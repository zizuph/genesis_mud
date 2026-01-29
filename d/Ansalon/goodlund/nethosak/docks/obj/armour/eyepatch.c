/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/armour/eyepatch.c
 *
 * glain
 *
 * Eyepatch that is worn by the captain of Stormseeker.  Lost his
 * eye in an arena dagger fight that took a turn for the worse.
 * Will add emotes to it as I think of them.
 *
 */
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

int worn;

void 
create_armour()
{
   set_name("patch");
   set_adj("eye");
   add_adj("black");
   set_short("black eye patch");
   set_ac(1);
   set_at(A_HEAD);
   set_long("This is a black leather eye patch used to cover up " +
      "the gruesome sight of a missing eye.\n");

   add_prop(OBJ_I_VOLUME, 10);
   add_prop(OBJ_I_WEIGHT, 10);

   /*add_cmd_item("kilt", "lift", "@@lift_kilt");*/

   set_af(TO);

   worn = 0;
}


/* 
 * Function name: wear
 * Description  : Sets the worn variable to true.
 * Arguments    : what - some object???
 * Returns      : int 0 - go ahead as normal
 *
 */
mixed
wear(object what)
{
   worn = 1;

   return 0;
}


/* 
 * Function name: remove
 * Description  : Sets the worn variable to false.
 * Arguments    : what - some object???
 * Returns      : int 0 - go ahead as normal
 *
 */
mixed
remove(object what)
{
   worn = 0;

   return 0;
}


/* 
 * Function name: lift_kilt
 * Description  : Lets the wearer show of his arse.
 * Returns      : string - a empty string
 */
string
lift_kilt()
{
   if (worn)
   {
      write("You lift your kilt up displaying your bare arse to " +
         "everyone.\n");

      say(QCTNAME(TP) + " lifts " + HIS(TP) + "kilt up displaying " +
         HIS(TP) + " bare arse to everyone.\n");
   
      return "";
   }

   return "Why do that?\n";
}
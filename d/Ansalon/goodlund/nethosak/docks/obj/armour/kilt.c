/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/armour/kilt.c
 *
 * glain
 *
 * Standard kilt worn by all minotaurs.  Will prolly move this file
 * up a dir.  Should this be A_LEGS or A_ROBE??
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
   set_name("kilt");
   set_adj("thin");
   add_adj("cloth");
   set_short("thin cloth kilt");
   set_ac(1);
   set_at(A_ROBE);
   set_long("This kilt is common dress among the minotaurs.  It " +
      "is made from very light cloth and provides some minor " +
      "protection to the legs.  Just be careful not to lift " +
      "it up to high, wouldn't want to embarrass yourself.\n");

   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(1, A_ROBE));

   add_cmd_item("kilt", "lift", "@@lift_kilt");

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
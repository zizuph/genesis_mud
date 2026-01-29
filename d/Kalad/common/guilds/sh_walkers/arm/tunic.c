/*
 * /d/Kalad/common/guilds/sh_walkers/arm/silk_tunic.c
 * Created By :  Sarr
 * Modified By:  Rico
 * First Modif:  13.12.96
 */

inherit "/d/Kalad/std/armour";

#include "/d/Kalad/defs.h"
#include "../defs.h"

string
random_color()
{
   int i = random(6);
   switch(i)
   {
      case 0:
         return "blue";
         break;

      case 1:
         return "white";
         break;

      case 2:
         return "green";
         break;

      case 3:
         return "red";
         break;

      case 4:
         return "black";
         break;

      default:
         return "yellow";
   }
}

void
create_armour()
{
   ::create_armour();

   set_name("tunic");
   set_adj("silk");
   add_adj(random_color());
   set_short(random_color() + ", silk tunic");
   set_long("This is a well-made, silk tunic with a solid color "+
      "pattern.  It looks as though a great deal of effort was "+
      "put into weaving it.  It must be very comfortable... and "+
      "expensive.\n");

   set_ac(1);

   set_at(A_TORSO);

   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 80);
   add_prop(OBJ_I_VALUE, 80);
}


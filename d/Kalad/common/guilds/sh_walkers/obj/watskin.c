/*
 * /d/Kalad/common/guilds/sh_walkers/obj/watskin.c
 * Created By : Rico 7.01.97
 * First Modif:
 */

inherit "/std/waterskin_1";

#include <stdproperties.h>
#include <macros.h>

public void
create_drink()
{
   set_name(({ "skin", "waterskin", "leather waterskin",
      "leather skin" }));
   add_adj("leather");

   add_prop(OBJ_I_WEIGHT, "@@my_weight");
   add_prop(OBJ_I_VOLUME, "@@my_volume");
   add_prop(OBJ_I_VALUE, 100);

   set_max_fill(3400);		/* 5 l maximum filling */
   set_filled(3400);
}

public string
long(string str)
{
   string retstr;

   retstr = "This is a waterskin that can hold up to 5 l's of water.\nIt's ";

   if (filled == 5000)
      retstr += "full";
   else if (filled > 4500)
      retstr += "nearly full";
   else if (filled > 4000)
      retstr += "quite full";
   else if (filled > 3000)
      retstr += "more than half-full";
   else if (filled > 2000)
      retstr += "about half-full";
   else if (filled > 1000)
      retstr += "only filled to about a quarter";
   else if (filled > 1)
      retstr += "nearly empty";
   else if (filled < 1)
      retstr += "empty";

   return retstr + ".\n";
}

public string
short()
{
   string retstr;
   return "a waterskin";
    
   switch(filled)
   {
      case 4500..5000:
         retstr += "(5l)"; break;
      case 3500..4499:
         retstr += "(4l)"; break;
      case 2500..3499:
         retstr += "(3l)"; break;
      case 1500..2499:
         retstr += "(2l)"; break;
      case  500..1499:
         retstr += "(1l)"; break;

      default:
         retstr += "(0l)"; break;
   }

      return retstr;
}

inherit "/std/object";
#include "/d/Kalad/defs.h"
/* This is one of the ways the inhabitants of the drow city of Undraeth
keep time in the Dark Dominion */
/* by Antharanos */
create_object()
{
   set_name("pillar");
   set_adj("gigantic");
   add_adj("unworked");
   
   set_short("gigantic unworked pillar");
   set_long("@@pillar_desc@@");
   
   add_prop(OBJ_I_WEIGHT,250000000);
   add_prop(OBJ_I_VOLUME,250000000);
   add_prop(OBJ_M_NO_GET,"The stalagmite cannot be removed from the ground!\n");
}

pillar_desc()
{
   int time;
   
   time = TIME;
   
   return ("A massive stalagmite mound that towers far into the air "+
      "above you. Despite its incredible height, several hundred feet by "+
      "your best estimate, its top is clearly visible due to the eerie red "+
      "glow emanating from the structure. You notice that by looking at "+
      "exactly how much of its entire length is glowing, you can tell what "+
      "hour of the day it is. It is now hour " + time + " here in the city "+
      "of Undraeth.\n");
}

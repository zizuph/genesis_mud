inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the bazaar, Undraeth");
   set_long("The bazaar of Undraeth.\n"+
      "You are at the very western edge of a great area located in the "+
      "center of the city of Undraeth that is not terribly cluttered "+
      "with the stalagmite buildings so common elsewhere in the city. "+
      "Here, the norm is many-colored tents, some decorated in faerie fire, "+
      "others decorated in a more mundane fashion. The rest of "+
      "the bazaar lies off to the northeast, east and southeast. "+
      "A wide avenue slices its way straight to the north and south, while "+
      "a smaller, narrower street eases its way to the southwest.\n");
   add_item(({"bazaar","great area","area"}),
      "It is where you are right now, look around.\n");
   add_item(({"city","undraeth"}),
      "The city lies all around the bazaar, towering in its darkness.\n");
   add_item(({"many-colored tents","tents","tent"}),
      "All manner and color of tent are visible around you.\n");
   add_item(({"faerie fire","fire"}),
      "It glows with a strange luminescence vaguely reminiscent of fireflies.\n");
   add_item(({"wide avenue","avenue"}),
      "A broad and meticulously clean street that travels in a direct line "+
      "from north to south.\n");
   add_item(({"smaller street","small street","narrower street","narrow street","street"}),
      "A small roadway that departs to the southwest, heading towards the "+
      "entrance to this city.\n");
   add_exit(CPASS(drow/d21),"north");
   add_exit(CPASS(drow/bazaar/b2),"northeast");
   add_exit(CPASS(drow/bazaar/b5),"east");
   add_exit(CPASS(drow/bazaar/b4),"southeast");
   add_exit(CPASS(drow/d22),"south");
   add_exit(CPASS(drow/d16),"southwest");
   set_noshow_obvious(1);
}
block()
{
   write("A glowing spider web suddenly appears before you! You cannot get "+
      "past it! It soon disappears as you back away.\n");
   say("A glowing spider web suddenly appears before " + QTNAME(TP) + "! " + capitalize(TP->query_pronoun()) + " cannot get past it! It soon disappears "+
      "as " + QTNAME(TP) + " backs away.\n");
   return 1;
}

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("A great many stalagmites and stalactites fill your field "+
      "of view. These immense structures of rock rise far above you, having "+
      "been structurally enhanced by the populace of the city into the "+
      "strangely beautiful structures before you. "+
      "The air around you is warm from the presence of so many living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "A single compound lies to the east. "+
      "You're on a street that runs directly from the north and straight "+
      "south, towards the plateau of Undraeth.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"single compound","compound"}),
      "A small grouping of stalagmites that have been magically fused to form "+
      "a livable structure. Before it hangs a sign.\n");
   add_item("sign","A few words in glowing faerie fire have been "+
      "written upon it.\n");
   add_cmd_item("sign","read",
      "It reads: Massage Parlour\n");
   add_exit(CPASS(drow/bazaar/b1),"north");
   add_exit(CPASS(drow/shop/massage_entr),"east","@@msg",-1,-1);
   add_exit(CPASS(drow/d23),"south","@@block");
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
msg()
{
   write("You stride towards the compound in the east.\n");
   say(QCTNAME(TP) + " strides towards the compound in the east.\n");
   return 0;
}

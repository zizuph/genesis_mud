inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Outside the Highland Gate");
   set_long("You now stand just outside the Highland Gate, one of three "+
      "major entrances into the famed city of Kabal. From here, the cobbled "+
      "High Street leads south towards the gate and far into the distance "+
      "in the northwest, where it passes the many forested estates of the "+
      "nobles. The immediate vicinity is rolling grassland, occasionally "+
      "broken by a solitary tree. However, the landscape becomes richer in "+
      "life to the northwest, where distant forests can be seen.\n");
   add_item(({"highland gate","gate","entrance"}),"A pair of massive steel "+
      "gates set within the encircling city walls of Kabal.\n");
   add_item(({"encircling city walls","city walls","walls","encircling walls","wall"}),
      "They tower to a height of at least thirty feet and are several feet in "+
      "thickness. Truly, they pose an insurmountable physical barrier to any "+
      "and all invading forces.\n");
   add_item(({"cobbled high street","high street","street","cobbled street"}),
      "The cobblestoned road leads south into Kabal and northwest through "+
      "the grasslands and into the forested lands of the nobles.\n");
   add_item(({"grassland","grasslands"}),"Gently rolling hills covered "+
      "tall green grass can be seen waving in the breeze. An occasional "+
      "tree can be seen here and there.\n");
   add_item(({"tree"}),"There are just a few trees nearby, with most of "+
      "the area being covered by waist-high grass.\n");
   add_item(({"green grass","grass"}),"It is tall and luxuriantly green "+
      "from the consistent rains.\n");
   add_item(({"forests","forest"}),"Far in the northwestern horizon, a "+
      "long band of green indicates the forested lands of the nobles of "+
      "Kabal.\n");
   add_item(({"large winch","winch"}),"A large metal rod used to open "+
      "up the Highland Gate.\n");
   add_exit("/d/Kalad/common/wild/high/w2","northwest",0,2);
   clone_object("/d/Kalad/common/caravan/door/hgdoor1")->move(TO);
}
void
init()
{
   ::init();
   AA(crank,crank);
}
int
crank(string str)
{
   if(!str || str != "winch")
      {
      notify_fail("Crank what? The winch maybe?\n");
      return 0;
   }
   write("You foolishly attempt to crank the winch but realize you have no "+
      "idea how to operate the mechanism.\n");
   say(QCTNAME(TP) + " foolishly attempts to crank the winch but realizes that " + TP->query_pronoun() + " has no idea how to operate the mechanism.\n");
   return 1;
}

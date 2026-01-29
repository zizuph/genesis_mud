inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside a small tent");
   set_long("The interior of this tent is truly a sight to behold!\n"+
      "Besides the usual amenities such as a sleeping mat, floor rug and "+
      "cooking pot, a host of other items line the tent's sides. Aside the "+
      "mat is a low wooden table and the edge of the tent floor is lined "+
      "with a mass of thorns.\n");
   add_item(({"tent"}),"Its what you're inside of, silly!\n");
   add_item(({"sleeping mat","mat"}),"A soft bed of camel fibers. Right "+
      "now it is rolled up neatly to one side.\n");
   add_item(({"floor rug","rug"}),"A finely woven, and smooth to the touch "+
      "carpet. Wonderful decorations cover its surface.\n");
   add_item(({"decorations","decoration","surface"}),"Colorful images of "+
      "the desert and its surprisingly plentiful life is sewn into the "+
      "carpet.\n");
   add_item(({"cooking pot","pot"}),"A brand new iron cooking pot, not a "+
      "single scratch marring its surface.\n");
   add_item(({"host","items","item"}),"A variety of strange and exotic "+
      "items line the wall, just a few of which are snake skins, bird "+
      "talons, tongues, eyeballs, fingers and more.\n");
   add_item(({"snake skins","snake skin","skins","skin"}),"The dried "+
      "and shedded skin of a desert snake.\n");
   add_item(({"bird talons","talons","talon"}),"The claws of a bird "+
      "of prey.\n");
   add_item(({"tongues","tongue"}),"The dried and swollen tongue of a "+
      "dead man!\n");
   add_item(({"eyeballs","eyeball"}),"The severed eyeball of some "+
      "poor creature.\n");
   add_item(({"fingers","finger"}),"A human-type digit, except for its "+
      "slightly reddish hue.\n");
   add_item(({"low wooden table","low table","wooden table","table"}),
      "The perfectly-polished table is bare of furnishings.\n");
   add_item(({"tent floor","floor"}),"Were it not for the rug, it would "+
      "be just the sand of the desert waste.\n");
   add_item(({"mass of thorns","mass","thorns","thorn"}),"A barrier used "+
      "to prevent desert creatures from wandering into the tent.\n");
   add_exit(CPASS(desert/camp/c31),"west",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/bed_witch");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A Bedellin witch stalks into her tent.\n");
   }
}

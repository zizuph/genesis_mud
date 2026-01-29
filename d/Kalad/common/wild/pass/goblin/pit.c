inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <ss_types.h>
#define CHECK_CLIMB 30
#define DAMAGE 100
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Pit");
   set_long("A large circular pit filled completely with viciously "+
      "sharp iron stakes. The ground is moist and slushy, and is covered "+
      "with some dark liquid. Above, you can see the lip of the pit, and "+
      "your only way out of this death trap.\n");
   add_item(({"iron stakes","stakes","stake"}),"Arranged all about the "+
      "floor, they have been pointed skyward, maliciously designed to "+
      "impale anyone falling into this trap. Luckily for you, someone has "+
      "already fallen into the pit, and as a result, bent several of the "+
      "stakes away from the sky.\n");
   add_item(({"ground"}),"It is covered with the unfortunate remains "+
      "of several foolish adventurers. Thick red blood covers the floor.\n");
   add_item(({"thick red blood","thick blood","red blood","blood","dark liquid","liquid"}),
      "It covers the floor of this pit, coloring it a sickening red in color.\n");
   add_item(({"floor"}),"The ground is disgustingly filthy.\n");
   add_item(({"lip"}),"It lies just beyond your reach...Damn!\n");
   add_item(({"walls","wall"}),"The sides of the pit are nearly "+
      "vertical, making a climb up very difficult.\n");
   add_exit(CPASS(goblin/g6),"up","@@climb",2,1);
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(CHECK_CLIMB))
      {
      write("You try to climb up the walls of the pit but only succeed in impaling yourself on some stakes!!!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " tries to climb up the walls of the pit but only succeeds in impaling " + TP->query_objective() + "self on some stakes!!!\n");
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to climb out of the pit!\n");
   return 0;
}

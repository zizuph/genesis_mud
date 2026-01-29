#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;

int guardian_spawned = 0;
object guardian;

void
reset_kalaman_room()
{
   if(!objectp(guardian))
   {
     guardian_spawned = 0;
    }

    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("gloomy entrance of a wizard's tower");

    add_item(({"entrance"}),
      "You can leave out the entrance to the streets of Kalaman.\n");
    add_item(({"strange black stone","black stone","stone","walls","gloomy light",
      "light"}),
      "The tower is made of strange black stone. While seemingly opaque, " +
      "the tower is lit with a gloomy light that seems to come from the walls.\n");
    add_item(({"stone staircase","staircase","stairs","open staircase"}),
      "A stone staircase circles the walls of the tower up to a broad platform " +
      "above you.\n");
    add_item(({"platform","broad platform"}),"At the top of the stone staircase " +
      "is a broad platform where the resident of the tower is likely to reside.\n");

    add_exit(CITY + "r6","out",0);
    add_exit(CITY + "tower02","up","@@check_guardian");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand within the entrance of a tower made of strange " +
    "black stone. No torches or lamp light this tower, however it seems " +
    "the walls allow some light to pass through - providing quite a gloomy " +
    "atmosphere. An open staircase circles the wall up to a broad " +
    "platform above you.\n";
}

int
check_guardian()
{
    if((guardian_spawned == 1) && !objectp(guardian))
    {
       write("You climb the staircase up to the platform...\n");
       return 0;
    }

   if(!objectp(guardian))
   {
       guardian = clone_object(KNPC + "spectral_minion");
       guardian->move(TO);
       guardian_spawned = 1;
       write("A spectral minion materialises in front of you.\n");
       say("A spectral minion materialises in front of you.\n");
       guardian->command("emote moans: You may not pass!");
       write("The spectral minion blocks your way up the staircase.\n");
       return 1;
   }
   
   guardian->command("emote moans: You were warned mortal!\n");
   guardian->command("kill " + TP->query_real_name());
   return 1;

}


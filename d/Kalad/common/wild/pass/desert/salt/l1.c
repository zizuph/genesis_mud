/* by Antharanos */
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>

#define KALAD_FOUND_SALT_EXIT "_kalad_found_salt_exit"

inherit "/d/Kalad/std/room";

public void
create_kalad_room()
{
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist cave");
   set_long("The staccato rythm of water dropping echoes around you, "+
      "lending to the eerie atmosphere within this subterranean cave. "+
      "Jagged stalagmites and stalactites fill this small, oval chamber, "+
      "making it quite painful to walk. In the east, a hole opens up into "+
      "gloomy darkness.\n");
   add_item(({"subterranean cave","cave","small chamber","oval chamber","chamber"}),
      "Surprisingly enough, there is an abundance of moisture in this "+
      "area, despite the harsh conditions just a few feet above you.\n");
   add_item(({"above"}),"The ceiling of the cave lies there.\n");
   add_item(({"ceiling"}),"A mass of stalactites hang from above, "+
      "threatening to collapse on top of you.\n");
   add_item(({"jagged stalagmites","stalagmites","stalagmite","jagged stalactites","stalactites","stalactite"}),
      "Masses of rock that have been formed due to the continual and slow "+
      "process of running water. As a result, the floor looks quite "+
      "treacherous.\n");
   add_item(({"water"}),"It lies all around you, covering everything.\n");
   add_item(({"floor"}),"It is covered with many jagged stalagmites, "+
      "making even a short walk quite painful.\n");
   add_item(({"hole","gloomy darkness","darkness"}),"It appears to "+
      "lead out of this chamber.\n");
   add_prop(OBJ_S_SEARCH_FUN,"search_ceiling");
   add_exit(CPASS(desert/salt/l2),"east","@@hurt",1,2);
   add_exit(CPASS(desert/salt/s29), "up", "@@exit_up", 1, 1);
}

int
exit_up()
{
    object *witnesses;
    if (TP->query_prop(KALAD_FOUND_SALT_EXIT))
    {
        witnesses = filter(FILTER_CAN_SEE_IN_ROOM(AINV(E(TP)) - ({TP})),
                TP->check_seen);
        foreach (object witness: witnesses)
        {
            if (!witness->query_prop(KALAD_FOUND_SALT_EXIT))
            {
                witness->add_prop(KALAD_FOUND_SALT_EXIT, 1);
                witness->catch_msg(QCTNAME(TP) + 
                    " uses a passage hidden in the ceiling!\n");
            }
        }
        return 0;
    }
    write("There is no obvious exit up.\n");
    return 1;
}


public string
search_ceiling(object me, string arg)
{
   if(arg != "ceiling")
      return "";
   if(TP->query_skill(SS_AWARENESS) < 30)
      return "";

   TP->add_prop(KALAD_FOUND_SALT_EXIT, 1);
   return "After a thorough search, you discover a passage leading up and "+
   "out of the cave!\n";
}

hurt()
{
   if(TP->query_base_stat(SS_DEX) < 50)
      {
      write("You stepped on a stalagmite! Ouch!\n");
      say(QCTNAME(TP) + " stepped on a stalagmite!\n");
      TP->heal_hp(-100);
      return 0;
   }
   write("You manage not to step on any stalagmites.\n");
   return 0;
}

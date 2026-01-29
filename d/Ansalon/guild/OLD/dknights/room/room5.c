
/**  DARGAARD KEEP ROOM **/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit GUILD_IN;

object guard1, guard2;

int allow_entry();

void
reset_dargaard_room()
{
   if(!objectp(guard1))
   {
      guard1 = clone_object(GUILD_NPC + "sana");
      guard1->move(TO);
   }

   if(!objectp(guard2))
   {
      guard2 = clone_object(GUILD_NPC + "trell");
      guard2->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Hallway underneath Dargaard Keep");
    set_long("As you enter this area, the shivering coldness "+
             "everpresent in the tunnels disappears. "+
	     "A dimm lit hallway is located to the north.\n");

    add_exit(GUILD_ROOM + "room1","north",0);
//    add_exit(GUILD_ROOM + "room6","south","@@allow_entry", 0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    add_prop(ROOM_I_NO_ATTACK, "You don't dare attack.\n");

    reset_dargaard_room();
}



int
allow_entry()
{
   if(objectp(guard1) && E(guard1) == TO)
   {
       if (TP->query_guild_member("Death Knight of Krynn"))
       {
           guard1->command("emote nods respectfully at you.\n");
           return 0;
       }
       if (TP->query_prop(I_SOLVED_STEP_0))
       {
           write("The wraiths move aside and lets you pass.\n");
           return 1;
       }
       if (TP->query_prop(LAST_WARNING))
       {
           guard1->command("emote rasps: Don't give me a reason to kill you.\n");
    //       guard1->command("kill "+TP->query_real_name());
           return 1;
       }
       if (!TP->query_prop(LAST_WARNING))
       {
           guard1->command("emote rasps: You do not have permission to enter the "+
                           "resting place of the Death Knights. Leave, now!\n");
           TP->add_prop(LAST_WARNING, 1);
       }
       return 1;
   }

   if(objectp(guard2) && E(guard2) == TO)
   {
       if (TP->query_guild_member("Death Knight of Krynn"))
       {
           guard1->command("emote nods respectfully at you.\n");
           return 0;
       }
       if (TP->query_prop(I_SOLVED_STEP_0))
       {
           write("The wraiths move aside and lets you pass.\n");
           return 1;
       }
       if (TP->query_prop(LAST_WARNING))
       {
           guard1->command("emote rasps: Don't give me a reason to kill you.\n");
    //       guard1->command("kill "+TP->query_real_name());
           return 1;
       }
       if (!TP->query_prop(LAST_WARNING))
       {
           guard2->command("emote rasps: You do not have permission to enter the "+
                           "resting place of the Death Knights. Leave, now!\n");
           TP->add_prop(LAST_WARNING, 1);
       }
       return 0;
   }

   return 0;
}

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit FLOTSAM_IN;
object priest;

void
reset_flotsam_room()
{
   if(!objectp(priest))
      {
      priest = clone_object(TEMP + "living/priest");
      priest->arm_me();
      priest->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Altar room");
   set_long("@@long_descr");
   
   add_item(({"tapestry","satyr","bloated satyr"}),
      "This tapestry depicts the God Chemosh in his " +
      "true form, a satyr with a goat's skull for a head. " +
      "\n");
   add_item(({"stone altar","altar","great stone altar"}),
      "This altar is a huge block of stone carved " +
      "with skulls as well as creatures of evil. It is stained red " +
      "with blood.\n");
   add_item(({"steps","dais"}),"Marble steps lead up the dais " +
      "to the altar.\n");
   
   
   add_exit(TEMP + "temp3","north",0);
   add_exit(TEMP + "temp4","northwest",0);
   add_exit(TEMP + "temp5","northeast",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in the altar room of the God of Death. Raised on " +
   "a dais before you stands a great stone altar, used to sacrifice the " +
   "living to quench the hunger of this malevolent deity. A tapestry of " +
   "recent make depicts a bloated satyr with a goats skull for a head " +
   "standing upon a dead and lifeless land, the land of Ansalon. " +
   "\n";
}

int
canticle_revelation(object ob)
{
     ob->catch_msg("\n\nThe dark shadows of this grim temple and the malevolent " +
            "presence of a dark god triggers a divine revelation!\n\n\n");
     OOTS_ADD_REV(ob,"canticle78","edification - canticle of the dragon, verse 7 and 8"); 

}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
       if(IS_OOTS(ob))
       {
          if(!OOTS_QUERY_REV(ob, "canticle78"))
          {
            set_alarm(1.5, 0.0, &canticle_revelation(ob)); 
          }
       }
    }

}

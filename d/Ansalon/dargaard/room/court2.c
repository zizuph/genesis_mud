
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court2
 *
 *
 *
 ************************************************************/


/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

object skeleton;


void
reset_dargaard_room()
{
   if(!objectp(skeleton))
   {
      skeleton = clone_object(DNPC + "skeleton");
      skeleton->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Northern part of the Courtyard of Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are in the courtyard"+
             " of Dargaard Keep, standing in foreplace of the main castle"+
             " entrance. Darkness shrouds the gate and you can even see"+
             " some movement beyond it."+
             " Above, you notice the defensive structures of the"+
             " castle. Ramparts to throw rocks at attackers who succeeded"+
             " to breach the outer walls and funnels to let boiling oil"+
             " rain on the unfortunates as well. The melody you have heard"+
             " before seems to come from the inside of the castle. However,"+
             " as you approach the song seems to end and the last notes"+
             " of the sad and haunting melody ring out and fade to oblivion."+
             " North of you is the main entrance to the castle."+
             " To the east and west the courtyard continues.\n"); 

    add_exit(DROOM + "court1","west",0);
    add_exit(DROOM + "nowhere","north","@@nowhere",0);
    add_exit(DROOM + "court3","east",0);
 

    add_item(({"wall", "walls", "castle"}),
      "The castle seems to be affect by the environment as well. Some of the finer ornaments"+
      " and structures have partly crumbled. Some of the outcroppings are the homes of "+
      " several plants. However, there are no animals like birds nearby.\n");

    add_item(({"gate", "entrance"}),
      "You must go nearer to the entrance. From this point you cannot see much because of the"+
      " lack of illumination.\n");


    reset_dargaard_room();
}

int
nowhere()
{
    write("The entrance to the Keep has been completely blocked by rubble and "+
          "debris.\n");
    return 1;
}


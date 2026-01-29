
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court5 
 *
 *
 *
 ************************************************************/


/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

object skeleton, skeleton2;


void
reset_dargaard_room()
{
   if(!objectp(skeleton2))
   {
      skeleton2 = clone_object(DNPC + "skeleton");
      skeleton2->move(TO);
   }
   if(!objectp(skeleton))
   {
      skeleton = clone_object(DNPC + "skeleton");
      skeleton->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Center of the Courtyard of Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are in the midst of the courtyard"+
             " in Dargaard Keep."+
             " Standing on the vast place you imagine how mighty Solamnic armies"+
             " once had been gathering here to do the bidding of the Kingpriest of Istar."+
             " Ironically this place seems"+
             " to be a strongold of shadows and darkness nowadays."+
             " The place seems to be neglected and abandoned and the wind drives"+
             " a small shrub over the courtyard. An old well stands on the middle of "+
             " the courtyard."+
             " The courtyard continues in almost every direction here.\n"); 

    add_exit(DROOM + "court4","west",0);
    add_exit(DROOM + "court6","east",0);
    add_exit(DROOM + "court7","southwest",0);	
    add_exit(DROOM + "court8","southeast",0);
    add_exit(DROOM + "court3","northeast",0);	
    add_exit(DROOM + "court1","northwest",0);

    add_cmd_item(({"well", "hole"}), ({"enter"}), "@@into_well");


    add_item(({"shrub"}),
      "The shrub is brown and obviously dead for some time now.\n");

    add_item(({"well"}),
      "The well looks ancient and completely dry.\n");

    reset_dargaard_room();
}


string
into_well()
{
    write("You climb down the old well.\n");
    TP->move_living("into the old well.",
      DROOM + "well.c", 1, 0);
    return "";
}

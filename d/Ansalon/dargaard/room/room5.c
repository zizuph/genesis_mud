
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room8 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit DARGAARD_IN;

object guard;

void
reset_dargaard_room()
{
   if(!objectp(guard))
   {
      guard = clone_object(DNPC + "fountain_guard");
      guard->move(TO);
   }
}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("At the foutain of blood");
    set_long("You find yourself at a strange fountain."+
             " The statue of a black knight made out of"+
             " obsidian stands upon a marble countryside"+
             " resembling the pre-cataclysm Solamnia. "+ 
             " From all over the marble country small,"+
             " blood-red fountains erupt and sprinkle the dark"+
             " knight. It seems like the whole land would"+
             " either suffer because of the knight or"+ 
             " pity him or maybe both.\n"); 

    add_exit(DROOM + "room13","north",0);
    add_exit(DROOM + "room12","west",0);
    add_exit(DROOM + "room6","east",0);
    add_exit(DROOM + "room4","south",0);

    add_item(({"statue", "knight"}),
        "The knight wears a solamnic armour of ancient design"+
        " of pre-cataclysm style. Since the visor is closed"+
        " you can't see the knight's face.\n");

    add_item(({"fountain"}),
	      "The dark-red liquid seems to be blood, indeed.\n");
        
    add_item(({"country", "marble"}),
	      "As you have a closer look you can see sites like"+
        " the High Clerist Tower, Vingaard Keep, Dargaard"+
        " Keep, Solanthus and even far to the south the"+
        " Kharolis mountains.\n");

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    add_item(({"torches"}), 
     "These are standard torches which you can find everywhere"+ 
     " on Krynn.\n"); 

    add_item(({"dust"}), 
     "This thick layer of white covers everything. Here and"+ 
     " there the dust was disturbed but you cannot make"+ 
     " out anything.\n"); 

}

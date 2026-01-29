
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room7 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit DARGAARD_IN;

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("A hallway of Dargaard Keep");
    set_long("You are standing in a small, domed"+
             " hall. The ever present mist covers"+
             " the floor, Leering gargoyles sit"+
             " upon the ledges staring coldly down."+
             " Unrecognizable crests and banners line"+
             " the walls as well as suits of armours."+
             " The dark hallway continues to the northeast "+
             "west and south.\n"); 

    add_exit(DROOM + "room19","west",0);
    add_exit(DROOM + "room11","south",0);
    add_exit(DROOM + "room17","northeast",0);

    add_item(({"crests", "crest"}), 
     "The crests are twisted by the heat and totally blackened"+ 
     " It is impossible to find any clue what or whom they resembled.\n"); 

    add_item(({"slime"}), 
     "The slime seems to be sticky and smells terribly"+ 
     " Maybe it is a kind of algae, maybe something"+ 
     " entirely different.\n"); 

    add_item(({"banners", "banner"}), 
     "Parts of the banners are burned and soot partly covers them."+ 
     " The intact parts colours and pictures have faded over the centuries.\n"); 

    add_item(({"torches"}), 
     "These are standard torches which you can find everywhere"+ 
     " on Krynn.\n"); 

    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work.\n"); 

    add_item(({"gargoyle", "gargoyles"}), 
     "These small imp-like creatures are made of stone."+ 
     " They have small, ugly horns at the head and on their"+ 
     " backs. Their lifless eyes seem to be fixed at you.\n"); 

    add_item(({"ledges", "ledge"}), 
     "A stony ledge which is often used to fix banners, trophies or small statues"+ 
     " for decorational purposes.\n"); 

    add_item(({"dust"}), 
     "This thick layer of white covers everything. Here and"+ 
     " there the dust was disturbed but you cannot make"+ 
     " out anything.\n"); 

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

    add_item(({"ground"}), 
     "The ground is even and in a good condition except some"+ 
     " puddles and debris lying around.\n"); 
  
}

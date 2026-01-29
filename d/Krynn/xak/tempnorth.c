/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKINROOM
inherit "/d/Krynn/solamn/guild/spells/chapel_base";

#include <ss_types.h>
#include <macros.h>

void
create_xak_room()
{
    set_short("The north holy circle");
    set_long("You are standing in an large circular chamber that stretches"
	     + " some 60 feet in diameter. The chamber walls are made of smooth"
	     + " white stone that soars up 60 feet to a domed ceiling. The"
	     + " chamber is given an extra appearance of size by its"
	     + " emptiness. Wonderous frescoes line the walls showing acts"
	     + " of miraculous healing filling you with awe. An exit leads"
	     + " south back into the main chamber.\n");
    
    add_exit(TDIR + "tempchamber.c", "south", 0);
    
    add_item(({"frescoe", "frescoes", "fresco"}), "@@fresco");
    INSIDE;
    DARK;
}

string
fresco()
{
    write("The frescoes show sight of miraculous healing. The lame"
	  + " walking, the blind seeing, the deaf hearing. In each case"
	  + " the afflicted is surrounded in a glowing blue nimbus which"
	  + " seems to heal the person. You realise that that is the power"
	  + " this goddesses priests and priestesses must have once"
	  + " possessed. How sad that so many have turned their eyes away"
	  + " from worshipping her.\n");
    return "";
}

 void                                                               
 init()                                                             
 {                                                                  
      init_chapel();                                                
      ::init();                                                     
 }             

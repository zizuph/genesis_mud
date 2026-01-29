/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKINROOM
inherit "/d/Krynn/solamn/guild/spells/chapel_base";

#include <ss_types.h>
#include <macros.h>

void
create_xak_room()
{
    set_short("The south worship room");
    set_long("This is the south worship room. It was here that"
	     + " people would come to worship Mishakal. This is a"
	     + " rectangular room in sharp contrast to the circular"
	     + " chamber outside. Light streams in from windows"
	     + " high up on the far wall. The room contains several"
	     + " marble benches and the west wall contains a raised"
	     + " dais. The room is however quite empty.\n");
    
    add_exit(TDIR + "tempchamber.c", "northeast", 0);
    
    add_item(({"bench", "benches", "marble bench", "marble benches"}), "@@bench");
    add_item(({"dais", "raised dais"}), "@@dais");
    
    INSIDE;
    LIGHT;
}

void                                                               
init()                                                             
{                                                                  
      init_chapel();                                                
      ::init();                                                     
}        

string
dais()
{
    write("A simple dais raised up on stone.\n");
    return "";
}

string
bench()
{
    write("The benches are made of good quality marble."
	  + " You think that they were probably covered with felt"
	  + " but that has long since worn away.\n");
    return "";
}

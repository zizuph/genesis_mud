/*
 * F23.c
 * Room containing a hidden small game pit trap which Thanduin will
 * come by and check periodically. Players can grab the dead rabbit
 * from the trap if they like, but it will anger thanduin.
 * - Alaron February 1998
 */

#include "dirheader.h"
#include "coramar.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

inherit BASETRAPROOM;

void
create_traproom()
{
    set_long("   The path here is narrow and seems to be under attack by a wide "+
	"variety of bushes, ferns and vines. Vines hang down from the giant limbs "+
	"of the trees above and they seem to slither across the forest floor like "+
	"thick green snakes. The brush here is so thick that the path is barely "+
	"visible. Occasionally a small rabbit will dart out of the bushes and scamper "+
	"across the path from one safe bush to another. The narrow path continues to the "+
	"southwest toward a tunnel-like formation of trees and to the east deeper "+
	"into the thick mist. The forest around you seems to disappear behind a veil "+
	"of gray, showing you only faint hints of what is out there, almost teasing you "+
	"with the outlines of the trees and bushes.\n\n");    

    add_fexit(CORAMAR+"f24", "east", 0);   
    add_fexit(CORAMAR+"f22", "southwest", 0);
   
}
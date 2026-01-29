// Tomas November 2017
// Evolved from:
// Equstrian Club


inherit "/lib/guild_support";
inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "huntclub.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/bits.h"

void
create_room()
{
    set_short("Hunting lodge porch");
    set_long("You're standing on wide covered porch of a large hunting lodge. " +
        "Double doors leading into the lodge can be seen to the north. Beyond the " +
        "clearing to the south, you can see a small animal path leading through the " +
        "trees.\n");

    add_item(({"lodge", "hunters lodge"}),
        "The lodge is largely comprised of stacked tree trunks one on top of another " +
        "and overlapping the logs at the corners, interlocking corners by notching the " +
        "logs at the ends. The joints were sealed with some sort of white mortar making " +
        "a water-tight seal. The shingled roof, is covered in green moss, providing an " +
        "extra layer of insulation. Large shuttered windows can be seen above the " +
        "porch.\n");
        
    add_item(({"windows", "shuttered windows"}),
        "Large windows set deep within the walls by the doors. Heavy shutters with " +
        "arrow slits, currently cover the windows.\n");
    
    add_item(({"wall","walls"}),
        "They are made of horizontally laid pine tree trunks with white " +
        "mortared joints.\n");

        
	add_item(({"mortar", "mortar lines", "lines"}),"Bleached white mortar can be seen " +
	    "between the pine tree logs, which make up the walls.\n");
	
	add_item(("porch"),
	    "This is a large cedar planked covered porch extending the length of the lodge. "+
	    "There are a pair of double doors leading into the lodge to the north. To the " +
	    "south is a small animal trail leading through the trees.\n");
	
	add_item(({"trees", "tree", "grove"}),
	    "A grove of tree's separated by a small trail can be seen to the south.\n");
  
    add_cmd_item("shutters", "open",
      "The shutters are closed and locked. You don't see a way to open them.\n");
    
    add_cmd_item("windows", "open",
      "The shutters are closed and locked. You don't see a way to open them.\n");
      
    add_prop(ROOM_I_INSIDE, 0);

    
    add_exit(HUNTCLUB_DIR + "huntclub_joinrm","north");
    add_exit("/d/Shire/misty/hunter_trail07", "south");
}






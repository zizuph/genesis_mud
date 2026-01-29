/*
 * Vale of the Anduin.
 * Varian 2015
 */
#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "vale/base";


void 
create_vale_room()
{
    set_items_vale();
    set_items_east();
    set_items_mirk();
    set_items_oldroad();
    set_herbs_1();
    
    set_short("Vale of the Anduin");
    set_long("A tall, yellowish grass surrounds you, swaying and brushing " +
    	"against you with every faint breeeze which twists past you. You are " +
        "on the eastern edge of a deep valley which stretches beyond your " +
        "sight to both the north and the south. Directly to the west, you " +
        "can see the valley dip down to cradle the wide, rushing waters of " +
        "the legendary Anduin river as it flows south towards Gondor. On the " +
        "other side of the valley, rocky foothills stretch higher and " +
        "higher until they seemingly touch the heavens as the majestic " +
        "Misty Mountains of legend. To the east, an endless forest of tall, " +
        "black oak trees looms menacingly immediately before you. " +
        "This is clearly the mighty Mirkwood Forest of which many " +
        "tales tell of darkness and danger. Not far to the south, you see " +
        "what appears to be an old road, cutting across the vale, connecting " +
        "the forest to a wide ford which crosses the river.\n"); 

    add_exit(MIRK_OR_DIR + "r01", "south",0,2,1);
    add_exit(VALE_DIR + "valen2w1", "north",0,2,1);
    add_exit(VALE_DIR + "valen2w2", "northwest",0,2,1);
    add_exit(VALE_DIR + "valen1w2", "west",0,2,1);
    add_exit("/d/Shire/anduin/east/rd05", "southwest",0,2,1);
    add_forest_entrance(MIRK_C_DIR + "r00/f07", "east"); 
    add_forest_entrance(MIRK_C_DIR + "r01/f07", "northeast");
    add_forest_entrance(MIRK_OR_DIR + "r02", "southeast");    
}

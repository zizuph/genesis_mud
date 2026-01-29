/*************************************************************************
 * - Cavern room                                                       - *
 * - Created by Damaris 03/2001                                        - *
 * - Recoded by Damaris 02/2002                                        - *
 *************************************************************************/
#pragma strict_types
#include "../defs.h"
inherit CAVE_BASE;

void
create_khalakhor_room()
{
    
    config_room("western");add_exit("cav0401", "west");
    add_exit("cav0301", "northwest");
    add_exit("cav0503", "southeast");
 

}

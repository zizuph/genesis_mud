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
    
    config_room("central");
    
    add_exit("cav0406", "east");    
    add_exit("cav0404", "west");
    add_exit("cav0304", "northwest"); 

}

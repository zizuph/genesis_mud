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
    
    config_room("eastern"); 
    
    add_exit("cav0410", "east");    
    add_exit("cav0310", "northeast");
    add_exit("cav0510", "southeast");
 

}

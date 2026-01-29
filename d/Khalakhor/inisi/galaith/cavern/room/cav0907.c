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
    
    config_room("southern");
    add_exit("cav0906", "west");
    add_exit("cav0808", "northeast");
 

}

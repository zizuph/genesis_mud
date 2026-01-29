/* File         : /d/Khalakhor/se_speir/plains/room/tfor_e_06.c
 * Creator      : Darragh@Genesis
 * Date         : 01-01-23   
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications:  
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit "/d/Khalakhor/se_speir/plains/room/tforbase";

void
create_khalakhor_room()
{
   create_tforest();

   add_exit(PLAINS + "tfor_e_05","west",0,1,1);
   add_exit(PLAINS + "tfor_f_07","southeast",0,1,1);
   add_exit(PLAINS + "tfor_f_06","south",0,1,1);
   add_exit(PLAINS + "tfor_f_05","southwest",0,1,1);

   set_long(query_long() + " Northwards and east of you the forest looks "
                         + "too deep and gloomy, the terrain hostile and "
                         + "unfriendly. Moving in those directions seems "
                         + "hopeless.\n");
}

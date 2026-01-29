/**********************************************************************
 * - beach1.c                                                       - *
 * - Beach room                                                     - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
#pragma strict_types
#include "local.h"  
inherit SEABASE;
#include <stdproperties.h>
 
public void create_sea()
{
    set_short("An ocean near the coast of SaMorgan");
    set_long("   This is an ocean near the village of SaMorgan in "+
      "Khalakhor. The cold clear water sparkles in between what "+
      "little sunlight the clouds let through.\n");

 
    add_exit(GALAITH + "sea2", "sea" ,0,0,1);
    add_exit(S_WEST + "samorgan/pier/pie1206", "pier" ,0,0,1);
}

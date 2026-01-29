/* Sea for SaMorgan
 * Damaris
 */
#pragma save_binary
#pragma strict_types
 
inherit "/d/Khalakhor/ship/macdunn/std/sea_base";
#include "local.h"
#include <stdproperties.h>
 
public void create_sea()
{
    set_short("An ocean near the coast of SaMorgan");
    set_long("   This is an ocean near the village of SaMorgan in "+
             "Khalakhor. The cold clear water sparkles in the sunlight.\n");
    add_item(({"waters","crystal waters","clear waters"}),
      "The water is pure and clean.\n");
    add_item("sky","The sky is lit with an all present amount of " +
      "sunshine, accented with thin clouds.\n");
 
    add_exit(MACDUNN_DIR + "sea4","sea",0,0,1);
    add_exit(SAMORGAN_PIER,        "pier",0,0,1);
}

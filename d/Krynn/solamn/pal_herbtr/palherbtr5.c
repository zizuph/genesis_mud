/* 
   created by Vitwitch 08/2021 
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

#define PALANTHAS_START "/d/Krynn/solamn/palanthas/aesthetics/sr6"
#define PALANTHAS_END "/d/Krynn/solamn/palanthas/aesthetics/swr8"
#define ROOM "/d/Krynn/solamn/pal_herbtr/"

inherit "/d/Krynn/solamn/pal_herbtr/palherbtr_base";

string *herbs = HERB_MASTER->query_herbs(({"garden","plains","marsh"}));


/* FUNCTIONS */

void
create_pal_herb_trail_room()
{
    add_exit(ROOM + "palherbtr6","clockwise",0);
    add_exit(ROOM + "palherbtr4","widdershins",0);
}


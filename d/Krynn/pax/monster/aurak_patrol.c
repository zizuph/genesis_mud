/* created by Aridor 04/19/94 */
/* -------------------------- */
/*
   aurak.c
   -------

   Copied and altered : 95/01/18
   By ................: Jeremiah

   Latest update .....: 95/03/16
   By ................: Rastlin


   Draconian to be used in Pax Tharkas.

 * Carnak September 2016, Altered the code to allow for the scale-plated chain
 *                        mail to spawn on this aurak by removing reduntant
 *                        arming functions.
 */

#include "/d/Krynn/pax/local.h"
#include <ss_types.h>

inherit "/d/Krynn/std/aurak";
inherit "/d/Krynn/std/patrol";


void
create_aurak()
{
    int i, j = random(4) + 5;
              /* j is the level of the draconian */


    for(i=0; i<6; i++)
        set_base_stat(i, j * 12 + random(14) + 40);

    set_skill(SS_DEFENCE,     100);
    set_skill(SS_PARRY,       100);
    set_skill(SS_WEP_SWORD,   100);  
    set_skill(SS_2H_COMBAT,   100);
    set_skill(SS_WEP_KNIFE,   j * 4 + random(4) + 65);
    set_skill(SS_WEP_CLUB,    j * 4 + random(4) + 65);
    set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
    set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
    set_skill(SS_WEP_AXE,     j * 4 + random(4) + 65);

    set_all_hitloc_unarmed(20);

    set_color("red");

    set_patrol_time(0);
    set_patrol_path(({"n", "n", "n", "smile", "s", "s", "s"}));
}






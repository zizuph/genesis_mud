/* created by Aridor 04/19/94 */
/* -------------------------- */
/*
   baaz.c
   ------

   Copied and altered : 95/01/18
   By ................: Jeremiah

   Latest update .....: 95/03/17
   By ................: Rastlin


   Draconian to be used in Pax Tharkas.

*/

#include "/d/Krynn/solamn/splains/local.h"
#include "/d/Krynn/pax/local.h"
#include <ss_types.h>

inherit BAAZ;

void
create_baaz()
{
    int i, j = random(4) + 1; /* j is the level of the draconian */
    string str;

    if (j < 1)
      j = 1;

    for(i=0; i<6; i++)
        set_base_stat(i, j * 3 + random(10) + 16);

    set_skill(SS_DEFENCE,     j + random(5) + 3);
    set_skill(SS_PARRY,       j + random(5) + 3);
    set_skill(SS_WEP_SWORD,   j + random(5) + 3);
    set_skill(SS_WEP_KNIFE,   j + random(5) + 3);
    set_skill(SS_WEP_CLUB,    j + random(5) + 3);
    set_skill(SS_WEP_POLEARM, j + random(5) + 3);
    set_skill(SS_WEP_JAVELIN, j + random(5) + 3);
    set_skill(SS_WEP_AXE,     j + random(5) + 3);


    set_act_time(3 + random(3));
    add_act("scream");
    add_act("stare");
    add_act("emote shows you his claws.");
    add_act("emote snarls: What are you doing here?");
    add_act(({"say Get lost you peasant!", "laugh evilly"}));
    add_act("emote shows you the finger, or rather, his middle claw.");
    add_act("frown");
    add_act("grin");
    add_act("glare evilly all");
    set_cact_time(10);
    add_cact("say You really think you can defeat me?");
    add_cact("say Ahhh, now I can test my battle skill.");
    add_cact("say I didn't even feel that!");
    add_cact("say Is that all you can do?");
    add_cact("say Don't take it personally but I'll kill you.");
    add_cact("grin");

    set_color("red");

}


#include PAX_DRAC_BASE



/* created by Aridor 04/19/94 */
/* -------------------------- */
/*
   kapak.c
   -------

   Copied and altered : 95/01/18
   By ................: Jeremiah

   Latest update .....: 95/03/17
   By ................: Rastlin


   Draconian to be used in Pax Tharkas. 

*/

#include "/d/Krynn/solamn/splains/local.h"
#include "/d/Krynn/pax/local.h"
#include <ss_types.h>

inherit KAPAK;

void
create_kapak()
{
    int i, j = random(4) + 3;
              /* j is the level of the draconian */

    for(i=0; i<6; i++)
        set_base_stat(i, j * 4 + random(10) + 16);
    set_skill(SS_DEFENCE,     j * 4 + random(5) + 10);
    set_skill(SS_PARRY,       j * 3 + random(5) + 10);
    set_skill(SS_WEP_SWORD,   j * 3 + random(5) + 10);
    set_skill(SS_WEP_KNIFE,   j * 3 + random(5) + 10);
    set_skill(SS_WEP_CLUB,    j * 3 + random(5) + 10);
    set_skill(SS_WEP_POLEARM, j * 3 + random(5) + 10);
    set_skill(SS_WEP_JAVELIN, j * 3 + random(5) + 10);
    set_skill(SS_WEP_AXE,     j * 3 + random(5) + 10);

    set_act_time(3);
    add_act("scream");
    add_act("stare");
    add_act("emote shows you his claws.");
    add_act("emote snarls: What are you doing here?");
    add_act(({"say Get lost!", "laugh"}));
    add_act("emote shows you the finger, or rather, his middle claw.");
    add_act("frown");
    add_act("grin");
    add_act("twiddle");
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

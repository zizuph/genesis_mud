/* created by Aridor 04/19/94 */
/* -------------------------- */
/*
   bozak.c
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

inherit BOZAK;

void
create_bozak()
{
    int i;

    for(i=0;i<6;i++)
      set_base_stat(i,random(30) + 40);

    set_skill(SS_DEFENCE,     random(25) + 23);
    set_skill(SS_PARRY,       random(25) + 23);
    set_skill(SS_WEP_SWORD,   random(25) + 23);
    set_skill(SS_WEP_KNIFE,   random(25) + 23);
    set_skill(SS_WEP_CLUB,    random(25) + 23);
    set_skill(SS_WEP_POLEARM, random(25) + 23);
    set_skill(SS_WEP_JAVELIN, random(25) + 23);
    set_skill(SS_WEP_AXE,     random(25) + 23);

    set_act_time(3+random(3));
    add_act("stare");
    add_act("emote shows you his claws.");
    add_act("emote snarls: What are you doing here?");
    add_act("emote snarls: You are not supposed to be here, get lost!");
    add_act("emote shows you the finger, or rather, his middle claw.");
    add_act("frown");
    add_act("grin");
    add_act("emote snarls: Do you want me to spill out your guts?");
    add_act("giggle");
    add_act("laugh evilly all");
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



/* tmpl_low.c: Low Tyrian Templar. Serpine, 12/28/95. */
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/tyr/npc/templar";
#include "defs.h"
 
void
create_monster ()
{
    ::create_monster();
    set_race_name("initiate");
    add_adj("Tyrian");
    set_gender(random(2));
    set_long("Lowest in the rankings of the Templars are the initiates. "
            +"Only given the most basic powers by their 'god'-king "
            +"Kalak, they serve more as expendible shock troops, spies "
            +"and petty bureaucrat. Still, they get a black cossak, "
            +"just like the more important Templars of Tyr.\n");
   
    set_stats(({ 65, 60, 75, 30, 30, 40 }));
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_WEP_AXE, 50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_BLIND_COMBAT, 20);
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 30);
    set_skill(SS_UNARM_COMBAT, 40);
    set_alignment(-250-(random(250)));
}

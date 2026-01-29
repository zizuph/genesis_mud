/* tmpl_hgh.c: High Tyrian Templar. Serpine, 12/28/95. */
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/athas/npcs/templar";
#include "defs.h"
 
void
create_monster ()
{
    ::create_monster();
    set_race_name("curate");
    add_adj("Tyrian");
    set_gender(random(2));
    set_long("Before you stands one of Tyr's Templars, the priests "
            +"and dark enforcers of the will of their god-king Kalak. "
            +"This one however is special, possessed of a dark, "
            +"powerful glare in the eye and the badge of a high-"
            +"Templar of Kalak, or Curate.\n");
   
    set_stats(({ 120, 110, 150, 80, 80, 60 }));
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 60);
    set_skill(SS_UNARM_COMBAT, 80);
    set_alignment(-500-(random(500)));
}

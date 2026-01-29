/* tmpl_mid.c: Mid Tyrian Templar. Serpine, 12/28/95. */
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/athas/npcs/templar";
#include "defs.h"
 
void
create_monster ()
{
    ::create_monster();
    set_race_name("templar");
    add_adj("tyrian");
    set_gender(random(2));
    set_long("Face shadowed by a black cossak, the Templars of Tyr are "
            +"always on guard against any threat to their god and king, "
            +"Kalak. Of course, a bit of a bribe now and then "
            +"isn't unwelcome.\n");
   
    set_stats(({ 90, 85, 110, 55, 55, 90 }));
    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_KNIFE, 75);
    set_skill(SS_BLIND_COMBAT, 35);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_UNARM_COMBAT, 60);
    set_alignment(-350-(random(350)));
}

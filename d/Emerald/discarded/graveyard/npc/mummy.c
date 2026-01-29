inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/chat";
inherit "/std/act/add_things";
 
#include "/d/Emerald/defs.h"
 
 
void
create_monster()
{
 
    if(!IS_CLONE)
        return;
 
    set_race_name("mummy");
    set_adj("large");
    set_long( "A large human figure, covered entirely in bandages."+
        ". It looks quite aggressive, you think it might be a good idea "+
        "to leave now.\n" );
 
    add_prop(LIVE_I_UNDEAD,30);
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_gender(2);
 
    set_all_hitloc_unarmed(15);
 
 
    set_stats(({60,60,60,20,20,60}));
    set_hp(10000);
 
    set_skill(SS_DEFENCE,40);
    set_skill(SS_UNARM_COMBAT,60);
 
}

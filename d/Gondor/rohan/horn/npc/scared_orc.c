inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("scared orc");
    set_race_name("orc");
    set_adj("scared");
    set_long(BSN("This orc looks scared. He knows his fate."));
    set_base_stat(SS_STR,random(5)+40);
    set_base_stat(SS_DEX,random(5)+40);
    set_base_stat(SS_CON,random(5)+40);
    set_base_stat(SS_INT,random(5)+30);
    set_base_stat(SS_WIS,random(5)+30);
    set_base_stat(SS_DIS,random(5)+55);
    set_alignment(-50);
    set_skill(SS_WEP_SWORD, random(5)+40);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY,30);
    set_skill(SS_AWARENESS,30);
    set_skill(SS_SNEAK,30);
    set_skill(SS_HIDE,30);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
}

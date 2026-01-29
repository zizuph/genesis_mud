#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

void
create_krynn_monster()
{
    set_name("alvaren");
    set_title("Nevril, the Blind Guard of the Fountain of Blood");
    set_race_name("human");
    set_adj("black-skinned");
    add_adj("eyeless");
    set_gender("G_MALE");
    set_long("You stand before a tall human. His head is shaved and covered with"+
                     " tatoos. His eye-sockets are empty, however, you have the feeling"+
                     " that he notice you.\n"+
                     " His hands are covered with blood. most likely from the fountain."+
                     " Every day he brings Lord Soth a cup filled at the fountain to drink"+
                     " in order to let him taste the pain he has caused in the centuries "+
                     " past.\n");

    set_stats(({200, 160, 160, 100, 90, 160}));

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    
    set_alignment(-600);
    add_prop(LIVE_I_UNDEAD, 100);
    set_act_time(9);      
    add_act("emote looks at the fountain in deep thoughts.");
    add_act("emote moves his hand through the liquid of the fountain.");
    add_act("say The fountain bears the blood and sorrow shed by Lord Soth and his men.");
    add_act("say Drink from the fountain, close your eyes and you will see your "+
            "masters sins and your own.");

    set_introduce(1);   
}


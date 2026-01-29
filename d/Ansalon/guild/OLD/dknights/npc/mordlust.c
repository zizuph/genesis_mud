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
    set_name("Mordlust");
    add_name("trainer");
    set_title("of the Abyss' sixth circle, Dargaard Keep's Master of Arms");
    set_race_name("human");
    set_adj("tatooed");
    add_adj("chain-wrapped");
    set_short("tatooed chain-wrapped female human");
    set_gender(G_FEMALE);
    set_long("You stand before a slender but muscular figure totally shrouded and"+
                     " wrapped in chains. Chains are dangling over her shaven head and a"+
                     " veil of spiked and edged chains hides her facial features.\n"+
                     " She resembles a human except for the strange yellow-glowing eyes."+
                     " However, you have heard of this infamous figure. She is a devil killed by Lord"+
                     " Soth's own hands in the Abyss and brought back to Dargaard Keep to train"+
                     " his knights. "+
                     "She is very good in her job since she still possess her ability to control"+
                     " her chains or, in fact any chains within 15 feet, with her will. One becomes"+
                     " really good in in no time in dodging and defending and  as well at desperate"+
                    " attacks when several barbed and wicked-edged chains shoot at you from"+
                    " several angles.\n");

    set_stats(({160, 160, 160, 100, 90, 160}));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    
    set_alignment(-1000);

    set_act_time(9);      
    add_act("emote 's chains snake around her and the barbed tips creep through the air like"+
                    " snake heads.");
    add_act("emote regards you with her glowing yellow eyes.");
    add_act("say Train or feel the pain my chains deliver!.");
    add_act("say Outside the training hall you are a noble but inside you are mine.");
    add_act("Soth killed me so that I may train you. Never forget this honour! Now"+
                   " show what you have learned.");

    set_cact_time(0);

    set_introduce(1);   
    add_cact("say You shall meet your maker! Prepare to die!");
}
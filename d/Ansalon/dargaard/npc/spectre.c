/*************************************************
 * Name     : spectre                            *
 * Location : Dargaard keep                      *
 * Made by  : Elmore                             *
 * Date     : April, 2001                        *
 *************************************************/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <options.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h";

inherit AM_FILE

string *face = ({"dreaded", "lethal", "ethereal"});

int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}



void
create_krynn_monster()
{
    string faces        = face[random(sizeof(face))]; 

    set_race_name("human");
    set_name("spectre");
    add_adj(faces);
    set_short(faces+ " spectre");
    set_long("This is one of the many creatures which "+
             "still hunts the Dargaard Keep. They were "+
             "unfortually stuck inside the Keep when "+
             "it burned to the ground. Now they are "+
             "trapped within these walls, hunting "+
             "anything that is alive.\n");

    set_stats(({(random(50)+10),150,104,89,78,250}));

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_UNARM_COMBAT, 85);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    add_prop(LIVE_I_UNDEAD, 100);
    set_gender(G_NEUTER);
    set_aggressive(VBFC_ME("check_aggressive"));

    /* Trolls can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_alignment(-1150);
    set_knight_prestige(200);

    set_all_hitloc_unarmed(10);

    MONEY_MAKE(random(10),"gold")->move(TO,1);  

    set_alignment(-1200);
    add_prop(CONT_I_WEIGHT, 400);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);

    set_random_move(30); 
    
    set_act_time(random(40));
    add_act("scream");
    add_act("scream");
    add_act("scream");
    add_act("cackle");
    add_act("grin");
    add_act("grin");

    command("wield all");
    command("wear all");
}

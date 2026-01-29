inherit "/d/Raumdor/std/monster";
#include "defs.h"
// Sarr.
/* Added header for stats. Nerull - 09*/

void
create_monster()
{
    ::create_monster();
    set_name("child");
    set_race_name("human");
    set_adj(({"little", "cute"}));    
    set_short("little cute child");
    set_gender(one_of_list(({G_MALE, G_FEMALE})));
    if (query_gender() == G_MALE)
        set_long("This is a little cute boy. He runs around with healthy " +
            "vigor. He smiles and plays with his toys.\n");
    else 
        set_long("This is a little cute girl. She giggles and bounces around " +
            "freely. She is full of curious vigor.\n");
    set_stats(STAT_ARRAY(30));
    set_alignment(DRAKMERE_ALIGN);
    set_act_time(6);
    add_act("giggle");
    add_act("say Mommy! Who is that stranger?");
    add_act("emote rolls around.");
    add_act("bounce");

    add_prop(LIVE_I_NEVERKNOWN, 1);
   
    equip(({
        query_gender() == G_MALE ?
            DRAKMERE_ARM_DIR + "c_pants" : DRAKMERE_ARM_DIR + "c_skirt",
        DRAKMERE_ARM_DIR + "c_shirt",
        DRAKMERE_ARM_DIR + "c_toy",
    }));
}

void
do_die(object who)
{
    who->add_prop(IS_ENEMY_OF_DRAKMERE,
            who->query_prop(IS_ENEMY_OF_DRAKMERE) + 1);
    
    ::do_die(who);
}


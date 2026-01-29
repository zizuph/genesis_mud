/*
    man-slave.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("man-slave");
    set_adj("muscular");
    add_adj("tan");
    add_name("slave");
    set_race_name("human");
    set_short("tan muscular man-slave");
    set_long("This large and muscular slave is completly naked. "+
        "He sits in the bath with his Mistress, washing her clean. "+
        "His strong, powerful arms and dark handsome features make "+
        "you wonder how her Mistress could resist demanding more than "+
        "just a bath.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    set_stats(({100,80,100,40,50,70}));
    set_skill(SS_DEFENSE,60);
    set_skill(SS_UNARM_COMBAT,60);
    set_act_time(5);
    add_act("emote soaps up the back of his Mistress.");
    add_act("carress samantha sensu");
    add_act("emote lathers up the scrub brush.");
    add_act("lick samantha slow");
    add_act("say Is this how you like it, my Mistress?");
    add_act("emote runs his tongue along his Mistress' neck.");
    add_prop(LIVE_I_NEVERKNOWN,1);
}

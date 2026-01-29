/* Undead Troll, Sarr */
/* 2017-08-19 Malus: Added set_mm_in, moving defaults to base/std file */

#include "defs.h"
inherit STD_UNDEAD;

void
create_monster()
{
    ::create_monster();
    set_name("troll");
    set_race_name("troll");
    set_adj("foul");
    add_adj("reeking");
    set_short("foul reeking troll");
    set_long("This huge troll is one of the most horrible sights you have"+
    " ever laid your eyes on. It is clearly undead. Its reeking, maggot "+
    "infested fur and skin, eyeless eye sockets, and massive build make it"+
    " look like one of the most terrible creatures you have ever encountered"+
    " in your life. It stares at you with hatred.\n");
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_DEFENCE,80);
    set_skill(SS_PARRY,85);
    set_skill(SS_2H_COMBAT,80);
    add_prop(OBJ_I_WEIGHT,30000);
    add_prop(OBJ_I_VOLUME,28000);
    add_prop(LIVE_I_UNDEAD,45);
    set_random_move(10);
    set_act_time(5);
    add_act("emote grunts.");
    add_act("emote wants to rip out your spine and add it to its collection.");
    set_cact_time(3);
    add_cact("say Me smash you brains out, den me eat dem!");
    add_cact("emote can't wait to feast on your warm corpse.");
    set_mm_in("smashes its way into your path!");

    equip(({
        COMMON_WEP_DIR + "utclub",
        COMMON_WEP_DIR + "utclub",
        COMMON_ARM_DIR + "utplate",
    })); 
}


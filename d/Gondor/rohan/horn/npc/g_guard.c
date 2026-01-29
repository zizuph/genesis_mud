/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/rohan/horn/npc/guard.c";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_extra_desc("");
    set_guard_type(1);
    ::create_monster();
    set_base_stat(SS_STR,random(5)+45);
    set_base_stat(SS_DEX,random(5)+40);
    set_base_stat(SS_CON,random(5)+40);
    set_base_stat(SS_INT,random(5)+30);
    set_base_stat(SS_WIS,random(5)+30);
    set_base_stat(SS_DIS,random(5)+45);
    set_skill(SS_WEP_POLEARM, random(5)+40);
    set_skill(SS_DEFENCE,30);
    set_skill(SS_PARRY,30);

    /* don't want the standard chats in these guards */
    clear_chat("I hate orcs.");
    clear_chat("Saruman is up to no good. I can feel it!");
    clear_chat("Orcs are the most vile beasts! All should die!");
    clear_chat("Who are you, and what are you doing in this land?");
    clear_chat("There is trouble on all of our borders.");
    clear_chat("What news from Gondor, stranger?");
    clear_chat("Stormcrow is the herald of strange events.");
    clear_chat("Plundering orcs carry off our black horses!");
    clear_chat("No foe has ever taken the Hornburg, if men defended it.");
}

public void
enter_env(object inv, object from)
{
    object erk;

    ::enter_env(inv, from);

    if ( objectp(erk = present("erkenbrand", ENV(TO))) &&
    query_leader() != erk )
	erk->team_join(TO);
}

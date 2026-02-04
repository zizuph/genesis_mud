/* /d/Terel/mountains/ghastly_keep/npc/g_spider.c
 *
 * A spider in the ghastly keep, just for decoration.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */
inherit "/std/monster";

#include "defs.h"
#include "../npc_stats.h";

void remove_spider(); 

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_monster()
{
    seteuid(getuid());

    set_race_name("spider");
    set_name("spider");
    add_name("_ghastly_keep_npc");
    add_name("ghastly");

    set_adj("black");
    set_adj("hairy");
    add_adj("spider");

    set_short("black hairy spider");

    set_gender(G_FEMALE);

    set_long("This black hairy spider is no larger than a tooth. "
            + "She's rushing in seemingly random directions. Her "
            + "face is covered with eight eyes shining like blackened "
            + "pin heads, and her mandibles are making a clicking sound.\n");

    add_prop(CONT_I_WEIGHT, 1100);
    add_prop(CONT_I_HEIGHT, 10);

    default_config_creature(30 + random(15));

    add_prop(LIVE_I_SEE_DARK,      1);
    add_prop(LIVE_I_NEVERKNOWN,    1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_appearance_offset(40);

    set_act_time(15);
    add_act("emote scurries around the web in seemingly random directions.");

}

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    set_alarm(0.1, 0.1, remove_spider);
}

void
remove_spider()
{
    tell_room(ETO, QCTNAME(TO)+ " rushes for the nearest exit.\n", (TO));
    TO->remove_object();
}
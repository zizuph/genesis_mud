/*
 * /d/Gondor/guilds/militia/npc/trainer.c
 *
 * This code is copyright (c) 2001 by Scott A. Hardy and Alyssa Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott and Alyssa Hardy have seen the 1991 document of Genesis'
 * called 'legal', and they do not forfeit any of their intellectual
 * property rights as that document supposes they would.  They are the
 * sole and complete owners of this code, which as of April 2001 they are
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of their code, Genesis acknowledges and agrees
 * to all of the above.
 *
 * Trainer for Thornlin Militia
 *
 * Coded by Auberon and Gwyneth
 */
inherit "/d/Gondor/std/monster";

#include "../attackers.c"
#include "../militia.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_gondor_monster()
{
    set_name("balan");
    add_name("trainer");
    add_name("man");
    set_title("the Relentless Goblinbane of the Thornlin Militia");
    set_race_name("human");
    set_long("This is a very muscular man. He looks wise and experienced, " +
        "and in charge of the training room.\n");
    set_short("muscular swift male human");
    set_adj(({"muscular", "swift"}));

    default_config_npc(130);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_AWARENESS,   65);
    set_skill(SS_HIDE,        25);
    set_skill(SS_DEFENCE,     50);
    set_skill(SS_PARRY,       50);
    set_skill(SS_APPR_MON,    50);
    set_alignment(350);
    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);
    set_money(({ random(20), random(10), random(5), random(2) }));
    set_equipment(({ (TOBJ + "cloak"), (TOBJ + "hauberk"),
        (TOBJ + "gauntlets"), (TOBJ + "spear") }));
    add_ask_item(({"militia", "thornlin militia"}),
        "say We are the Thornlin Militia! We protect our town from " +
        "invading orcs, goblins and wolves.");
    add_ask_item(({"orcs", "goblins", "wolves", "wolf", "goblin", "orc"}),
        ({"scowl", "say They are servants of the East!",
          "say There seem to be more of the East's foul servants about lately.",
          "say I've killed many in my day!"}));
    set_default_answer( ({ "say I'm not sure I know what you're talking about.",
        "say Ask someone else, I can't say.", "emote is lost in thought.",
        "say Are you here to train?" }) );
}

void
intro_me(object name)
{
    command("say to " + OB_NAME(name) + " A pleasure to meet you!");
    command("introduce me to " + OB_NAME(name));
}
 
void
add_introduced(string str)
{
    object who = find_living(str);
    if (member_array("Balan", m_indexes(who->query_introduced())) == -1)
        set_alarm(2.8, 0.0, &intro_me(who));
}

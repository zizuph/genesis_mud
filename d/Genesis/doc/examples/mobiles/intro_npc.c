/*
 * /doc/examples/mobiles/intro_npc.c
 *
 * This is a very simple example of an npc that reacts to introductions.
 */

inherit "/std/monster";

/* Inherit this file to allow the npc to react to introductions */
inherit "/d/Genesis/lib/intro";

#include <const.h>   // for G_MALE
#include <macros.h>  // for OB_NAME

void
create_monster()
{
    set_name("bob");
    set_race_name("human");
    set_adj("friendly");
    set_gender(G_MALE);
    set_stats(({ 20, 20, 20, 20, 20, 20 }));
}

/*
 * This is called if the person has already been introduced before.
 * Note that you don't need to define this function.  If you don't,
 * define it, a default routine will be executed.
 */
void
greet(object who)
{
    command("say Nice to meet you again, " + who->query_name() + "!");
    command("smile");
}

/*
 * This is called if the person has not been introduced before.
 * Note that you don't need to define this function.  If you don't
 * define it, a default routine will be executed.
 */
void
introduce(object who)
{
    /* Note that we use OB_NAME(who) rather than who->query_real_name()
     * here.  OB_NAME always gives a unique name, so it should always
     * be used in place of the standard name when targeting a command.
     *
     * Imagine a situation where a player named "Paladin" introduces
     * to this npc, and a paladin npc is in the room as well.  Doing
     * "introduce myself to paladin" might introduce me to the player
     * *or* the npc.  Using OB_NAME will avoid any such problems.
     */
    command("introduce myself to " + OB_NAME(who));
    command("say A pleasure to meet you, " + who->query_name() + "!\n");
}

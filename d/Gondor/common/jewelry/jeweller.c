/*
 * /d/Gondor/common/jewelry/jeweller.c
 *
 * The storekeeper for the jewelry shop.
 *
 * Coded by Gwyneth, 08/26/02
 */
inherit "/d/Gondor/std/monster.c";

#include <macros.h>

public int
no_attack()
{
    write("A very tough looking bodyguard picks you up off your feet and " +
        "pushes you out of the store.\n");
    say("A very tough looking bodyguard picks " + QTNAME(this_player()) +
        " up off " + this_player()->query_possessive() + " feet and " +
        "pushes " + this_player()->query_objective() + " out of the store.\n");
    this_player()->command("&south");
    return 1;
}

public void
create_gondor_monster()
{
    set_name("theodore");
    set_race_name("human");
    set_adj(({ "grey-haired", "spectacled" }));
    set_title(", Master Jeweller and Craftsman");
    set_long("He looks very distinguished and wise with his gold-rimmed " +
        "spectacles. He is dressed in formal attire, and decorated with " +
        "examples of his work.\n");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " says: Put any gems you want me to use " +
        "on the counter.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, &no_attack());
    add_prop(OBJ_I_NO_ATTACK, &no_attack());
    add_ask_item(({ "jewelry", "buy" }), ({ ({ "say We have lovely items! " +
        "Won't you take a closer look?",
        "emote beckons you to look in the glass display." }) }));
    add_ask_item(({ "offer", "gems", "offer gems", "gem", "counter" }),
        ({ ({ "say When you are done ordering a piece of jewelry that " +
        "needs gems, please put the exact number of gems on the counter.",
        "say Then 'offer gems' so I can begin my work.", "say Don't worry " +
        "about anyone stealing your gems. I keep special track of each " +
        "person's gems!" }) }));
    set_default_answer("say Have you read the instructions and sign yet?");
    default_config_npc(100);
}

public void
introduce(object player, string who)
{
    if (!objectp(player))
        return;
    if (!interactive(player))
        return;

    if (!present(player, environment(this_object())))
        return;

    set_alarm(1.0, 0.0, &command("introduce myself to " + OB_NAME(player)));
    set_alarm(2.3, 0.0, &command("say It's a pleasure to meet you! " +
            "What lovely item may I show to you today?"));
    return;
}

public void
add_introduced(string who)
{
    object  player;

    player = find_player(who);
    if (!objectp(player) || player->query_met(query_real_name()))
        return;
    set_alarm(2.0, 0.0, &introduce(player, who));
}

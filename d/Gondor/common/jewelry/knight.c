/*
 * /d/Gondor/common/jewelry/knight.c
 *
 * The Knight in charge of the orders of chivalry
 *
 * Coded by Gwyneth, 08/26/02
 */
inherit "/d/Gondor/std/monster.c";

#include <macros.h>

public int
no_attack()
{
    write("The Knight draws his sword quickly " +
        "and presses it against your throat. As he glares at you, you " +
        "back down. Obviously there will be no fighting here.\n");
    say(QCTNAME(this_object()) + " draws his sword quickly and presses " +
        "it against " + this_player()->query_possessive() + " throat. " +
        "As " + QTNAME(this_object()) + " glares at " + 
        this_player()->query_objective() + ", " + QTNAME(this_player()) +
        " backs down. Obviously there will be no fighting here.\n");
    return 1;
}

public void
create_gondor_monster()
{
    set_name("oliver");
    add_name("knight");
    set_title("the Knight Grand Cross");
    set_race_name("human");
    add_adj(({ "charming", "courteous" }));
    set_long("From his dress, he appears to be a knight from Dol Amroth. " +
        "A scabbard hangs from his belt, where a very deadly looking sword " +
        "is sheathed. His calloused hands and battle scarred face show " +
        "him to be a very skilled fighter. Yet his eyes show a kindness " +
        "and gentleness that one wouldn't expect to see in such a " +
        "battle-hardened warrior.\n");

    add_prop(OBJ_M_NO_MAGIC_ATTACK, &no_attack());
    add_prop(OBJ_I_NO_ATTACK, &no_attack());
    default_config_npc(100);
    add_ask_item(({ "order", "orders", "found", "found order" }),
        ({ ({ 
        "say You want to found an order?",
        "say Well, it costs five hundred platinum.",
        "say Once you have that, you can 'found order-name'.",
        "say You'll want to select your order emblem and colour.",
        "say Then 'pay for order-name' and go next door to get your regalia."
        }) }));
    add_ask_item(({ "fire", "fireplace" }), ({ ({"emote looks puzzled",
        "say You know, I think it's a secret passageway!",
        "say People go inside and never come out.", "think",
        "say Either that, or it leads to some monster and they're eaten!"})}));
    set_default_answer(({ "say Have you read the book yet?",
        "say Maybe it's in the book." }));
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
    set_alarm(2.3, 0.0, &command("emote bows respectfully."));
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

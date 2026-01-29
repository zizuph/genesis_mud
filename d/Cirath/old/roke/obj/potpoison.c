/*
 * potpoison.c
 *
 * Used in obj/pot.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/poison_effect";

#include <poison_types.h>

void
create_poison_effect()
{
    ::create_poison_effect();

    set_interval(15);
    set_time(200);
    set_poison_type("vegetable");
    set_strength(500);

    set_damage(({POISON_HP, -3}));

    poisonee = environment(this_object());
}

void
calm()
{
    poisonee->catch_msg("This is really some good grass!\n");
    poisonee->catch_msg("You can feel it doing miracles with your body.\n");
}

void
feelgood()
{
    poisonee->catch_msg("You feel extremly good!\n");
}

void
tell_damage_player(int i, string s)
{
    int j;

    object ob;

    ob = poisonee;

    j = random(6);

    switch (j)
    {
    case 0:
        ob->catch_msg("The world seems to turn for a moment.\n");
        break;
    case 1:
        ob->catch_msg("Some pink elefants dance before your eyes.\n");
        break;
    case 2:
        ob->catch_msg("Worms are crawling on your legs.\n");
        break;
    case 3:
        ob->catch_msg("An uncomfortable itch spreads on your body.\n");
        break;
    case 4:
        ob->command("choke");
        break;
    case 5:
        ob->command("puke");
        break;
    }

    set_alarm(itof(1+random(10)), 0.0, feelgood);
}

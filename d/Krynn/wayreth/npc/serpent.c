/*
 * Filename:        wayreth\npc\serpent.c
 * Description:     This serpent is a living staff, its counter part can be found in
 *                  wayreth\obj\staves\serpents.c, red robes can use this staff which
 *                  at a word of command will transform into a serpant protecting them
 *                  from attack.
 *                  Maybe the wizard should be disallowed to cast any spells while the
 *                  serpent is alive?
 *
 * Copyright (c) Nov 2000 by Daniel W. Mathiasen, Boron@Genesis
 *
 * Revision history:
 *
 */
#pragma strict_types


#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";


inherit "/std/creature";
inherit "/std/combat/unarmed";

public void
create_creature()
{
    set_name("snake");
    set_short("snake");


    set_stats( ({ 100, 100, 100, 100, 100, 100 }), 20);

}

public int
special_attack(object victim)
{
    object snake;
    mixed *hitresult;
    string how;
    int pen;
    int stat_avg;

    snake       = this_object();
    stat_avg    = snake->query_stat_average();

    // set the penetration of the special to be the stat average of the snake
    // unless, though we cap at 60
    pen = stat_avg > 60 ? 60 : stat_avg;

    hitresult = victim->hit_me( pen , W_IMPALE, snake, -1);

    switch (hitresult[0])
    {
        case 0:
            how = " snaps";
            break;
        case 1..30:
            how = " leaps mouth first and snaps";
            break;
        case 31..50:
            how = " leaps wildly at you with the fangs biding";
            break;
        default:
            how = " carefully snap";
            break;
    }

    victim->catch_tell(query_The_name(victim) + how + " into your " +
                        "flesh leaving nothing but the sensation of wild " +
                        "flames in your vanes.\n");
    tell_watcher(QCTNAME(snake) + how + " into " + QTNAME(victim) + ".\n");

    if (victim->query_hp() <= 0)
    {
        victim->do_die(this_object());
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}
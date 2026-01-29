/*
 * /d/Emerald/common/guild/vamp/npc/lost_player.c
 *
 * This is the base file for the wandering npcs who
 * are supposed to seem like players lost in the mist
 * which surrounds the vampire guild.
 *
 * Copyright (c) October 2000, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/d/Emerald/std/emerald_monster";
inherit "/d/Genesis/lib/intro.c";

#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>

/* prototypes */
public void    create_lost_player();
public void    create_emerald_monster();
public void    introduce(object who);
void           react_intro(object tp);


/*
 * Function name:        create_lost_player
 * Description  :        dummy routine for inheriting files
 */
public void
create_lost_player()
{
} /* create_lost_player */


/*
 * Function name:        create_emerald_monster
 * Description  :        set up the npc
 */
public void
create_emerald_monster()
{
    set_random_move(5);
    
    create_lost_player();
} /* create_emerald_monster */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */

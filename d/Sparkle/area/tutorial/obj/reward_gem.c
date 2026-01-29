/*
 *  /d/Sparkle/area/tutorial/obj/reward_gem.c
 *
 *  This gem is given out by:
 *    /d/Sparkle/area/tutorial/npc/hetzel.c
 *  to players who complete a conversation tree which leads
 *  to the reward. It can only be given once to any player.
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

/* Prototypes */
public void        create_gems();


/* 
 * Function name:        create_gems
 * Description  :        set up the gem
 */
public void
create_gems()
{
    add_name("_tutorial_item");
    config_gems("gemstone", "gemstones", "blue", 8000, 
        GEM_VERY_COMMON, 50, 82);
    set_long("@@default_gem_long@@ Gems are a special type"
      + " of object in Genesis. Like money, they will stay"
      + " with you over multiple logins. This one is worth"
      + " some money. You should take it to the General Store"
      + " in Greenhollow and sell it. Then take the money you"
      + " earn and train skills in the Adventurer Guild.\n");
} /* create_gems */


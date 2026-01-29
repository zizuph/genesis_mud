/* /d/Gondor/guilds/defenders/rooms/train.c
 *
 * Defenders, guildhall.
 *
 * Nerull, 2016
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "defs.h";
#include "../guild.h";

inherit DEF_STD_ROOM;
inherit "/lib/skill_raise";

void set_up_skills();


public void
create_def_room()
{
	set_short("Some room");
	set_long("This is a temporary room.\n");

    create_skill_raise();
    set_up_skills();

    add_exit(DEF_GUILDDIR + "rooms/h2_1",   "south");

    reset_room();
}


public void
init()
{
    init_skill_raise();
    ::init();
}


void
set_up_skills()
{
    string to;

    //--------------------------------------------------


    // Offensive special
   // sk_add_train(SS_LYCAN_RAVAGE, "use ravage",
     //   "ravage", 80, 100);

    // Defensive special
    //sk_add_train(SS_LYCAN_REGEN, "use unnatural regeneration",
      //  "regeneration", 80, 100);

    //--------------------------------------------------

    to = "fight better while unarmed or with claws";
    sk_add_train(SS_UNARM_COMBAT,                ({ to, to }),  0,0, 100);

    to = "fight better while blinded";
    sk_add_train(SS_BLIND_COMBAT,                ({ to, to }),  0,0, 80);

    to = "defend yourself";
    sk_add_train(SS_DEFENCE,                     ({ to, to }),  0,0, 95);

    to = "sense your environment";
    sk_add_train(SS_AWARENESS,                   ({ to, to }),  0,0, 90);

    to = "sense your true location";
    sk_add_train(SS_LOC_SENSE,                   ({ to, to }),  0,0, 90);

    to = "sense your true location";
    sk_add_train(SS_TRACKING,                ({ to, to }),  0,0, 80);

    //to = "defend yourself";
    //sk_add_train(SS_PARRY,                  ({ to, to }),  0,0, 90);

    //**************************************************************



}


void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;



    rank = sk_rank(to_lev);

    this_player()->catch_msg("You teach yourself to "+
        sk_tdesc[snum][0] + " better.\n");
    write("You achieve the rank of " + rank + ".\n");
    say(QCTNAME(this_player()) + " teaches "+this_player()->query_objective()+"self to "+
        sk_tdesc[snum][1] + " and receives "+
        "the rank of " + rank + ".\n");
}


int
sk_improve(string str)
{
    if (this_player()->query_guild_name_lay() != GUILDNAME_OCC)
    {
        write("You are not allowed to train here!\n");
        return 1;
    }

    return ::sk_improve(str);
}


void
reset_room()
{
   
}


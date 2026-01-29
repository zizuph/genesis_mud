
 /* Spiritwalkers Training Room for the Walkers of Thalassia */
 /* by Jaacar 1998                               */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

#include "spirit_skills.h"

void
create_room()
{
    set_short("Training chamber");
    set_long("You are on a plateau in the middle of a desert stretching "+
        "as far as you can see in all directions.  A steady blistering "+
        "wind blows here, carrying with it the scent of sulphur and "+
        "brimstone.  The sky is dark red and clouds of fire drift unnaturally "+
        "fast across the barren landscape.  You find the heat here pleasing.  "+
        "Unintelligible words in a forgotten language seem to play "+
        "across your mind.  This must be the elemental plane of fire, "+
        "from where you draw your power.  Lord Pyros seems closer here, "+
        "beckoning you just at the edge of your consciousness.  "+
        "You feel somehow that if you would just 'concentrate', secrets "+
        "of all you could 'learn' would be revealed to you.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(PSUCHAE_ROOM,"south",0,1);

    create_skill_raise();
    set_up_skills();
}

void
init()
{
    ::init();
    init_skill_raise();
    add_action("sk_improve","concentrate");
    add_action("check_improve","improve");
}

int
query_prevent_snoop()
{
    return 1;
}

int
check_improve(string str)
{
    write("To improve your skills here you must 'concentrate' upon them.\n");
    return 1;
}

public int
sk_improve(string sk)
{
    if (TP->query_skill(SS_WALKER_PUNISHMENT) == TRAIN_BANNED)
    {
        write("You have been banned from training by the council!\n");
        return 1;
    }
    return ::sk_improve(sk);
}

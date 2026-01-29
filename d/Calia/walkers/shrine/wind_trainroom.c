
 /* Windwalkers Training Room for the Walkers of Thalassia */
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
#include WIND_HEADER
#include COUNCIL_HEADER

#include "wind_skills.h"

void
create_room()
{
    set_short("Training chamber");
    set_long("You are floating in mid-air.  The blue sky seems "+
        "to extend in all directions.  Clouds of all shapes and "+
        "sizes float around, some rushing as if blown by a "+
        "hurricane, others gently drifting.  You have a hard time "+
        "orienting yourself here ; you can't see the ground, and "+
        "you are completely weightless.  Soon you become "+
        "accustomed to how this world works, and are able to "+
        "lazily drift around among these clouds, only by willing "+
        "yourself to do so.  This must be the plane of "+
        "elemental Air, from where you draw your powers.  Lady "+
        "Aeria seems closer here, beckoning you just at the edge "+
        "of your consciousness.  You feel that if you could "+
        "just 'concentrate', secrets would be revealed to you "+
        "of all the wonders you could 'learn' here.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(AERIA_ROOM,"southeast",0,1);

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

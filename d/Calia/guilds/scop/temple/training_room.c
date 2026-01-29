
/*
 * training_room.c
 *
 * Training room for the Spirit Circle of Psuchae Temple
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

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
    set_short("An austere silver chamber");
    set_long("You have entered what appears to be the most austere "+
        "chamber in the temple, with silvery-grey walls and a cold "+
        "floor made up of stone tiles adorned with the triple-ring "+
        "emblem of Spirit. Woven white rugs with silver and gold "+
        "threads are placed at even intervals, at which you may kneel to "+
        "learn and concentrate upon the wisdom that Psuchae might reveal.\n");

    add_item(({"rug","rugs","prayer rug","prayer rugs"}),"These prayer "+
        "rugs are here to kneel on while concentrating on your studies.\n");
    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"bank","north",0,1);
    add_exit(SPIRIT_TEMPLE+"chapel","south",0,1);
    create_skill_raise();
    set_up_skills();
}

public varargs int
sk_query_max(int snum, int silent)
{
    if (snum != SS_ELEMENT_SPIRIT)
        return ::sk_query_max(snum, silent);

    if (TP->test_bit("Calia", SCOP_GURU_GROUP,
        SCOP_GURU_BIT))
        return ::sk_query_max(snum, silent);

    return 90;
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
    if (TP->query_skill(SS_SPIRIT_PUNISHMENT) == TRAIN_BANNED)
    {
        write("You have been banned from training by the council!\n");
        return 1;
    }
    return ::sk_improve(sk);
}

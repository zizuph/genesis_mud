/*
    The room is immediately outside the Marble Tower.    

    Bishop, July 2003.
*/

#pragma strict_types

inherit "/std/room";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"

object guardian;

void
reset_room()
{
    setuid();
    seteuid(getuid());

    if (!objectp(guardian))
    {
        guardian = clone_object(TOWER_NPCS + "guardian");
        guardian->move_living("M", TO);
    }
}

void
init_college_training()
{
    sk_add_train(SS_WEP_POLEARM, "attack with a polearm", "polearm",
        50, 50, SS_DEX, 40);
    sk_add_train(SS_DEFENCE, "defend oneself in combat", "defence", 50, 50,
        SS_DEX, 40);
}


int
sk_hook_cant_train(string skill, int to_lev)
{
    notify_fail("You fail to adopt what Myam teaches you.\n");
    return 0;
}

int
sk_hook_no_list_improve()
{
    write("You cannot improve further with Myam's aid. Perhaps you" +
        " can learn a new skill, or train elsewhere?\n");
    return 1;
}

int
sk_hook_no_list_learn()
{
    write("Myam cannot teach you anything new. Perhaps you could improve" +
        " an existing skill, or train elsewhere?\n");
    return 1;
}

public int
sk_improve(string sk)
{
    if (!objectp(guardian))
    {
        write("Noone is here to train you.\n");
        return 1;
    }

    if (!strlen(TP->is_college_member()))
    {
        write(guardian->query_The_name(TP) + " refuses to give you any" +
            " training.\n");
        return 1;
    }

    return ::sk_improve(sk);
}

int
may_enter()
{
    if (TP->query_wiz_level())
    {
        write("As you are a wizard, you are let into the Marble Tower.\n");
        return 0;
    }
    
    if (strlen(TP->is_college_member()))
    {
        write("You enter the Marble Tower.\n");
        return 0;
    }
    
    if (objectp(guardian))
    {
        guardian->command("say You do not study here, " + TP->query_race_name()
            + ". I forbid you to enter.");
        return 1;
    }
    
    write("You try to enter the tower, but for each step you take towards" +
        " the entrance, you feel as if someone stabs you with a knife." +
        " The excruciating pain stops you long before you get within" +
        " arm's length of the entrance.\n");
    say(QCTNAME(TP) + " approaches the entrance to the tower, but stops" +
        " short and drops to " + TP->query_possessive() + " knees with" +
        " a pained expression.\n"); 
    return 1;
}


void
create_room()
{
    set_short("At the base of a tall marble tower");
    
    set_long("You have arrived just outside a tall, strange tower" +
        " in the mountains. Fashioned entirely out of what appears to" +
        " be marble, it is square at the base, then narrows into a" +
        " cylinder and tops off with a clear dome. The location" +
        " itself commands a spectacular view of western Calia. A narrow path" +
        " from the tower takes you around an outcropping to the north," +
        " while passage in any other direction is blocked by rough" +
        " terrain.\n");
    
    add_item(({"tower", "tall tower", "strange tower", "tall, strange" +
        " tower"}), "This tower must reach at least a hundred feet into" +
        " the air. The construction is seamless, as if it were carved" +
        " from a single slab of marble. No windows can be seen.\n"); 
    add_item(({"dome", "clear dome"}), "It is too high up to get a" +
        " good reading on what it is made out of, and from this angle" +
        " it is hopeless to see through it.\n");
    add_item("outcropping", "It is just a natural bulge in the ridge" +
        " that obscures your view of where the path ends up.\n");
    add_item("ridge", "This ridge runs along the side of the mountain." +
        " You are closer to the base of the mountain than to the top.\n");               
    add_item("base", "The base of the tower is perfectly square.\n");
    add_item("view", "You have a great view of the foothills of Mt. Kyrus" +
        " to the southwest, further north you see the city of Gelan.\n");
    add_item(({"entrance", "gate"}), "The only way to enter the tower" +
        " appears to be through this simple, unlocked gate.\n");
    
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_HIDE, 90);
    
    add_exit(TOWER + "tower_outside2.c", "north", 0);
    add_exit(TOWER + "tower_corr_1_1.c", "in", "@@may_enter");
    reset_room();
    init_college_training();
}

void
init()
{
    ::init();
    init_skill_raise();
}


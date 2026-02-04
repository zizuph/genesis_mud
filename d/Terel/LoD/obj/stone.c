/*
 * stone.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#define LETTER  (LOD_DIR + "obj/letter")

int found = 0;

public void
create_object()
{
    set_name("stone");
    add_name("wall_stone");
    set_adj("rectangular");
    
    set_long("It's a well-cut rectangular huge stone. It looks as if it " +
             "used to be in a wall.\n");
    
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 28000);
    add_prop(OBJ_M_NO_GET, "It's too heavy to be taken.\n");
}

public int
do_turn(string str)
{
    notify_fail("Turn what?\n");
    if (!str || !id(str))
        return 0;
       
    if (TP->query_fatigue() < 20)
    {
        write("You are too tired right now to even make an attempt!\n");
        TP->command("$sweat");
        return 1;
    }

    if (TP->query_stat(SS_STR) > 85 + random(11))
    {
        write("By gathering all your strength, you manage to turn the " +
              short() + ".\n");
        say(QCTNAME(TP) + " turns the stone.\n");
        TP->add_fatigue(-15);
        if (!found)
        {
            tell_room(ETO, "Something was hidden under the stone!\n");
            seteuid(getuid());
            clone_object(LETTER)->move(ETO);
            found = 1;
        }
        return 1;
    }
    else if (TP->query_stat(SS_STR) > 58 + random(11))
    {
        write("For a short while you thought that the " +
                       "stoned moved.\n");
    }
    else
    {
        write("Ouch. It is too heavy.\n");
    }
    TP->add_fatigue(-15);
    TP->command("$sweat");
    say(QCTNAME(TP) + " tries to turn the " + short() + ".\n");
    return 1;
}

public void
init()
{
    ::init();
    
    add_action(do_turn, "turn");
}

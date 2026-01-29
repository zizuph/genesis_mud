inherit "/std/object";

#include "../defs.h"
#include <macros.h>
#include "/d/Emerald/lib/quests.h"
#define RIGHT_PLACE    "/d/Emerald/graveyard/graveyard"
#define FOUND_GRAVE     "_i_have_found_grave_"
#define PLAYER_O_GIVEN  "_flowers_given_to"

int plant(string str);

create_object()
{
    set_short("bunch of flowers");
    set_name("flowers");
    add_name(({"bunch of flowers", "_emerald_quest_flowers_"}));
    set_adj("wild");
    set_long("These are some simple wild flowers dug up with their roots. A " +
             "cloth has been tied carefully around their roots to keep " +
             "them from drying up.\n");

    add_prop(OBJ_I_VOLUME, 2348);
    add_prop(OBJ_I_WEIGHT, 439);
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_S_WIZINFO, "These flowers are used in a quest to plant them" +
             " on a grave. You can plant the flowers at grave when you " +
             "have found the proper grave in ~Emerald/graveyard/something.\n");
    getuid();
    seteuid(getuid()); 
}

void
init()
{
    ::init();
    add_action(plant, "plant");
}

int
plant(string str)
{
    object ob = query_prop(PLAYER_O_GIVEN);
    
    NF("Plant flowers?\n");
    if (!str)
        return 0;
    NF("You better have the flowers before you try to do anything with " +
       "them.\n");
    if (TP != ENV(TO))
        return 0;
    if (MASTER_OB(ENV(TP)) == RIGHT_PLACE)
    {
        NF("Plant flowers where?\n");
        if (!parse_command(str, environment(), " [the] [wild] 'flowers' [on]" +
                       " [at] [the] 'grave' "))
            return 0;
        write("You plant the flowers at the grave.\n");
        if (TP == ob)
        {
            write("In the corner of your eye you glimpse a ghosty " +
                  "appearance of a lady regarding you with a serene " +
                  "expression. As soon as you turn towards her she " +
                  "dissapears without a trace.\n");
            if (TP->test_bit("Emerald", QUEST0_GROUP, FLOWER_BIT))
            {
                write("You feel quite satisfied with your deed.\n");
            }
            else
            {
                write("You feel a little more experienced.\n");
                TP->set_bit(QUEST0_GROUP, FLOWER_BIT);
                TP->add_exp(FLOWER_XP, 0);
                log_file("flower_quest",capitalize(TP->query_real_name())+
                         " completed the Flower quest.   "+ctime(time())+"\n");
            }
        }
        tell_room(ENV(TP), QCTNAME(TP) + " plants some flowers at one of the" +
                  " graves.\n", TP);
        set_alarm(1.0, 0.0, remove_object);
        return 1;
    }
    NF("Plant flowers?\n");
    if (!parse_command(str, environment(), " [the] [wild] 'flowers' "))
        return 0;
    NF("You can't plant the flowers inside silly!\n");
    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You can't plant the flowers inside silly!\n");
        return 1;
    }
    write("You plant the flowers in the ground.\n");
    tell_room(TP, QCTNAME(TP) + " plants some flowers here.\n", TP);
    set_alarm(1.0, 0.0, remove_object);
    return 1;
}

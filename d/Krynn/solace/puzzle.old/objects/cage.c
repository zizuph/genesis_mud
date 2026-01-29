/* The cage containing the monkey. ~solace/puzzle/objects/window */

inherit "/std/receptacle";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

int monkey_released, alarm_id;

int query_monkey_released()
{
    return monkey_released;
}

void create_receptacle()
{
    set_name("cage");
    set_adj("large");
    add_adj("iron");
    set_long("The cage is very large and is held in place suspended above "+
        "the floor by eight thick linked chains: Four connected to the "+
        "floor and four to the ceiling; one at each corner.@@monkey_here@@\n");

    set_cf(TO);
    set_no_pick();

    set_key(CAGE_KEY);

    add_prop(CONT_I_LOCK, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_HIDDEN, 1);

    add_prop(CONT_I_VOLUME,     0);
    add_prop(CONT_I_WEIGHT,     0);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);

    change_prop(OBJ_M_NO_GET, "The cage is chained to the floor and ceiling!\n");
}

string monkey_here()
{
    return(monkey_released ? "" : " You notice a small hairy monkey inside "+
        "the cage. It looks very sad and "+(random(2) ? "keeps shaking the "+
        "cage in anticipation of release" : "keeps chattering at you to get "+
        "you to open the cage")+". You wonder how long it has been there.");
}

int open(object ob)
{
    if(!monkey_released && !pointerp(get_alarm(alarm_id)))
        alarm_id = set_alarm(0.5, 0.0, "release_monkey", TP);

    return 0;
}

void release_monkey(object ob)
{
    object monkey;

    if(!objectp(ob) || !present(ob, E(TO)))
        return;

    monkey_released = 1;
    monkey = clone_object(CREATURES + "monkey");

    ob->catch_msg("As soon as you open the door to the cage, a monkey "+
        "jumps out, obviously relieved to be free again.\n");

    tell_room(E(ob),"As soon as "+QTNAME(ob)+" opens the door to the cage"+
        "a monkey jumps out, obviously relieved to be free again.\n", ob);

    monkey->move(E(ob));
}

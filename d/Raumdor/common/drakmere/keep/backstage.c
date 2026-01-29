#include "defs.h"
#define GUARDS 3
inherit KEEP_ROOM;

object *guards = allocate(GUARDS);

object priest;
object labourer;
object mason;

void
create_room()
{
    ::create_room();
    add_exit(DRAKMERE_DIR + "road22","north");
    CLOCK->add_event(TO);
    reset_room();
}

void
spawn_priest()
{
    object guard;

    priest = clone_object(COMMON_NPC_DIR + "high_priest");

    priest->move(TO);
    for (int i = 0; i < 4; i++)
    {
        guard = clone_object(DRAKMERE_NPC_DIR + "dguard");
        guard->set_random_move(0);
        guard->move(TO);
        priest->team_join(guard);
    }
    priest->schedule();
}

void
spawn_stone_convoy()
{
    object block, cart, guard = clone_object(DRAKMERE_NPC_DIR + "dguard");
    labourer = clone_object(COMMON_NPC_DIR + "labourer");

    guard->set_random_move(0);
    guard->move(TO);
    labourer->move(TO);
    labourer->team_join(guard);

    cart = labourer->summon_cart();
    cart->add_guard(guard);

    block = clone_object(COMMON_OBJ_DIR + "stone_block");
    block->set_heap_size(40);
    block->move(cart, 1);

    labourer->schedule();
}

void
spawn_mason()
{
    mason = clone_object(COMMON_NPC_DIR + "mason");
    mason->move(TO);
    mason->schedule();
}

void
spawn_wood_convoy()
{
    object obj, barrel, cart,
           toolbox = clone_object(COMMON_OBJ_DIR + "toolbox"),
           npc = clone_object(COMMON_NPC_DIR + "labourer");

    npc->move(TO);
    cart = npc->summon_cart();

    for (int i = 0; i < 4; i++)
    {
        barrel = clone_object(COMMON_OBJ_DIR + "breakable_barrel");

        // Planks
        obj = clone_object(COMMON_OBJ_DIR + "plank");
        obj->set_heap_size(20);
        obj->move(barrel);

        // Posts
        obj = clone_object(COMMON_OBJ_DIR + "post");
        obj->set_heap_size(8);
        obj->move(barrel);

        barrel->move(cart, 1);
    }
    
    // Nails
    obj = clone_object(COMMON_OBJ_DIR + "nail"),
    obj->set_heap_size(100);
    obj->move(toolbox, 1);

    // Hammer
    obj = clone_object(COMMON_OBJ_DIR + "hammer");
    obj->move(toolbox, 1);

    // Glue
    obj = clone_object(COMMON_OBJ_DIR + "glue");
    obj->move(toolbox, 1);

    toolbox->move(cart, 1);

    // Saw
    obj = clone_object(COMMON_WEP_DIR + "saw");
    obj->move(cart, 1);

    // Shovel
    obj = clone_object(COMMON_WEP_DIR + "shovel");
    obj->move(cart, 1);

    npc->schedule();
}

mixed
query_waypoint_direction(string waypoint)
{
    if (waypoint == "keep")
        return 1;
    return "north";
}

void
spawn_beach_guards()
{
    int i;
    for (i = 0; i < GUARDS; i++)
    {
        if (!guards[i])
        {
            guards[i] = clone_object(DRAKMERE_NPC_DIR + "beach_guard");
            guards[i]->move(TO);
            guards[i]->schedule();
        }
    }
}

void
event_hook(int hour)
{
    if (hour == 6)
    {
        spawn_beach_guards();
    }
    if (hour == 8)
    {
        spawn_wood_convoy();
    }
    /*
    if (hour == 7 && !priest)
    {
        spawn_priest();
    }
    else if (hour == 9 && !labourer)
    {
        spawn_stone_convoy();
    }
    else if (hour == 10 && !mason)
    {
        spawn_mason();
    }
    */
}

int *
query_coordinates()
{
    return ({61, 0, 0});
}

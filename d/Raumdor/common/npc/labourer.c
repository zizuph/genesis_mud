#include "../drakmere/defs.h"
inherit STD_DIR + "good_npc";
inherit LIB_DIR + "schedule";

int work_stage = 0;
object cart;
object horse;

object
summon_cart()
{
    horse = clone_object(STEEDS_DIR + "carthorse");
    cart = clone_object(COMMON_OBJ_DIR + "cart");
    horse->move(E(TO));
    cart->move(E(TO));
    horse->set_pulled_object(cart);
    horse->do_lead(TO);
    cart->add_guard(TO);
    return cart;
}

void
do_stone_work()
{
    if (!present(horse, E(TO)) || !present(cart, E(TO)))
        stop_current_routine(STATUS["FAILURE"]);

    if (!present("_stone_block", cart))
        stop_current_routine(STATUS["SUCCESS"]);

    switch(work_stage++)
    {
        case 0:
            command("get two _stone_blocks from " + OB_NAME(cart));
            if (!present("_stone_block", TO))
            {
                interrupt_current_routine(STATUS["BLOCKED"]);
                work_stage = 0;
            }
            break;
        default:
            command("drop stone blocks");
            work_stage = 0;
            break;
    }
}

void
do_wood_work()
{
    if (query_attack() || !present(horse, E(TO)) || !present(cart, E(TO)))
    {
        stop_current_routine(STATUS["FAILURE"]);
        return;
    }

    if (work_stage > 1 && work_stage < 9 && !present("shovel", TO))
    {
        seen_emote("looks around nervously.");
        stop_current_routine(STATUS["FAILURE"]);
        return;
    }

    switch(work_stage++)
    {
        case 0:
            command("south");
            break;
        case 1:
            command("get shovel from cart");
            break;
        case 2:
            command("wield shovel");
            break;
        case 3:
            seen_emote("clears a patch on the ground.");
            break;
        case 4:
            seen_emote("starts digging a hole.");
            break;
        case 5:
            seen_emote("measures the depth of a hole with his shovel.");
            break;
        case 6:
            seen_emote("smacks some dirt with his shovel, compressing it.");
            break;
        case 7:
            seen_emote("crouches down, examining his work.");
            break;
        case 8:
            command("put shovel in cart");
            break;
        case 9:
            command("get barrel from cart");
            break;
        case 10:
            if (present("barrel", TO))
                command("drop barrel");
            else
                work_stage += 4;
            break;
        case 11:
            command("get four planks from barrel");
            break;
        case 12:
            if (present("plank", TO))
               work_stage -= 2;
            command("drop planks");
            break;
        case 13:
            command("get two posts from barrel");
            break;
        case 14:
            if (present("post", TO))
                work_stage -=2;
            else
                work_stage -= 6;
            command("drop posts");
           break;
        case 15:
           command("get barrel");
           break;
        case 16:
            if (present("barrel", TO))
            {
                command("put barrel in cart");
                work_stage -= 2;
                break;
            }                
        default:
            command("north");
            stop_current_routine(STATUS["SUCCESS"]);
            break;
    }
}

void
do_work()
{
    do_wood_work();
}

void
do_despawn()
{
    if (present(cart, E(TO)))
        cart->remove_object();
    if (present(horse, E(TO)))
        horse->remove_object();
    clear_schedule();
    remove_object();
}

void
create_npc()
{
    ::create_npc();
    add_name("labourer");
    set_race_name("human");
    set_adj("nervous");
    set_short("nervous labourer");

    set_long("This man looks to be working the ground diligently, " +
        "though not without checking over his shoulder frequently.\n");

    set_stats(({80,70,80,50,60,80}));
    set_skill(SS_DEFENCE, 60);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(400);

    set_default_answer("say I don't know, I have work to do.", 1);

    equip(({
        COMMON_ARM_DIR + "overalls",
        COMMON_ARM_DIR + "work_shoes",
    }));
}

void
schedule()
{
    object routine;

    CLOCK->add_event(TO);

    routine = clone_object(STD_DIR + "autopath");
    routine->set_destination("beach");
    routine->set_live(TO);
    queue_routine(routine);

    routine = clone_object(STD_DIR + "routine");
    routine->set_routine_callback(do_work);
    routine->set_repeat_delay(5.0);
    queue_routine(routine);

    routine = clone_object(STD_DIR + "autopath");
    routine->set_destination("keep");
    routine->set_live(TO);
    queue_routine(routine);

    routine = clone_object(STD_DIR + "routine");
    routine->set_routine_callback(do_despawn);
    queue_routine(routine);
    
    start_schedule();
}

#include "../drakmere/defs.h"
inherit STD_MONSTER;
inherit LIB_DIR + "schedule";

int work_stage = 0;

void
do_despawn()
{
    seen_emote("leaves, happy to be done with work.");
    clear_schedule();
    remove_object();
}

void
do_work()
{
    object ob;

    if (!present("_masonry_trowel", TO) || !present("_mortar_bucket", TO)) 
        stop_current_routine(STATUS["FAILURE"]);

    switch(work_stage++)
    {
        case 0:
            command("get _stone_block");
            if (!present("_stone_block", TO))
                stop_current_routine(STATUS["SUCCESS"]);
            break;
        case 1:
            seen_emote("gathers some mortar on his trowel.");
            break;
        case 2:
            if (!(ob = present("_stone_block", TO)))
            {
                seen_emote(" furrows his brow.");
                work_stage = 0;
                break;
            }
            seen_emote("butters a stone block with mortar and adds " +
               "it to the wall.");
            ob->remove_object();
            break;
        default:
            seen_emote("taps a newly placed stone block into place, " +
              "removing excess mortar with his trowel.");
            work_stage = 0;
            break;
    }
}

void
create_monster()
{
    ::create_monster();
    add_name("mason");
    set_race_name("human");
    set_adj("anxious");
    set_short("anxious mason");

    set_long("This man looks prepared to work, but seems quite " +
      "apprehensive.\n");

    set_stats(({80,70,80,50,60,80}));
    set_skill(SS_DEFENCE, 60);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(400);

    set_default_answer("say I don't know, I have work to do.", 1);

    equip(({
        COMMON_WEP_DIR + "trowel",
        COMMON_ARM_DIR + "overalls",
        COMMON_ARM_DIR + "work_shoes",
        COMMON_OBJ_DIR + "mortar",
    }));
}

void
schedule(int nightfall)
{
    object routine;

    if (nightfall)
    {
        clear_schedule();
        command("say It's almost nightfall. I'm heading back before it's too late!");
        command("drop stone blocks");
    }
    else
    {
        CLOCK->add_event(TO);

        routine = clone_object(STD_DIR + "autopath");
        routine->set_destination("beach");
        routine->set_live(TO);
        queue_routine(routine);

        routine = clone_object(STD_DIR + "routine");
        routine->set_routine_callback(do_work);
        queue_routine(routine);
    }

    routine = clone_object(STD_DIR + "autopath");
    routine->set_destination("keep");
    routine->set_live(TO);
    queue_routine(routine);

    routine = clone_object(STD_DIR + "routine");
    routine->set_routine_callback(do_despawn);
    queue_routine(routine);
    
    start_schedule();
}

void
event_hook(int hour)
{
    if (hour == 16)
        schedule(1);
}



#include "../drakmere/defs.h"
inherit STD_MONSTER;
inherit LIB_DIR + "intro";
inherit LIB_DIR + "schedule";

void
do_despawn()
{
    foreach (object ob: query_team())
        ob->remove_object();
    remove_object();
}

void
create_monster()
{
    set_name("hipstarius");
    add_name("priest");
    set_race_name("human");
    set_adj("ancient");
    add_adj("priest");
    set_short("ancient priest");
    set_long(
      "This old and wise-looking priest clad in white robes and gold " +
      "trimmings. He has a long, grey beard and has a kind look in his eyes, " +
      "though also a look of concern.\n");
    set_stats(({60, 40, 40, 100, 180, 160}));
    set_alignment(1000);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 60);
    set_skill(SS_AWARENESS, 70);
    set_title("the High Priest of Drakmere");
    set_default_answer(
      "say What did you want? My hearing isn't what it used to be.", 1);
    /*
    set_act_time(12);
    add_act("say Kids these days, with their fast horses and loud minstels.");
    add_act("say Faith is for dark times like these.");
    add_act("say Creator guide me.");
    add_act("@@seen_emote|tugs his long, grey beard thoughtfully.");
    add_act("emote mumbles a prayer to the Creator.");
    add_act(
      "say 'Tis a fool's errand to seek that foul temple in the forest.");
      */
    set_cact_time(6);
    add_cact(
      "shout Damn you to the Netherworld! Can't you leave an old priest to " +
      "his business?!");
    add_cact("shout May the Creator smite you down!");
    add_cact(
      "shout This is what can become of you when you don't worship " +
      "regularly!");
    add_cact("shout Leave me be, you foul thing!");

    equip(({
      COMMON_ARM_DIR + "priest_robe", COMMON_ARM_DIR + "priest_ring",
    }));
}
/*
void
event_hook(int hour)
{
    if (hour == 17)
    {
        command("say The hour is late. We must return.");
        stop_current_routine(STATUS["SUCCESS"]);
    }
}

void
do_blessing()
{
    if (query_attack())
        return;
    switch(random(6))
    {
        case 0:
            seen_emote("closes his eyes and traces his hand in a circular " +
              "motion.");
            break;
        case 1:
            command("$emote chants softly.");
            break;
        case 2:
            seen_emote("raises his hands towards the sky, curls his " +
              "fingers as though capturing some invisible substance, and " +
              "slowly draws his arms down while opening his hands over " +
              "the area.");
            break;
        case 3:
            seen_emote("bends down and touches the gound with one hand " +
              "while making ritualistic gestures with the other.");
            break;
        case 4:
            command("$touch wall");
            break;
        default:
            command("$say Too often do the dead encroach upon our " +
              "connection to distant lands. Enough is enough!");
            break;
    }
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
    routine->set_routine_callback(do_blessing);
    routine->set_repeat_delay(20.0);
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
*/

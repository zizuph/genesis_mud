#include "defs.h"

#include "defs.h"
inherit NFLATS_ROOM;

object steed, knight;

void
create_room()
{
    ::create_room();
    set_long(
      "These flats stretch out north to the mountains, and south, into the " +
      "dreaded forest. The ground is flat, dirty and dusty. You notice a " +
      "strange symbol on the ground, etched into the bare dirt.\n");
    add_item(({"skull", "symbol"}),
      "It is a large skull and seems to be made out of dried mud brick. The " +
      "skull's mouth is open very wide, as though it were screaming.\n");
    set_no_exit_msg(({"northwest", "north", "northeast"}),
      "Mountains rise in that direction, preventing passage.\n");
    add_exit(NFLATS_DIR + "nflats11", "east", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats04", "southeast", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats03", "south", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats02", "southwest", 0, NFLATS_FATIGUE);
    add_exit(NFLATS_DIR + "nflats09", "west", 0, NFLATS_FATIGUE);

    reset_room();
}

void
init()
{
    ::init();
    add_action("do_cut", "cut");
    add_action("do_cut", "scrape");
    add_action("do_cut", "pierce");
    add_action("do_cut", "jab");
}

int
do_cut(string str)
{
    notify_fail(CAP(query_verb()) + " yourself with what?\n");
    if (str != "myself with horn")
        return 0;
    notify_fail("You don't have the horn.\n");
    if (!present(QUEST_HORN_NAME, TP))
        return 0;
    write("You " + query_verb() +
          " yourself with the bloody demon horn, and let the blood flow from " +
          "your wound into the mouth of the skull!\n");
    set_alarm(3.0, 0.0,
      &tell_room(TO, "The skull's eyes begin to glow bright green.\n"));
    set_alarm(6.0, 0.0,
      &tell_room(
        TO, "The skull speaks: I deem ye worthy, to enter the darkness.\n"));
    set_alarm(10.0, 0.0, "reward", TP);
    return 1;
}

void
reward(object ob)
{
    if (ob->test_bit("Raumdor", 3, 2))
        return;
    ob->set_bit(3, 2);
    tell_object(ob, "You feel a little more experienced!\n");
    ob->add_exp_quest(500);
    KLOG("QUEST/khiraa_entrance_quest",
      ob->query_name() + " awarded by " + MASTER_OB(TO) +
        " with 500 xp. bit 3,2\n");
}

void
reset_room()
{
    if (random(4) || steed || knight)
        return;
    knight = clone_object(COMMON_NPC_DIR + "death_knight_1");
    steed  = clone_object(STEEDS_DIR + "skeletal_steed");
    steed->do_mount(knight);
    steed->move_living("M", TO);
    knight->move_living("M", TO);
    knight->add_act("mount horse");

    TELL_CAN_SEE(TO, QCNAME(knight) + " rides in on " + QNAME(steed) + ".\n");
}

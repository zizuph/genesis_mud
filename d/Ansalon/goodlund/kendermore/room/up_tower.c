#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit KENDERMORE_OUT;
inherit STREET_DESC;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("On a narrow ledge");
    set_long("@@long_descr");

    add_item("ledge", "It is a very narrow ledge. This is the widest spot.\n");
    add_item("tower", "It holds water meant to be used by the citizens of " + 
        "Kendermore. Oddly enough, there doesn't seem to be a tap to get " + 
        "the water out.\n");
    add_item("view", "The city of Kendermore spreads out below you in all " + 
        "directions.\n");
    add_item(({"city", "kendermore"}), "The streets of Kendermore twist and " + 
        "turn in a confusing maze.\n");
    add_item(({"street", "streets"}), "@@street_descr@@\n");
    add_item("water", "You don't see any way to get at it.\n");

    add_cmd_item("down", "climb", "@@climb_tower");

    reset_kendermore_room();
    return;
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "You stand on a narrow ledge " +
        "of a very tall water tower. This is probably a favorite " + 
        "place for kender to test their climbing skills. The view up here " + 
        "is fantastic, but the only way out of here seems to be...down.\n");
}

string
climb_tower()
{
    if (TP->query_skill(SS_CLIMB) < 30)
    {
        write("You can't possibly imagine how you got up here in the " + 
            "first place, but going down is going to be painful!\nYou shut " + 
            "your eyes and begin to climb. Your foot slips, sending you " + 
            "tumbling down to the ground.\n");
        say(QCTNAME(TP) + " starts to climb down, but falls to the ground.\n");
        TP->heal_hp(-50);
        tell_room(KROOM + "w_tower", QCTNAME(TP) + " falls from above.\n");
        TP->move_living("M", KROOM + "w_tower", 0, 0);
        return "";
    }

    if ((TP->query_skill(SS_CLIMB) < 45) &&
        (TP->query_encumberance_weight() >29))
    {
        write("You start to make your way down the water tower, but slip " + 
            "and tumble all the way down to the ground!\n");
        say(QCTNAME(TP) + " starts to make " + HIS(TP) + " way down the " + 
            "water tower, but slips and tumbles all the way down to the " + 
            "ground!\n");
        TP->heal_hp(-50);
        tell_room(KROOM + "w_tower", QCTNAME(TP) + " falls from above.\n");
        TP->move_living("M", KROOM + "w_tower", 0, 0);
        return "";
    }

    write("You carefully climb down the way you came.\n");
    say(QCTNAME(TP) + " carefully climbs down the way " + HE(TP) + " came.\n");
    tell_room(KROOM + "w_tower", QCTNAME(TP) + " climbs down from the " + 
        "tower.\n");
    TP->move_living("M", KROOM + "w_tower", 1, 0);
    return "";
}

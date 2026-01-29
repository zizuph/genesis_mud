#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

inherit "/lib/unique";
inherit STREET_DESC;
inherit KENDERMORE_OUT;
inherit QEXITS;

#define GET_MONTH (CLOCK->query_month())

void switch_street();

object kender, puppy;
int thorn_found = 0;
int last_time = 0;
string *ranrooms = ({(KROOM + "house1"), (KROOM + "house2"), (KROOM + "house3"),
    (KROOM + "house4"), (KROOM + "house5"), (KROOM + "house6"),
    (KROOM + "house7"), (KROOM + "house8"), (KROOM + "tree"),
    (KROOM + "up_tower")});

void
reset_kendermore_room()
{
    thorn_found = 0;
}

void
create_kendermore_room()
{
    set_short("By a tall statue");
    set_long("@@long_descr");
    add_item(({"house", "houses"}), "Even the houses here have a " +
        "carefree feeling. " +
        "There doesn't seem to be any way in from here.\n");
    add_item(({"kendermore", "city"}), "The city of Kendermore spreads " +
        "out around you in a complicated twisting of streets. It is the " +
        "home of many kender when they aren't adventuring and exploring.\n");
    add_item(({"street", "road"}), "The road is made of cobblestones. " +
        "It winds " +
        "beyond your view.\n");
    add_item(({"sign", "signs"}), "Best to ask directions instead.\n");
    add_item("statue", "This statue of a young elf is carved of plain " +
        "grey stone on a grey base, but the skill and care that went into " +
        "it are amazing. The shoulder length, wavy hair seems to almost " +
        "flutter in the breeze. She is dressed for battle, sword in one " +
        "hand, shield in another. Wisdom and cunning shines from the eyes " +
        "of a hunter. This is one warrior you'd rather have as a friend " +
        "than foe.\n");
    add_item("base", "It's made of the same grey stone that the statue is " +
        "made of.\n");
    add_cmd_item(({"base","panel"}), "push", "@@push_base");
    add_cmd_item("house", "enter", "@@enter_house");
    add_search(({"base", "statue"}), 2, "find_panel", 1);

    switch_street();

    set_tell_time(100);
    add_tell("A kender bumps into you, apologizes and continues on " +
        "his way.\n");
    add_tell("Bright laughter rings out from nearby.\n");
    add_tell("A kender arrives, excitedly picks up a piece of shiny " +
        "metal from the ground, and happily skips away.\n");
    add_tell("A small mouse scurries across your path.\n");
    add_tell("A loud crashing sound reaches your ears.\n");
    add_tell("A small bug skitters under a bush.\n");

    add_npc(KNPC + "puppy", 3);
    add_npc(KNPC + "std_kender", 1);

    reset_kendermore_room();
}

string
find_panel()
{
    return "You find a hidden panel in the base of the statue!\n";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "Houses stand on both sides " +
        "of you. " + street_descr() + " A beautifully carved stone statue " +
        "stands here. The road continues on its " +
        "winding way to the " + find_exits() + ". Numerous signs point " +
        "in all directions, but they tend to contradict each other and " +
        "point in directions where there are no exits.\n");
}

string
enter_house()
{
    write("You look for a way into the house, but find none.\n");
    say(QCTNAME(TP) + " searches for a way into the house, but finds " +
        "none.\n");
    return "";
}

void
switch_street()
{
    if (GET_MONTH > 6)
    {
        add_invis_exit("null", "north", "@@blocked_street");
        add_exit(KROOM + "street34", "northwest", 0);
        add_exit(KROOM + "street30", "south", 0);
    }
    else
    {
        add_invis_exit("null", "northwest", "@@blocked_street");
        add_exit(KROOM + "street34", "north", 0);
        add_exit(KROOM + "street30", "south", 0);
    }
}

int
blocked_street()
{
    write("A house has been built in that direction!\nMaybe there's " +
        "another way around.\n");
    return 1;
}

string
push_base()
{
    object thorn_circlet;

    if (last_time + 10 > time())
    {
        write("You try to push the a spot on the base of the "+
            "statue but it seems dislodged from "+
            "having recently been touched, and fails to move.\n");
        return "";
    }

    last_time = time();

    if (!thorn_found) 
    {    
        thorn_found = 1;
        thorn_circlet = clone_unique(KOBJ + "thorns", 3);
    }

    if (thorn_circlet)
    {
        write("You look around, and when nobody is looking, you push on a " +
            "spot on the base of the statue.\n");
        thorn_circlet->move(ranrooms[random(10)]);
        write("A circlet of silvery thorns falls from a hole in the base " +
            "of the statue. Before you can pick it up, a curious kender " +
            "walks in, casually pockets it, and walks away.\n");
        thorn_found = 1;
        return "";
    }

    write("You look around, and when nobody is looking, you push on a " +
        "spot on the base of the statue. You find nothing.\n");

    return "";
}


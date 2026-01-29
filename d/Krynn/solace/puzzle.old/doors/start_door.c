/* Entrance door. ~solace/puzzle/doors/start_door */

inherit "/std/door";

#include "../defs.h"
#include "/sys/macros.h"
#include "/secure/std.h"
#include "../../../mucalytic/sys/language.h"

void create_door()
{
    set_name("start_door");
    set_door_name(({"door", "metal door", "strong door", "strong metal door"}));
    set_door_desc("A very solid looking metal door in the south wall. Upon "+
        "it is the emblem of a tall disturbing human wearing a black hooded "+
        "cloak, hiding his face.\n");

    set_open(1);
    set_locked(0);

    set_door_id("entrance_door");
    set_other_room(LOCATIONS + "entrance");

    set_open_command("open");
    set_close_command("close");
    set_pass_command(({ "s", "south" }));

    set_open_desc("A strong metal door lies open to the south and ");
    set_closed_desc("A strong metal door lies closed to the south and ");

    set_open_mess(({"heaves the strong metal door open.\n", "The strong metal "+
        "door in the north wall is heaved open by someone in the other room.\n"}));

    set_close_mess(({"heaves the strong metal door shut.\n", "The strong metal"+
        " door in the north wall is heaved shut by someone in the other room.\n"}));
}

void let_them_pass(string arg)
{
    ::pass_door(arg);
}

void let_them_open_door(string arg)
{
    ::open_door(arg);
}

void let_them_close_door(string arg)
{
    ::close_door(arg);
}

int pass_door(string arg)
{
    object hands;

    let_them_pass(arg);

    if(query_open())
    {
        hands = present("hands", TP);

        if(objectp(hands))
        {
            hands->remove_prop(OBJ_M_NO_DROP);
            hands->move(find_object(LOCATIONS + "entrance"));
        }

        if(TP->query_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST))
        {
            if(!TP->test_bit(getuid(TO), GROUP, BIT))
            {
                TP->add_exp(60000, 0);
                TP->set_bit(GROUP, BIT);

                write("You suddenly feel more experienced!\n");
                K_QUEST_LOG("quest", "Puzzle Quest", TP, 60000);
            }

            TP->remove_prop(PLAYER_I_COMPLETED_PUZZLE_QUEST);
        }

        find_object(LOCATIONS + "entrance")->set_occupied(0);
        set_alarm(0.5, 0.0, "say_stuff");
        return 1;
    }

    write("You walk into the closed metal door!\n");
    say(QCTNAME(TP)+" walks into the closed metal door to the north.\n");
    return 1;
}

int open_door(string arg)
{
    object trapdoor1, trapdoor2;

    trapdoor1 = present("start_trapdoor", E(TO));
    trapdoor2 = present("azazel_trapdoor", find_object(LOCATIONS + "azazel"));

    if(member_array(arg, query_door_name()) == -1)
        return 0;

    if(!query_open())
    {
        trapdoor1->do_close_door();
        trapdoor2->do_close_door();

        tell_room(E(trapdoor1), "The trapdoor in the floor slams shut.\n");
        tell_room(E(trapdoor2), "The trapdoor in the ceiling slams shut.\n");
    }

    let_them_open_door(arg);
    return 1;
}

int close_door(string arg)
{
    object trapdoor1, trapdoor2;

    trapdoor1 = present("start_trapdoor", E(TO));
    trapdoor2 = present("azazel_trapdoor", find_object(LOCATIONS + "azazel"));

    if(member_array(arg, query_door_name()) == -1)
        return 0;

    if(query_open())
    {
        trapdoor1->do_open_door();
        trapdoor2->do_open_door();

        tell_room(E(trapdoor1), "The trapdoor in the floor creaks open.\n");
        tell_room(E(trapdoor2), "The trapdoor in the ceiling creaks open.\n");
    }

    let_them_close_door(arg);
    return 1;
}

int say_stuff()
{
    write("\nYou are suddenly bathed in a soft blue light!\n");
    write("A mysterious voice mumbles: Your belongings have been restored.\n");
    return 1;
}

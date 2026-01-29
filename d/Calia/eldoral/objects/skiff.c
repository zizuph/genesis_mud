#include "../defs.h"
#include <filter_funs.h>
#include <composite.h>

#define SKIFF_DECK (OBJ + "skiff_deck")
inherit "/std/object";

string *rooms = ({MOUNT + "mshore2",
                 LAKE + "lake1",
                 LAKE + "lake2",
                 LAKE + "lake3",
                 LAKE + "lake4",
                 LAKE + "lake5",
                 LAKE + "lake6",
                 LAKE + "lake7",
                 LAKE + "lake8",
                 SHORE + "shore1",
                 });
public int do_board(string str);
public void next_sail(int index);

public void
remove_items(object ob)
{
    int i,
        j,
        count1,
        count2;

    mixed *temp;

    if (!ob || !objectp(ob))
        return;

    temp = ob->query_item();

    if (!(count1 = sizeof(temp)))
        return;
      
    for (i = 0; i < count1; i++)
    {
        if (pointerp(temp[i][0]) && (count2 = sizeof(temp[i][0])))
        {
            for (j = 0; j < count2; j++)
            {
                if (member_array(temp[i][0][j], ob->query_base_items()) < 0)
                    ob->remove_item(temp[i][0][j]);
            }
        }
        else
        {
            if (member_array(temp[i][0], ob->query_base_items()) < 0)
                ob->remove_item(temp[i][0]);
        }
    }
}

public void
update_items()
{
    object deck;
    string *temp;
    int i;

    if (!environment(TO))
        return;

    if (!(deck = find_object(SKIFF_DECK)))
        return;

    remove_items(deck);
    temp = environment(TO)->query_item();

    for (i = 0; i < sizeof(temp); i++)
    {
        deck->add_item(temp[i][0],temp[i][1]);
    }
}

public string
occupants()
{
    string ret;
    object *temp;

    temp = all_inventory(find_object(SKIFF_DECK));

    if (!temp || !sizeof(temp))
    {
        ret = "";
    }
    else
    {
        ret = "Within the skiff you see ";
        ret += COMPOSITE_LIVE(temp) + ".";
    }
    return ret;
}


public void
create_object()
{
    set_name("skiff");
    add_name("boat");
    set_adj("small");
    add_adj("wooden");
    set_long("The boat is a small, wooden skiff, capable of carrying " +
        "maybe two or three people. It's construction is quite odd, as " +
        "if a leftover from days long gone. It seems to be carved " +
        "entirely from one piece of wood, which is further made stranger " +
        "by the long, curving head of a dragon which adorns the " +
        "bow of the small vessel. Even stranger yet, is the complete " +
        "lack of any visible means of motion, yet sail it will. " +
        "@@occupants@@\n");

    setuid(); seteuid(getuid());
    if (IS_CLONE)
        SKIFF_DECK->set_skiff(TO);
    rooms[0..9]->load_me();

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 50000);
}

public void
init()
{
    ::init();
    add_action(do_board, "board");
    add_action(do_board, "enter");
    add_action(do_board, "embark");
}

public int
do_board(string str)
{
    object *temp;
    int i,
        weight = 0;

    notify_fail(capitalize(query_verb()) + " what? The skiff?\n");

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] 'skiff' / 'boat'"))
        return 0;

    if (!environment(TO)->query_prop(ROOM_I_IS_SKIFF_PORT))
    {
        notify_fail("You can't board the skiff from here, it's " +
            "much to unstable.\n");
        return 0;
    }

    temp = deep_inventory(find_object(SKIFF_DECK));
    for (i = 0; i < sizeof(temp); i++)
    {
        weight += temp[i]->query_prop(OBJ_I_WEIGHT);
    }

    if (weight > 300000)
    {
        write("The skiff is already heavily loaded, it would " +
            "likely sink beneath your weight.\n");
        return 1;
    }

    write("You step into the skiff, balancing carefully as it rocks " +
        "back and forth beneath your weight.\n");
    say(QCTNAME(TP) + " steps into the skiff, balancing carefully " +
        "as it rocks back and forth beneath " +
        TP->query_possessive() + " weight.\n");
    TP->move_living("M", SKIFF_DECK, 1, 0);
    say(QCTNAME(TP) + " steps into the skiff, balancing carefully " +
        "as it rocks back and forth beneath " +
        TP->query_possessive() + " weight.\n");
    return 1;
}

public void
start_sailing(int index)
{
    if (index < 0 || index > sizeof(rooms))
        return;

    if (index == 0 || index == 9)
    {
        tell_room(environment(TO), "The small skiff scrapes off " +
            "the pebbly shore and glides off across the lake.\n");
        tell_room(find_object(SKIFF_DECK), "The small skiff scrapes " +
            "off the pebbly shore and glides off across the lake.\n");
        TO->move(find_object(rooms[++index]), 1);
        tell_room(environment(TO), "A small skiff leaves the " +
            "shore and draws close.\n");
        set_alarm(10.0, 0.0, &next_sail(index + 2));
    }
    else
    {
        next_sail(++index);
    }
}

public void
next_sail(int index)
{
    if (index >= 18)
        index = 0;
    tell_room(environment(TO), "The skiff glides silently across " +
        "the waters, vanishing into the fog.\n");
    tell_room(find_object(SKIFF_DECK), "The skiff glides silently " +
        "across the waters.\n");
    TO->move(find_object(rooms[index]), 1);
    tell_room(environment(TO), "A small skiff appears from the " +
        "depths of the fog, gliding silently across the water.\n");
    if (environment(TO)->query_prop(ROOM_I_IS_SKIFF_PORT))
    {
        tell_room(environment(TO), "The skiff scrapes to a gentle " +
            "halt upon the shore.\n");
        tell_room(find_object(SKIFF_DECK), "The skiff scrapes " +
            "to a gentle halt upon the shore.\n");
        if (index >= 9)
            return;
        set_alarm(60.0, 0.0, &start_sailing(index));
    }
    else
    {
        set_alarm(10.0, 0.0, &next_sail(++index));
    }
}

public void
enter_env(object to, object from)
{
    ::enter_env(from, to);
    if (!objectp(to))
        return;

    update_items();
}

    

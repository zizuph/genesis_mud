/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's living/bedroom
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

private object cat, basket;
private int key_found = 0, sniff_alarm, eat_alarm;

public void
create_earthsea_room()
{
    set_short("A living room");
    set_long("Small but comfortable, this room " +
        "boasts a large cushioned chair and a woven " +
        "rug upon the floor. A small mattress " +
        "by the west wall appears to " +
        "be where the resident sleeps. A little " +
        "table by the chair holds some pretty " +
        "rocks, some interesting shells, and a candle.\n");
    add_item((({"shells", "interesting shells"})),
        "It seems the inhabitant collects sea shells. You see " +
        "some different kinds of shells, some spiral-shaped, " +
        "some clam-shaped, all in different shades of light " +
        "to deep blue.\n");
    add_item((({"rocks", "pretty rocks"})),
        "A handful of pretty rocks, including " +
        "a little piece of amethyst, a rose crystal " +
        "and a blue malachite lie in a small " +
        "earthen bowl on the table.\n");
    add_item((({"rug", "woven rug"})),
        "The rug, woven of blue goat wool, " +
        "appears a bit worn, and covered with " +
        "black cat hairs.\n");
    add_item((({"mattress", "small mattress"})),
        "The mattress is only big enough for one, " +
        "suggesting that the resident lives alone. " +
        "It has a colourful red quilt covering it.\n");
    add_item("fireplace",
        "The fireplace opens to the large hearth in " +
        "the kitchen.\n");
    add_item((({"table", "small table"})),
        "The small table of unfinished pine holds a few " +
        "trinkets and a candle.\n");
    add_item((({"wall", "door", "west wall", "hole", "small door"})),
        "There is a hole in the west wall, which the cat uses for " +
        "a door.\n");
    add_item("candle",
        "The candle provides light in the dark.\n");
    add_item("chair",
        "The large chair looks very comfortable.\n");
    reset_room();
    add_prop(OBJ_S_SEARCH_FUN, "find_key");
    add_exit("witch_kitchen", "north");
}

public void
reset_room()
{
    key_found = 0;

    if(!objectp(cat))
    {
        cat = clone_object("/d/Earthsea/gont/tenalders/npc/cat");
        cat->move(this_object());
        cat->command("emote enters, brushing against your leg.");
    }
}

public void
cat_eats_cream(object cream, object tp)
{
    object to = this_object();

    eat_alarm = 0;

    if(!present(cream, to) || !present(tp, to) || !present(cat, to))
    {
        return;
    }

    cat->command("emote walks over to the dish of cream.");
    cat->command("emote licks up all the cream.");

    seteuid(getuid(to));
    cream->remove_object();

    if(tp->query_prop(GOT_KITTY_QUEST) &&
        (!QH_QUERY_QUEST_COMPLETED(tp, "cat_quest")))
    {
        QH_QUEST_COMPLETED(tp, "cat_quest");
        tp->remove_prop(GOT_KITTY_QUEST);
        tp->catch_tell("You feel more experienced!\n");
    }
}

public void
cat_sniff(object tp, object cream)
{
    object to = this_object();

    sniff_alarm = 0;

    if(eat_alarm || !present(tp, to) || !present(cat, to) ||
        !present(cream, to))
    {
        return;
    }

    tell_room(to, "The little black cat sits up and sniffs " +
        "the air.\n");
    eat_alarm = set_alarm(3.0, 0.0, &cat_eats_cream(cream, tp));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!sniff_alarm && interactive(from))
    {
        if(ob->id("_cream_") && present(cat, this_object()))
        {
            sniff_alarm = set_alarm(3.0, 0.0, &cat_sniff(from, ob));
        }
    }
}

public string
find_key(object player, string str)
{
    object key;

    if(str == "hole" && (!key_found))
    {
        key_found = 1;
        setuid();
        seteuid(getuid(this_object()));
        key = clone_object("/d/Earthsea/gont/tenalders/obj/items/redwood_key");
        key->move(player);
        return "You found a wooden key!\n";
    }

    return "You find nothing of value there.\n";
}

public int
set_cream(string str)
{
    object tp = this_player(), to = this_object(), cream;
    string dish;
    int x;

    if(!str || !(x = parse_command(str, to,
        "%w [on] / [onto] [the] [floor] ", dish)) ||
        (x <= 0) || !(cream = present("_cream_", tp)) ||
        !cream->id(dish))
    {
        return notify_fail("Set what/where?\n");
    }

    cream->move(to);
    tell_room(to, QCTNAME(tp) + " sets the cream "+
        "on the floor.\n", ({ tp }));
    write("You set the cream on the floor.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(set_cream, "put");
    add_action(set_cream, "drop");
    add_action(set_cream, "set");
}

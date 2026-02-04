/*
 * A grave with no name Mortricia 930430
 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <cmdparse.h>
#include "/d/Terel/common/terel_defs.h"

#define PATH           MANSION + "graveyard/"
#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()
#define MAX_DEPTH      5

object tombstone;
int dig_depth;

int query_at_coffin();

void
create_room()
{
    set_short("At tombstone");
    set_long(BS(
        "This place gives you an eerie feeling. You are " +
        "surrounded, except to the south, by a thick hedge. " +
        "You better leave the dead alone and leave this place " +
        "quickly.\n"
    ));

    add_item("hedge", "It looks old and impenetrable.\n");

    add_exit(PATH + "grvpath1", "south", 0);

    seteuid(getuid(TO));
    tombstone = clone_object(MANSION + "obj/tombstone");
    tombstone -> move(TO);

    dig_depth = 0;
}

void
init()
{
    ::init();
    add_action("do_dig", "dig");
    add_action("do_fill", "fill");
}

do_dig(string str)
{
    object *ob;
    string item;

    notify_fail("Dig with what?\n");
    if (!str) return 0;
    if (sscanf(str, "with %s", item) != 1) return 0;

    ob = FIND_STR_IN_OBJECT(item, TP);
    if (sizeof(ob) == 0) return 0;
    if (sizeof(ob) >= 2) return 0;
    notify_fail("The "+ob[0]->short()+" is useless for digging.\n");
    if (ob[0]->query_name() != "shovel") return 0;

    if (dig_depth == MAX_DEPTH) {
        write("You cannot dig any deeper.\n");
    } else {
        write("You start to dig with the "+ob[0]->short()+".\n");
        say(QCTNAME(TP) + " starts to dig with " +
            LANG_ADDART(ob[0]->short())+".\n");
        dig_depth++;
    }
    update_dig_desc();
    return 1;
}

do_fill(string str)
{
    object *ob;
    string item;

    notify_fail("What ?\n");
    if (dig_depth == 0) return 0;

    notify_fail("Fill what with what?\n");
    if (!str) return 0;
    if (sscanf(str, "hole with %s", item) != 1) return 0;

    ob = FIND_STR_IN_OBJECT(item, TP);
    if (sizeof(ob) == 0) return 0;
    if (sizeof(ob) >= 2) return 0;
    notify_fail("The "+ob[0]->short()+" is useless for digging.\n");
    if (ob[0]->query_name() != "shovel") return 0;

    write("You fill the hole using the "+ob[0]->short()+".\n");
    say(QCTNAME(TP) + " fills a hole using " +
        LANG_ADDART(ob[0]->short())+".\n");
    dig_depth--;
    update_dig_desc();
    return 1;
}

void
update_dig_desc()
{
    int i;

    remove_my_desc();
    remove_item("hole");
    remove_exit("down");
    i = (100 * dig_depth) / MAX_DEPTH;
    if (i == 0) return;
    switch (i) {
        case 100..999:
            add_my_desc(BS(
                "There is a deep hole here.\n"
            ));
            add_item("hole", "It looks very deep; you cannot see " +
                     "the bottom of it.\n");
            add_exit(PATH + "ug1", "down", 0);
            break;
        case 75..99:
            add_my_desc(BS(
                "There is a rather deep hole here.\n"
            ));
            add_item("hole", "You barely see the bottom of it.\n");
            break;
        case 50..74:
            add_my_desc(BS(
                "There is a hole here.\n"
            ));
            add_item("hole", "It's a hole that somebody must have dug here.\n");
            break;
        case 25..49:
            add_my_desc(BS(
                "There is a shallow hole here.\n"
            ));
            add_item("hole", "It's not much of a hole really.\n");
            break;
        case 1..24:
            add_my_desc(BS(
                "There are some scratches on the ground, just " +
                "like if someone has started to dig a hole.\n"
            ));
            add_item("hole", "It's not much of a hole really.\n");
            break;
        default:
            break;
    }
    return;
}

int
query_at_coffin()
{
    if (dig_depth == MAX_DEPTH) return 1;
    return 0;
}

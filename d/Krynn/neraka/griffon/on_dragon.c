/* Dragon coded by Nick */
/* Converted to griffon by Macker */
inherit  "/d/Krynn/std/room";
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "local.h"

void
create_krynn_room()
{
    set_short("On griffon");
    set_long(BS(
        "You are sitting on the back of a large fearless griffon. " +
    "As you examine his sleek feathers and the strong muscles he " +
    "uses to power his mighty wings, you decide it wise to HOLD ON.", 70));

    add_item("griffon", "You are sitting comfortably on its back.\n");
    add_exit("@@room_down", "down", "@@going_down");

    OUTSIDE  /* An outside room */

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
init()
{
    ::init();
    add_action("hold_on", "hold");
    add_action("hold_on", "HOLD");
}

int
hold_on(string str)
{
    object griffon, *ob;
    int i;

    str= L(str);
    seteuid(getuid(TO));
    NF("Hold on to what?\n");
    if(!((str=="on")||(str=="on to griffon")||(str=="griffon")))
    if ((str != "him") && (str != "griffon"))
      return 0;
    ob = all_inventory(TO);
    for (i = 0; i < sizeof(ob); i++)
      ob[i]->move(DRAGON_ROOM, 1);
    griffon = (DRAGON_ROOM)->query_dragon();
    griffon->rem_void();
    (DRAGON_ROOM)->set_place((DRAGON_ROOM)->query_place_num() + 1);
    tell_room(environment(griffon), "The griffon leaves into the sun.\n");
    griffon->move(VOID, 1);

    write("Just as you grab ahold of the griffon, he jolts upward into the sky!\n");
    say(QCTNAME(TP) + " grabs ahold of the griffon just to be safe. " +
        "Seeing this, you immediately do the same.\nSuddenly the griffon " +
        "jolts upward into the sky!\n");
    return 1;
}

void
drop_all()
{
    object *ob;
    int i;

    ob = all_inventory(TO);
    for (i = 0; i < sizeof(ob); i++)
      {
      ob[i]->move((DRAGON_ROOM)->query_place(), 1);
    tell_object(ob[i], "The griffon suddenly jolts up into the sky, " +
    "sending you hurtling to the ground.\nAs you admire the rather large " +
    "bump on your head, you decide to HOLD ON next time.\n");
      tell_room((DRAGON_ROOM)->query_place(), "Suddenly " + QTNAME(ob[i]) +
            " arrives falling through the air.\n", ob);
      }
}

void
going_down()
{
    if (sizeof(all_inventory(TO)) <= 1)
      (DRAGON_ROOM)->set_flying(0);
}

object
room_down() { return (DRAGON_ROOM)->query_place(); }


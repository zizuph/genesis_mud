/*
 * /d/Gondor/common/jewelry/fireplace.c
 *
 * The secret fireplace room.
 *
 * Coded by Gwyneth
 */
inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include "jewelry.h"
#include "/d/Gondor/pelargir/lib/defs.h"

#define BRIDGE "/d/Gondor/lebennin/rroad/bridge"

public string search_bricks(object actor, string str);

public string
exa_bricks()
{
    string text = "They are covered in soot from long use.";

    if (this_player()->query_skill(SS_AWARENESS) >= random(50,
      atoi(OB_NUM(this_player()))))
    {
        text += " One of the bricks is slightly sunken.\n";
    }

    return text + "\n";
}

public void
create_gondor()
{
    set_short("inside a sooty fireplace");
    set_long("You stand inside a sooty fireplace that is larger than " +
        "it first appeared. The fireplace has grown cold since the wood " +
        "has burned down to nothing but ashes. Dark soot stains mark the " +
        "bricks, which make up the sides of the fireplace, from long use.\n");

    add_exit(JEWELRY_DIR + "chivalry", "out");
    add_item(({ "brick", "bricks"}), &exa_bricks());
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_bricks");
}

public void
do_slide()
{
    int i, size;
    object *things;

    tell_room(this_object(), "The floor under your feet drops away!\n" +
            "You slide down a narrow passageway, unable to stop your " +
            "descent. You land with a THUD next to a muddy river.\n");

    things = all_inventory(this_object());
    for (i = sizeof(things) - 1; i >= 0; i--)
    {
        if (living(things[i]))
        {
            tell_room(BRIDGE, QCTNAME(things[i]) + " lands in the " +
                "muddy bank with a THUD!\n");
            things[i]->move_living("M", BRIDGE, 1, 1);
        }
        else if (!things[i]->num_heap())
        {
            tell_room(BRIDGE, capitalize(LANG_ADDART(things[i]->short())) + 
                " lands in the muddy bank with a THUD!\n");
            things[i]->move(BRIDGE);
        }
        else
        {
            tell_room(BRIDGE, capitalize(things[i]->short()) +
                (things[i]->num_heap() == 1 ? " lands " : " land ") +
                "in the muddy bank with a THUD!\n");
            things[i]->move(BRIDGE);
        }
    }
}

public string
search_bricks(object actor, string str)
{
    if (str != "brick" && str != "bricks")
        return "";

    set_alarm(1.0, 0.0, &do_slide());
    return("You run your hand along the bricks. As your hand crosses " +
            "a sunken brick, you push it.\n");
}

public void
enter_inv(object ob, object from)
{
    object room, soot;

    ::enter_inv(ob, from);

    if (!living(ob))
        return;

    room = find_object(JEWELRY_DIR + "chivalry");

    room->extinguish_fire();
    soot = present("_fireplace_soot_", ob);
    if (objectp(soot))
        soot->remove_object();

    clone_object(JEWELRY_DIR + "soot")->move(ob, 1);

    if (ob->query_prop(PEL_I_DID_ATTACK))
    {
        tell_room(this_object(), "You see some movement in the main room.\n" +
            "A male human voice shouts: Leave you murdering bastard!\n");
        do_slide();
    }

}


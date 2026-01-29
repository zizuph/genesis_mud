/*
 * /d/Gondor/minas/rooms/paintq.c
 *
 * Painting room for the painter in Minas Tirith.
 *
 * Coded by Gwyneth, August 27, 2000
 */

inherit "/d/Gondor/std/room.c";

#include <cmdparse.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/rooms/paint_gon.h"

#define OBJ_M_NO_ALTER "_obj_m_no_alter"

public string read_sign();

object gPainter;

public string
read_sign()
{
    return("          Armour Painting\n" +
    "         ----------------\n" +
    "\n" +
    "  Here you may request to have a piece of armour\n" +
    "  painted " + COLOURL + " with the emblem of " + PLACE + "\n" + 
    "  If you have a piece of armour that is already\n" +
    "  painted in other colours, you may request to\n" +
    "  have it repainted in the colours of " + PLACE + ",\n" +
    "  'restore' the armour to its original state,\n" +
    "  as well as inquire about the price of painting.\n" +
    "\n" +
    "  Simply 'paint <armour><colour>' or 'inquire about <armour>'.\n" +
    "  Available colours are brown, green, silver and white.\n");
}

public void
reset_room()
{
    if (!objectp(gPainter))
    {
        gPainter = clone_object(PAINTER);
        gPainter->arm_me(0);
        gPainter->move(this_object(), 1);
    }
}

nomask void
create_gondor()
{
    set_short("In a small back room in Minas Tirith");
    set_long("This is a small, but well-lit room behind the smithy. " +
        "The light from several lamps flickers every so often, " +
        "making shadows dance upon the walls. Buckets of paint are " +
        "stacked against one wall right next to a large assortment " +
        "of brushes. A sturdy oak table and chair have been placed " +
        "within an arm's length of the paints and brushes. A sign " +
        "has been pinned to the wall. An opening in the north wall " +
        "leads to the armoury.\n");
    add_prop(ROOM_M_NO_STEAL, 1);
    add_prop(ROOM_I_INSIDE, 1);
    add_cmd_item( ({"sign", "poster"}), "read", read_sign);
    add_item( ({"sign", "poster"}), read_sign);
    add_item(({"sturdy oak table", "sturdy table", "oak table",
        "table"}), "The table shows paint stains and scratches " +
        "revealing a history of heavy use, but is obviously " +
        "the work of an expert carpenter.\n");
    add_item(({"stains", "paint stains"}), "They are a variety of " +
        "colours and shapes, and some even appear to be doodles!\n");
    add_item(({"several lamps", "lamps", "lamp", "light"}), "The " +
        "lamps have been placed in strategic spots to make best use " +
        "of their light.\n");
    add_item(({"wall", "walls", "shadows", "shadow"}), "Shadows " +
        "flicker across the walls in a hypnotic dance.\n");
    add_item(({"bucket", "buckets", "paint", "buckets of paint",
        "paint buckets"}), "The buckets contain a large assortment of " +
        "colours.\n");
    add_item(({"brushes", "brush"}), "These are very ordinary " +
        "looking brushes, yet in the right hands incredible images " +
        "can be brought to life.\n");
    add_item("chair", "The chair is made of sturdy oak, and padded " +
        "with a comfortable and well-worn cushion.\n");
    add_item(({"ceiling", "floor", "ground"}), "Oddly enough, splashes " +
        "of colour spot both the ceiling and the floor.\n");
    add_item(({"armoury", "north wall", "opening"}), "Loud noises and " +
        "heat make their way to this small room from the armoury.\n");

    add_exit(MINAS_DIR + "rooms/armoury", "north", 0, 0);
    reset_room();
}

public int
start_paint(string str)
{
    int mon, paint_index;
    string mess, *arr, paint;
    mixed *armour;

    if (!present(gPainter, this_object()))
    {
        notify_fail("There is nobody here to assist you.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Paint which armour what colour?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, all_inventory(this_player()),
      " %i %s ", armour, paint))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    paint_index = member_array(paint, COLOUR);
    if (paint_index == -1)
    {
        notify_fail("That colour is not an option.\n");
        return 0;
    }

    armour = NORMAL_ACCESS(armour, 0, 0);

    if (sizeof(armour) > 1)
    {
        notify_fail("Only one armour at a time may be painted.\n");
        return 0;
    }

    if (!sizeof(armour))
    {
        notify_fail("Paint which armour what colour?\n");
        return 0;
    }

    if (!IS_ARMOUR_OBJECT(armour[0]))
    {
        notify_fail("Only armours are painted here.\n");
        return 0;
    }

    if (wildmatch("/d/Gondor/guilds/rangers/obj/*cloak*",
      file_name(armour[0])))
    {
        notify_fail("That item looks just fine as it is.\n");
        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_GIVE))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't give the " +
                LANG_THESHORT(armour[0]) + " away to be painted.\n");
        }

        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_DROP))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("Oddly enough, you can't seem to do that.\n");
        }

        return 0;
    }

    if (armour[0]->query_lock())
    {
        notify_fail(capitalize(LANG_THESHORT(armour[0])) +
            " cannot be painted over.\n");
        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_ALTER))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail(capitalize(LANG_THESHORT(armour[0])) +
            " cannot be painted over.\n");
        }

        return 0;
    }

    if (paint != "white" &&
      (!gPainter->allow_paint(this_player()->query_real_name(), paint)))
    {
        gPainter->command("whisper to " + OB_NAME(this_player()) +
            " You haven't given me the right additives for " +
            paint + " paint yet. You can still paint it white, " +
            "or collect the right ingredients for me.");
        return 1;
    }
    arr = armour[0]->query_prop(OBJ_S_PAINTED);
    if (sizeof(arr) > 0)
    {
        if (arr[2] == paint)
        {
            notify_fail(capitalize(LANG_THESHORT(armour[0])) +
                " is already painted " + COLOUR[paint_index] + ".\n");
            return 0;
        }
        else if (gPainter->query_marker())
        {
            gPainter->command("emote looks rather busy. It " +
                "appears that you must wait your turn.\n");
            return 1;
        }
        else
        {
            if (!MONEY_ADD(this_player(),
              -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
            {
                notify_fail("You can't afford to have " +
                    LANG_THESHORT(armour[0]) + " repainted.\n");
                return 0;
            }
            mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
            write("You pay " + mon + " copper to " +
                gPainter->query_the_name(this_player()) + ".\n");
            gPainter->add_paint(this_player(), armour[0], paint_index ,1);
            return 1;
        }
    }
    if (gPainter->query_marker())
    {
        gPainter->command("emote looks rather busy. It " +
            "appears that you must wait your turn.\n");
        return 1;
    }

    mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
    if (!MONEY_ADD(this_player(),
      -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(armour[0]) + " painted.\n");
        return 0;
    }

    write("You pay " + mon + " copper to " +
        gPainter->query_the_name(this_player()) + ".\n");

    gPainter->add_paint(this_player(), armour[0], paint_index, 0);
    return 1;    
}

public int
inquire(string str)
{
    int i, sz;
    mixed *arm;
    string *arr, place;

    if (!strlen(str))
    {
        notify_fail("Inquire about which item?\n");
        return 0;
    }

    str = lower_case(str);
    if (!parse_command(str, this_player(), 
      "[about] [the] [price] [of] [the] [a] %i", arm))
    {
        notify_fail("You don't seem to have such an armour on you.\n");
        return 0;
    }

    arm = NORMAL_ACCESS(arm, 0, 0);

    sz = sizeof(arm);

    if (!sz)
    {
        notify_fail("Inquire about which item?\n");
        return 0;
    }

    if (!present(gPainter, this_object()))
    {
        notify_fail("There is nobody here to help you.\n");
        return 0;
    }

    i = -1;
    while(++i < sz)
    {
        if (!IS_ARMOUR_OBJECT(arm[i]) ||
          arm[i]->query_prop(OBJ_M_NO_DROP) ||
          arm[i]->query_prop(OBJ_M_NO_GIVE) ||
          arm[i]->query_lock())
        {
            gPainter->command("say I'm afraid I can't work with the " +
                arm[i]->short() + ".");
        }
        else
        {
            gPainter->command("say It would cost you " +
                ((arm[i]->query_prop(OBJ_I_VOLUME) * 1728) / 2000) +
                " copper to paint the " + arm[i]->short() + ".");
            if (sizeof(arm[i]->query_prop(OBJ_S_PAINTED)) > 0)
            {
                gPainter->command("say It would cost you " +
                    ((arm[i]->query_prop(OBJ_I_VOLUME) * 1728) / 4000) +
                    " copper to restore the " + arm[i]->short() + ".");
            }
        }
    }

    return 1;
}

public void
add_solv(object arm)
{
    string *adjs = arm->query_adjs();
    string *nadjs = arm->query_prop(OBJ_S_PAINT_INFO)[3];

    if (!gPainter->solv_tells(arm, this_player()))
    {
        return;
    }
 
    arm->move(gPainter, 1);
    write("You hand your " + arm->short() + " to " +
        gPainter->query_the_name(this_player()) + ".\n");
    say(QCTNAME(this_player()) + " hands " + this_player()->query_possessive() +
        " " + arm->short() + " to " + QTNAME(gPainter) + ".\n");
    write("You request to have your " + arm->short() +
        " restored to its unpainted state.\n");
    arm->set_long(arm->query_prop(OBJ_S_PAINT_INFO)[0]);
    arm->set_short(arm->query_prop(OBJ_S_PAINT_INFO)[1]);
    arm->set_pshort(arm->query_prop(OBJ_S_PAINT_INFO)[2]);
    arm->remove_adj(adjs);
    arm->add_adj(nadjs);
    arm->remove_name("_gondor_painted");
    arm->remove_prop(OBJ_S_PAINTED);
    arm->remove_prop(OBJ_S_PAINT_INFO);
    arm->add_prop(OBJ_M_NO_ALTER, 1);
    return;
}

public int
start_solv(string str)
{
    int mon;
    string mess, *arr;
    mixed *armour;

    if (!present(gPainter, this_object()))
    {
        notify_fail("There is nobody here to assist you.\n");
        return 0;
    }

    if (gPainter->query_marker())
    {
        gPainter->command("say I am busy with another job now.");
        notify_fail("It appears you must wait your turn.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Restore which armour?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, all_inventory(this_player()),
      " %i ", armour))
    {
        notify_fail("You don't seem to have that item.\n");
        return 0;
    }

    armour = NORMAL_ACCESS(armour, 0, 0);

    if (sizeof(armour) > 1)
    {
        notify_fail("Only one armour at a time may be restored.\n");
        return 0;
    }

    if (!sizeof(armour))
    {
        notify_fail("Restore which armour?\n");
        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_GIVE))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("You can't give the " +
                LANG_THESHORT(armour[0]) + " away to be restored.\n");
        }

        return 0;
    }

    if (mess = armour[0]->query_prop(OBJ_M_NO_DROP))
    {
        if (stringp(mess))
        {
            notify_fail(mess);
        }
        else
        {
            notify_fail("Oddly enough, you can't seem to do that.\n");
        }

        return 0;
    }

    arr = armour[0]->query_prop(OBJ_S_PAINTED);
    if (!sizeof(arr))
    {
        notify_fail("That item can't be restored.\n");
        return 0;
    }

    mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 4000);
    if (!MONEY_ADD(this_player(),
      -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 4000)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(armour[0]) + " restored.\n");
        return 0;
    }

    write("You pay " + mon + " copper to " +
        gPainter->query_the_name(this_player()) + ".\n");

    add_solv(armour[0]);
    return 1;    

}

public void
init()
{
    ::init();

    add_action(start_paint, "paint");
    add_action(inquire, "inquire");
    add_action(start_solv, "restore");
}

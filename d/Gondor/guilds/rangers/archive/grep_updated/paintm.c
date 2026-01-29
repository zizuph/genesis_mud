/*
 * /d/Gondor/morgul/city/rooms/paintm.c
 *
 * Painting room for the painter in Minas Morgul.
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
#include "/d/Gondor/morgul/cellar/paint_mm.h"

public string read_sign();

object gPainter;

public string
read_sign()
{
    return("          Armour Painting\n" +
    "         ----------------\n" +
    "\n" +
    "  Here you may order a piece of armour painted\n" +
    "  " + COLOUR + " with the emblem of " + PLACE + "\n" + 
    "  If you have a piece of armour that is already\n" +
    "  painted in other colours, you may order it\n" +
    "  repainted in the colours of " + PLACE + "\n" +
    "  as well as inquire about the price of painting.\n" +
    "\n" +
    "  Simply 'paint <armour>' or 'inquire about <armour>'.\n");
}

public void
reset_room()
{
    if (!objectp(gPainter))
    {
        gPainter = clone_object(PAINTER);
        gPainter->arm_me();
        gPainter->move(TO, 1);
    }
}

nomask void
create_gondor()
{
    set_short("In a dirty back room in Minas Morgul");
    set_long("This is a small, but well-lit room behind the " +
        "smithy. The light from several lamps flickers every " +
        "so often, making shadows dance upon the walls. Buckets " +
        "of paint are stacked against one wall right next to a " +
        "large assortment of brushes. A sturdy oak table and chair " +
        "have been placed within an arm's length of the paints and " +
        "brushes. A sign has been pinned to the wall. A small opening " +
        "leads out to the west.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_STEAL, 1);
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

    add_exit(MORGUL_DIR + "cellar/wsmithy", "west", 0, 0);

    reset_room();
}

public string
query_pair(object ob, int pl)
{
    string sh_desc = ob->short();

    if (wildmatch("*pair*", sh_desc))
    {        
        if (pl)
        {
            return "pairs of ";
        }
        else
        {
            return "pair of ";
        }
    }
    return "";
}

public string
query_true_name(object ob, int pl)
{
    int i, sz;
    string *names, sh_desc, *descs, *temp;

    /* Find the names and short desc for the armour (non-plural forms) */
    if (!pl)
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }
    /* Find the plural names and plural short for the armour if
       the pshort hasn't been set. */
    else if (!ob->plural_short())
    {
        names = ob->query_pnames();
        sh_desc = (ob->short() + "s");
    }
    /* Find the plural names and plural short for the armour if
       the pshort has been set. */
    else
    {
        names = ob->query_pnames();
        sh_desc = ob->plural_short();
    }

    if (wildmatch("*pairs*", sh_desc))
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }

    /* Remove any names with spaces in them for the calculation,
       such as "pair of boots" in order to get a nicer
       looking output. */
    for (i = sizeof(names) - 1; i > -1; i--)
    {
        if (wildmatch("* *", names[i]))
        {
            names -= ({ names[i] });
        }
    }

    temp = names;

    /* Remove the name of armour(s) for the calculation, as it's not
       our first choice for a description. We put it back
       in the end in case armour is the only name. */
    if (member_array("armour", names) >= 0)
    {
        names -= ({ "armour" });
    }

    if (member_array("armours", names) >= 0)
    {
        names -= ({ "armours" });
    }

    /* Make an array of each word in the short desc. */
    descs = explode(sh_desc, " ");    

    /* If a name is in the short desc, choose this for the
       name to return as in the case of "blue dragonscale armour" */
    for (i = 0, sz = sizeof(names); i < sz; i++)
    {
        if (member_array(names[i], descs) >= 0)
        {
            return names[i];
        }
    }

    /* We don't want the object number to be given if it
       comes down to that. */
    if (temp[0] == OB_NUM(ob))
    {
        if (pl)
        {
            return "armours";
        }
        else
        {
            return "armour";
        }
    }

    return temp[0];
}

public void
add_paint(object arm, int r)
{
    string *adjs = arm->query_adjs();
    string desc;

    if (!gPainter->paint_tells(arm, TP))
    {
        return;
    }
 
    arm->move(gPainter, 1);
    write("You hand your " + arm->short() + " to " +
        gPainter->query_the_name(TP) + ".\n");
    say(QCTNAME(TP) + " hands " + TP->query_possessive() +
        " " + arm->short() + " to " + QTNAME(gPainter) + ".\n");

    /* If the armour has never been painted, find the short. */
    if (!r)
    {
        desc = arm->short();
        write("You order " + gPainter->query_the_name(TP) +
            " to paint your " + desc + " " + 
            COLOUR + " with the emblem of " + PLACE + ".\n");
        arm->set_long( LONG(arm) );
    }
    /* If the armour has been painted, find the original short. */
    else
    {
        desc = arm->query_prop(OBJ_S_PAINTED)[1];
        write("You order " + gPainter->query_the_name(TP) +
            " to repaint your " + 
            arm->short() + " " + COLOUR +
            " with the emblem of " + PLACE + ".\n");
        arm->set_long( RLONG(arm) );
        arm->remove_name("_gondor_painted_white");
    }

    arm->add_prop(OBJ_S_PAINTED, ({ PLACE, desc }));
    arm->remove_adj(adjs);
    arm->add_adj(ADJS);
    arm->set_short( SHORT(arm) );
    arm->set_pshort( PSHORT(arm) );
    arm->add_name("_gondor_painted_black");
}

public int
start_paint(string str)
{
    int mon;
    string mess, *arr;
    mixed *armour;

    if (!present(gPainter, TO))
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

    if (!stringp(str))
    {
        notify_fail("Paint which armour?\n");
        return 0;
    }

    str = lower_case(str);

    if (!parse_command(str, all_inventory(this_player()),
      " %i [white] ", armour))
    {
        notify_fail("You don't seem to have a " + str + ".\n");
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
        notify_fail("Paint which armour?\n");
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
        notify_fail("That cloak looks just fine as it is.\n");
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

    arr = armour[0]->query_prop(OBJ_S_PAINTED);
    if (sizeof(arr) > 0)
    {
        if (arr[0] == PLACE)
        {
            notify_fail(capitalize(LANG_THESHORT(armour[0])) +
                " is already painted with the emblem of " + PLACE + ".\n");
            return 0;
        }
        else
        {
            if (!MONEY_ADD(TP,
              -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
            {
                notify_fail("You can't afford to have " +
                    LANG_THESHORT(armour[0]) + " repainted.\n");
                return 0;
            }

            mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
            write("You pay " + mon + " copper to " +
                gPainter->query_the_name(TP) + ".\n");
            log_file("painted", ctime(time()) + " " + TP->query_name() +
                " " + file_name(armour[0])+ " white " +
                "to black (" + SHORT(armour[0]) + "/" + PSHORT(armour[0]) +
                ") for " + mon + " copper.\n");
            add_paint(armour[0], 1);
            return 1;
        }
    }

    if (!MONEY_ADD(TP,
      -((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000)))
    {
        notify_fail("You can't afford to have " +
            LANG_THESHORT(armour[0]) + " painted.\n");
        return 0;
    }

    mon = ((armour[0]->query_prop(OBJ_I_VOLUME) * 1728) / 2000);
    write("You pay " + mon + " copper to " +
        gPainter->query_the_name(TP) + ".\n");
    log_file("painted", ctime(time()) + " " + TP->query_name() +
        " " + file_name(armour[0])+ " black (" + SHORT(armour[0]) +
        PSHORT(armour[0]) + ") for " + mon + " copper.\n");
    add_paint(armour[0], 0);
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
    if (!parse_command(str, TP, "[about] [the] [price] [of] [the] [a] %i",
      arm))
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

    if (!present(gPainter, TO))
    {
        notify_fail("There is nobody here to help you.\n");
        return 0;
    }

    i = -1;
    while(++i < sz)
    {
        arr = arm[i]->query_prop(OBJ_S_PAINTED);

        if (sizeof(arr) > 0)
        {
            place = arr[0];
        }

        if (!IS_ARMOUR_OBJECT(arm[i]) ||
          arm[i]->query_prop(OBJ_M_NO_DROP) ||
          arm[i]->query_prop(OBJ_M_NO_GIVE) ||
          arm[i]->query_lock() ||
          place == "Minas Morgul")
        {
            gPainter->command("say I'm afraid I can't paint the " +
                arm[i]->short() + ".");
        }
        else
        {
            gPainter->command("say It would cost you " +
                ((arm[i]->query_prop(OBJ_I_VOLUME) * 1728) / 2000) +
                " copper to paint the " + arm[i]->short() + ".");
        }
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(start_paint, "paint");
    add_action(inquire, "inquire");
}

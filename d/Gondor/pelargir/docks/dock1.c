/*
 * /d/Gondor/pelargir/docks/dock1.c
 *
 * Here stops Grosso, Captain of the Circle Line, on his tour from
 * Sparkle to Pelargir and Re Albi.
 * There is also a small quest in this room.
 *
 * Original version by Cinder and Olorin.
 *
 * Modification log:
 * Olorin, 12-Jan-1997: Added the quest.
 * Gnadnar, 14-Jan-1999: fixed bug in filter of worn objects
 * Gorboth, 31-Oct-2005: changed code to force the quest to reset if a
 *                       player left it in a half-finished state for more
 *                       than 4 resets.
 * Tapakah, 31-May-2009: converted to the new ship model
 */
#pragma strict_types
 
inherit "/d/Gondor/std/room";
inherit "/d/Gondor/pelargir/city_items.c";
#include "/d/Gondor/common/lib/gs_include.c"
#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../lib/repair_dock.h"

inherit "/d/Genesis/gsl_ships/lib/pier";

#define MIN_AWARE      20
#define STRENGTH      200
#define PELARGIR_I_BROKEN_PLANK "_pelargir_i_broken_plank"
#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
// Global variables:
static object  Sailor;
static object  sign;
static int     Plank_Status = 1,    // 1 - plank broken, 2 - plank
                                    // removed, 3 - plank replace, but
                                    // not nailed down, 0 - plank
                                    // replaced and nailed down.
               Plank_Nailed = STRENGTH,
               Room_Resets = 0;  /* how many times has the room reset
                                  * since someone half completed the
                                  * dock repair quest?
                                  */

// Prototypes:
public int     stumble();
public string  climb_dock();
public string  exa_planks();
public string  exa_plank();
public string  remove_plank();
public string  replace_plank();

public int     query_plank() { return Plank_Status; }
public void    set_plank(int i) { Plank_Status = i; }

public void
reset_room()
{
    if (!Plank_Status || Room_Resets > 4)
    {
        Plank_Status = 1;
        Plank_Nailed = STRENGTH;
        Room_Resets = 0;
    }
    else
    {
        Room_Resets++;
    }

    if (!objectp(Sailor))
    {
        Sailor = clone_object(PELAR_DIR + "npc/sailor");
        Sailor->arm_me();
        Sailor->move_living("down", TO);
    }
}

public void
create_gondor()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This dock seems very old indeed. The wood is still "
        + "sturdy and a ship still docks here, though the wood seems "
        + "almost petrified with age. The water gurgles and churns "
        + "loudly below from the merging Sirith river. To the south "
        + "the many docks of Pelargir extend along the shoreline, and "
        + "to the west, the Anduin river spreads its width almost "
        + "beyond your vision. Across the mouth of the Sirith to the "
        + "north, you can view the lighthouse tower."));

    add_item( ({"dock", "wood", }), BSN("The dock reaches out into "
        + "the water of the Anduin where it rests on wooden pillars "
        + "that are completely covered by shells and clams. The "
        + "wooden planks on top of the dock show the signs of decades "
        + "of heavy use."));
    add_item( ({"shells", "clams", "pillars", "wooden pillars"}), 
        BSN("The wooden pillars on which the dock rests are covered "
            + "by a thick layer of shells and clams. They are out of "
            + "reach however."));
    add_item( ({"planks", "wooden planks", }), exa_planks);
    add_item( ({"plank", "wooden plank", "broken plank" }),
        exa_plank); 
            
    add_cmd_item( ({"down", "dock", "pillar", "hole",  }), "climb",
        climb_dock); 
    add_cmd_item( ({"plank", "broken plank", }), "remove",
        remove_plank); 
    add_cmd_item( ({"plank", "broken plank", }), "replace",
        replace_plank); 
            
    add_dockships();
    add_anduin("docks");
    add_towers();
    add_lighthouse("bay");
    add_sirith();
    add_admiral("southwest");

    add_exit(PELAR_DIR + "docks/dock2", "south", stumble);
    add_exit(PELAR_DIR + "streets/shipwright05", "west", stumble);

    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();
    add_pier_entry(MASTER_OB(TO), "Pelargir", "Pan-Donut Circle");
    initialize_pier();
}

object
query_sign ()
{
  return sign;
}

public string
climb_dock()
{
    if (item_id("hole"))
        return "You try to climb down through the hole, but it is too "
            + "small for you.\n";
    return "You try to climb down under the dock, but you cannot "
        + "find any footholds, so you give up your attempt.\n";
}

private void
add_hole()
{
    add_item("hole", BSN("There is a large gaping hole among the "
        + "planks that form the top of the dock. It is about a foot "
        + "wide and four feet in length. "
        + "Someone should put a plank over the hole to close it "
        + "before someone gets hurt in it."));
}

public string
exa_planks()
{
    object  tp = TP;
    int     skill = tp->query_skill(SS_AWARENESS);
    string  desc = "The top of the dock is covered by thick wooden "
        + "planks which show the signs of heavy use and old age. The "
        + "planks are still sturdy enough to carry heavy weights and "
        + "they are generally in good repair.";

    if (Plank_Status == 2)
        desc += " One of the planks is missing however and the "
            + "remaining hole is a dangerous trap for dockworkers "
            + "and passengers.";
    else if ((skill >= MIN_AWARE) ||
        tp->query_prop(PELARGIR_I_BROKEN_PLANK))
    {
        if (Plank_Status == 1)
        {
            tp->add_prop(PELARGIR_I_BROKEN_PLANK, 1);
            desc += " One of the planks is broken however and now "
                + "is a dangerous trap for dockworkers and "
                + "passengers.";
        }
        else
            desc += " One of the planks has been replaced recently.";
    }

    return BSN(desc);
}

public string
exa_plank()
{
    object  tp = TP;
    int     skill = tp->query_skill(SS_AWARENESS);
    string  desc;

    if (Plank_Status == 2)
        return "One of the planks is missing. All that remains is "
            + "a dangerous hole.\n";
    else if ((skill < MIN_AWARE) &&
        !tp->query_prop(PELARGIR_I_BROKEN_PLANK)) 
        return "All planks look alike, old and sturdy.\n";
    else if (Plank_Status == 1)
    {
        tp->add_prop(PELARGIR_I_BROKEN_PLANK, 1);
        return "The broken plank is a dangerous trap for people "
            + "walking on the dock, as they might stumble over "
            + "it. The plank is broken in the middle, but both "
            + "ends are still nailed to the dock. It might be "
            + "possible to remove the broken plank with the proper "
            + "tools.\n";
    }
    else
    {
        desc = "One of the planks does not fit to the others "
            + "making up the top of the dock. It looks as if it "
            + "has been replaced recently.";
        if (Plank_Status == 3)
            desc += " You noticed that it has not yet been nailed "
                + "on to the dock, but rather only put into the hole "
                + "to cover it.";
        return BSN(desc);
    }
}

public int
stumble()
{
    object  tp = TP,
           *inv;
    int     skill = tp->query_skill(SS_AWARENESS);

    if ((Plank_Status != 1) ||
        tp->query_prop(PELARGIR_I_BROKEN_PLANK) ||
        tp->query_npc()) 
        return 0;

    if ((random(skill) < MIN_AWARE) && 
        (random(tp->query_stat(SS_DEX)) < MIN_AWARE))
    {
        tp->add_prop(PELARGIR_I_BROKEN_PLANK, 1);
        write("As you try to move on, you clumsily stumble over a "
            + "broken plank on the dock and fall down.\n");
        inv  = filter(all_inventory(tp), &->check_seen(tp));
        inv -= filter(inv, &->query_prop(OBJ_I_NO_DROP));
        inv -= filter(inv, objectp @ &->query_worn());
        if ( sizeof(inv) )
            tp->command("$drop " + OB_NAME(ONE_OF_LIST(inv)));
        if ( sizeof(tp->query_weapon(-1)) )
            tp->command("$unwield all");
        return 1;
    }
    return 0;
}

private string
check_replace()
{
    int     vol;
    object  tp = TP,
            plank;

    if (objectp(plank = present("plank", TP)) &&
        !plank->query_prop(OBJ_I_BROKEN)) 
    {
        // We have a good new plank, but is it the right size?
        // Due to the lack of a height or length prop for objects, we
        // just check the volume of the new plank:
        if ((vol = plank->query_prop(OBJ_I_VOLUME)) < 16000)
        {
            set_alarm(0.0, 0.0, &plank->remove_object());
            return "You put the " + plank->short() + " into the hole "
                + "on the dock.\n"
                + "Alas, it is too short and falls through the "
                + "hole.\n";
        }
        else if (vol > 20000)
            return "You try to put the " + plank->short() + " into "
                + "the hole on the dock, but it is too long.\n";
        else
        {
            // Between 16000 and 20000 ccm is the right size:
            // Width 30 cm, thickness 5 cm, length 120 cm (18 000 ccm).
            Plank_Status = 3;
            say(QCTNAME(tp) + " puts " + LANG_ADDART(plank->short())
                + " into the hole on the dock, closing it.\n");
            write("You put the " + plank->short() + " into the hole "
                + "on the dock.\n"
                + "It is a perfect fit and covers the hole "
                + "completely.\n");
            remove_item("hole");
            plank->remove_object();
            SET_STAGE(tp, REPAIR_REPLACE);
            /*
            tp->add_prop(PELARGIR_I_REPAIR_DOCK,
                tp->query_prop(PELARGIR_I_REPAIR_DOCK) |
                REPAIR_REPLACE);
                */
            return "";
        }
    }
    return "You do not have a new plank to close the hole in "
        + "the dock.\n";
}

public string
replace_plank()
{
    switch (Plank_Status)
    {
    case 0: 
        return "The broken plank has already been replaced.\n";
    case 1:
        return "You will have to remove the broken plank first.\n";
    case 2:
        return check_replace();
    case 3:
        return "The plank has already been replaced.\n"
            + "It still has to be nailed onto the dock, however.\n";
    }
}

public string
remove_plank()
{
    object  tp = TP,
           *weps = tp->query_weapon(-1),
            tool,
            plank;
    int     str = tp->query_stat(SS_STR),
            fat;
    string  rest,
            tool_name;

    if (Plank_Status == 3)
    {
        plank = clone_object(PELAR_DIR + "obj/plank");
        plank->move(TO, 1);
        say(QCTNAME(tp) + " removes a loose " + plank->short() 
            + "from the dock, revealing a hole.\n"); 
        add_hole();
        return "You remove the loose " + plank->short() + " from the "
            + "dock and drop it, revealing a hole.\n";
    }

    if (Plank_Status != 1)
        return "There is no plank to remove here.\n";

    // We permit only one weapon to be wielded.
    if (sizeof(weps) > 1)
        return "You will never manage to remove the plank while "
            + "your hands are occupied wielding weapons.\n";

    if ((fat = tp->query_fatigue()) < 10)
        return "You are too exhausted to do that!\n";

    if (strlen(rest = query_item_rest_command()))
    {
        if (sscanf(rest, "with %s", tool_name) <= 0)
            return "Try to remove the plank.\n";

        if (!sizeof(weps) || !weps[0]->id(tool_name))
        {
            if (!objectp(tool = present(tool_name, tp)))
                return "You don't have any " + tool_name + ".\n";
            else if (!(function_exists("create_object", tool) == WEAPON_OBJECT))
                return "You cannot use the " + tool_name + " to pry the plank lose.\n";
            else
                return "Wield the " + tool_name + " first!\n";
        }
    }

    // If a weapon is wielded, it is used as a tool, but if it is not
    // suited to the task at hand, it is likely that it will break:
    // We can use crowbars. Swords, polearms, axes, and knives may
    // break, clubs cannot be used:
    if (sizeof(weps))
    {
        tool = weps[0];
        if (tool->id("crowbar"))
            str *= 2;
        else if (tool->query_wt() == W_CLUB)
            return "You cannot use your " + tool->short() + " to pry "
                + "the broken plank loose.\n";

        write("You try to pry the broken plank loose with your " 
            + tool->short() + ".\n");
        say(QCTNAME(tp) + " tries to pry a broken plank loose "
            + "using " + tp->query_possessive() + " " + tool->short()
            + ".\n");

        if ((random(str) > tool->query_pen()) && !tool->id("crowbar"))
        {
            tool->remove_broken();
            write("Oops, it looks like your " + tool->short() + 
                " was not made for this kind of work.\n" + 
                "You feel pretty stupid.\n");
            say("Obviously, the " + tool->short() + " was not made "
                + "for that kind of work.\n");
            return "";
        }
    }
    else
    {
        write("You try to pry the broken plank loose with your " 
            + "bare hands.\n");
        say(QCTNAME(tp) + " tries to pry a broken plank loose "
            + "with " + tp->query_possessive() + " bare hands.\n");
    }

    if (!objectp(tool))
    {
        str = MIN(str, fat * 2);
        tp->add_fatigue(- MAX(10, str / 2));
    }
    else
    {
        str = MIN(str, fat * 5);
        tp->add_fatigue(- MAX( 5, str / 5));
    }

    Plank_Nailed -= random(str);

    if (Plank_Nailed <= 0)
    {
        Plank_Status = 2;
        write("You succeed in removing the broken plank.\n"
            + "Now there is a hole in the dock in place of the broken "
            + "plank.\n");
        say(QCTNAME(tp) + " removes the broken plank.\n"
            + "Now there is a hole among the planks on top of the "
            + "dock.\n");
        add_hole();
        plank = clone_object(PELAR_DIR + "obj/plank");
        plank->set_length(120);
        plank->add_prop(OBJ_I_BROKEN, 1);
        plank->move(TO, 1);
        SET_STAGE(tp, REPAIR_REMOVE);
    }
    else
    {
        write("The plank gives a little, but you fail to remove it.\n");
    }
    return "";
}

public int
do_replace(string str)
{
    object *obj;
    string  vb = query_verb(),
            what,
            result;

    NFN(CAP(vb) + " what with what?");
    if (!strlen(str))
        return 0;

    if (!parse_command(LOW(str), TP, " [the] %w 'with' [the] %i ",
        what, obj))
        return 0;

    obj = NORMAL_ACCESS(obj, 0, 0);

    if (!sizeof(obj) || (what != "hole"))
        return 0;

    if (strlen(result = replace_plank()))
        write(result);
    return 1;
}

public int
do_insert(string str)
{
    object *obj;
    string  vb = query_verb(),
            what,
            result;

    NFN(CAP(vb) + " what into what?");
    if (!strlen(str))
        return 0;

    if (!parse_command(LOW(str), TP, " [the] %i 'in' / 'into' [the] %w ",
        obj, what))
        return 0;

    obj = NORMAL_ACCESS(obj, 0, 0);

    if (!sizeof(obj) || (what != "hole"))
        return 0;

    if (strlen(result = replace_plank()))
        write(result);
    return 1;
}

public int
do_nail(string str)
{
    int     n;
    object  nails,
            hammer,
            tp = TP;
    string  vb = query_verb();

    if (!strlen(str))
        NFN0(CAP(vb) + " what to what?");

    if (!objectp(hammer = present("hammer", tp)))
        NFN0("You need a hammer if you wish to " + vb +
            " something to something.");

    if (hammer->query_wielded() != tp)
        NFN0("You must wield your " + hammer->short() + " first!");

    if (!objectp(nails = present("nail", tp)))
        NFN0("You don't have any nails!");

    if (function_exists("create_heap", nails) != (OBJ_DIR + "nail"))
    {
	if (MASTER_OB(nails) == "/std/leftover")
	{
	    write("You smash the fingernail into pulp.\n");
	}
	else
	{
	    WRITE("You attempt to hammer the nail into the plank, " +
		"but it flies out of your grasp and falls into the " +
		"water below.");
	}
	nails->remove_object();
	return 1;
    }

    if (!parse_command(LOW(str), ({ }), 
        " 'plank' / 'board' 'to' 'dock' "))
        NFN0(CAP(vb) + " what to what?");

    if (Plank_Status < 3)
        NFN0("That is not necessary here.");

    if ((n = nails->num_heap()) > 1)
        nails->set_heap_size(n - 1);
    else
        nails->remove_object();
    say(QCTNAME(tp) + " nails a plank to the dock.\n");

    if (++Plank_Status > 4)
    {
        write("You nail the plank to the dock with a second nail.\n"
            + "Both ends of the plank are securely fastened to the "
            + "dock now and the repair is completed.\n");
        Plank_Status = 0;
        SET_STAGE(tp, REPAIR_NAIL);
    }
    else
        write("You secure one end of the plank to the dock with a "
            + "single nail.\n"
            + "Perhaps you should use at least one other nail.\n");

    return 1;
}

public void
init()
{
    ::init();

    add_action(do_replace, "close");
    add_action(do_replace, "cover");
    add_action(do_insert,  "put");
    add_action(do_nail,    "nail");
}

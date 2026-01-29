/*
 *  /d/Gondor/guilds/rangers/north/north_funcs.c
 *
 *  Various functions for North Hideout rooms
 *
 *  Coded by Alto, 18 July 2001
 *
 */
inherit "/d/Gondor/std/room.c";

#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* Global variables */

string             *handle    =({});
string             *extradesc =({});
string             gExline, gVehicle;
static object      gTstand;

#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"

/* Prototypes */

public void        north_add_items();
public int         daylight();
public void        north_add_torch();
public string      vantage_extraline();
public int         vantage_add_cmds();
public int         crawl_stairs();
public int         leap_chasm();
public int         swing_rope();
public int         move_stones();
public int         exit_room();
public int         move_ranger(object who);
public void        vantage_add_items();


void
north_add_items()
{
    add_prop(ROOM_M_NO_SCRY, 1);
    add_item(({"room"}), "You look around and see a number of interesting "
        + "things.\n");
    add_item(({"floor", "stone floor", "ground"}), "The floor here "
        + "is made from ancient slabs of stone covered by soft carpets. "
        + "Near the walls you can still make out the rich forest green "
        + "of the carpet as it was when first placed over the floor. "
        + "In most places, however, the colouration has long been worn away "
        + "by the passage of generations of booted feet.\n");
    add_item(({"carpet", "carpets"}), "The carpets covering the floor were "
        + "once dyed with a rich green stain. Only those places out of the "
        + "way of booted feet, however, have survived the ages unscathed.\n");
    add_item(({"slabs", "ancient slabs", "stone"}), "The floor is made up of "
        + "great slabs of stone, quarried long ago by dwarves in the service "
        + "of the kingdom of Arnor.\n");
    add_item(({"wall", "walls"}), "The walls, like most things in the "
        + "hideout, are constructed from stone. Unlike most rock, however, "
        + "the stone of the hideout feels almost warm to the touch. Deep roots "
        + "are not touched by the frost.\n");
    add_item(({"ceiling"}), "The ceilings of the hideout vault above you, "
        + "supported by graceful arches.\n");
    add_item(({"arches", "graceful arches"}), "The crafting of the "
        + "ceiling must have required amazing labour and skill. The arches "
        + "supporting it are thin, sweeping and graceful, and from a distance "
        + "appear to be real trees growing inside.\n");
    add_item(({"hideout", "north hideout", "northern hideout"}), "It "
        + "is all around you. The compound is entirely below the ground, and "
        + "were you to view it from the outside, all you would see are the "
        + "remains of the tower above.\n");
}

void
north_add_torch()
{
    object *inv;

    inv = all_inventory(this_object());

    if (!sizeof(filter(inv, &->id("torchstand"))))
    {
        gTstand = clone_object(OBJ_DIR + "torchstand");
        gTstand->set_time(1999);
        gTstand->set_lit(1);
        gTstand->set_replace_msg("A grey-cloaked sentinel slips quietly into "
            + "the room and places a new torch in the iron stand. After "
            + "lighting the new torch, the sentinel slips away and "
            + "disappears around a corner.\n");
        gTstand->set_no_desc(1);
        gTstand->remove_prop(CONT_I_ATTACH, 1);
        gTstand->move(TO);
    }
}


/*
 * Function name: daylight
 * Description  : return lightlevel of room
 * Returns      : 0 if evening/night, 1 otherwise
 */
public int
daylight()
{
    string timestr = tod();
    if (timestr == "night" || timestr == "evening")
        return 0;
    return 1;
}


string
vantage_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"The stairs are cracked and broken here. It would be best if "
               + "you tried to crawl over them.", 
/*2*/     "There is a huge chasm between the stairs directly in front "
               + "of you and those several feet further away. You think "
               + "you can leap across it.", 
/*3*/     "There are no stairs here at all! Someone has tied a rope to "
               + "a peg on the wall. Perhaps you can swing on it to the "
               + "next landing.",
/*4*/     "The stairwell is choked with rubble here. You will need to "
               + "move several heavy stones before you can pass."});


    string *handle =
/*1*/     ({"stairs", 
/*2*/       "chasm", 
/*3*/       "rope",
/*4*/       "stones"});


    gExline = one_of_list(extradesc);

    position = member_array(gExline, extradesc);

    gVehicle = handle[position];

    return gVehicle;
}


/* Add commands for respective movement item */

int
vantage_add_cmds()
{
    switch (gVehicle)
    {
    case "stairs":
        add_cmd_item(({"stairs", "over stairs", "over the stairs"}), "crawl",
            &exit_room());
        add_item(({"stairs", "steps", "step"}), "The stairs here look very "
            + "untrustworthy. Many are cracked and broken, and some are "
            + "almost entirely eroded away. It would be best to just get "
            + "down on all fours and crawl over them.\n");
        return 1;

    case "chasm":
        add_cmd_item(({"chasm", "the chasm", "across chasm", 
            "across the chasm"}), "leap", &exit_room());
        add_item(({"chasm", "huge chasm"}), "The stairs here have "
            + "completely crumbled and fallen away, leaving a huge "
            + "chasm. The only way up from here would be to leap "
            + "across it.\n");
        return 1;

    case "rope":
        add_cmd_item(({"rope", "on rope", "on the rope"}), "swing",
            &exit_room());
        add_item(({"rope"}), "It looks sturdy and relatively new. You "
            + "may be able to swing on it to the next landing.\n");
        add_item(({"stairs", "steps"}), "There are none here, which "
            + "presents a problem if you intend to go further up the "
            + "stairwell.\n");
        add_item(({"peg"}), "It is mounted on the wall, and has a "
            + "rope tied to it.\n");
        return 1;

    case "stones":
        add_cmd_item(({"stones", "the stones", "heavy stones", 
            "the heavy stones"}),
            "move", &exit_room());
        add_item(({"stones", "heavy stones", "stone", "heavy stone"}), 
            "These stones certainly look heavy. They also impede further "
            + "progress up the stairwell. You wonder if you can move them.\n");
        add_item(({"rubble"}), "Fallen stones have almost completely "
            + "blocked the stairwell here.\n");
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please file "
            + "a bug report.\n");
        return 1;
    }
}


/* Set long description of room with extraline from above */

string
long_desc()
{
    return "You are climbing up a ruined stairwell somewhere beneath the "
        + "ruins of Fornost. Every footstep seems treacherous, and you "
        + "find yourself wondering if it was such a good idea to attempt "
        + "the stairwell. " + gExline + "\n";
}


/* Additional items common to all vantage rooms */

void
vantage_add_items()
{
    add_item(({"wall", "walls"}), "The only wall here runs along the "
        + "outside of the stairwell. The inner side of the stairwell "
        + "opens into a yawning darkness. There is an iron torch stand "
        + "mounted on the wall here.\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"floor", "ground"}), "The floor here is comprised of "
        + "crumbling stairs.\n");
    add_item(({"roof", "ceiling"}), "Looking up, you see only the stairwell "
        + "circling up into the yawning darkness.\n");
    add_prop(ROOM_M_NO_SCRY, 1);
}


/* Functions for what player sees while moving to the next room */

int
finish_moving(object who)
{
    who->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}

int
crawl_stairs()
{
    object actor = TP;

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.1, 0.0, &actor->catch_tell("You bend down on all fours and "
        + "begin to crawl across the crumbling stairs.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("A step breaks loose under your "
        + "weight!\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("You scramble forward as quickly "
        + "as possible, steps crumbling and breaking away beneath you.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " bends down on all "
        + "fours and begins to crawl across the crumbling stairs.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "A step breaks "
        + "loose beneath " + QCTNAME(actor) + "!\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " scrambles forward as quickly as possible.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}

int
leap_chasm()
{
    object actor = TP;

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You back away from the chasm "
        + "and get a running start.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("You leap into the open air!\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("You barely make it across "
        + "and stumble as you land.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " backs away from "
        + "the chasm and gets a running start.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " leaps into the open air!\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " just barely makes it across.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}

int
swing_rope()
{
    object actor = TP;

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.1, 0.0, &actor->catch_tell("You lean back on the rope. It "
        + "seems sound enough to hold your weight.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Trusting your life to your "
        + "judgement of rope-quality, you leap into the open air!\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("You swing through the darkness "
        + "and let go when you think the rope is at its highest arc.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " takes the rope and "
        + "leans back on it.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "Grasping the rope, " 
        + QCTNAME(actor) + " leaps into the open air!\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " swings away into the darkness.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}

int
move_stones()
{
    object actor = TP;

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You bend down and begin moving "
        + "aside the heavy stones.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("Ouch! Was that your back making "
        + "that horrible cracking noise?\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("You push enough stones aside to "
        + "forge a small path through the rubble. As you pass through, "
        + "however, most of the stones roll back into place.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " bends down and starts "
        + "moving aside the heavy stones.\n", actor);
    set_alarm(2.0, 0.0, &tell_room(environment(actor), "Crack! You hear "
        + "the sound a back makes when it has been strained beyond "
        + "wisdom.\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) 
        + " pushes enough stones aside to forge a small path through the "
        + "rubble. As " + PRONOUN(actor) + " moves past, however, most "
        + "of the stones roll back into place.\n", actor));

    set_alarm(5.0, 0.0, &finish_moving(actor));

    return 1;
}

/* Move player to next room */
int
exit_room()
{
    object actor = TP;

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    switch (gVehicle)
    {
    case "stairs":
        crawl_stairs();
        set_alarm(6.0, 0.0, &move_ranger(actor));
        return 1;

    case "chasm":
        leap_chasm();
        set_alarm(6.0, 0.0, &move_ranger(actor));
        return 1;

    case "rope":
        swing_rope();
        set_alarm(6.0, 0.0, &move_ranger(actor));
        return 1;

    case "stones":
        move_stones();
        set_alarm(6.0, 0.0, &move_ranger(actor));
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please make "
            + "a bug report.\n");
        return 1;
    }
}


/* Error check fuction - masked in room files */

int
move_ranger(object who)
{
    write("This should not happen. Please make a bug report.\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    string name;
    object entrance;

    ::enter_inv(ob, from);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      (SECURITY->query_wiz_dom(name) == "Shire" &&
       SECURITY->query_wiz_rank(name) >= WIZ_STEWARD) ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;


    (RANGERS_NOR_DIR + "stairs.c")->teleledningsanka();
    entrance = find_object(RANGERS_NOR_DIR + "stairs.c");
    if (entrance->query_allowed(name))
        return;

    clone_object(RANGERS_OBJ + "tracker")->move(ob, 1);
    return;
}

void
leave_inv(object ob, object to)
{
    string name;
    object tracker, entrance;

    ::leave_inv(ob, to);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      (SECURITY->query_wiz_dom(name) == "Shire" &&
       SECURITY->query_wiz_rank(name) >= WIZ_STEWARD) ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;

    (RANGERS_NOR_DIR + "stairs.c")->teleledningsanka();
    entrance = find_object(RANGERS_NOR_DIR + "stairs.c");
    if (entrance->query_allowed(name))
        return;

    tracker = present("_ranger_tracker", ob);
    if (objectp(tracker))
        tracker->remove_object();
}

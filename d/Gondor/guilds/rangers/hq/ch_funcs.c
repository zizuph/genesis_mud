/*
 *  /d/Gondor/guilds/rangers/hq/ch_funcs.c
 *
 *  Various functions for Central Headquarters rooms
 *
 *  Coded by Alto, 20 June 2001
 *  Modifications:
 *  - Tigerlily, 02 January 2004, replaced write in 
 *        set_alarms with catch_tell, updated references
 *        to multiple this_player() calls in functions
 *        called by alarms
 *  - Gwyneth, 03 May 2004 - Added comments, neatened, improved efficiency
 *  - Petros, 18 May 2011 - fixed enter_inv so that it does what it says, and not track arches
 *
 */
inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* Global variables */

string             *handle    =({});
string             *extradesc =({});
string             Exline, Vehicle;
object             actor;
static object      Tstand;

#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"

/* Prototypes */

public string      vantage_extraline();
public int         vantage_add_cmds();
public int         grasp_vine(object tp);
public int         leap_branch(object tp);
public int         clamber_bark(object tp);
public int         swing_rope(object tp);
public int         ascend_ladder(object tp);
public int         exit_room();
public int         move_ranger(object tp);
public void        vantage_add_items();
public void        hideout_add_items();
public int         daylight();
public void        hideout_add_torch();

/* 
 * Function name: vantage_extraline
 * Description  : Generates a random extraline and movement item
 *                which it then sets to global variables Vehicle and Exline.
 * Returns      : string Exline - one of: vine, branch, bark, rope or ladder
 */
string
vantage_extraline()
{
    int position;

    string *extradesc =
/*1*/   ({"Just out of reach, you spy a rather slippery looking vine. "
           + "Perhaps you can grasp it.", 
/*2*/     "There is a sturdy-looking branch above you. "
           + "It might be possible to leap to it.", 
/*3*/     "The bark on the tree looks especially coarse here. "
           + "A skilled climber might clamber up it.",
/*4*/     "There is a frayed rope tied to the branches beside "
           + "you. It might be possible to swing to another part of the "
           + "tree.",
/*5*/     "Someone has tied a slim rope-ladder here. It looks "
           + "rather old and frayed, but if you are brave you may be "
           + "able to ascend it."});


    string *handle =
/*1*/     ({"vine", 
/*2*/       "branch", 
/*3*/       "bark",
/*4*/       "rope",
/*5*/       "ladder"});


    position = (random(100)/20);
    Exline = extradesc[position];
    Vehicle = handle[position];

    return Vehicle;
}


/* 
 * Function name: vantage_add_cmds
 * Description  : Add commands for respective movement item
 * Returns      : 1
 */
int
vantage_add_cmds()
{
    switch (Vehicle)
    {
    case "vine":
        add_cmd_item(({"vine", "the vine", "slippery vine", "the slippery vine",
            "slippery looking vine", "the slippery looking vine"}), "grasp",
            &exit_room());
        add_item(({"vine", "the vine", "slippery vine", "the slippery vine",
            "slippery looking vine", "the slippery looking vine"}), "A dark "
            + "green vine hangs just within your reach. It glistens slightly, "
            + "giving it a somewhat slippery appearance. It might not be such "
            + "a wise idea to rest your weight on it.\n");
        return 1;

    case "branch":
        add_cmd_item(({"branch", "to branch", "to the branch", 
            "to the sturdy-looking branch"}), "leap", &exit_room());
        add_item(({"branch", "sturdy-looking branch"}), "Several feet "
            + "above your head is a thick branch that looks like it would "
            + "hold your weight.\n");
        return 1;

    case "bark":
        add_cmd_item(({"bark", "up bark", "up the bark"}), "clamber",
            &exit_room());
        add_item(({"bark", "bark on tree"}), "The bark here is peeling "
            + "off the tree in large strips. You get the impression that "
            + "it would provide a great deal of traction against your "
            + "clothing.\n");
        return 1;

    case "rope":
        add_cmd_item(({"rope", "the rope", "on rope", "on the rope"}),
            "swing", &exit_room());
        add_item(({"rope", "the rope", "frayed rope"}), "This rope looks "
            + "like it was tied here ages ago! It is tied somewhere high "
            + "above you and dangles just within reach. Parts of it look "
            + "a little thin and frayed.\n");
        return 1;

    case "ladder":
        add_cmd_item(({"ladder","the ladder","rope-ladder","the rope-ladder"}),
            "ascend", &exit_room());
        add_item(({"ladder", "the ladder", "rope-ladder", "the rope-ladder"}),
            "The thin rope-ladder is mounted somewhere out of sight above "
            + "you. It looks very old and worn.\n");
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please file "
        + "a bug report.\n");
        return 1;
    }
}


/* 
 * Function name: long_desc
 * Description  : Set long description of room with extraline from above
 * Returns      : string - the description
 */
string
long_desc()
{
    string extra;

    extra = Exline;

    return "You are climbing among the trees somewhere in the Druedain "
        + "forest in Anorien. A slight breeze whispers through the leaves "
        + "and you can feel the weight of the forest shifting about you. "
        + extra + "\n";
}


/*
 * Function name: vantage_add_items
 * Description  : Additional items common to all vantage rooms, added
 *                to a room's create function.
 */
void
vantage_add_items()
{
    add_item(({"trees", "druedain", "druedain forest", "tree", "forest"}), 
        "The trees of the Druedain are tall, dense and ancient. The smell of "
        + "leaves is thick in the air.\n");
    add_item(({"leaves", "leaf", "branches"}), "There are so many leaves "
        + "that it is "
        + "difficult to see through them.\n");
    add_item(({"sky", "ground"}), "It is difficult to see through the "
        + "dense leaves.\n");
}


/*
 * Function name: finish_moving
 * Description  : Removes the prop that keeps track of whether or not
 *                a player is moving.
 * Arguments    : object tp - the moving player
 * Returns      : 1 always
 */
int
finish_moving(object tp)
{
    tp->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}

/*
 * Function name: grasp_vine
 * Description  : Gives the moving player messages as they move.
 * Arguments    : object tp - the moving player
 * Returns      : 1
 */
int
grasp_vine(object tp)
{
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("As your hands close upon " +
        "the vine, you notice that it is rather slippery.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("Your hands begin to " +
        "slip!\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("As your grip on the " +
        "vine continues to slip, you look down and notice how " +
        "perilously high above the ground you are.\n\n"));
    set_alarm(10.0, 0.0, &tp->catch_tell("You begin to slide a " +
        "little faster when you notice that you are running out " +
        "of vine to cling to!\n\n"));
    set_alarm(15.0, 0.0, &tp->catch_tell("You struggle frantically to wrap "
        + "your legs about the slippery vine. You cannot seem to find enough "
        + "purchase to slow your descent!\n\n"));
    set_alarm(20.0, 0.0, &tp->catch_tell("At the last moment, you manage to "
        + "loop the vine about your left leg. Inch by inch you begin to pull "
        + "yourself up the vine.\n\n"));

    tell_room(environment(tp), QCTNAME(tp) + " grabs the vine and "
        + "immediately begins sliding downward!\n", tp);
    set_alarm(10.0, 0.0, &tell_room(environment(tp), QCTNAME(tp) +
        " continues to slip and slide down the vine!\n", tp));
    set_alarm(20.0, 0.0, &tell_room(environment(tp), "At the last moment, "
        + QCTNAME(tp) + " manages to loop the vine about "
        + tp->query_possessive() + " left leg and crawl inch by "
        + "inch back up the vine.\n", tp));

    set_alarm(20.0, 0.0, &finish_moving(tp));

    return 1;
}

/*
 * Function name: leap_branch
 * Description  : Gives the moving player messages as they move.
 * Arguments    : object tp - the moving player
 * Returns      : 1
 */
int
leap_branch(object tp)
{
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("Throwing caution to the " +
        "wind, you leap for the sturdy-looking branch.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("Leaves and twigs batter " +
        "your face and arms as you soar through the air.\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("As your hands close " +
        "about the sturdy-looking branch, you confidently shift " +
        "your weight and swing your body through a wide arc.\n\n"));
    set_alarm(10.0, 0.0, &tp->catch_tell("You tuck your legs up " +
        "to your chest and somersault through several tight backward " +
        "spins.\n\n"));
    set_alarm(12.0, 0.0, &tp->catch_tell("Your feet land squarely on the "
        + "sturdy-looking branch!\n\n"));

    tell_room(environment(tp), QCTNAME(tp) + " leaps for the "
        + "sturdy-looking branch.\n", tp);
    set_alarm(5.0, 0.0, &tell_room(environment(tp), QCTNAME(tp) +
        " grasps the branch in both hands and swings beneath it through "
        + "a wide arc.\n", tp));
    set_alarm(12.0, 0.0, &tell_room(environment(tp), QCTNAME(tp) + 
        " somersaults through several tight backward spins, after which "
        + tp->query_possessive() + " feet land squarely on the "
        + "sturdy-looking branch!\n", tp));

    set_alarm(12.0, 0.0, &finish_moving(tp));

    return 1;
}


/*
 * Function name: clamber_bark
 * Description  : Gives the moving player messages as they move.
 * Arguments    : object tp - the moving player
 * Returns      : 1
 */
int
clamber_bark(object tp)
{

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);
    set_alarm(0.0, 0.0, &tp->catch_tell("You wrap your arms and legs "
        + "tightly about the rough bark.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("With the confidence of those "
        + "familiar with trees, you clamber upward.\n\n"));
    tell_room(environment(tp), QCTNAME(tp) + " clambers upward, "
        + "clinging to the rough bark.\n", tp);
    set_alarm(2.0, 0.0, &finish_moving(tp));
    return 1;
}

/*
 * Function name: swing_rope
 * Description  : Gives the moving player messages as they move.
 * Arguments    : object tp - the moving player
 * Returns      : 1
 */

int
swing_rope(object tp)
{

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("You give the rope a good "
        + "tug. It seems to hold.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("Getting a good grip on "
        + "the rope, you lean back until it stretches tight and then "
        + "leap into the open air.\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("Wind streams through your "
        + "hair as you swing through a wide curve.\n\n"));
    set_alarm(10.0, 0.0, &tp->catch_tell("At the last moment, "
        + "you release the rope and land lightly upon a higher "
        + "branch.\n\n"));

    tell_room(environment(tp), QCTNAME(tp) + " grabs the rope and "
        + "leaps into the open air!\n", tp);
    set_alarm(5.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " swings on the rope through a wide curve.\n", tp));
    set_alarm(10.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " releases the rope at the last moment and lands lightly upon "
        + "a higher branch.\n", tp));
    set_alarm(10.0, 0.0, &finish_moving(tp));

    return 1;
}


/*
 * Function name: ascend_ladder
 * Description  : Gives the moving player messages as they move.
 * Arguments    : object tp - the moving player
 * Returns      : 1
 */
int
ascend_ladder(object tp)
{
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("You begin to ascend the "
        + "rungs of the rope-ladder. In retrospect, you are not so "
        + "sure this was a good idea.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("Your foot rips completely "
        + "through one of the rungs!\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("As you dangle from your "
        + "hands, you look down and notice there is nothing between "
        + "you and the ground far below.\n\n"));
    set_alarm(10.0, 0.0, &tp->catch_tell("Using only your arms, "
        + "you pull yourself further up the rope-ladder.\n\n"));
    set_alarm(12.0, 0.0, &tp->catch_tell("With relief you clamber "
        + "onto a higher branch!\n\n"));

    tell_room(environment(tp), QCTNAME(tp) + " attempts to climb "
        + "the rope-ladder.\n", tp);
    set_alarm(2.0, 0.0, &tell_room(environment(tp), QCTNAME(tp)
        + " rests "
        + tp->query_possessive() + " weight on the first rung and "
        + tp->query_possessive() + " foot rips completely through it!\n", tp));
    set_alarm(10.0, 0.0, &tell_room(environment(tp), "Using only "
        + tp->query_possessive() + " arms, " + QCTNAME(tp) +
        " climbs up the tattered rope-ladder.\n", tp));

    set_alarm(12.0, 0.0, &finish_moving(tp));
    return 1;
}

/* 
 * Function name: exit_room
 * Description  : Moves the player to the next room
 * Returns      : 1/0 success/failure
 */
int
exit_room()
{
    object tp = this_player();

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    switch (Vehicle)
    {
    case "vine":
        grasp_vine(tp);
        set_alarm(21.0, 0.0, &move_ranger(tp));        
        return 1;

    case "branch":
        leap_branch(tp);
        set_alarm(13.0, 0.0, &move_ranger(tp));        
        return 1;

    case "bark":
        clamber_bark(tp);
        set_alarm(3.0, 0.0, &move_ranger(tp));        
        return 1;

    case "rope":
        swing_rope(tp);
        set_alarm(11.0, 0.0, &move_ranger(tp));        
        return 1;

    case "ladder":
        ascend_ladder(tp);
        set_alarm(13.0, 0.0, &move_ranger(tp));        
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please make "
            + "a bug report.\n");
        return 1;
    }
}


/* 
 * Function name: move_ranger
 * Description  : Error check fuction - masked in room files
 * Arguments    : object tp - the player moving
 */
int
move_ranger(object tp)
{
    tp->catch_tell("This should not happen. Please make a bug report.\n");
    return 0;
}

void
hideout_add_items()
{
    add_item(({"floor", "wooden floor", "ground"}), "The floor here "
        + "is made from long sturdy planks of wood. Near the walls you "
        + "can still make out the lustrous varnish that once made this floor "
        + "shine like a mirror. In most places, however, the finish has "
        + "long been worn away by the passage of generations of booted "
        + "feet.\n");
    add_item(({"varnish", "finish", "stain"}), "The floor was once finished "
        + "with a deep red stain, protected by clear resin buffed to a shine. "
        + "Only those places out of the way of booted feet, however, have "
        + "survived the ages unscathed.\n");
    add_item(({"planks", "sturdy planks"}), "The floor is made up of long "
        + "planks of oak, milled from the trees of the Druedain forest.\n");
    add_item(({"wall", "walls", "panel", "panels", "oak panel", "oak panels"}), 
        "The walls, like most things in the "
        + "hideout, are constructed from wood. You feel a warm glow in this "
        + "place, rather unlike the cold stone rooms and dwellings in "
        + "so-called civilized regions.\n");
    add_item(({"ceiling"}), "The ceilings of the hideout arch above you, "
        + "supported by massive crossbeams.\n");
    add_item(({"crossbeams", "massive crossbeams", "beams", "beam", 
        "oak beams"}), "The crafting of the "
        + "ceiling must have required amazing labour and skill. The beams "
        + "supporting it look to be made of entire sections of tree.\n");
    add_item(({"hideout", "central headquarters", "headquarters"}), "It "
        + "is all around you. To take in the entire building, you would need "
        + "to step outside. Even then, much of it would be hidden from "
        + "casual view.\n");
    add_item(({"wood"}), "Almost everything in the hideout seems to be made "
        + "of sturdy hardwoods milled from the Druedain forest by the "
        + "men of Gondor.\n");
}

void
hideout_add_torch()
{
    object *inv;

    inv = all_inventory(this_object());

    if (!sizeof(filter(inv, &->id("torchstand"))))
    {
        Tstand = clone_object(OBJ_DIR + "torchstand");
        Tstand->set_time(1999);
        Tstand->set_lit(1);
        Tstand->set_replace_msg("An apprentice ranger slips quietly into "
            + "the room and places a new torch in the iron stand. After "
            + "lighting the new torch, the apprentice bustles away and "
            + "disappears around a corner.\n");
        Tstand->set_no_desc(1);
        Tstand->remove_prop(CONT_I_ATTACH, 1);
        Tstand->move(TO);
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

/*
 * Function name: enter_inv
 * Description  : Masks enter_inv to check on the validity of a wizard's
 *                entrance. Only Gondorians or arches are allowed without
 *                tracking. Clones a tracking device.
 * Arguments    : object ob - the object entering the room
 *                object from - the object that ob came from
 */
void
enter_inv(object ob, object from)
{
    string name;

    ::enter_inv(ob, from);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
       (SECURITY->query_wiz_dom(name) == "Shire" &&
       SECURITY->query_wiz_rank(name) >= WIZ_STEWARD) ||
       SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;

    clone_object(RANGERS_OBJ + "tracker")->move(ob, 1);
    return;
}

/*
 * Function name: leave_inv
 * Description  : Masked to remove tracking device from a non-authorized
 *                wizard or log if it is not present (destructed).
 * Arguments    : object ob - the object leaving the room
 *                object to - the destination of ob
 */
void
leave_inv(object ob, object to)
{
    string name;
    object tracker;

    ::leave_inv(ob, to);

    if (!living(ob) || !ob->query_wiz_level())
        return;

    name = ob->query_real_name();
    if (SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return;

    tracker = present("_ranger_tracker", ob);
    if (objectp(tracker))
        tracker->remove_object();
    else
        log_file("intruder", extract(ctime(time()), 4) + " in " +
            file_name(ENV(ob)) + " " + CAP(ob->query_real_name())
            + " failed to have tracker cloned.\nPresent: "
            + COMPOSITE_LIVE(all_inventory(ENV(ob))) + ".\n");
}

/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_funcs.c
 *
 *  Various functions for Ranger ambush spots
 *
 *  Coded by Alto, 02 August 2001
 *
 *  Typo fix by Toby, 25 Sept 2006 (throns = thorns)
 */
inherit "/d/Gondor/std/room.c";

#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define AMBUSH_I_MOVE       "_ambush_i_move"

/* Global variables */
string             *Handle    =({}), *Extradesc =({});
string             Exline, Vehicle, Msg1, Msg2, Msg3, RmMsg1, RmMsg2, Room;

/* Prototypes */
public string ambush_extraline();
public int    ambush_add_cmds();
public int    exit_room();
public int    move_ranger(object actor);
public int    check_amb_move();

string
ambush_extraline()
{
    int position;

    string *Extradesc =
/*1*/   ({"The path here is choked with vines and tree limbs. Just when "
               + "you begin to think about retracing your steps, you notice "
               + "a small ditch you could crawl through.", 
/*2*/     "There is a rather deep gully before you. Leaning over the gully "
               + "is a large oak tree with many sturdy-looking branches. "
               + "It might be possible to cross the gully by jumping to "
               + "a branch.", 
/*3*/     "The path ends at a small cliff face. Someone has tied a rope "
               + "from above.",
/*4*/     "A small stream flows across the path. It looks rather deep, which "
               + "is probably why someone put a bridge here for you to "
               + "cross.",
/*5*/     "A small stream flows across the path. It looks rather deep, which "
               + "is probably why someone tied a vine to the branches of "
               + "a large tree on the near bank.",
/*6*/     "The path ends at a small cliff face. Fortunately, there is a "
               + "ladder leaning against it.",
/*7*/     "A small stream flows across the path.",
/*8*/     "The path here is choked with bushes."});


    string *Handle =
/*1*/     ({"ditch", 
/*2*/       "branch", 
/*3*/       "rope",
/*4*/       "bridge",
/*5*/       "vine",
/*6*/       "ladder",
/*7*/       "stream",
/*8*/       "bushes"});


    position = random(159) / 20;
    Exline = Extradesc[position];
    Vehicle = Handle[position];
    return Vehicle;
}


/* 
 * Function name: ambush_add_cmds
 * Description  : Add commands for respective movement item
 * Returns      : 1
 */
int
ambush_add_cmds()
{
    switch (Vehicle)
    {
    case "ditch":
        add_cmd_item(({"ditch", "through ditch", "through the ditch"}), 
            "crawl", &exit_room());
        add_item(({"vines", "limbs", "tree limbs"}), "The path appears "
            + "to be completely blocked with hanging vines and tree limbs.\n");
        add_item(({"ditch", "small ditch"}), "You may be able to crawl through "
            + "it to get through the vines and limbs. It looks muddy.\n");
        return 1;

    case "branch":
        add_cmd_item(({"branch", "to branch", "to the branch"}), 
            "jump", &exit_room());
        add_item(({"gully", "large gully"}), "A deep gully opens in the "
            + "path before you. Looking over the edge, you realize a fall "
            + "would most likely kill you.\n");
        add_item(({"tree", "trees", "oak tree", "large tree",
            "large oak tree"}), "Near the edge of the gully grows one of "
            + "the largest oak trees you have ever seen. Many of its branches "
            + "hang over the gully, some reaching even to the other side.\n");
        add_item(({"branch", "branches"}), "One of the branches looks like "
            + "it would bear your weight if you jumped to it.\n");
        return 1;

    case "rope":
        check_amb_move();
        add_cmd_item(({"rope", "the rope"}), "climb", &exit_room());
        add_item(({"cliff", "face", "cliff face"}), "The path ends at the "
            + "bottom of a tall cliff face. It rises far above you and "
            + "appears to have no reliable niches for climbing.\n");
        add_item(({"rope"}), "It looks sturdy enough. It appears to be "
            + "tied somewhere above and dangles down the cliff face.\n");
        return 1;

    case "bridge":
        add_cmd_item(({"bridge", "the bridge"}), "cross", &exit_room());
        add_item(({"stream", "small stream"}), "A babbling stream flows "
            + "rapidly across the path here. It looks deep and "
            + "dangerous.\n");
        add_item(({"bridge"}), "A swinging bridge is suspended over the "
            + "stream. It looks rather temporary and not at all designed "
            + "for long-term use.\n");
        return 1;

    case "vine":
        add_cmd_item(({"vine", "the vine", "on the vine", "across stream",
            "across the stream", "on vine"}), "swing", &exit_room());
        add_item(({"stream", "small stream"}), "A babbling stream flows "
            + "rapidly across the path here. It looks deep and "
            + "dangerous.\n");
        add_item(({"vine"}), "A long brown vine has been tied to some "
            + "of the branches reaching over the stream. Perhaps you can "
            + "swing across the stream on it.\n");
        add_item(({"tree", "trees", "large tree"}), "Near the "
            + "edge of the stream grows an "
            + "especially large tree. Many of its branches "
            + "hang over the stream, but none of them reach the other "
            + "side.\n");
        add_item(({"branch", "branches"}), "One of the branches has "
            + "a vine tied to it.\n");
        add_item(({"bank", "near bank"}), "It is where you are standing "
            + "at the moment, trying to figure out a way across the "
            + "stream.\n");
        return 1;

    case "ladder":
        add_cmd_item(({"ladder", "the ladder", "on the ladder"}),
            "climb", &exit_room());
        add_item(({"cliff", "face", "cliff face"}), "The path ends at the "
            + "bottom of a tall cliff face. It rises far above you and "
            + "appears to have no reliable niches for climbing.\n");
        add_item(({"ladder"}), "It looks sturdy enough.\n");
        return 1;

    case "stream":
        add_cmd_item(({"stream", "across stream", "the stream", 
            "across the stream"}),
            "swim", &exit_room());
        add_item(({"stream", "small stream"}), "A babbling stream flows "
            + "rapidly across the path here. It looks deep and "
            + "dangerous. Nonetheless, if you wish to pass it, you "
            + "will have to swim across it.\n");
        return 1;

    case "bushes":
        add_cmd_item(({"bushes", "the bushes", "bush", "the bush", "gap",
            "small gap", "the small gap"}),
            "enter", &exit_room());
        add_item(({"bush", "bushes", "brambles", "thorns"}), "Brambles, "
            + "thorns and bushes seem to completely block the path here. "
            + "On closer examination, however, you see a small gap in "
            + "some of the bushes that may be entered.\n");
        add_item(({"gap", "small gap"}), "There still seem to be plenty "
            + "of sharp thorns in the small gap, but perhaps you can get "
            + "through without losing too much blood.\n");
        add_item(({"thorn", "thorns"}), "They look very sharp.\n");
        return 1;

    default:
        write("The ambush point appears to be unreachable. Please file "
        + "a bug report.\n");
        return 1;
    }
}

/*
 * Function name:
 * Description  : Set long description of room with extraline from above
 * Returns      : string - long description
 */
string
long_desc()
{
    return "You are somewhere near the road, following a path that would "
        + "be hidden to eyes less skilled than your own. " + Exline + "\n";
}

/* 
 * Function name: ambush_add_items
 * Description  : Additional items common to all ambush rooms
 */
void
ambush_add_items()
{
    add_item(({"road"}), "It cannot be seen from here, but you have "
        + "not travelled far from it.\n");
    add_item(({"path"}), "The path here is almost completely hidden. "
        + "Only your experience with secret marks and tracking allows "
        + "you to follow it.\n");
}

void
two_alarm_move(object actor)
{
    actor->add_prop(AMBUSH_I_MOVE, 1);

    set_alarm(0.1, 0.0, &actor->catch_tell(Msg1));
    set_alarm(2.0, 0.0, &actor->catch_tell(Msg2));

    set_alarm(0.1, 0.0, &tell_room(environment(actor), RmMsg1, actor));
    set_alarm(2.0, 0.0, &tell_room(environment(actor), RmMsg2, actor));

    set_alarm(2.0, 0.0, &actor->remove_prop(AMBUSH_I_MOVE));
    set_alarm(3.0, 0.0, &move_ranger(actor));        
}

void
three_alarm_move(object actor)
{
    actor->add_prop(AMBUSH_I_MOVE, 1);

    set_alarm(0.1, 0.0, &actor->catch_tell(Msg1));
    set_alarm(2.0, 0.0, &actor->catch_tell(Msg2));
    set_alarm(5.0, 0.0, &actor->catch_tell(Msg3));

    set_alarm(0.1, 0.0, &tell_room(environment(actor), RmMsg1, actor));
    set_alarm(2.0, 0.0, &tell_room(environment(actor), RmMsg2, actor));

    set_alarm(5.0, 0.0, &actor->remove_prop(AMBUSH_I_MOVE));
    set_alarm(6.0, 0.0, &move_ranger(actor));        
}

/* Move player to next room */

int
exit_room()
{
    object actor = TP;

    if (actor->query_prop(AMBUSH_I_MOVE))
    {
        actor->catch_tell("You are already moving!\n");
        return 1;
    }

    switch (Vehicle)
    {
    case "ditch":
        Msg1 = "You bend down on all fours and begin to crawl through the "
            + "ditch.\n\n";
        Msg2 = "Yuck. Now you are all muddy.\n\n";
        Msg3 = "Dripping with mud, you emerge from the far end of the "
            + "ditch.\n\n";
        RmMsg1 = QCTNAME(actor) + " bends down on all fours and begins "
            + "to crawl through the ditch.\n";
        RmMsg2 = "Yuck. " + QCTNAME(actor) + " gets covered in mud.\n";
        three_alarm_move(actor);
        return 1;

    case "branch":
        Msg1 = "You back up and run toward the stream.\n\n";
        Msg2 = "Just before you reach the edge of the stream, you leap "
            + "for the branch.\n\n";
        Msg3 = "You manage to reach the branch! After swinging back and "
            + "forth a few times, you jump to the far bank.\n\n";
        RmMsg1 = QCTNAME(actor) + " backs up and runs toward the stream, "
            + "leaping for a branch overhanging the stream just before "
            + actor->query_pronoun() + " reaches the near bank.\n";
        RmMsg2 = QCTNAME(actor) + " reaches the branch and swings to the "
            + "far bank.\n";
        three_alarm_move(actor);
        return 1;

    case "rope":
        Msg1 = "You give the rope a good tug. It seems sturdy enough.\n\n";
        Msg2 = "You skillfully climb up the face of the cliff.\n\n";
        RmMsg1 = QCTNAME(actor) + " gives the rope a good tug.\n";
        RmMsg2 = QCTNAME(actor) + " skillfully climbs up the face of the "
            + "cliff.\n";
        two_alarm_move(actor);
        return 1;

    case "bridge":
        Msg1 = "You step out onto the swinging bridge, which gives and "
            + "bounces beneath your weight.\n\n";
        Msg2 = "As you move across the bridge, the swinging and bouncing "
            + "becomes more pronounced. You begin to worry that you might "
            + "be thrown off into the water!\n\n";
        Msg3 = "With a sigh of relief you reach the far bank of the "
            + "stream.\n\n";
        RmMsg1 = QCTNAME(actor) + " steps out onto the swinging bridge, "
            + "which gives and bounces beneath " + actor->query_possessive()
            + " weight.\n";
        RmMsg2 = "After much bouncing and swinging, " + QCTNAME(actor)
            + " reaches the far end of the bridge.\n";
        three_alarm_move(actor);
        return 1;

    case "vine":
        Msg1 = "You give the vine a good tug. It seems sturdy enough.\n\n";
        Msg2 = "With a prayer for luck, you lean back on the vine and "
            + "swing across the stream!\n\n";
        RmMsg1 = QCTNAME(actor) + " gives the vine a good tug.\n";
        RmMsg2 = QCTNAME(actor) + " leans back on the vine and swings "
            + "across the stream!\n";
        two_alarm_move(actor);
        return 1;

    case "ladder":
        Msg1 = "You step up onto the first rung of the ladder. There are "
            + "many more above you.\n\n";
        Msg2 = "You quickly climb up the face of the cliff.\n\n";
        RmMsg1 = QCTNAME(actor) + " steps up onto the first rung of the "
            + "ladder and begins to climb.\n";
        RmMsg2 = QCTNAME(actor) + " quickly climbs up the face of the cliff.\n";
        two_alarm_move(actor);
        return 1;

    case "stream":
        Msg1 = "You look nervously at the deep and rushing water. Taking "
            + "a deep breath, you leap from the bank and plunge into the "
            + "icy stream!\n\n";
        Msg2 = "The current sucks you under!\n\n";
        Msg3 = "Swimming with all your might, you finally manage to reach "
            + "the far bank.\n\n";
        RmMsg1 = QCTNAME(actor) + " looks nervously at the deep and rushing "
            + "water. Taking a deep breath, " + PRONOUN(actor) + " leaps from "
            + "the bank and plunges into the stream!\n";
        RmMsg2 = "After disappearing beneath the surface of the water "
            + "several times, " + QCTNAME(actor) + " finally manages to "
            + "reach the far bank.\n";
        three_alarm_move(actor);
        return 1;

    case "bushes":
        Msg1 = "You tentatively push aside some of the brambles. Ouch! "
            + "A thorn!\n\n";
        Msg2 = "With a few scrapes and cuts to show for it, you manage "
            + "to push your way through the bushes.\n\n";
        RmMsg1 = QCTNAME(actor) + " pushes aside some of the brambles and "
            + "manages to cut " + actor->query_possessive()
            + " finger on some thorns.\n";
        RmMsg2 = QCTNAME(actor) + " manages to push "
            + actor->query_possessive() + " way through the bushes.\n";
        two_alarm_move(actor);
        return 1;

    default:
        write("The vantage point appears to be unreachable. Please make "
            + "a bug report.\n");
        return 1;
    }
}


void
set_ambush_move(string room)
{
    Room = room;
}

int
move_ranger(object actor)
{
    say(QCTNAME(TP) + " moves down the path and disappears from sight.\n");
    tell_room(Room, QCTNAME(TP) + " arrives from behind you.\n");

    actor->move_living("M", Room, 1, 0);
    return 1;
}

int
check_amb_move()
{
    if (TP->query_prop(AMBUSH_I_MOVE))
    {
        write("You are busy navigating the path - concentrate on what "
              + "you are doing!\n");
        return 1;
    }

    return 0;
}


int
query_prevent_snoop()
{
    // for purposes of preventing scry
    return 1;
}


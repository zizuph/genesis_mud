/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge11.c
 *
 *  This is the northernmost reach of the ledge which extends along
 *  the western cliff faces which border Del Rimmon in the Blackwall
 *  Mountains. A tree grows at the edge of the precipice, laden
 *  with acorns for those who care. A crack below the tree roots
 *  makes its way into a hidden area behind the cliff walls. A portal
 *  here leads into what was once an outpost manned by the Elves of
 *  Telberin. Due to the recent eartquake, it has been damaged to the
 *  point of being unable to open.
 *
 *  Copyright (c) March 1999, by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeside/cliffs/ledge_master.c";
inherit "/d/Emerald/blackwall/delrimmon/lib/corporeal_flux";


#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* definitions */
#define  REQUIRED_SKILL        15
#define  FOUND_ROOTS_CRACK     "_found_roots_crack"
#define  WHERE_TO   "/d/Emerald/blackwall/delrimmon/lakeside/nw_cliff6"

/* global variables */
public int     Acorns;    /* how many acorns on tree? */
public mixed   Rope = 0;  /* has a rope been tied to the tree? */

/* prototypes */
public void    create_ledge();
public void    leave_inv(object ob, object to);
public int     say_password(string arg);
public string  exa_roots();
public string  exa_crack();
public int     check_skills(object pl);
public int     enter_crack(string str);
public void    init();
public void    reset_room();
public string  exa_tree();
public string  exa_rope();
public mixed   exa_acorn();
public string  exa_branch();
public int     pick_acorn(string arg);
public int     tie_rope(string str);
public int     climb_rope(string arg);

/*
 * Function name: create_ledge
 * Description  : allows us to create the room with area presets
 */
void
create_ledge()
{
    add_name("_emerald_rope_tie");
    set_cliff_base(DELRIMMON_DIR + "lakeside/nw_cliff4");

    set_extraline("The ledge has come to an abrupt halt here at"
      + " the edge of a sheer precipice. The cliffs curve on in"
      + " a northeasterly direction, but not before a deep groove"
      + " in the rock face cuts dramatically to the west,"
      + " defining the edge of the sheer drop. At the edge of the ledge"
      + " a stone portal has been carved into the rock face here,"
      + " shaded somewhat by a tree which grows at the edge of the"
      + " precipice.");

    add_item( ({ "cracks", "large cracks" }), BSN(
        "These cracks run completely through the stone. Such damage"
      + " is often sustained due to earthquakes and other natural"
      + " phenomenon."));
    add_item( ({ "stone", "stone of the door",
                 "stone of the doors" }), BSN(
        "The stone of the doors does not appear to have been"
      + " carved from that of the cliff face."));
    add_item( ({ "face", "rock face", "face of the rock" }), BSN(
        "A portal has been carved into the rock face here, shaded"
      + " somewhat by a tree which grows at the edge of the"
      + " precipice."));
    add_item( ({ "portal", "stone portal" }), BSN(
        "The portal looks simple at a first glance, little more"
      + " than a rectangular depression in the rock face. However,"
      + " a cunning doorway lies embedded within this space."));
    add_item( ({ "door", "doorway", "cunning door", 
                 "cunning doorway", "doors", "slabs", "slab",
                 "slab-like door", "slab-like doors", "set",
                 "set of doors", "set of slab-like doors",
                 "space" }), BSN(
        "Resting within the portal in the rock face, a set of"
      + " slab-like doors stand silently in this high place. An"
      + " emblem has been carved into the stone on the door's surface."));
    add_item( ({ "precipice", "precipices", "drop", "sheer drop",
                 "edge", "edge of the precipice", "groove",
                 "deep groove" }), BSN(
        "The precipice is defined by the sudden shearing of the"
      + " cliff face in an almost fully westward direction. A tree"
      + " grows from the rock of the cliff above the lip of the"
      + " precipice."));
    add_item(({"lip","lips","lip of the precipice"}), BSN(
        "A dizzying drop beckons from the lip of the precipice,"
      + " where a tree grows from the rock of the cliff."));
    add_item( ({ "tree", "trees" }), exa_tree);
    add_item(({"trunk","trunks","tree trunk","tree trunks"}), BSN(
        "The trunk of this old tree is thick and gnarled. The roots"
      + " of the tree seem to dig deeply into the face of the"
      + " cliff, separating and dividing the rock like fingers"
      + " through sand."));
    add_item( ({"root", "roots"}), exa_roots);
    add_item( ({ "crack", "deep crack" }), exa_crack);
    add_item( ({ "acorn", "acorns" }), exa_acorn);
    add_item( ({ "branch", "branches" }), exa_branch);

    add_cmd_item( ({ "door", "doorway", "portal", "doors" }),
                  ({ "open", "pull" }),
        "The stone slabs do not bear any handhold or device by"
      + " which you might open them.\n");
    add_cmd_item( ({ "door", "doorway", "portal", "doors" }),
                  ({ "unlock" }),
        "You see no lock on the doorway of any kind.\n");
    add_cmd_item( ({ "door", "doorway", "portal", "doors" }),
                  ({ "push", "shove" }),
        "You strain mightily against the doors, but they do not"
      + " budge.\n");

    add_exit(DELRIMMON_DIR + "lakeside/cliffs/ledge10","southwest");

    set_no_exit_msg( ({ "north", "northeast" }),
        "The ledge ends to the north, where a tree grows along a"
      + " precipice before a sheer drop.\n");
    set_no_exit_msg( ({ "east", "southeast", "south" }),
        "The ledge ends in a sheer drop in that direction.\n");
    set_no_exit_msg( ({ "west", }),
        "The stone portal is sealed shut.\n");
    set_no_exit_msg( ({ "northwest" }),
        "The walls of the cliffs rise to meet you in that direction.\n");

    reset_room();
} /* create_ledge */


/*
 * Function name:        leave_inv
 * Description  :        Called when objects leave this container or
 *                       when an object is about to change its weight,
 *                       volume, or light status.
 * Arguments    :        ob: The object that just left this inventory
 *                       to: where it went
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->query_prop(TOUCH_PROP))
    {
        ob->catch_tell("You remove your hands from the stone doorway.\n");
        ob->remove_prop(TOUCH_PROP);
    }

    return;
} /* leave_inv */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       outpost doors
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to incant?");
    }
    
    string  txt = LOW(arg);   

    if (txt == MANAGER->query_password(this_player()) ||
        txt == MANAGER->query_password(this_player()) + "." ||
        txt == MANAGER->query_password(this_player()) + "!")
    {
        write("You incant: "
          + CAP(MANAGER->query_password(this_player())) + "!\n"
          + "The cracks of the doorway blink with dim blue"
          + " light, but nothing else happens.\n");
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* say_password */


/*
 * function name:        exa_roots
 * description  :        provide the player with a description of the
 *                       roots and add a prop to them to let us
 *                       know that they are now aware of the crack
 * returns      :        string -- the roots description 
 */
public string
exa_roots()
{
    TP->add_prop(FOUND_ROOTS_CRACK, 1);

    return BSN("It appears as though years of twisting and pushing"
      + " at the rock face have allowed the roots of this tree to"
      + " tunnel completely through the cliff face. A deep crack is"
      + " visible below the trunk, just underneath the lip of the"
      + " precipice.");
} /* exa_roots */

/*
 * function name:        exa_crack
 * description  :        we only want the player to be able to examine
 *                       the crack if they have noticed it already
 *                       by examining the roots of the tree.
 * returns      :        string -- the description, or a denial.
 */
public string
exa_crack()
{
    if (TP->query_prop(FOUND_ROOTS_CRACK))
    {
        return BSN("Below the lip of the precipice, and somewhat"
          + " obscured from view, a crack is visible. It looks to"
          + " have been formed at least partially by what must have"
          + " been a very powerful earthquake which rocked this region"
          + " recently. The roots of the tree have torn away the thin"
          + " outer layer of the cliff face which may have hidden"
          + " this crack from view otherwise. It looks wide enough to"
          + " enter, though it would probably be quite difficult to do"
          + " so.");
    }

    return BSN("You find no crack.");
} /* exa_crack */

/*
 * function name:        check_skills
 * description  :        a routine to check to see if the player is
 *                       skilled enough to climb into the crack.
 *                       called by enter_crack(string str)
 * arguments    :        pl -- the player object
 * returns      :        1 -- success, 0 -- failure
 */
public int
check_skills(object pl)
{
    int     player_skill = pl->query_skill(SS_ACROBAT)
                         + pl->query_skill(SS_CLIMB) / 5,
            difficulty   = REQUIRED_SKILL + random(10),
            difference   = player_skill - difficulty;

find_player("gorboth")->catch_msg(BSN("Difference: " + difference));
    if (difference <= 0)
        return 0;

    return 1;
} /* check_skills */

/*
 * function name:        enter_crack
 * description  :        allow the player to try to enter the crack
 *                       if they are not too tired. add a bit of
 *                       fatigue whether they pass the skill check
 *                       or not.
 * arguments    :        str -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
enter_crack(string str)
{
    object *others = FILTER_PLAYERS(all_inventory(TO));
    int     i;

    if (!strlen(str))
    {
        NFN0(CAP(QVB) + " where?");
    }

    if (!parse_command(str, ({}),
        "[in] [to] [into] [the] [deep] 'crack'"))
    {
        return 0;   /* parse_command failed, pass it to the mudlib */
    }

    if (!TP->query_prop(FOUND_ROOTS_CRACK))
    {
        WRITE("What?");
        return 1;
    }

    if (TP->query_fatigue() < 15)
    {
        WRITE("You are too tired to try that right now.");
        return 1;
    }

    if (!check_skills(TP))
    {
        TP->add_fatigue(-15 - random(15));
        WRITE("Balancing yourself as best as you can, you attempt to"
           + " work your way into the crack below the precipice. After"
           + " a brief struggle with the tree trunk, and a few close"
           + " calls with gravity, you decide to rest for a bit.");
        return 1;
    }

    while (i < sizeof(others))
    {
        others[i]->add_prop(FOUND_ROOTS_CRACK,1);
        i++;
    }

    write(BSN("Skillfully balancing yourself against the lip of the"
        + " precipice, you grasp the trunk of the tree, and"
        + " swing yourself safely into the crack"
        + " along the cliff face."));
    say(QCTNAME(TP) + " grips the trunk of a tree growing along the"
                    + " precipice, and swings down over the ledge to"
                    + " land in a crack inside the cliff walls.\n");
    TP->move_living("M",
                    DELRIMMON_DIR + "lakeside/cliffs/crack1", 1, 0);
    say(QCTNAME(TP) + " arrives, swinging into this crack from the"
                    + " ledge above the precipice.\n");

    return 1;
} /* enter_crack */

/*
 * function name:        init
 * description  :        add some verbs to the player
 */
public void
init()
{
    ::init();

    add_action(enter_crack, "climb");
    add_action(enter_crack, "enter");
    add_action(pick_acorn, "pick");
    add_action(pick_acorn, "get");
    add_action(pick_acorn, "take");
    add_action(say_password, "incant");
    add_action(do_touch, "touch");
    add_action(tie_rope, "tie");
    add_action(tie_rope, "untie");
    add_action(climb_rope, "climb");
} /* init */


/*
 * function name:    reset_room
 * description  :    set the value of Acorns to > 1 if it is 0
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem =
            clone_object(DELRIMMON_DIR 
                       + "obj/normal_emblem")->move(this_object());
    }

    if (!Acorns)
    {
        Acorns = 1 + random(4);
    }
} /* reset_room */


/*
 * function name:        exa_tree
 * description  :        provide a description of the tree, with
 *                       a variation if there are acorns growing
 *                       there.
 * returns      :        string -- the tree description
 */
public string
exa_tree()
{
    string  tree_txt = "Remarkably, this tree has somehow weathered"
                     + " the intense winds and rockslides which are"
                     + " common along these cliffs. Its twisted and"
                     + " gnarled trunk grows at an odd angle from the"
                     + " cliff face, where the edge of the precipice"
                     + " jogs westward. ";

    if (Acorns)
    {
        tree_txt += "A few acorns are growing on the tree.";
    }

    if (Rope)
    {
        tree_txt += " Someone has tied a rope to the tree, which"
                  + " dangles over the ledge.";
    }

    return BSN(tree_txt);
} /* exa_tree */


/* 
 * Function name:        exa_rope
 * Description  :        allow players to look at the rope, if one
 *                       has been tied to the ledge.
 * Returns      :        string - the desc for the add_item
 */
public string
exa_rope()
{
    if (!Rope)
    {
        return "You find no rope.\n";
    }

    return "A rope has been tied to the trunk of a tree here. It"
      + " dangles over the ledge, reaching down toward the base"
      + " of the cliffs.\n";
} /* exa_rope */


/*
 * function name:        exa_acorn
 * description  :        describe the acorns, if there are any
 * returns      :        string -- the acorn desc,
 *                       0 -- no acorns to see
 */
public mixed
exa_acorn()
{
    if (!Acorns)
    {
        return 0;
    }

    if (Acorns == 1)
    {
        return BSN("A single acorn clings stubbornly to the branches"
                 + " of the tree.");
    }

    return BSN("A few acorns cling stubbornly to the branches of the"
             + " tree. You count " + LANG_WNUM(Acorns) + " of them.");
} /* exa_acorn */


/*
 * function name:        exa_branch
 * description  :        provide a description of the tree branches
 * returns      :        string -- the description
 */
public string
exa_branch()
{
    if (!Acorns)
    {
        return "The branches of the tree are twisted and barren.\n";
    }

    return exa_acorn();
} /* exa_branch */


/*
 * function name:        pick_acorn
 * description  :        allow the player to try to pick an acorn
 *                       from the tree
 * arguments    :        string arg -- what the player typed
 * returns      :        1 -- success, 0 -- failure
 */
public int
pick_acorn(string arg)
{
    object  acorn;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] 'acorn' / 'acorns' [from] [the] [tree]"
      + " [branch] [branches]"))
    {
        return 0;
    }

    if (!Acorns)
    {
        NFN0("There are no acorns on the tree.");
    }

    WRITE("You carefully balance yourself against the tree trunk, and"
        + " pick an acorn from one of the branches.");
    say(QCTNAME(TP) + " carefully balances " + TP->query_objective()
      + "self against the trunk of the the tree, and picks an acorn"
      + " from one of the branches.\n");

    acorn = clone_object(DELRIMMON_DIR + "obj/acorn")->move(TP);
    Acorns--;

    return 1;
} /* pick_acorn */


/*
 * Function name: tie_rope
 * Description:   allow players to tie a rope to the 
 *                tree
 * Arguments:     str - what the player typed
 * Returns:       0 / 1 - failure / success
 */
public int
tie_rope(string str)
{
    mixed   fail;
    object  obj;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (query_verb() == "untie" || query_verb() == "get")
    {
        if (!parse_command(str, ({}),
            "[the] 'rope' [from] [the] [tree]") ||
            !Rope)
        {
            return 0; /* can't parse the syntax */
        }

        if (query_verb() == "get")
        {
            notify_fail("You would need to untie it first.\n");
            return 0;
        }

        this_player()->reveal_me(1);
        write("You untie the rope from the tree where it"
          + " falls to coil upon the ground.\n");
        tell_room(QCTNAME(this_player()) + " unties the"
          + " rope from the trunk of the tree.\n",
            this_player());

        Rope->move(this_object());
        Rope = 0;

        remove_item( ({ "rope", "ropes" }) );

        return 1;
    }        

    if (!(parse_command(str, all_inventory(this_player()),
        "%o 'to' [the] [trunk] [of] [the] 'trunk' / 'tree'", obj)))
    {
        // parse_command() failed
        notify_fail("What do you want to tie to what?\n");
        return 0;
    }

    // check properties! This is vitally important!
    if (fail = obj->query_prop(OBJ_M_NO_DROP))
    {
        if (!stringp(fail))
        {
            fail = "You cannot get rid of the "+obj->short()+"\n";
        }

        notify_fail(fail);
        return 0;
    }

    if (Rope)
    {
        write("There is already a rope tied to the tree.\n");
        return 1;
    }

    this_player()->reveal_me(1);
    write("You tie the "+obj->short()+" firmly to the trunk of the"
      + " tree. The end falls over the ledge to dangle down toward"
      + " the base of the cliff.\n");
    tell_room(this_object(), QCTNAME(this_player())+" ties "
      + LANG_ADDART(obj->short()) + " to the trunk of the tree.\n",
        this_player());

    Rope = obj;
    add_item( ({ "rope", "ropes" }), exa_rope);

    obj->move(DELRIMMON_DIR + "void");
    return 1;
} /* tie_rope */


/*
 * Function name:        climb_rope
 * Description  :        allow players to climb down the rope
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - succes, 0 - failure
 */
public int
climb_rope(string arg)
{
    if (!Rope)
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] 'rope'"))
    {
        return 0; /* can't parse the syntax */
    }

    write("Gripping tightly to the rope, you make your way carefully"
      + " down the side of the cliffs. Before long, the base of the"
      + " cliff has extended far enough away from the perimeter of"
      + " the precipice that you are able to repel down its sides."
      + " Eventually, you reach the end of the rope, and pause,"
      + " balancing against the rocky slope perhaps thirty feet"
      + " from the ground. Figuring yourself capable enough, you"
      + " release your grip on the rope and slide and stumble your"
      + " way to the bottom of the slope down a long cleft in the"
      + " rock. You dust yourself off and stand up.\n");
    tell_room(WHERE_TO, QCTNAME(this_player()) + " arrives,"
      + " sliding down a cleft in the cliff walls to land in"
      + " a dusty heap. Standing up, " + this_player()->query_pronoun()
      + " dusts " + this_player()->query_objective() + "self"
      + " off and peers painfully back up the slope.\n");
    this_player()->move_living("M", WHERE_TO, 1, 1);
    tell_room(this_object(), QCTNAME(this_player())
      + " grasps a rope tied to the tree and disappears climbing"
      + " down over the ledge.\n");

    return 1;
} /* climb_rope */

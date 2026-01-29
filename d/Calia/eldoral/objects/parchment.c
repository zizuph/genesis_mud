/* 
 * parchment 
 * 
 * This item is part of the 'sword in the stone' quest in 
 * eldoral, used with charcoal sticks to copy some patterns. 
 * 
 * Khail, Dec 6/96 
 * 
 * History: 
 *    6/96         Created                                     Khail 
 * 27/9/01         Made to query SWORD_BRAIN for valid locs    Maniac 
 */ 
#pragma strict_types

#include "defs.h"
#include <cmdparse.h>
#include <composite.h>

inherit "/std/object";

string *chimera_loc, *warrior_loc; 

string copy;
string type;
int *duplicates;

/*
 * Function name: query_mark_placement
 * Description  : Returns a list of all the available places
 *                for marks on the parchment, if a type has
 *                been set, depending on which type is set.
 * Arguments    : n/a
 * Returns      : A list of locations as a composite string.
 */
public string
query_mark_placement()
{
    if (!type || !strlen(type))
        return "";

    if (type == "chimera")
        return COMPOSITE_WORDS(chimera_loc);
    else
        return COMPOSITE_WORDS(warrior_loc);
}

/*
 * Function name: exa_marks
 * Description  : Generates a result for when players examine the
 *                marks on the parchment (if the marks exist).
 * Arguments    : n/a
 * Returns      : A string description of the marks on the sheet.
 */
public string
exa_marks()
{
    string str;
    string *temp1 = allocate(4),
           *temp2 = allocate(4);
    int i;

  /* No description if no type is set. */
    if (!type || !strlen(type))
        return "";

  /* If the player has compared, they can no longer see the */
  /* individual marks, only the marks that coincide on both */
  /* parchments. */
    if (TP->query_prop(LIVE_I_HAS_COMPARED) &&
        pointerp(duplicates))
    {
      /* Loop through the duplicates array and find the */
      /* corresponding location descriptions. */
        for (i = 0; i < 4; i++)
        {
            temp1[i] = warrior_loc[duplicates[i]];
            temp2[i] = chimera_loc[duplicates[i]];
        }
        str = "Four of the marks in the individual patterns " +
            "coincide exactly in the combined pattern. The " +
            "four x-marks on the warrior pattern, " +
            COMPOSITE_WORDS(temp1) + ", and on the " +
            "chimera pattern, " + COMPOSITE_WORDS(temp2) + ".\n";

      /* Only return this description for the chimera parchment, */
      /* otherwise the player will get two of the same message. */
        if (type == "chimera")
            return str;
        else
            return "";
    }

  /* If the player hasn't compared parchments yet, they'll see */
  /* the full list of 12 locations for x-marks, representing */
  /* the twelve pillars standing in each pattern. */
    else
    {
        if (type == "chimera")
            temp1 = chimera_loc;
        else
            temp1 = warrior_loc;
        str = "Scattered at various points around the figure of " +
            "the " + type + " are twelve x-marks. Spread out in " +
            "a roughly circular formation, they lie on the " +
            "following places: " + COMPOSITE_WORDS(temp1) + ".\n";
    }

    return str;
}

/*
 * Function name: set_duplicates
 * Description  : Sets the duplicates array, which describes
 *                which locations coincide. For example, 
 *                ({1,4,9,11}) means that the second, fifth,
 *                tenth and twelfth x-marks on the parchments
 *                coincide.
 * Arguments    : arr - Integer array as described above.
 * Returns      : n/a
 */
public void
set_duplicates(int *arr)
{
    duplicates = arr;
}

/*
 * Function name: query_duplicates
 * Description  : Sees if the array described in set_duplicates() has
 *                been set, and if so what it is.
 * Arguments    : n/a
 * Returns      : 0 if no duplicates, otherwise an array as
 *                described above.
 */
public mixed
query_duplicates()
{
    return duplicates;
}
   
/*
 * Function name: set_copy
 * Description  : Sets whether this parchment was used to copy the
 *                warrior pattern, or chimera pattern.
 * Arguments    : str - String describing which pattern to set. 
 *                      Either 'warrior' or 'chimera'.
 * Returns      : n/a
 */
public void
set_copy(string str)
{
  /* Set nothing if no arg. */
    if (!str || !strlen(str))
        return;

  /* Set nothing if given an unrecognized argument. */
    if (str != "chimera" &&
        str != "warrior")
        return;

  /* Set the 'type' variable to the argument, and generate */
  /* a copy description based on it. */
    type = str;
    copy = "Copied onto the parchment is a strange " +
        "rendition of what looks like a highly-stylised " +
        "version of a " + str + ". " +
        "Twelve x-marks surround the picture in a " +
        "circular formation.\n";

  /* Now that there's something on the parchment, add the */
  /* add_item for the x-marks on it. */
    add_item(({"x-marks", "x's", "x marks"}), "@@exa_marks");
}

/*
 * Function name: query_copy
 * Description  : Returns the copy description that is set in 
 *                set_copy(). Note this returns the full description,
 *                not just 'warrior' or 'chimera'.
 * Arguments    : n/a
 * Returns      : A string describing the pattern on the parchment,
 *                if any.
 */
public string
query_copy()
{
    if (!copy)
        return "";
    else
        return copy;
}

/*
 * Function name: create_object
 * Description  : Turns this object into a piece of parchment.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_object()
{
    set_name("parchment");
    add_name("sheet");
    add_name("paper");
    add_name(ELDORAL_PARCHMENT_NAME);
    set_adj("thin");
    add_adj("cream-coloured");
    set_short("thin cream-coloured sheet of parchment");
    set_long("This sheet of parchment is of strangely " +
        "good quality. Unlike the thick, coarse pieces " +
        "that are often found, this one has been somehow " +
        "treated and thinned to a point where it's " +
        "actually almost transparent. @@query_copy@@\n");

    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_S_WIZINFO, "This scrap of parchment is to be " +
        "used by players for the Sword in the Stone quest in " +
        "Eldoral. It's used for players to copy patterns found " +
        "in the northeast and southwest courtyards of Eldoral, " +
        "which will reveal a combination of stones to depress " +
        "in /d/Calia/eldoral/ruins/catacomb_hub to release " +
        "the sword.\n");

    seteuid(getuid()); 
    chimera_loc = secure_var(SWORD_BRAIN->valid_locs(0)); 
    warrior_loc = secure_var(SWORD_BRAIN->valid_locs(1)); 
}

/*
 * Function name: do_copy
 * Description  : Allows the player to attempt to copy a pattern
 *                onto the paper. They must be standing in specific
 *                rooms to do so, however.
 * Arguments    : str - String argument player passed with the 
 *                      command verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_copy(string str)
{
    string to_copy,
           copy_tool,
           onto_what;
    mixed  pen,
           paper,
           temp;

    notify_fail("Copy what with what onto what?\n");
 
  /* Do nothing if no argument given. */  
    if (!str || !strlen(str))
        return 0;

  /* Fail if we can't see anything. */
    if (!CAN_SEE_IN_ROOM(TP))
    {
        notify_fail("It's too dark to copy anything.\n");
        return 0;
    }

  /* Fail if we can't make sense out of the syntax. */
    if (!parse_command(str, TP, "%s 'with' %i 'on' / 'onto' %i",
        to_copy, pen, paper))
        return 0;

  /* Players can only try to copy 'pattern', 'chimera', or */
  /* 'warrior'. */
    if (to_copy != "pattern" && 
        to_copy != "chimera" &&
        to_copy != "warrior")
    {
        notify_fail("You see no need to copy the " +
            to_copy + ".\n");
        return 0;
    }

  /* If 'pattern' doesn't exist as an add item, the player's */
  /* probably in the wrong room, so do nothing. */
    if (!(environment(TP)->query_item("pattern")))
    {
        notify_fail("You see no such thing to copy.\n");
        return 0;
    }

  /* The two rooms in which players can copy define the */
  /* function query_pattern(). One returns 'chimera', the */
  /* other returns 'warrior'. If this function is not */
  /* defined, do nothing, as we're in the wrong room. */
    if (!(strlen(environment(TP)->query_pattern())))
    {
        notify_fail("You see no such thing worth " +
            "copying.\n");
        return 0;
    }

  /* Set to_copy to either 'chimera' or 'warrior', based */
  /* on what room we're in. */
    to_copy = environment(TP)->query_pattern();

  /* Fail if the player tried copying with more than one 'pen'. */
    if (!pen[0])
    {
        if (sizeof(pen[1..]) > 1)
        {
            NF("You can't copy with more than one thing at " +
                "a time.\n");
            return 0;
        }
        else
            pen = (object)pen[1];
    }

    else if (pen[0] > 0)
    {
        if (pen[0] > 1)
        {
            NF("You can't copy with more than one thing at " +
                "a time.\n");
            return 0;
        }
        else
            pen = (object)pen[pen[0]];
    } 

    else
        pen = (object)pen[-pen[0]];

  /* Fail if the player can't see the selected 'pen' */
    if (!CAN_SEE(TP, pen))
    {
        NF("You can't copy with something you can't see.\n");
        return 0;
    }

  /* If the 'pen' isn't the charcoal sticks, fail. */
    if (!(pen->id(ELDORAL_CHARCOAL_NAME)))
    {
        NF("The " + pen->short() + " probably wouldn't do the job " +
            "properly.\n");
        return 0;
    }

  /* Fail if the player tried copying with more than one 'paper'.*/
    if (!paper[0])
    {
        if (sizeof(paper[1..]) > 1)
        {
            NF("You can't copy onto more than one thing at " +
                "a time.\n");
            return 0;
        }
        else
            paper = (object)paper[1];
    }

    else if (paper[0] > 0)
    {
        if (paper[0] > 1)
        {
            NF("You can't copy onto more than one thing at " +
                "a time.\n");
            return 0;
        }
        else
            paper = (object)paper[paper[0]];
    } 

    else
        paper = (object)paper[-paper[0]];

  /* Fail if the player can't see the selected 'paper' */
    if (!CAN_SEE(TP, paper))
    {
        NF("You can't copy onto something you can't see.\n");
        return 0;
    }

  /* Fail if the paper isn't the parchment in eldoral. */
    if (!(paper->id(ELDORAL_PARCHMENT_NAME)))
    {
        notify_fail("The " + paper->short() + 
            " probably wouldn't do the job " +
            "properly.\n");
        return 0;
    }

  /* Fail if the paper's already been copied onto. */
    if (strlen(paper->query_copy()))
    {
        notify_fail("That " + paper->short() + " has already " +
            "been written on.\n");
        return 0;
    }

  /* Copy the pattern onto the parchment. */
    write("You carefully " + query_verb() + " the " +
        to_copy + " onto the " + paper->short()  +
        " with the " + pen->short() + ", marking the " +
        "positions of the pillars with x's.\n");
    say(QCTNAME(TP) + " draws something on " +
        LANG_ADDART(paper->short()) + " with " +
        LANG_ADDART(pen->short()) + ".\n");
    paper->set_copy(environment(TP)->query_pattern());
    if (type == "warrior")
        TP->add_prop(LIVE_I_SWORD_QUEST,
            TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_COPY_WARR);
    else if (type == "chimera")
        TP->add_prop(LIVE_I_SWORD_QUEST,
            TP->query_prop(LIVE_I_SWORD_QUEST) | SWQ_COPY_CHIM);
    return 1;
}
 
/*
 * Function name: do_compare
 * Description  : Compare two parchments together.
 * Arguments    : str - String passed by the player with the command
 *                      verb.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
public int
do_compare(string str)
{
    mixed temp;
    string first,
           second;
    object firstob,
           secondob;
    mixed *firstarr,
          *secondarr;

    int *randoms = allocate(4);

  /* Do nothing if the player didn't say what to compare. */
    if (!str || !strlen(str))
        return 0;

  /* Try to make sense out of the command argument. */
    if (!parse_command(str, TP, "%i 'and' / 'with' %i",
        firstarr, secondarr))
    {
        if (!parse_command(str, TP, "%i", firstarr))
        {
            notify_fail("Compare what with what?\n");
            return 0;
        }
    }

  /* Make sure the player is only trying to compare two papers. */
    if (firstarr[0] < 0)
        firstob = firstarr[-firstarr[0]];
    else if (!firstarr[0])
    {
        if (sizeof(firstarr) > 3)
        {
            write("You can only compare two parchments at one time.\n");
            return 1;
        }
        firstob = firstarr[1];
        if (sizeof(firstarr) == 3)
            secondob = firstarr[2];
    }
    else if (firstarr[0] > 0)
    {
        if (firstarr[0] > 2)
        {
            write("You can only compare two parchments at one time.\n");
            return 1;
        }
        firstob = firstarr[1];
        if (firstarr[0] == 2)
            secondob = firstarr[2];
    }                     

    if (!secondob && pointerp(secondarr))
    {
        if (secondarr[0] < 0)
            secondob = secondarr[-secondarr[0]];
        else if (!secondarr[0])
        {
            if (sizeof(secondarr) > 2)
            {
                write("You can only compare two parchments at one time.\n");
                return 1;
            }
            secondob = secondarr[1];
        }
        else if (firstarr[0] > 0)
        {
            if (firstarr[0] > 1)
            {
                write("You can only compare two parchments at one time.\n");
                return 1;
            }
            secondob = secondarr[1];
        }                     
    }

  /* Fail if the player is trying to compare a parchment */
  /* with itself. */
    if (firstob == secondob)
    {
        notify_fail("You can't compare the same object " +
            "with itself.\n");
        return 0;
    }

  /* Make sure the player's got actual objects. */
    if (!objectp(firstob) && objectp(secondob))
    {
        notify_fail("Compare what with " + secondob->short() + "?\n");
        return 0;
    }
    else if (objectp(firstob) && !objectp(secondob))
    {
        notify_fail("Compare " + firstob->short() + " with what?\n");
        return 0;
    }
    else if (!objectp(firstob) && !objectp(secondob))
    {
        notify_fail("Compare what with what?\n");
        return 0;
    }

  /* Do the actual comparison. */
    write("You hold the " + firstob->short() + " and the " + 
        secondob->short() + " over one another, and compare them " +
        "closely.\n");
    say(QCTNAME(TP) + " compares " + 
        COMPOSITE_DEAD(({firstob, secondob})) + 
        " closely.\n");

  /* They don't see much if both parchments don't have anything */
  /* on them. */
    if (!firstob->query_copy() ||
        !strlen(firstob->query_copy()))
    {
        write("There is nothing worth comparing on " +
            "the " + firstob->short() + ".\n");
        return 1;
    }

    if (!secondob->query_copy() ||
        !strlen(secondob->query_copy()))
    {
        write("There is nothing worth comparing on " +
            "the " + secondob->short() + ".\n");
        return 1;
    }

  /* Both parchments have copies, and different ones. Therefore, */
  /* mark the player has having compared, and set the duplicates */
  /* array based on the current keystones for the Sword in the */
  /* Stone Quest. */
    write("As you compare the " + 
        COMPOSITE_DEAD(({firstob, secondob})) +
        ", you realize that the patterns contained " +
        "on them interlock to form a single picture " +
        "of a warrior superimposed over a chimera! " +
        "And much to your intrigue, you notice that " +
        "four of the x's on the individual patterns " +
        "coincide with each other's positions. " +
        "Curious.\n");

    TP->add_prop(LIVE_I_HAS_COMPARED, 1);

    if (!duplicates || !sizeof(duplicates))
    {
        seteuid(getuid());
        SWORD_BRAIN->set_keystones();
        randoms = m_indexes(SWORD_BRAIN->query_keystones());
        ({firstob, secondob})->set_duplicates(randoms);
    }
    return 1;
}    
        
/*
 * Function name: init (MASK)
 * Description  : Called when objects meet. Used here to add commands
 *                to a player.
 * Arguments    : n/a
 * Returns      : n/a
 */       
public void
init()
{
    ::init();
    add_action(do_copy, "draw");
    add_action(do_copy, "copy");
    add_action(do_copy, "transcribe");
    add_action(do_compare, "compare");
}


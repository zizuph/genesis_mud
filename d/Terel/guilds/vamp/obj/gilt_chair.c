//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/object";

#include "../defs.h"

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>


#define PLAYER_M_SITTING ("_player_m_sitting")

static object *sitting = ({ });

string my_long();
string my_short();
string cushion_desc();
string sitting_on_cushion(string seated);
int do_rise(string str);
int occupied;

/*
 * Function name: leave_the_room
 * Description  : rise the sitting persons before they leave.
 * Returns      : (int) 0 - always allow the leaving.
 */
public int
leave_the_room(void)
{
    object who = this_player();

    if (who->query_prop(PLAYER_M_SITTING) &&
      (query_verb() != "In") &&
      (query_verb() != "At"))
    {
        do_rise(0);
    }

    return 0;
}


public void
create_object()
{
    set_short(my_short);
    set_long(my_long);
    set_name("chair");
    set_adj(({"long", "low", "gilt", "lounge", "lounging"})); 
    add_prop(OBJ_I_VALUE, 100000);
    add_prop(OBJ_M_NO_GET, "It is far too large and heavy.\n");
    set_no_show_composite(1);
}

/*
 * Function name: cushion_desc
 * Description  : Describe the cushions and show who is sitting in them.
 * Returns      : (string)the description
 */
public string
cushion_desc()
{
    return ("There is a comfortable cushion on it, covered in plush "+
        "red velvet.\n ") +
    sitting_on_cushion("");
}

/*
 * Function name: sitting_on_cushion
 * Description  : Combine those sitting into a nicely formatted string.
 * Arguments    : string seated - predefined text.
 * Returns      : (string) the formatted text.
 */
public string
sitting_on_cushion(string seated)
{
    string *text;
    int size;

    if (!sizeof(sitting))
    {
        return (strlen(seated) ? (seated) : "");
    }

    seated = (strlen(seated) ? (seated + " ") : "");

    if (member_array(TP, sitting) != -1)
    {
        seated += ("You are reclining upon a low gilt chair" +
	      ((sizeof(sitting) == 1) ? "." : (", as is " +
	      COMPOSITE_WORDS(map((sitting - ({ TP }) ),
		&->query_the_name(TP))) + "\n")));
    }
    else
    {
        seated += (capitalize(COMPOSITE_WORDS(map(sitting,
	      &->query_the_name(TP)))) +
	      ((sizeof(sitting) == 1) ? " is" : " are") +
	      " reclining decadently upon it.\n");
    }

    seated += COMPOSITE_WORDS(text) + " ";

    return (strlen(seated) ? (seated) : "") +"\n";
}


/*
 * Function name: my_long
 * Description  : The description of this object.
 * Returns      : (string)description
 */
public string
my_long()
{
    string str;

    str = "This is a long low chair intended for reclining.  "+
          "It is resting high up on the dais so that anyone "+
          "laying on it would be slightly above eye-level. "+
          "It is made of wood and heavily gilded, with a plush "+
          "red velvet cushion added for comfort.\n";

    return str + sitting_on_cushion("");
}

/*
 * Function name: my_short
 * Description  : The short description of this item
 * Returns      : (string)description
 */
public string
my_short()
{
    if (!occupied)
        return "low gilt chair";
    else
        return "low gilt chair with "+ (COMPOSITE_WORDS(map(sitting,
            &->query_the_name(TP)))) +" reclining upon it";
}

/*
 * Function name: do_rise
 * Description  : command to rise
 * Argument     : string str - the argument to the command
 * Returns      : (int) 1/0 - I handled this / SEP
 */
public int
do_rise(string str)
{
    object tp;
    int tmp;

    if (stringp(str))
    {
        notify_fail("Rise what?\n");
        return 0;
    }

    tp = this_player();
    tmp = member_array(tp, sitting);
    if (tmp == -1)
    {
        notify_fail("You are not seated.\n");
        return 0;
    }

    write("You get up from the low gilt chair.\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " languidly rises "+
        "from the low gilt chair " +
        tp->query_pronoun() + " was reclining on.\n",
	  ({ tp }), tp );

    sitting -= ({ tp });

    tp->remove_prop(PLAYER_M_SITTING);
    tp->unset_no_show_composite();
    if (sizeof(sitting) == 0)
        occupied = 0;
    return 1;
}

/*
 * Function name: do_sit
 * Description  : The function for sitting down.
 * Arguments    : The arguments for the command
 * Returns      : (int)1/0 - I handle this / Not my problem
 */
public int
do_sit(string str)
{
    object *oblist, *ob, tp;

    tp = this_player ();
#if 0
    if ((member_array(TP, sitting) != -1))
    {
        notify_fail("You are already reclining on the chair.\n");
        return 0;
    }
#endif /* 0 */

    if (!stringp(str) || str == "down" || str == "chair" ||
      parse_command(str, ({ }), "[down] [on] / [upon] [the] [low] [gilt] 'chair'"))
    {
        if (member_array(tp, sitting) != -1)
	  {
            notify_fail("You are already reclining on it.\n");
            return 0;
        }
        ob = FIND_STR_IN_OBJECT(str, this_player());   
        if (sizeof(ob))
        {
            notify_fail("You can't sit in it while you are holding it.\n");
            return 0;
	}
	if (occupied)
	{
	    notify_fail("It is already in use.\n");
	    return 0;
	}
      else
      {
	    write("You lean back upon the low gilt chair, settling "+
              "comfortably on your side in a reclining position.\n");
	    say(QCTNAME(tp) + " leans into the low gilt chair, "+
              "settling on "+ tp->query_possessive() +" side "+
              "in a comfortable reclining position.\n");
	}
	sitting += ({ tp });
	tp->set_no_show_composite(1);
	tp->add_prop(PLAYER_M_SITTING, 1);
	occupied = 1;
	return 1;
    }

    oblist = PARSE_THIS(str, "[on] [in] [the] [lap] [of] [the] %l");
    if (!sizeof(oblist))
    {
       notify_fail("You wouldn't dare!\n");
	 return 0;
    }
}

/*
 * Function name: do_stand
 * Description  : Command to stand up.
 * Arguments    : string str - the argument to the command.
 * Returns      : (int)1/0 - I handle this/ Not my problem
 */
public int
do_stand(string str)
{
    if (str != "up")
    {
	notify_fail("Stand what? Stand up perhaps?\n");
	return 0;
    }

    return do_rise(0);
}


public int
do_nothing()
{
    do_rise(0);
    return 0;
}


/*
 * Function name: init
 * Description  : Init the local command set.
 */
public void
init()
{
    ::init();

    add_action(do_rise,   "rise");
    add_action(do_sit,    "sit");
    add_action(do_sit,    "sink");
    add_action(do_stand,  "stand");
    add_action(do_sit,    "recline");
    add_action(do_nothing,"north");
    add_action(do_nothing,"south");
    add_action(do_nothing,"east");
    add_action(do_nothing,"west");
    add_action(do_nothing,"up");
    add_action(do_nothing,"down");
    add_action(do_nothing,"southeast");
    add_action(do_nothing,"southwest");
    add_action(do_nothing,"northeast");
    add_action(do_nothing,"northwest");
    add_action(do_nothing,"enter");
    add_action(do_nothing,"search");
    add_action(do_nothing,"climb");
}

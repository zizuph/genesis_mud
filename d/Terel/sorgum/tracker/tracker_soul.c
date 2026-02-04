/* This comment tells emacs to use c++-mode -*- C++ -*- */
 
/*
 * tracker_soul.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit "/cmd/std/command_driver";

/*
 * Function name: get_soul_id
 * Description:   Return a proper name in order to get a nice printout
 * Returns:  A string that is the name of this soul
 */
public string
get_soul_id()
{
    return "Tracker Guild";
}
 
/*
 * Function name: query_cmd_soul
 * Description:   Is this a cmd_soul
 * Returns:  1 (an int) to indicate this is a cmd_soul.
 */
public int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description:   A list of verbs and functions (please add new in alphabetical
 *                order)
 * Returns:  A mapping from verbs to functions
 */

public mapping
query_cmdlist()
{

   return ([
   "blink":"blink",
   "farewell":"farewell",
   "twink":"twink"
   ]);

}

/********************* blink *****************************************/
int
blink(string str)
{
    if (strlen(str)) {
	NF("Blink what?\n");
	return 0;
    }
   
    write("You blink.\n");
    all(" blinks.");
    return 1;
}

/********************* farewell *****************************************/
int
farewell(string str)
{
    object *oblist;
   
    oblist = parse_this(str, "[to] %l");
   
    if (!sizeof(oblist)) {
	NF("Farewell who?\n");
	return 0;
    }    
   
    actor("You bid farewell to", oblist);
    target(" bids farewell to you.", oblist);
    all2act(" bids farewell to", oblist);
    return 1;
}

/********************* twink *****************************************/
int
twink(string str)
{
    object obj;
    
    if (!strlen(str)) {
	NF("Twink whom?\n");
	return 0;
    }

    if ((obj = present(str, ETP)) == 0) {
	NF("That person is not here.\n");
	return 0;
    }

    if (!living(obj)) {
	NF("Not a living target\n");
	return 0;
    }

    obj->catch_msg("\n        _____                 \n" +
		   "        |_ _|       Yo Twink! \n" +
		   "   n    |O O|    n            \n" +
		   "   H   _|\\_/|_   H            \n" +
		   "  nHnn/ \\___/ \\nnHn           \n\n");

    obj->catch_msg(QCTNAME(TP) + " just flipped you off for being " +
		   "the twink you are!\n");

    tell_room(ETP, QCTNAME(TP) + " flips off " + QTNAME(obj) + " for " +
	      "being such a twink.\n", ({TP, obj}));

    TP->catch_msg("You flip off " + QCTNAME(obj) + " for being a twink\n");
    
    return 1;
}

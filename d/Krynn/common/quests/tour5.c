/* A touristing object, small quest. Made by Aridor for Krynn, 06/15/94 */

inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH
#define NAME "tour5"

int *arr; /* The array holding what we have completed. */
string *str_arr; /* Holding the id strings */

/*
 * Function name: ask
 * Description:   The function called when somebody asks about this quest
 * Arguments:     ob - the object asking
 * Returns:       0 - if nothing is written to the object
 *                1 - if something was written
 */
int
ask(object ob)
{
    if (!ob)
	return 1; /* If there was an object we would have written something. */

    tell_object(ob,"Please visit the delivery office in Newports.\n");
    return 1;
}

/*
 * Function name: reward
 * Description:   Function called when an object wants a reward
 * Arguments:     The object wanting the reward
 * Returns:       0 - if no reward was given, I write the error code
 *                1 - Reward was given, you write the standard messages
 *                2 - Reward given, I write the standard message
 */
int
reward(object ob)
{
    int i, sum;

    for (i = 0; i < sizeof(arr); i++)
	if (arr[i])
	    sum += 40;

    if (!sum)
    {
	tell_object(ob, "It seems you haven't visited the delivery office yet.\n");
	return 0;
    }


    ob->add_exp(sum, 0); /* Add quest exp. */
    seteuid(getuid(TO));

    K_QUEST_LOG("quest", "Tour 5", ob, sum);
    return sum;
}

/*
 * Function name: pass
 * Description:   Function called when player wants to pass
 * Arguments:     The object wanting to pass
 * Returns:       0 - if no pass granted, I write the error code
 *                1 - pass granted, you write the standard messages
 *                2 - pass granted, I write the standard message
 */
int
pass(object ob)
{
    tell_object(ob, 
	"You are not allowed to pass this one, try once again.\n");
    return 0;
}

/*
 * Function name: query_arr
 * Description:   Query a number in the array to tell that this was done
 * Arguments:     i - the number in the array
 * Returns:       1/0
 */
int
query_arr(string str)
{
    int i;

    for (i = 0; i < sizeof(str_arr); i++)
	if (str_arr[i] == str)
	    return arr[i];

    return 0;
}

/*
 * Function name: set_arr
 * Description:   Set a number in the array to tell that this was done
 * Arguments:     i - the number in the array
 */
int
set_arr(string str)
{
    int i;

    for (i = 0; i < sizeof(str_arr); i++)
	if (str_arr[i] == str)
	    arr[i] = 1;
}

/*
 * Function name: create_object
 * Description:   The standard create
 */
void
create_object()
{
    str_arr = allocate(10);
    arr = allocate(10);
    set_name("card");
    set_adj("touristing");
    add_name(NAME);
    set_short("@@my_short");
    set_long(""	 +
             "It's the fifth touristing card you have from Krynn.\n" +
	     "You must find the delivery office in Newports.\n\n" +
	     "In the delivery office you can 'ask for a delivery tour'.\n" +
	     "Doing what you get told then you can earn some money!\n" +
	     "Don't forget to return to the Master and ask for your\n" +
	     "reward for finding the office.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_NO_DROP, 1);

    str_arr = ({"delivery office"});
}

/* Function name: my_short
 * Description:   Get a short description telling how much of the quest
 *                is solved
 * Returns:       The short description
 */
string
my_short()
{
    string short;

    short = "touristing card marked 5 ";
    if (arr[0])
	short += "(solved)";
    else
	short += "(unsolved)";

    return short;
}



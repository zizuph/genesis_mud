/* A touristing object, small quest. Made by Nick for Krynn */

inherit "std/object";
#include "/d/Krynn/common/defs.h"
#include QUESTH
#define NAME "Tour 2"

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

    tell_object(ob,BS(
	"Go to the Inn of Last Home and then to Tantallon and visit some " +
	"of the locals there.", 70));
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
	    sum += 60;

    if (!sum)
    {
	tell_object(ob, "It seems you have no reward to get for this one.\n");
	return 0;
    }

    if (sum == (60 * sizeof(str_arr)))
	sum += 200; /* The player did all the parts. */


    ob->add_exp(sum, 0); /* Add quest exp. */
    seteuid(getuid(TO));
    
    K_QUEST_LOG("quest", "Tour 2", ob, sum);
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
    add_name("tour2");
    set_short("@@my_short");
    set_long("" +
	"It's the second touristing card you have from Krynn.\n" +
	"Here is what you have to do, remember you might still get a reward\n"+
	"if you only manage to solve part of it.\n\n"+
    "First go to the Inn of the Last Home and give Tika a hug from me.\n"+
	"Then find the village of Tantallon.\n" +
    "Mary would love spiced potatoes from the Inn of the Last Home.\n"+
	"Find the well in Tantallon and drink from it.\n" +
  "There is a drunk human at the Guardians Pub who wants someone to\n" +
        "sing in there, maybe you can do that?\n\n" +
	"Return then to the Quest master and get your reward.\n" +
	"");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_NO_DROP, 1);

    str_arr = ({"tika", "guard", "dragon", "mary", "well"});
}

/*
 * Function name: my_short
 * Description:   A short description telling how much of the quest is solved
 * Returns:       The short description
 */
string
my_short()
{
    string short;
    int i, j;

    short = "touristing card marked 2 ";

    for (i = 0; i < sizeof(arr); i++)
	j += arr[i];

    switch (j)
    {
    case 0:
	short += "(unsolved)";
	break;
    case 1:
    case 2:
    case 3:
	short += "(partly solved)";
	break;
    case 4:
	short += "(almost solved)";
	break;
    case 5:
	short += "(solved)";
	break;
    default:
	short += "(messed up)";
    }

    return short;    
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

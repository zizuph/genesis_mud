/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * glow.c
 *
 * Used in the zodiac quest.
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/quest_bits.h"

inherit STDOBJECT;

#include <ss_types.h>

/*
 * Global variables
 */

string	shape;
int	exp_given;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    ::create_object();
    shape = "nothing (because a wizard cloned it ilegally ;--)";
    set_name("coal");
    set_adj("piece of black");
    set_long("@@long_desc");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 0);
    set_alarm(300.0, -1.0, "self_destruct");
    exp_given = 0;
}

/*
 * Function name: set_shape
 * Description:   Write access to shape variable.
 *                
 */ 
public void
set_shape(string str)
{
    shape = str;
}

/*
 * Function name: shape_recognizable
 * Description:   See if the player can see a zodiac shape:
 *                     if avg(int, wis) = 50 : 50% chance of recognition.
 *                     if avg(int, wis) < 25 : no chance of recognition
 *                     if avg(int, wis) = 100: 75% chance
 */ 
nomask int
shape_recognizable()
{
    return (random(TP->query_stat(SS_INT) + TP->query_stat(SS_WIS)) > 50);
}

/*
 * Function name: quest_solved
 * Description:   Give exp to the player, if they have not already
 *                done this quest.
 * Returns:       A string which is printed to the player
 *                
 */ 
public string
quest_solved()
{
    int	exp_to_give;

    FIX_EUID;
    /*
     * Only one player at time can get xp for looking at it.
     */
    if (exp_given) return("");
    exp_given++;
    if (TP->test_bit("Terel", QUEST_FIRE_GROUP, QUEST_FIRE_BIT))
	return(" ");
    TP->set_bit(QUEST_FIRE_GROUP, QUEST_FIRE_BIT);
    exp_to_give = TP->query_exp();
    if (exp_to_give > QUEST_FIRE_EXP)
	exp_to_give = QUEST_FIRE_EXP;
    this_player()->add_exp(exp_to_give, 0);
    write_file(QUEST_LOG, TP->query_name() +
	       " solved fire-quest (" + ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
	   "enlightened than before...");
}

/*
 * Function name: long_desc
 * Description:   The long desc of this object.  PLayer will see a shape
 *                for zodiac of int/wis high enough.
 */ 
public string
long_desc()
{
    return("This is a black piece of coal. As you watch it, " +
	   "you find that it has a very unusual shape. " +
	   (shape_recognizable() ?
	    "Your trained eyes recognize faintly the shape of " +
	    shape + ", but it could be as well " +
	    "anything else." + quest_solved() + "\n"
	    :
	    "However, you don't succeed finding out what the shape reminds " +
	    "you of.... But somehow you feel it could be important " +
	    "to find it out. Maybe you're just too dumb?\n"));
}

/*
 * Function name: self_destruct
 * Description:   remove the object, and print a message if it's in the
 *                inventory of a living.
 */ 
public void
self_destruct()
{
    object eto;

    eto = ETO;
    if (living(eto))
	tell_object(eto, "The piece of black coal crumbles to dust.\n");
    remove_object();
}


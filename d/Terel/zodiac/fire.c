/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * fire.c
 *
 * Used in the zodiac quest.
 * Fixed so ogres can finish the quest - Cherek 2015
 */

#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;
#include "/d/Terel/include/quest_bits.h"
#include "/d/Terel/include/zodiac.h"
#include <ss_types.h>



string  shape;
int     exp_given;

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
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{ 

    ::create_object();
    set_name("fire");
    set_adj("orange");
    set_short("orange fire");
    set_long("This fire emits orange light.\n");
    shape = "nothing (because a wizard cloned it ilegally ;--)";
    add_item("light", "The light seems to dip everything in this room in " +
	     "an orange color.\n");
    add_prop(OBJ_I_NO_GET, "If you wish to lose the use of your hand "+
             "feel free.\n");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_LIGHT, 1);

}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_touch", "touch");
    add_action("do_touch", "feel");
    add_action("do_touch", "enter");
}

/*
 * Function name: remove_flag
 * Description:   Remove the fire_burnt_already prop.
 * Arguments:     tp - the player.
 */
public void
remove_flag(object tp)
{
    if (tp)
        tp->remove_prop("_fire_burnt_already");
}

public string
try_get()
{
    if (TP->query_prop("_fire_burnt_already"))
    {
        return "You don't dare to touch the fire after " +
	           "you burnt yourself...\n";
    }
    TP->add_prop("_fire_burnt_already",1);
    set_alarm(15.0 + itof(random(5)), -1.0, &remove_flag(TP));
    TP->reduce_hit_point(TP->query_max_hp() / 5);
    TP->do_die(TO);
    say(QCTNAME(TP) + " tries to get the fire, but is burnt.\n");
    return "You try to touch the fire, but it is hot.. OUCH that hurt!!\n";
}

do_touch(string str)
{
    NF(capitalize(query_verb()) + " what?\n");
    if (str != "fire")
	return 0;
    
    write(try_get());
    return 1;
}


/*
 * Function name: shape_recognizable
 * Description:   See if the player can see a zodiac shape:
 *                     if avg(int, wis) = 50 : 50% chance of recognition.
 *                     if avg(int, wis) < 25 : no chance of recognition
 *                     if avg(int, wis) = 100: 75% chance
 * I have grealty lowered the above so ogres can also finish this
 * quest. - Cherek, December 2015
 */
nomask int
shape_recognizable()
{
    return (random(TP->query_stat(SS_INT) + TP->query_stat(SS_WIS)) > 10);
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
    int exp_to_give;

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
    write_file(QUEST_LOG, TP->query_name() + " solved " +
        "the Zodiac orange component (fire-quest) (" +
        ctime(time()) + ")\n");
    return(" Suddenly you feel much more experienced and " +
           "enlightened than before...");
}


public void
extinguish()
{
    object thisroom;
    int hint;

    thisroom = find_object(HINT_ROOMS[1]);
    hint = thisroom->query_real_hint();
    set_shape(SIGPR[hint] + SIGEQ[hint]);

    tell_room(ETO, "A plume of smoke rises from the fire. As you watch it, " +
           "you find that it has a very unusual shape. " +
           (shape_recognizable() ?
            "Your trained eyes recognize faintly the shape of " +
            shape + ", but it could be as well " +
            "anything else." + quest_solved() + "\n"
            :
            "However, you don't succeed finding out what the shape reminds " +
            "you of.... But somehow you feel it could be important " +
            "to find it out. Maybe you're just too dumb?\n"));
   remove_object();
}

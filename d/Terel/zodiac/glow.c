/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * glow.c
 *
 * Used in the zodiac quest.
 */

#include "/d/Terel/include/Terel.h"

inherit STDOBJECT;

/*
 * Function name: create_object
 * Description:   Default constructor.
 */
public void
create_object()
{
    set_name("fire");
    add_name(({"glow","Zodiac:glow"}));
    set_adj("glowing");
    set_short("glowing fire");
    set_long("Those are the glowing remains of an extinguished fire.\n");
    add_item("light", "The glowing fire doesn't emit much light anymore.\n");
    add_prop(OBJ_I_NO_GET,"@@try_get");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_VALUE, 0);
    set_alarm(20.0, -1.0, "cool_down");
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
}

/*
 * Function name: try_get
 * Description:   hurt the player if the try and get the fire.
 * Returns:       a string that tells the player they are burnt.
 */ 
public string
try_get()
{
    TP->reduce_hit_point(TP->query_max_hp() / 20);
    TP->do_die(0);
    say(QCTNAME(TP) + " tries to get the glowing fire, but is burnt.\n");
    return("You try to touch the glowing fire, but it is hot.. OUCH that " +
           "hurt!!\n");
}

/*
 * Function name: do_touch
 * Description:   Handle the touch action
 * Returns:       1/0
 */ 
public int
do_touch(string str)
{
    notify_fail("Touch what?\n");
    if (str == "fire" || str == "glow")
    {
        write(try_get());
        return 1;
    }
    return 0;
}

/*
 * Function name: cool_down
 * Description:   replace the glow with the ash
 */ 
public void
cool_down()
{
    object ash;

    FIX_EUID;
    ash = clone_object(ZODIAC_DIR + "ash");
    ash->move(ETO);
    tell_room(ETO, "The glowing fire cools down.\n");
    remove_object();
}
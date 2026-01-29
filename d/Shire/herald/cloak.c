/* 
 *  /d/Bree/obj/cloak.c  
 *
 *  Based on the morgul robe. Non-rebootable cloak that, when worn, 
 *  it hides mortal's short descr, and when mortal wears hood, it blocks 
 *  others from remembering them. Naturally, not affected by wizards. ;)
 *  -- Finwe, April 2002
 *
 *  Removed the following code:
 *        TP->add_prop(LIVE_I_NON_REMEMBER,1);
 *
 *  Rules of LIVE_I_NEVERKNOWN implemented by Admin, this goes under that
 *  and is WAY to powerful for a layman anyhow.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Shire/sys/defs.h"
//#define OBJ_DIR     "/d/Shire/bree/obj/"
#define OBJ_DIR     "/d/Shire/herald/"


/*
 *      Global variables:
 */
static object Shadow;

public int query_value()
{
    return 0;
}

/*
 * Function name: create_armour
 * Description:   Creator.
 */
public void create_armour()
{
    set_name(({"cloak"}));
    add_name(({"_bree_cloak"}));
    set_adj(({"large", "brown", "hooded"}));
    set_short("brown hooded cloak");
    set_long("This is a large brown cloak with a wide hood. It is made " +
        "of thick material. The cloak is oversized and large enough to " +
        "envelope you completely, and hide you from prying eyes.\n");
    add_item(({"hood", "wide hood", }), 
        "The hood is large, designed to be worn over the head and face. " +
        "When worn, the hood is large enough to probably hide your " +
        "features from ruffians and villians.\n");
    set_ac(1);
    set_af(this_object());
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  900);

    setuid();
    seteuid(getuid());
}

/*
 * Function name: remove
 * Description:   the remove function for the robe
 * Argument:      ob - object pointer to the robe
 * Returns:       int  0 - No effect, the armour can be removed
 *                     1 - It can be removed but no text should be
 *                         printed (it was done in the function)
 *                    -1 - It can not be removed, default failmsg will
 *                         be written 
 *                string - It cannot be removed, 'string' is the fail
 *                         message to print 
 */
public mixed remove(object ob)
{
    if (ob != this_object())
    {
        return -1;
    }
    if (this_player()->query_hooded())
    {
        Shadow->remove_shadow();
    }
    return 0;
}

/*
 * Function name: wear
 * Description  : This function might be called when someone tries to wear
 *                this armour. To have it called, use set_af().
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.
 */
public mixed wear(object ob)
{
 object user;
    
    user = this_player();

    if (ob != this_object())
    {
        return -1;
    }
        write("You wear the "+ query_short()+ " around your body.\n");
        say(QCTNAME(user)+ " wears "+ LANG_ASHORT(this_object())+
            ".\n");

        TP->add_prop(OBJ_M_NO_STEAL, 1);
        return 1;
}



/*
 * Function name: leave_env
 * Description:   remove the hood shadow if the robe leaves its
 *                environment 
 * Arguments:     from - old environment, to - new environment
 */
public void
leave_env(object from, object to)
{
    if (objectp(from) && from->query_hooded())
    {
        Shadow->remove_shadow();
    }

    ::leave_env(from, to);
}

/*
 *Function name: do_hood
 *Description:   wear the hood
 *Argument:      command verb argument
 *Returns:       1/0
 */
public int do_hood(string str)
{
 object holder, user;
 string  vb, pron;

    vb = query_verb();
    if (vb == "hood")
    {
        pron = "whom";
    }
    else
    {
        pron = "what";
    }
    notify_fail(capitalize(vb)+ " "+ pron+ "?\n");
    if (!strlen(str))
    {
        return 0;
    }

    holder = environment(this_object());
    user = this_player();

    if ((vb == "hood") && ((str != "me") && (lower_case(str) !=
        holder->query_real_name())))
    {
        return 0;
    }
    if ((vb == "wear") && (str != "hood"))
    {
        return 0;
    }
    if (holder != user)
    {
        notify_fail("You do not have the cloak.\n");
        return 0;
    }
    if (query_worn() != user)
    {
        notify_fail("You must wear your cloak first.\n");
        return 0;
    }
    if (user->query_hooded())
    {
        notify_fail("You are already wearing your hood!\n");
        return 0;
    }

    write("You draw the hood over your head. It falls down over your " +
        "face, concealing your features from everyone.\n");
    say(QCTNAME(user)+ " pulls the hood of "+ HIS_HER(user)+ " cloak over "+
        HIS_HER(user)+ " head. It falls down over "+ HIS_HER(user)+ 
        " face, concealing their features from you.\n");

    Shadow = clone_object(OBJ_DIR + "robe_hood_shadow");
    Shadow->shadow_me(user);

    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int do_reveal(string str, int silent = 0)
{
 object holder, user;
 string  vb, pron;

    vb = query_verb();
    switch (vb)
    {
    case "unhood":
    case "reveal":
        pron = "whom";
        break;
    case "reveal":
        vb = "remove";
    case "remove":
        pron = "what";
        break;
    }

    holder = environment(this_object());
    user = this_player();
    notify_fail(capitalize(vb)+ " "+ pron+ "?\n");
    if (!strlen(str))
    {
        return 0;
    }
    switch (vb)
    {
    case "unhood":
        if (str == "me")
        {
            break;
        }
        if (lower_case(str) == holder->query_real_name())
        {
            break;
        }
        notify_fail("You may only remove your own hood.\n");
        return 0;
        break;
    case "reveal":
        if (str == "me")
        {
            break;
        }
        if (lower_case(str) == holder->query_real_name())
        {
            break;
        }
        return 0;
        break;
    case "remove":
        if (str != "hood")
        {
            return 0;
        }
        break;
    }

    if (holder != user)
    {
        notify_fail("You don't have the cloak.\n");
        return 0;
    }

    if (!user->query_hooded())
    {
        notify_fail("You are not wearing your hood!\n");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood, revealing your features for " +
            "all to see.\n");
        say(QCTNAME(user)+ " removes "+ HIS_HER(user)+ " hood.\n");
        TP->remove_prop(OBJ_M_NO_STEAL);

    }

    Shadow->remove_hood_shadow();
    return 1;
}


public void
init()
{
    ::init();
    add_action(do_hood  ,   "hood" );
    add_action(do_hood  ,   "wear" );
    add_action(do_reveal, "reveal" );
    add_action(do_reveal, "unhood" );
    add_action(do_reveal, "remove" );
}


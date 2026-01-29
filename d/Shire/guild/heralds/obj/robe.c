/*
 * Change Log:
 * commented out the hood shadow to remove the white-robed hooded adjectives.
 * Raymundo, May 2020
 *
 * Adjusted the message players see when they wear and remove the hood
 * so that it no longer indicates that their features are hidden.
 *
 * Raymundo, August 2021
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";

#include "/d/Shire/sys/defs.h"
#include "../herald.h"
#include "../titles.h"

#include <language.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <state_desc.h>

//object hood_shadow;
int hooded;
public int valid_owner();

/*
 * Function name: create_object
 * Description:   Creator.
 */
public void 
create_object()
{

    set_name("robe");
    add_name("_herald_robe_");
    set_short("flawless flowing white robe");
    add_adj(({"flawless","flowing","white"}));
    set_long("This beautiful white robe is made of the finest silk " +
        "imaginable, and woven in such a way that it all seems a whole, " +
        "rather than stitched parts. You notice you may <hwear hood> or " +
        "<hremove hood>, or <help herald> to learn more about the " +
        "Heralds.\n");
    add_item(({"secret letters","letters"}), "They read: 'help herald'.\n");
    add_cmd_item("letters","read","The letters read:\n"+
        "If you find yourself lost, just 'help herald'.\n");

    set_wf(this_object());
    set_slots(A_ROBE);

    add_prop(OBJ_I_VALUE,     0);
    add_prop(OBJ_I_WEIGHT,  120);
    add_prop(OBJ_I_VOLUME,  500);
    add_prop(OBJ_I_NO_DROP,   1);
    add_prop(OBJ_M_NO_GIVE,   1);

    set_looseness(20);
    set_layers(1);

    // guild objects do not expire over time as normal equipment.
    // this should not be called in an object without AoB approval!
    remove_item_expiration();
}

public string 
query_recover() 
{ 
    return 0; 
}

/*
 * Function name: valid_owner
 * Description  : Checks whether the owner has the rights to this robe
 */
public int valid_owner()
{
    object user = this_player();

    if ((!IS_MEMBER(user)) && (!user->query_wiz_level())) 
    {
        return 0;
    }

    return 1;
}

/*
 * Hood functions
 */

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
public mixed 
remove(object ob)
{
    if (hooded == 1)
    {
   //     hood_shadow->remove_shadow();
        write("You remove the "+ query_short()+ " from around your body.\n");
        say(QCTNAME(TP)+ " removes "+ LANG_ASHORT(this_object()) + ".\n");
        return 1;
    }

    if (ob != this_object())
    {
        return -1;
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
public mixed 
wear(object ob)
{
 object user;
    
    user = this_player();
    string robe_str;

    if (ob != this_object())
    {
        return -1;
    }

    if (HERALD_CORRUPTION(user))
        robe_str = "";
    else
        robe_str = " It shimmers in the light."; 

    write("You wear the "+ query_short()+ " around your body." +
        robe_str + "\n");
    say(QCTNAME(user)+ " wears "+ LANG_ASHORT(this_object())+
        "." +robe_str+ "\n");
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
 /*   if (objectp(from) && from->query_hooded())
    {
        hood_shadow->remove_hood_shadow();
    } 
 */
    hooded = 0;
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
        notify_fail("You do not have the " + short() + ".\n");
        return 0;
    }
    if (query_worn() != user)
    {
        notify_fail("You must wear your " + short() + " first.\n");
        return 0;
    }
    if (hooded == 1)
    {
        notify_fail("You are already wearing your hood!\n");
        return 0;
    }

    write("You draw the hood over your head.\n");
    say(QCTNAME(user)+ " pulls the hood of "+ HIS_HER(user)+ " cloak over "+
        HIS_HER(user)+ " head.\n");
    hooded = 1;
 //   setuid();
 //   seteuid(getuid());

 //   hood_shadow = clone_object(HERALD_GUILD_OBJ + "robe_hood_shadow");
 //   hood_shadow->shadow_me(user);

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

    if (hooded == 0)
    {
        notify_fail("You are not wearing your hood!\n");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood.\n");
        say(QCTNAME(user)+ " removes "+ HIS_HER(user)+ " hood.\n");
        
    }

 //   hood_shadow->remove_hood_shadow();
    hooded = 0;
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_hood  ,   "hwear" );
    add_action(do_reveal, "hremove" );
}


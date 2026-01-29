#pragma strict_types
#pragma save_binary

inherit "/std/armour";
inherit "/std/shadow";


#include "/d/Shire/sys/defs.h"
#include "/d/Shire/herald/herald.h"
#include "titles.h"

#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#define STARTING_AC  5
#define OBJ_DIR     "/d/Shire/bree/obj/"

static object Shadow;

void
create_armour()
{
    setuid();
    seteuid(getuid());

    set_name("robe");
    add_name("_herald_robe_");
    set_short("flawless flowing white robe");
    add_adj(({"flawless","flowing","white"}));
    set_long("This beautiful white robe is made of the finest silk imaginable, " +
        "and woven in such a way that it all seems a whole, rather than " +
        "stitched parts. You notice you may <hwear hood> or <hremove hood>, " +
        "or <help herald> to learn more about the Heralds.\n");

    add_prop(OBJ_I_WEIGHT,   120);
    add_prop(OBJ_I_VOLUME,   500);
    add_prop(OBJ_I_VALUE,      0);
    add_prop(OBJ_M_NO_DROP,    1);
    add_prop(OBJ_M_NO_STEAL,   1);
    set_default_armour(STARTING_AC, A_ROBE);

    add_item(({"secret letters","letters"}), "They read: 'help herald'.\n");
    add_cmd_item("letters","read","The letters read:\n"+
      "If you find yourself lost, just 'help herald'.\n");
    set_likely_cond(0); 
    set_likely_break(0);
}

public string query_recover() { return 0; }

public int 
query_ondo_effect()
{
    if (query_ac() > STARTING_AC)
	return 1;

    return 0;
}

void
ondo_spell(int result)
{
    if (!result)
    {
	set_ac(STARTING_AC);
	query_worn()->update_armour(TO);
	return;
    }

    set_ac(result);
    query_worn()->update_armour(TO);
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
public mixed remove(object ob)
{
write (this_player()->query_hooded());
    if (this_player()->query_hooded())
    {
        Shadow->remove_shadow();
//        write("You must remove your hood first.");
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
public mixed wear(object ob)
{
 object user;
    
    user = this_player();

    if (ob != this_object())
    {
        return -1;
    }
        write("You wear the "+ query_short()+ " around your body. It shimmers in the light.\n");
        say(QCTNAME(user)+ " wears "+ LANG_ASHORT(this_object())+
            ". It shimmers in the light.\n");
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
        Shadow->remove_hood_shadow();
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
        notify_fail("You do not have the " + short() + ".\n");
        return 0;
    }
    if (query_worn() != user)
    {
        notify_fail("You must wear your " + short() + " first.\n");
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

    Shadow = clone_object("/d/Shire/herald/robe_hood_shadow");
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
    }

    Shadow->remove_hood_shadow();
    return 1;
}


public void
init()
{
    ::init();
    add_action(do_hood  ,   "hwear" );
    add_action(do_reveal, "hremove" );
}


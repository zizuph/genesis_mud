#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"

inherit "/lib/commands.c";

int cont_alarm = 0;

void
create_wearable_pack()
{
    set_name("guige");
    set_short("leather guige");
    set_pshort("leather guiges");
    set_adj("leather");
    set_long("This guige is a long leather strap, used to hang a shield " +
        "on the back when not in use. Used in combat, it frees a " +
        "warrior to use a weapon requiring two hands without discarding " +
        "the shield <ghang>, and can be easily retrieved when " +
        "needed <grelease>.");

    set_slots(A_BACK);
    set_looseness(20);
    set_layers(1);
    set_keep(1);
    set_wf(TO);
    set_cf(TO);

    add_prop(OBJ_I_VALUE, 850);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_WEIGHT, 15000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_REDUCE_WEIGHT, 110);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_M_NO_INS, "Try <ghang> shield instead.\n");

    remove_name("pack");

    //Enable default item expiration
    set_item_expiration();

}

/*
 * Function name: short
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the short
 * Returns      : The short description.
 */
public varargs string
short(object for_obj)
{
    /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used.
     */
    return check_call(obj_short, for_obj);
}

/*
 * Function name: pshort
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the pshort
 * Returns      : The plural short description.
 */
public varargs string
plural_short(object for_obj)
{
     /* This line is copied from object.c as we don't want the 
     * instance of short in receptacle to be used
     */

   return check_call(obj_pshort, for_obj); 

}

/*
 * Function name: long
 * Description  : A the status of the container to it.
 * Arguments    : string str - the psuedo-item the person wants to see.
 *                object for_obj - who wants to know the long
 * Returns      : string - The long description.
 */
public varargs string
long(string str, object for_obj)
{
    string desc;
    desc = query_long();

    if (!strlen(str))
    {
        desc += ((query_prop(CONT_I_CLOSED)) ?
            "\n" : " ");
    }
    return desc;
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("The leather guige currently holds " + 
            COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("The leather guige currently does not " +
            "hold anything.\n");
    }
}

int
close(object obj)
{
    string arty = obj->short();
    write("There is no way to close the " + arty + ". It is just a strap!\n");
    return 3;
}

/* 
 * Reject containers of any sort. 
 */
int
prevent_enter(object ob)
{
        if(ob->query_at() != A_SHIELD)
        {
            write("Only shields can be attached to the leather guige.\n");
            return 1;
        }
        if (ob->query_prop(OBJ_I_BROKEN))
        {
            write("The leather guige cannot hold broken items.\n");
            return 1;
        }
        
    return ::prevent_enter(ob);
}

public void
pack_fill_hook(object *moved)
{
    write("You hang " + COMPOSITE_DEAD(moved) + " from your " + short()
        + ".\n");
    tell_room(E(TP), QCTNAME(TP) + " hangs " + COMPOSITE_DEAD(moved)
        + " from " + HIS(TP) + " " + short() + ".\n", TP);
    return;

    ::pack_fill_hook(moved);
    return;
}

public void
pack_empty_hook(object *moved)
{
    write("You detach " + COMPOSITE_DEAD(moved) + " from your " + short()
        + ".\n");
    tell_room(E(TP), QCTNAME(TP) + " detaches " + COMPOSITE_DEAD(moved)
        + " from " + HIS(TP) + " " + short() + ".\n", TP);
        return;

    ::pack_empty_hook(moved);
    return;
}


void
init()
{
    ::init();

    ADA("ghang");
    ADA("grelease");
}

int
restore_no_ins(string artme)
{
    add_prop(CONT_M_NO_INS, "Try <ghang> instead.\n");
    cont_alarm = 0;
    return 1;
}

int
ghang(string str)
{
    string *strhold, holdername, wepstr;
    object wep, holder, *inme;
    object * oblist;

    NF("Hang what on what?\n");
    if (!str)
        return 0;

    oblist = parse_this(str, "[the] %o");

    NF("Hang what?\n");
    if (!sizeof(oblist))
        return 0;

/*
    if (!sscanf(str, "%s on %s", wepstr, holdername))
        return 0;

    if (!(wep = present(wepstr, TP)))
        return 0;

    NF("Hang your " + wepstr + " on what?\n");
    if (!(holder = present("guige", TP)))
        return 0;
*/

    holder = present("guige", TP);
    wep = oblist[0];
    strhold = holder->query_names();
    inme = all_inventory(holder);

    NF("Hang what? Be more specific!\n");
    if (!present(wep, TP))
        return 0;
    
    if (IN_ARRAY("guige", strhold))
    {
        string holdisplay = holder->short();
        string wepdisplay = wep->short();
        NF("Only shields can be hung on your " + holder->short()
        + ".\n");
        if (wep->query_at() != A_SHIELD)
            return 0;

        NF("There is already a shield on your " + holder->short() + ".\n");
        if (sizeof(inme) != 0)
            return 0;

        holder->remove_prop(CONT_M_NO_INS);
        if(wep->move(holder))
        {
            write("Your " + holdisplay + " already has a shield on it.\n");
            return 1;
        }

        holder->restore_no_ins(strhold[0]);
        write("You hang your " + wepdisplay + " on your "
        + holdisplay + ".\n");
        say(QCTNAME(TP) + " hangs " + HIS(TP) + " " + wepdisplay
        + " on " + HIS(TP) + " " + holdisplay + ".\n");
        return 1;
    }
    
    NF("Buggy!\n");
    return 0;
}

int
grelease(string str)
{
    string *strhold, holdername, wepstr, holdstr;
    object wep, holder, *inme;
    mixed ddo;

    NF("Release from what?\n");
    if (!str)
        return 0;

    NF("Release from guige you mean?\n");
    if (!sscanf(str, "from %s", holdername))
        return 0;

    NF("Release from what?\n");
    if (!(holder = present(holdername, TP)))
        return 0;

    strhold = holder->query_names();
    holdstr = holder->short();

    NF("Your " + holdstr + " has nothing attached to it.\n");
    if (sizeof(inme = all_inventory(holder)) == 0)
        return 0;

    wep = inme[0];
    wepstr = wep->short();
    if (TP->query_tool(W_BOTH))
    {
        NF("Your hands are too full to hold a shield.\n");
        return 0;
    }
    else
    {
        switch (wep->query_hands())
        {
            case W_LEFT:
                if (TP->query_tool(W_LEFT))
                {
                    NF("Your left hand is already occupied.\n");
                    return 0;
                }
                break;
            case W_RIGHT:
                if (TP->query_tool(W_RIGHT))
                {
                    NF("Your right hand is already occupied.\n");
                    return 0;
                }
                break;
            case W_BOTH:
                if ((TP->query_tool(W_RIGHT)) || (TP->query_tool(W_LEFT)))
                {
                    NF("You haven't enough space in your hands to hold "
                    + "a shield.\n");
                    return 0;
                }
                break;
        }
    }
    
    TP->catch_msg("You release your " + wepstr + " from your " + holdstr
        + ".\n");
    tell_room(E(TP), QCTNAME(TP)+ " releases " + HIS(TP) + " " + wepstr
        + " from " + HIS(TP) + " " + holdstr + ".\n", TP);

    if (wep->move(TP))
        wep->move(TP, 1);
    
    if (stringp(ddo = wep->command_wear()))
        write(ddo);
    return 1;
}

/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory. */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    wearable_item_leave_env(old, dest);
}


string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover() + 
        query_container_recover();
}
 
void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    init_container_recover(arg);
    ::init_keep_recover(arg);
}


/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * coffin.c
 *
 * A coffin.
 */

#include "/d/Terel/include/Terel.h"

inherit "/std/container";

#include <ss_types.h>
#include <cmdparse.h>

object check_key(string prop, object ob);

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_open",   "open");
    add_action("do_close",  "close");
    add_action("do_lock",   "lock");
    add_action("do_unlock", "unlock");
}

create_container()
{
    set_name("coffin");
    set_short("old coffin");
    set_adj("old");
    set_long("@@my_long");
    add_prop(CONT_I_WEIGHT,     15000);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_VOLUME,     8000);
    add_prop(CONT_I_MAX_VOLUME, 15000);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_CLOSED,     0);
    add_prop(CONT_I_LOCK,       0);
    
    add_prop(OBJ_I_NO_GET, 1);

    add_item(({"lock"}), "The lock seems quite old and made of iron.\n");
}

/*
 * Function name: do_open
 * Description:   Handle the open action
 * Returns:       1/0
 */
public int
do_open(string what)
{
    object ob;

    NF("Open what?\n");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    if (TO -> query_prop(CONT_I_LOCK)) {
	write("The " + short() +" is locked.\n");
	return 1;
    }
    
    if (!(TO -> query_prop(CONT_I_CLOSED))) {
	write("The " + short() +" is already opened.\n");
	return 1;
    }
    write("You open the " + short() + ".\n");
    say(QCTNAME(TP) + " opens the " + short() + ".\n");
    TO->add_prop(CONT_I_CLOSED, 0);
    return 1;
}

/*
 * Function name: do_close
 * Description:   Handle the close action
 * Returns:       1/0
 */
public int
do_close(string what)
{
    object ob;

    NF("Close what?\n");
    if (!what) return 0;

    if (!parse_command(what, environment(), "%o", ob)) return 0;

    if (ob != TO) return 0;

    if (TO -> query_prop(CONT_I_CLOSED)) {
	write("The " + short() + " is already closed.\n");
	return 1;
    }
    write("You close the "+TO->short()+".\n");
    say(QCTNAME(TP) + " closes the " + short() + ".\n");
    TO->add_prop(CONT_I_CLOSED, 1);
    return 1;
}

/*
 * Function name: do_unlock
 * Description:   Handle the open action
 * Returns:       1/0
 */
public int
do_unlock(string what)
{
    object key, ob1, ob2;

    NF("Unlock what?\n");
    if (!what) return 0;

    NF("Unlock what with what?\n");
    if(!parse_command(what, environment(),
	"%o 'with' %o", ob1, ob2)) return 0;

    NF("Unlock what?\n");
    if (ob1 != TO) return 0;

    NF("Unlock "+TO->short()+" with what?\n");
    if (ob2->query_name() != "key") return 0;

    if (!(TO -> query_prop(CONT_I_LOCK))) {
	write("The "+TO->short()+" is already unlocked.\n");
	return 1;
    }

    key = check_key("key_owner", TP);
    if (key != ob2) {
	write("You don't have the proper key to do that.\n");
	return 1;
    }

    write("You unlock the " + short() + " with your " + key->short() + ".\n");
    say(QCTNAME(TP) + " unlocks the " + short() + ".\n");
    add_prop(CONT_I_LOCK, 0);
    return 1;
}

/*
 * Function name: do_lock
 * Description:   Handle the lock action
 * Returns:       1/0
 */
public int
do_lock(string what)
{
    object key, ob1, ob2;

    NF("Lock what?\n");
    if (!what) return 0;

    NF("Lock what with what?\n");
    if(!parse_command(what, environment(),
	"%o 'with' %o", ob1, ob2)) return 0;

    NF("Lock what?\n");
    if (ob1 != TO) return 0;

    NF("Lock "+ short() + " with what?\n");
    if (ob2->query_name() != "key") return 0;

    if (TO -> query_prop(CONT_I_LOCK)) {
	write("The "+TO->short()+" is already locked.\n");
	return 1;
    }
    if (!(TO -> query_prop(CONT_I_CLOSED))) {
	write("The "+TO->short()+" is opened, you have to close it first.\n");
	return 1;
    }

    key = check_key("key_owner", TP);
    if (key != ob2) {
	write("You don't have the proper key to do that.\n");
	return 1;
    }
    write("You lock the "+TO->short()+" with your "+key->short()+".\n");
    say(QCTNAME(TP) + " locks the "+TO->short()+".\n");
    TO->add_prop(CONT_I_LOCK, 1);
    return 1;
}

/*
 * Function name: my_long
 * Description:   Returns the long description, which depends on the
 *                state of the coffin (open/locked).
 */
public string
my_long()
{
    string str;

    str = "It's an "+TO->short()+". It looks sturdy";
    if (TO->query_prop(CONT_I_CLOSED)) str = str + ". It is closed";
    if (TO->query_prop(CONT_I_LOCK)) str = str + " and locked";
    str = str + ".";
    return BSN(str);
}

/*
 * Function name: check_key
 * Description:   Look for an object in the inventory with the given
 *                prop and return it.
 * Arguments:     prop - the property
 *                ob   - the ob to look in the invetory of
 * Returns:       The object with the desired prop or 0 if not found.
 */
public object
check_key(string prop, object ob)
{
    int i;
    object *ob_arr, r_ob;

    r_ob = 0;
    ob_arr = all_inventory(ob);
    for(i=0; i<sizeof(ob_arr); i++) {
	if (ob_arr[i]->query_prop(prop) == ob->query_name()) {
	    r_ob = ob_arr[i];
	}
    }
    return r_ob;
}

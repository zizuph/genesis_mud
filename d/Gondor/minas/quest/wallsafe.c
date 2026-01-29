inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

void
create_receptacle()
{
   set_name("safe");
   add_name("wallsafe");
   set_short("wallsafe, partly hidden among the bookshelves");
   set_adj("sturdy");
   set_long("This sturdy wallsafe is fastened to the wall.\n");

   set_key("Gimilzors_wallsafe_key");
   set_no_pick();

   add_prop(CONT_I_WEIGHT,     29000);
   add_prop(CONT_I_VOLUME,     5000);
   add_prop(CONT_I_MAX_WEIGHT, 92000);
   add_prop(CONT_I_MAX_VOLUME, 92000);
   add_prop(CONT_I_RIGID, 1);
   add_prop(CONT_I_CLOSED, 1);
   add_prop(CONT_I_LOCK, 1);
   add_prop(OBJ_I_VALUE, 1100);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_M_NO_GET, "The wallsafe is fastened to the wall!\n");
}

/*
 * Function name: do_default_unlock
 * Description  : If parent do_default_unlock() succeeds, and if player
 *		  using wallsafe key is not the player who found the key,
 *		  remove the ledger.
 * Arguments    : str - the rest of the command line by the mortal
 * Returns      : 1 = success, 0 = failure.
 */
public int
do_default_unlock(string str)
{
    int		rval;
    string	key_owner,
		name;
    object	ledger,
		key,
		tp = TP;

    if (!(rval = ::do_default_unlock(str)))
    {
	return 0;
    }
    key = present("Gimilzors_wallsafe_key", tp);
    if (tp->test_bit("Gondor", TOUR_GROUP, MTIRITH_MURDER_BIT))
    {
	name = tp->query_real_name();
	ledger = present("ledger", TO);
	log_file("murder", ctime(time())+" "+name+
	    " opened wallsafe, has done quest already.\n");
	if (objectp(ledger))
	{
	    ledger->remove_object();
	}
	if (objectp(key) &&
	    tp->query_name() != "Dior")
	{
	    write("Oops -- the key shatters!\n");
	    key->remove_object();
	}
	return 1;
    }
    if (objectp(key))
    {
	key_owner = key->query_prop(MT_PW5_S_OWNER);
	name = tp->query_real_name();
	ledger = present("ledger", TO);
	if (key_owner != name &&
	    (name != "dior" ||
	     tp->query_prop(MT_PW5_S_KEY_SOURCE) != key_owner))
	{
	    log_file("murder", ctime(time())+" "+name+
		" opened wallsafe with "+
		(strlen(key_owner) ? key_owner : "nobody" )+"'s key.\n");
	    if (objectp(ledger))
	    {
		ledger->remove_object();
	    }
	}
	else if (objectp(ledger))
	{
	    ledger->add_prop(MT_PW5_S_OWNER, key_owner);
	}
	if (tp->query_name() != "Dior")
	{
	    write("Oops -- the key shatters!\n");
	    key->remove_object();
	}
    }
    return rval;
}

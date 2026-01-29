#pragma save_binary
#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/tyr/tyr.h"
#define NFN notify_fail

/*
 *      Global variables:
 */
static  object  Shadow;

public int     query_value() { return 0; }

/*
 * Function name: create_armour
 * Description:   Creator.
 */
public void
create_armour()
{
    set_name("cloak");
    set_adj("hooded");
    add_adj("dark");
   set_short("dark hooded cloak");
    set_long("This is a large cloak that stretches the length of the body.  It is "
	+"so black that it looks like a living shadow.  There is a hood " 
    	+"on it as well that probably could be useful.\n");
   add_item(({"hood", "wide hood", }),"The hood will allow the "
   +"wearer to conceal their features when it is raised.\n");
   set_ac(2);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,  700);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);

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
public mixed
lower(object ob, string str)
{
if(str !="hood")
	return -1;
    if (ob != TO)
        return -1;

    if (TP->query_hooded())
        Shadow->remove_shadow();

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
    object  tp = TP;

    if (ob != TO)
        return -1;

    {
     write("You wear the "+query_short()+" around your body.\n");
     say(QCTNAME(TP)+" wears the dark hooded cloak.\n");
        return 1;
    }
}

/*
 * Function name: query_recover
 * Description:   no recovery, since the robe autoloads
 * Returns:       0
 */
public string query_recover() { return 0; }
/*
 *Function name: do_hood
 *Description:   wear the hood
 *Argument:      command verb argument
 *Returns:       1/0
 */
public int
do_hood(string str)
{
    if (ENV(TO) != TP)
    {
        return 0;
    }

    if (query_worn() != TP)
    {
		NFN("You do not wear your cloak!\n");
        return 0;
    }

    if (TP->query_hooded())
    {
	NFN("You are already wearing your hood!\n");
        return 0;
    }

   write("You pull the hood of your cloak over your head, concealing your "
      +"features.\n");
  say(QCTNAME(TP)+" pulls the hood of "+HIS_HER(TP)+" cloak over "
   +HIS_HER(TP)+ " head, concealing " +HIS_HER(TP)+ " features.\n");

    setuid();
   seteuid(getuid());
    Shadow = clone_object(TYR_ARM + "hood_shadow");
    Shadow->shadow_me(TP);
    return 1;
}

/*
 * Function name: do_reveal
 * Description:   remove the hood
 * Argument:      str - argument
 *                silent - write no message if 1
 * Returns:       1/0
 */
public int
do_reveal(string str, int silent = 0)
{

    if (ENV(TO) != TP)
    {
	    NFN("You do not have the cloak!\n");
        return 0;
    }

    if (!TP->query_hooded())
    {
	    NFN("You are not wearing your hood!\n");
        return 0;
    }

    if (!silent)
    {
        write("You remove the hood and reveal your face again.\n");
       say(QCTNAME(TP)+" removes "+HIS_HER(TP)+" hood.\n");
    }

    Shadow->remove_hood_shadow();
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_hood,   "hood");
   add_action(do_hood,   "raise");
    add_action(do_reveal, "reveal");
    add_action(do_reveal, "unhood");
   add_action(do_reveal, "lower");
    add_action(do_reveal, "remove");
}



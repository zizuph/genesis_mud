/*
 * /d/Gondor/common/arm/trousers.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * A pair of configurable trousers.
 *
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>	/* for OBJ_I_*		*/
#include <wa_types.h>		/* for A_LEGS		*/
#include <formulas.h>		/* for F_VALUE_ARMOUR	*/
#include "/d/Gondor/defs.h"

public void	create_armour();
public void	configure(string adj0, string adj1, string material,
			  string style, string extra);
public string	query_recover();
public void	init_recover(string arg);


/*
 * Function name:	create_armour
 * Description	:	set up the trousers
 */
public void
create_armour()
{
    set_name("trousers");
    set_pname("trouserses");
    set_default_armour(5, A_LEGS, ({ 0, 0, 0 }), 0);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(5) + random(10) - 5));
    configure("dark", "supple", "leather", "comfortable", "");
} /* create_armour */


/*
 * Function name:	configure
 * Description	:	set up the trousers desc
 * Arguments	:	string adj0	may be ""
 *			string adj1	required
 *			string material	required
 *			string style	required
 *			string extra	may be "";
 *					else should start with ", "
 * short is "pair of <adj1> <material> trousers"
 * long is "The pair of <style> trousers is made
 *		of <adj0> <adj1> <material><extra>.\n"
 * i use "pair of" so the line giving condition, which will use the
 * singular, doesn't look odd.
 */
public void
configure(string adj0, string adj1, string material, string style,
	string extra)
{
    remove_adj(query_adjs());
    set_adj( ({ adj1, material }) );
    set_short("pair of " + adj1 + " " + material + " trousers");
    set_pshort("pairs of " + adj1 + " " + material + " trousers");
    set_long(BSN("The pair of " + style + " trousers is made of " +
    	(strlen(adj0) ? adj0 + " " : "") + adj1 + " " + material +
	extra + "."));
} /* configure */


/*
 * Function name:	query_recover
 * Description	:	mask parent to save our description
 * Returns	:	string -- the recovery string
 */
public string
query_recover()
{
    int		l;
    string	*tmp,
		adj0,
		style,
		extra,
		myarg;

    tmp = query_adjs();
    sscanf(long(),
	   "The pair of %s trousers is made of %s" + tmp[0] + 
	   	" " + tmp[1] + "%s.",
	   style, adj0, extra);
    if (l = strlen(adj0))
    {
	/* strip trailing space */
	adj0 = adj0[..(l - 2)];
    }

    /* CONFIG#adj0:adj1#material#style#extra# */
    myarg = "CONFIG#" + adj0 + ":" + tmp[0] + "#" + tmp[1] +
	    "#" + style + "#" + extra + "#";

    return ::query_recover() + myarg;
} /* query_recover */


/*
 * Function name:	recover
 * Description	:	mask parent to recover our description
 * Arguments	:	string arg -- the arguments to parse
 */
public void
init_recover(string arg)
{
    string	armour_arg,
		adj0,
		adj1,
		material,
		style,
		extra;

    /* CONFIG#adj0:adj1#material#style#extra# */
    if (sscanf(arg, "%sCONFIG#%s:%s#%s#%s#%s#",
	       armour_arg, adj0, adj1, material, style, extra) == 6)
    {
	configure(adj0, adj1, material, style, extra);
	::init_recover(armour_arg);
    }
    else
    {
	::init_recover(arg);
    }
} /* init_recover */

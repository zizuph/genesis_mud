/*
 * /d/Gondor/lebennin/sirith/farms/obj/cider.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */


#pragma save_binary
#pragma strict_types

inherit "/std/drink.c";

#include <stdproperties.h>	/* for OBJ_I_*	*/
#include "/d/Gondor/defs.h"

public void	create_drink();
public void	init();
public int	smell_cider(string arg);


/*
 * Function name:	create_drink
 * Description	:	set up the cider
 */
public void
create_drink() 
{
    set_name("cider");
    set_pname("ciders");
    add_name("mug");
    add_pname("mugs");
    set_adj("apple");
    set_short("mug of apple cider");
    set_pshort("mugs of apple cider");
    set_long(BSN("The cider is a clear golden colour, with an "+
	"aroma of apples."));

    add_prop(OBJ_I_VALUE, 5);
    set_soft_amount(226);
    set_alco_amount(4);
    add_prop(OBJ_I_WEIGHT, 226);
    add_prop(OBJ_I_VOLUME, 226);

} /* create_drink */


/*
 * Function name:	init
 * Description	:	add smell, sniff verbs
 */
public void
init()
{
    ::init();
    add_action(smell_cider, "smell");
    add_action(smell_cider, "sniff");
} /* init */


/*
 * Function name:	smell_cider
 * Description	:	handle attempts to smell/sniff cider
 * Argument	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 otherwise
 */
public int
smell_cider(string arg)
{
    if (arg == "cider" ||
	arg == "apple cider" ||
	arg == "mug" ||
        arg == "ciders" ||
	arg == "apple ciders" ||
	arg == "mugs" ||
        arg == "mug of apple cider" ||
	arg == "mugs of apple cider")
    {
    	write("The golden cider smells strongly of apples.\n");
	return 1;
    }
    return 0;
} /* smell_cider */

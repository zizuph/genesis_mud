/*
 * /d/Gondor/pelargir/obj/mirrorbracket.c
 *
 * Copyright (C) August 20, 1998 by Ron Miller (Tyr)
 *
 * This is the bracket atop the central pedestal in the lamproom
 * which holds the mirror of the quest to repair the lighthouse
 * beacon.
 * 
 * Revision History:
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit     "/std/container";

#include    <stdproperties.h>
#include    "/d/Gondor/defs.h"
#include    "/d/Gondor/pelargir/beacon_defs.h"

/* prototypes */
public void    create_container();
static mixed   check_insert();
public void    enter_inv(object ob, object from);

/*
 * Function name:    create_container()
 * Description:      create the bracket which holds the mirror
 */
public void
create_container()
{
    set_name( ({ "bracket", "mirrorbracket", "mirror bracket" }) );

    set_short("mirror bracket");

    set_adj( ({ "second", "mirror", "back" }) );

    set_long(BSN("This badly corroded bracket at the rear of the "+
        "mechanism is designed to support a mirror of some sort. "+
        "From this position, light would be reflected back toward "+
        "the bracket at the front of the mechanism."));

    set_no_show_composite(1);   /* makes bracket "non-obvious" */

    add_prop(CONT_I_WEIGHT, 50000);     /* set weight at 50 kg */
    add_prop(CONT_I_MAX_WEIGHT, 65000);  /* it can contain 65 kg (lens) */
    add_prop(CONT_I_VOLUME, 2000);      /* set volume at 2 Ltr */
    add_prop(CONT_I_MAX_VOLUME, 8000);  /* it can contain 8 Ltr */
    add_prop(CONT_I_RIGID,1);           /* it is a rigid object */
    add_prop(CONT_M_NO_INS, check_insert); /* only mirror fits bracket */
    add_prop(OBJ_M_NO_GET, "The bracket is a permanent part of the "+
                         "mechanism and cannot be removed.\n");
} /* end create_container */

/*
 * Function name:    check_insert()
 * Description:      verifies correct match of mirror to mirrorbracket
 */
static mixed
check_insert()
{
    int    i=1;
    object obj;

    while (objectp(obj=previous_object(--i)))
    {
        if (obj == TO)
        {
            if (previous_object(i-1)->id(MIRROR_NAME))
            {
                /* only Lumendil can load brackets */
                if (TP->query_name() != "Lumendil")
                {
                    return "You lack the skill required handle such "+
                    "delicate repairs. Perhaps someone with more "+
                    "expertise about this mechanism would be more "+
                    "successful.\n";
                }
                return 0;
            }
            return "The brackets on this mechanism are highly "+
                   "specialized and each one will only accommodate "+
                   "the item it was specifically designed to hold.\n";
        }
    }
    return "The brackets on this mechanism are highly specialized and "+
           "each one will only accommodate the item it was "+
           "specificallydesigned to hold.\n";

    /* make the mirror un-removeable */
    add_prop(CONT_M_NO_REM, "Removing the mirror is an extremely "+
        "delicate operation and best left to the hands of a skilled "+
        "lighthouse attendant./n");  

}    /* end check_insert */

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    if (ob->id(MIRROR_NAME))
    {
        ob->add_prop(OBJ_M_NO_GET,
            "Lumendil has firmly attached the mirror in its "+
            "bracket. It would almost certainly be damaged if "+
            "you continued your unskilled efforts to remove it.\n");
    }
} /* enter_inv */

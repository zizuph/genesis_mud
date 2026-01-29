/*
 * /d/Gondor/pelargir/obj/lensbracket.c
 *
 * Copyright (C) July 29, 1998 by Ron Miller (Tyr)
 *
 * This is the bracket atop the central pedestal in the lamproom
 * which holds the lens of the quest to repair the lighthouse
 * beacon.
 *
 * Revision history:
 *    6/28/99 - revised per Gnadnar's suggestions by Tyr
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
 * Description:      create the bracket which holds the lens
 */
public void
create_container()
{
    set_name( ({ "bracket", "lensbracket", "lens bracket" }) );
    set_short("lens bracket");
    set_adj( ({ "first", "lens", "front" }) );
    set_long(BSN("This large circular ring is diametrically opposite " +
        "its counterpart atop the pedestal. It is built to hold a " +
        "rather large lens."));

    set_no_show_composite(1);   /* makes bracket "non-obvious" */

    add_prop(CONT_I_WEIGHT, 50000);     /* set weight at 50 kg */
    add_prop(CONT_I_MAX_WEIGHT, 60000);  /* it can contain 10 kg (lens) */
    add_prop(CONT_I_VOLUME, 2000);      /* set volume at 2 Ltr */
    add_prop(CONT_I_MAX_VOLUME, 6000);  /* it can contain 4 Ltr */
    add_prop(CONT_I_RIGID,1);           /* it is a rigid object */
    add_prop(CONT_M_NO_INS, check_insert); /* only lens fits in bracket */

    add_prop(OBJ_M_NO_GET, "The bracket is a permanent part of the " +
                         "mechanism and cannot be removed.\n");
} /* end create_container */

/*
 * Function name:    check_insert()
 * Description:      verifies correct match of lens to lensbracket
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
            if (previous_object(i-1)->id(LENS_NAME))
            {
                /* only Lumendil can load brackets */
                if (TP->query_name() != "Lumendil")
                {
                    return "You lack the skill required handle such " +
                    "delicate repairs. Perhaps someone with more " +
                    "expertise about this mechanism would be more " +
                    "successful.\n";
                }
                return 0;
            }
            return "The brackets on this mechanism are highly " +
            "specialized and each one will only accommodate " +
            "the item it was specifically designed to hold.\n";
        }
    }
    return "The brackets on this mechanism are highly specialized and " +
    	"each one will only accommodate the item it was " +
    	"specifically designed to hold.\n";
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
    if (ob->id(LENS_NAME))
    {
        ob->add_prop(OBJ_M_NO_GET,
            "The lens is held fast by the mechanism, and you lack " +
            "the expertise required to remove it.\n");
    }
} /* enter_inv */

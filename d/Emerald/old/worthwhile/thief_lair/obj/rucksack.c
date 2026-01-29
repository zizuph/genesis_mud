/* This is a sturdy rucksack, ideal for someone going camping.            */
/* Most mortals, however, will use it to store all the loot they carry... */
/* Keep functionality taken straight from the excellent example given in  */
/* the tutorial written by Meracde.                                       */
/* Coded 14/06/96 by Tulix III.                                           */

inherit "/lib/keep";
inherit "/std/container";

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Emerald/tulix/t_defs.h"

/* Always a good idea to keep Mercade happy. */
#pragma strict_types

/* We define the VBFC string for our own function. */
#define MY_OBJ_M_NO_SELL "@@my_obj_m_no_sell@@"

/* Prototype functions */
string rucksack_instructions();
string rucksack_filled_desc();
int    fill_rucksack(string str);
int    empty_rucksack(string str);
int    open_rucksack(string str);
int    close_rucksack(string str);


/* 
 * Function name: create_container
 * Description:   Define the basic functions of the rucksack.
 */
void
create_container()
{
    set_keep(1);    /* This call is required or 'keep' won't work. */

    set_name("rucksack");
    set_pname("rucksacks");
    set_adj("sturdy");
    add_adj(({"strong hessian", "hessain"}));
    set_short("sturdy rucksack");
    set_pshort("sturdy rucksacks");
    set_long("This sturdy rucksack would be a great asset to anyone going " +
        "camping. It is based on a light wooden frame which has been " +
        "covered with flexible, but strong, hessian material. It looks as " +
        "if it would withstand anything that the weather can throw at it, " +
        "short of a tornado. Having a large flap on the front, it is " +
        "remarkably easy to fill and empty, too. There is some writing on " +
        "the side.\nThe rucksack seems able to last a long while.\n");
    add_item( ({"hessian", "hessian material"}), "The hessian material " +
        "used to make this rucksack is coarse, but very strong, as it " +
        "made from is hemp and jute woven together.\nThough not fully " +
        "waterproof, it should keep equipment safe from the weather.\n");
    add_item( ({"large flap", "flap"}), "The large flap on the rucksack " + 
        "stops anything from falling out.\n");
    add_item( ({"writing", "side"}), rucksack_instructions() );
    add_cmd_item( ({"writing", "side"}), "read", rucksack_instructions() );

    add_prop(CONT_I_WEIGHT, 2000);       /* Quite heavy for a rucksack. */
    add_prop(CONT_I_VOLUME, 2400);       /* Floats on water when empty. */
    add_prop(CONT_I_REDUCE_WEIGHT, 100); /* 100 seems to be standard.   */
    add_prop(CONT_I_REDUCE_VOLUME, 125); /* 125 seems to be standard.   */
    add_prop(CONT_I_MAX_VOLUME, 125000); /* Less max volume than usual. */
    add_prop(CONT_I_MAX_WEIGHT, 155000); /* Good (not best) max weight. */
    add_prop(CONT_I_CLOSED, 1);          /* Starts off closed.          */
    add_prop(OBJ_I_VALUE, 250);          /* Useful, and so is valuable. */
    add_prop(OBJ_S_WIZINFO, "This rucksack is a handy for storing all " +
        "the loot that mortals tend to carry. Rucksacks are carried " +
        "by various npcs in Emerald.\nCarrying capacity etc. was based on " +
        "similar containers found in Gondor, Kalad and Calia.\n");
}

/* 
 * Function name: rucksack_instructions
 * Description:   Give instructions on how to use the rucksack.
 * Returns:       A string containing the instructions.
 */
string
rucksack_instructions()
{
    return "To store all your ill-gotten gains in the rucksack, use " +
        "<fill rucksack>.\nWhen you want take them out again, use " +
        "<empty rucksack>.\nTo prevent accidental sale, you can use " +
        "<keep> in the normal way.\nThe rucksack cannot be sold " +
        "in a shop unless empty, too.\nMade in Emerald.\n";
    /* What's that marketing phrase? 'It pays to advertise!' *chuckle* */
}

/* 
 * Function name: rucksack_filled_desc
 * Description:   Give a description of how much room is left in the rucksack.
 * Returns:       A string description of how full the rucksack is.
 */
string 
rucksack_filled_desc()
{
    int full_pc, volume_pc, weight_pc;

    /* It is especially helpful to know when the rucksack is empty -     */
    /* if you are in the shop and trying to sell all your loot quickly.  */
    if (!sizeof(all_inventory(TO)))
        return "The rucksack is now totally empty.\n";
    
    /* Calculate the percentage volume filled so far. */
    volume_pc  = (TO->query_prop(OBJ_I_VOLUME) * 100 /
                  TO->query_prop(CONT_I_MAX_VOLUME));
                  
    /* Calculate the percentage weight used so far. */
    weight_pc  = (TO->query_prop(OBJ_I_WEIGHT) * 100 /
                  TO->query_prop(CONT_I_MAX_WEIGHT));

    /* Use the largest of the two percentages above. */
    if (volume_pc > weight_pc)
        full_pc = volume_pc;
    else
        full_pc = weight_pc;

    /* Each consecutive case below represents an extra 10% full. */
    switch (full_pc/10)
    {
        /* 0% - 9% full. */
        case 0:
            return "The rucksack is virtually empty.\n";

        /* 10% - 19% full. */
        case 1:
            return "The rucksack is only partially filled.\n";

        /* 20% - 29% full. */
        case 2:
            return "The rucksack can carry much more equipment.\n";

        /* 30% - 39% full. */
        case 3:
            return "The rucksack can carry a lot more equipment.\n";

        /* 40% - 49% full. */
        case 4:
            return "The rucksack is less than half full.\n";

        /* 50% - 59% full. */
        case 5:
            return "The rucksack is just over half full.\n";

        /* 60% - 69% full. */
        case 6:
            return "The rucksack can carry some more equipment.\n";

        /* 70% - 79% full. */
        case 7:
            return "The rucksack can carry a bit more equipment.\n";

        /* 80% - 89% full. */
        case 8:
            return "The rucksack is nearly full.\n";

        /* 90% - 99% full. */
        case 9:
            return "The rucksack is nearly bursting at the seams.\n";

        /* Exactly 100% full - difficult to achieve, but possible. */
        case 10:
            return "The rucksack is bursting at the seams.\n";
        
        default:
            return "";
    }
}

/* 
 * Function name: init
 * Description:   Add the rucksack specific commands to the player.
 */
void
init()
{
    ::init();
    add_action(fill_rucksack,  "fill");
    add_action(empty_rucksack, "empty");
    add_action(open_rucksack,  "open");
    add_action(close_rucksack, "close");
}

/* 
 * Function name: fill_rucksack
 * Description:   Try to put any surplus items into the rucksack.
 * Arguments:     str: the rest of the command string.
 * Returns:       0 = failure, 1 = success.
 */
int
fill_rucksack(string str)
{
    object *items, *items_in, rucksack;
    int i;
    
    if (!strlen(str))
    {
        NF("Fill what?\n");
        return 0;
    }

    /* Check what the player wants to fill with parse_command. */
    parse_command(str, ENV(TP), "[up] [the] %o", rucksack);
    
    /* Is this object the one being filled? */
    if (rucksack != TO)
    {
        NF("Fill what?\n");
        return 0;
    }

    /* Let's try to fill the rucksack with the players stuff. */
    items = all_inventory(TP);
    items_in = ({ });

    if (TO->query_prop(CONT_I_CLOSED))
    {
        NF("The rucksack is closed.\n");
        return 0;
    }
    
    if (!sizeof(items))
    {
        NF("You don't have much to fill the rucksack with.\n");
        return 0;
    }

    for (i=0 ; i<sizeof(items) ; i++) 
    {
        if (!items[i])
            continue;

        /* Check to make sure we don't move autoloading objects, etc. */
        if (items[i]->query_prop(CONT_I_IN) ||
            !CAN_SEE(TP, TO) ||
            !CAN_SEE(TP, items[i]) ||
            items[i]->query_worn() ||
            items[i]->query_wielded() ||
            items[i]->query_auto_load())
            continue;
        
        /* The move efun does not move items into containers that are full, */
        /* so we don't need to worry about that possibility.                */
        if (!items[i]->move(TO))
        {
            if (!sizeof(items_in))
                items_in = ({ items[i] });
            else
                items_in += ({ items[i] });
        }
    }
    
    /* Tell everybody what went into the rucksack. */
    if (!sizeof(items_in))
    {
        NF("You put nothing into the rucksack.\n");
        return 0;
    }
    else    
    {
        write("You put " + COMPOSITE_DEAD(items_in) + 
            " into the rucksack.\n" + TO->rucksack_filled_desc());
    
        tell_room(ENV(TP), QCTNAME(TP) + " puts " + 
            COMPOSITE_DEAD(items_in) + " into a rucksack.\n", TP);
    }

    return 1;
}

/* 
 * Function name: empty_rucksack
 * Description:   Try to take everything out of the rucksack.
 * Arguments:     str: the rest of the command string.
 * Returns:       0 = failure, 1 = success.
 */
int
empty_rucksack(string str)
{
    object *items, *items_out, rucksack;
    int i;

    if (!strlen(str))
    {
        NF("Empty what?\n");
        return 0;
    }

    /* Check what the player wants to empty with parse_command. */
    parse_command(str, ENV(TP), "[out] [the] %o", rucksack);
    
    /* Is this object the one being emptied? */
    if (rucksack != TO)
    {
        NF("Empty what?\n");
        return 0;
    }

    /* Let's try to empty the rucksack of the players stuff. */
    items = all_inventory(TO);
    items_out = ({ });

    if (TO->query_prop(CONT_I_CLOSED))
    {
        NF("The rucksack is closed.\n");
        return 0;
    }
    
    if (!sizeof(items))
    {
        NF("There is nothing in the rucksack.\n");
        return 0;
    }

    for (i=0 ; i<sizeof(items) ; i++) 
    {
        if (!items[i])
            continue;

        /* Is it too dark to get stuff from the rucksack? */
        if (!CAN_SEE(TP, TO) ||
            !CAN_SEE(TP, items[i]))
            continue;
        
        /* The move efun does not move items into players that cannot carry */
        /* anything else, so we don't need to worry about that possibility. */
        if (!items[i]->move(TP))
        {
            if (!sizeof(items_out))
                items_out = ({ items[i] });
            else
                items_out += ({ items[i] });
        }
    }
    
    /* Tell everybody what came out of the rucksack. */
    if (!sizeof(items_out))
    {
        NF("You took nothing out of the rucksack.\n");
        return 0;
    }
    else    
    {
        write("You take " + COMPOSITE_DEAD(items_out) + 
            " out of the rucksack.\n" + TO->rucksack_filled_desc());
    
        tell_room(ENV(TP), QCTNAME(TP) + " takes " + 
            COMPOSITE_DEAD(items_out) + " out of a rucksack.\n", TP);
    }

    return 1;
}

/* 
 * Function name: open_rucksack
 * Description:   Open the rucksack, if it isn't already open.
 * Arguments:     str: the rest of the command string.
 * Returns:       0 = rucksack was not opened, 1 = rucksack was opened.
 */
int
open_rucksack(string str)
{
    object rucksack;
    
    if (!strlen(str))
    {
        NF("Open what?\n");
        return 0;
    }

    /* Check what the player wants to open with parse_command. */
    parse_command(str, ENV(TP), "[up] [the] %o", rucksack);
    
    /* Is this object the one being opened? */
    if (rucksack != TO)
    {
        NF("Open what?\n");
        return 0;
    }
    
    if (TO->query_prop(CONT_I_CLOSED))
    {
        write("You open the large flap on your rucksack.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " opens the large flap on " +
            "a rucksack.\n", TP);
        TO->remove_prop(CONT_I_CLOSED);
        return 1;
    }
    else
    {
        NF("The large flap on the rucksack is already open.\n");
        return 0;
    }
}

/* 
 * Function name: close_rucksack
 * Description:   Close the rucksack, if it isn't already closed.
 * Arguments:     str: the rest of the command string.
 * Returns:       0 = rucksack was not closed, 1 = rucksack was closed.
 */
int
close_rucksack(string str)
{
    object rucksack;
    
    if (!strlen(str))
    {
        NF("Close what?\n");
        return 0;
    }

    /* Check what the player wants to close with parse_command. */
    parse_command(str, ENV(TP), "[off] [the] %o", rucksack);
    
    /* Is this object the one being closed? */
    if (rucksack != TO)
    {
        NF("Close what?\n");
        return 0;
    }
    
    if (!TO->query_prop(CONT_I_CLOSED))
    {
        write("You close the large flap on your rucksack.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " closes the large flap on " +
            "a rucksack.\n", TP);
        TO->add_prop(CONT_I_CLOSED, 1);
        return 1;
    }
    else
    {
        NF("The large flap on the rucksack is already closed.\n");
        return 0;
    }
}

/*
 * The following code was 'borrowed' (as defined in the dictionary by Mylos)
 * from the keeping tutorial written by Mercade. Nice job, too! #:-)
 */

/*
 * Function name: query_recover
 * Description  : This function is called to get the recover string.
 * Returns      : string - the recover string.
 */
string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

/*
 * Function name: init_recover
 * Description  : This function is called to restore the recover string.
 * Arguments    : string arg - the recovery information.
 */
void
init_recover(string arg)
{
    /* Restore the keep recover information. */
    init_keep_recover(arg);
}

/*
 * Function name: set_keep
 * Description  : This function is a mask of the set_keep(). If the keep
 *                protection is set, we set it, but if it is removed, we
 *                do not remove the property, but set our own.
 * Arguments    : int keep - 1 - set the keep protection. [default]
 *                           0 - remove the keep protection. If we do this,
 *                               we rather set our own protection.
 */
void
set_keep(int keep = 1)
{
    if (keep)
    {
        /* Keep protection is being set, let the normal code handle it. */
        ::set_keep(keep);
    }
    else
    {
        /* The normal code would now remove the property, but we rather
         * set our own VBFC function as argument to the property.
         */
        this_object()->add_prop(OBJ_M_NO_SELL, MY_OBJ_M_NO_SELL);
    }
}

/*
 * Function name: query_keep
 * Description  : Since we changed the set function, we must also change
 *                the query function. The existance of the property is no
 *                longer enough to be sure that the keep protection is
 *                indeed active. Therefore we mask this function too.
 * Returns      : int 1/0 - true if this object is keep-protected.
 */
int
query_keep()
{
    /* If the real value of the setting of the property is our VBFC
     * function, this means that the keep protection is not active. Since
     * we need to know when it _is_ active, we check for not equal.
     */
    return (query_prop_setting(OBJ_M_NO_SELL) != MY_OBJ_M_NO_SELL);
}

/*
 * Function name: my_obj_m_no_sell
 * Description  : This function is the VBFC that is called when the keep
 *                protection is not active. We use it to test whether the
 *                rucksack contains any items. If so, prevent the rucksack
 *                from being sold.
 * Returns      : mixed - fail message (string) if rucksack is not for sale.
 *                      - 0 (int) if the rucksack is for sale.
 */
mixed
my_obj_m_no_sell()
{
    /* If the rucksack isn't empty, we probably don't want to sell it. */
    if (sizeof(all_inventory()))
        return "You should empty the " + short() + " before selling it.\n";
    else
        return 0;
}

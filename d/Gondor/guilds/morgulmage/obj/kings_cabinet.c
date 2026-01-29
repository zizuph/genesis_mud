/*
 * /d/Gondor/guilds/morgulmage/obj/kings_cabinet.c
 *
 * This cabinet is accessible only to the King.
 *
 * Coded by Mercade, March 20 1998.
 */

#pragma strict_types

inherit "/std/receptacle.c";
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/*
 * Function name: create_receptacle
 * Description  : Constructor. Called to create this receptacle.
 */
void
create_receptacle()
{
    set_short("ornamented cabinet");
    set_name("cabinet");
    set_adj("ornamented");

    set_long("The cabinet is made of solid oak. It looks sturdy and " +
        "is decorated with various arcane symbols. On the door, underneath " +
        "the picture of a large Lidless Eye, painted in the colour of " +
        "blood, a crown can be seen. This is unmistakenly the cabinet in " +
        "which the King of Morgul keeps some ancient items, related to " +
        "his power and majesty. No man, mortal or undead, should ever " +
        "peek inside.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The cabinet is fixed to the floor, you cannot take it.\n");
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_VOLUME,  4500);
    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     1);

    set_cf(this_object());

    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    set_enable_logging(0);
    set_enable_recovery(1);
    
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
}

/*
 * Function name: open
 * Description  : To ensure that only the King of Morgul can open this chest,
 *                this function is called. It will return 0 for the King and
 *                prints a fail message to all other mortals. Then it returns
 *                '3' to indicate that the messages have been printed.
 * Returns      : int 0/3 - possible/impossible to open.
 */
public int
open(object obj)
{
    /* Lord of the Nazgul. */
    if (this_player()->query_nazgul() == 2)
    {
        return 0;
    }

    /* No reason to insult wizards, even though they have no place in it. */
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    write("Begone, ye fool! Thou shallt not touch the door of this "
      + "cabinet, lest you be whipped by the King of Morgul!\n");
    say(QCTNAME(TP) + " approaches the ornamented cabinet of the King "
      + "of Morgul! " + capitalize(TP->query_possessive()) + " hand quivers "
      + "and you see that " + TP->query_pronoun() + " does not dare to "
      + "actually open the door.\n");
    return 3;
}

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
    ::enter_inv(ob, from);
    
    if (from == this_object())
    {
        return;
    }
    
    add_rack_entry(ob);
}


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}

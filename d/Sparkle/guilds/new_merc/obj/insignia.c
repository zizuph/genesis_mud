/*
 *  /d/Sparkle/guilds/new_merc/obj/insignia.c
 *
 *  This is the guild object for the Mercenary Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";

#include "../merc_defs.h"
#include <stdproperties.h>
#include <wa_types.h>

/* Prototypes */
public void        create_object();
void               leave_env(object from, object to);
void               appraise_object(int num);


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("insignia");
    add_name(GUILD_EMBLEM_ID);
    add_adj( ({ "free", "mercenary", "guild" }) );

    set_short("mercenary insignia");

    set_long("A small square of onyx has been polished, inset with an"
      + " image of a golden hand, and fixed to small metal chain that"
      + " can be worn around the neck.\n\n"
      + "This insignia is carried by all members of " + GUILD_NAME
      + ". You can use <merchelp> to get information on the guild and"
      + " abilities that membership offers.\n");

    config_wearable_item(A_NECK, 1, 6, this_object()); 

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  300);
    add_prop(OBJ_I_VOLUME,  500);

    remove_prop(OBJ_I_VALUE);
} /* create_object */


/* The following two functions are masked as per the instructions in
 * the header of /lib/wearable_item.c
 */

void
leave_env(object from, object to)
{
     ::leave_env(from, to);

     wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

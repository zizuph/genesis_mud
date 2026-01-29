#pragma strict_types

inherit "/std/object";

/* Inherit /lib/help to enable the help functionality. */
inherit "/lib/help";

#include "guild.h"

#include <stdproperties.h>

void
create_object()
{
    set_name("horn");
    add_name(GUILD_EMBLEM_ID);
 
    add_adj("big");

    set_long("The horn given to you by the " + GUILD_NAME + ".\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  2000);
    add_prop(OBJ_I_VOLUME,  500);

    remove_prop(OBJ_I_VALUE);

    /* We add help in a folder, and we add a category "demoguild".
     * The folder contains two help files:
     *     history.help and levels.help
     *
     * This offers the following commands:
     *     help demoguild  --> lists the topics: history and levels.
     *     help [demoguild] levels
     *     help [demoguild] history
     */
    
    /* Give the directory in which the help files are located. Using a
     * directory requires us to also set a category. */
    set_help_dir("/d/Genesis/doc/examples/guild/occ_fighter/help");

    /* Set the category for this help. It is mandatory when using a
     * directory of help files. This routine takes a single string, or
     * an array of string, e.g. ({ "demoguild", "dg" }) would have
     * worked too. Just make sure that the categories are UNIQUE in
     * the realms, or otherwise they wouldn't work as category :-) */
    set_help_category("demoguild");
}

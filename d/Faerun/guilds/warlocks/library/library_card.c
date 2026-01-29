/*
 *  /d/Faerun/guilds/warlocks/library/library_card.c
 *
 *  This card allows the holder to be a librarian and maintain the scrolls 
 *  and shelves of teh Warlock guild library.
 */
#include "/d/Faerun/defs.h"
#include "../guild.h";

inherit "/std/object";

void create_object()
{
    set_name("card");
    add_name(LIBRARY_CARD);
    add_adj("library");
    set_short("library card");
    set_long("This is a library card for the Warlock guild library. It is " +
        "proof you are a librarian and can maintain the scrolls, shelves, " +
        "and other aspects of the library.\n");

    add_prop(OBJ_I_WEIGHT,  5);
    add_prop(OBJ_I_VOLUME,   5);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP,  1);
    add_prop(OBJ_M_NO_STEAL, 1);
}


/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string 
query_auto_load() 
{
    return MASTER + ":"; 
}


void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
    if (inv->query_ghost())
	return;

    set_alarm(30.0, 0.0, "check_card", inv);
}

// Checks if player is still a member of the guild when they login
// If they aren't, the card is removed from their inventory
void
check_card(object ob)
{
    if (!IS_MEMBER(TP))
    {
        ob->catch_msg("\n\nThe library card from the Warlock guild explodes " +
            "before your eyes since you are no longer a member of the guild.\n");
        remove_object();
    	return;
    }
}




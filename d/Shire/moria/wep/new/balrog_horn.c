/*
 * Znafsnuf
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 * 
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

int b_title();

/*
 * Function name: create_object
 * Description  : Set up default values for parts of the ship
 */
void
create_object()
{
    set_name("horn");
    add_name("_balrog_of_moria_horn");
    set_adj("broken");
    add_adj("test");

    set_short("broken horn");

    set_long("A balrog horn\n");

    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);


    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}) );

    add_prop(MAGIC_AM_ID_INFO, ({
        "You feel there must be great powers in a balrog's horn.\n", 20,
        "Something .\n", 50 }));

    add_prop(OBJ_S_WIZINFO, "Balrog's horn.\n");
}

/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
public void
init()
{
    ::init();
    add_action(b_title, "btitle");
}

int
b_title()
{
    seteuid(getuid(this_object()));
    this_player()->add_autoshadow("/d/Shire/moria/wep/new/balrog_title");
    clone_object("/d/Shire/moria/wep/new/balrog_title")->shadow_me(this_player());
    this_player()->catch_msg("You present yourself as 'Balrog Bane'.\n");
    return 1; 
}
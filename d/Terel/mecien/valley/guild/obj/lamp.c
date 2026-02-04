/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/container";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define EMBER    GUILD_DIR + "obj/ember"
#define TP       this_player()
#define TO       this_object()

public int add_ember();       /* Returns 1/0 depending on success */
public int remove_ember();    /* Returns 1/0 depending on success */

public void
create_container()
{
    set_name("lamp");
    add_name(MYSTIC_LAMP);
    add_name("sacred_lamp");
    set_adj("silver");
    set_long("A small ornate silver lamp. It is covered with intricate " +
             "patterns and small four-pointed stars. It has a small cover " +
             "that looks like a tiny crown, with which things can be " +
             "placed with the lamp.\n");

    add_prop(CONT_M_NO_REM, "You cannot do that.\n");
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_WEIGHT, 351);
    add_prop(CONT_I_MAX_VOLUME, 151);
}

public int
add_ember()
{
    object ember;

    seteuid(getuid());
    add_prop(CONT_I_CLOSED, 0);
    ember = clone_object(EMBER);
    if (ember->move(TO)) {
        ember->remove_object();
        add_prop(CONT_I_CLOSED, 1);
        return 0;
    }
    add_prop(CONT_I_CLOSED, 1);
    return 1;
}

public int
remove_ember()
{
    object ember;

    add_prop(CONT_I_CLOSED, 0);
    ember = present(MYSTIC_EMBER, TO);
    if (ember) {
        ember->remove_object();
        add_prop(CONT_I_CLOSED, 1);
        return 1;
    }
    add_prop(CONT_I_CLOSED, 1);
    return 0;
}

/*
 * /d/Gondor/common/dwarf_guild/obj/cabinet.c
 *
 * This cabinet is placed in the join.c cave of the Dwarven race guild. In
 * It, members may find a belt for them to wear as token of membership. There
 * is no code preventing people from getting more belts, but if people take
 * advantage of this feature, I will alter it.
 *
 * /Mercade, 17 January 1994
 *
 * Revision history:
 * Fixed enable_reset() to fit with the new GD. 7/3-94, by Elessar.
 */

#pragma save_binary

inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../dwarf.h"

/*
 * This define defines the standard inventory that should be cloned every
 * reset if the cabinet is not filled. The first entry is the function that
 * used to create the object, the second its filename and the third is the
 * number of objects that should be in the cabinet.
 */
#define MINIMUM_INVENTORY \
    ({ ({ "create_armour", DWARVEN_RACE_GUILD_BELT, 3 }) })
#define CABINET_ID DWARVEN_RACE_GUILD_PREFIX + "cabinet_"

/*
 * Global variables
 */
mixed  to_check   = MINIMUM_INVENTORY;
object last_manip = TO;

/*
 * Prototype
 */
void reset_container();

void
create_container()
{
    set_name("cabinet");
    add_name(CABINET_ID);

    add_adj("wooden");

    set_short("wooden cabinet");
    set_pshort("wooden cabinets"); /* should never happen */

    set_long(BSN("It is a wooden cabinet. In it, members of the " +
        DWARVEN_RACE_GUILD_NAME + ", may find a belt, the token of " +
        "membership."));

    FIX_EUID;

    set_cf(TO);

    add_prop(CONT_I_CLOSED,          1);
    add_prop(CONT_I_RIGID,           1);
    add_prop(CONT_I_VOLUME,     320000);
    add_prop(CONT_I_WEIGHT,     132000);
    add_prop(CONT_I_MAX_VOLUME, 900000);
    add_prop(CONT_I_MAX_WEIGHT, 300000);
    add_prop(OBJ_M_NO_GET,
        BSN("The cabinet is too heavy to get."));
    add_prop(OBJ_M_NO_INS,
        BSN("There is no reason to put anything in the cabinet."));

    enable_reset();
    reset_container();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!objectp(to))
    {
        return;
    }

    ob->remove_prop(OBJ_M_NO_GET);

    set_alarm(1.0, 0.0, "reset_container");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    ob->add_prop(OBJ_M_NO_GET, VBFC_ME("may_remove_belt"));
}

mixed
may_remove_belt()
{
    if (IS_MEMBER(TP))
    {
        return 0;
    }

    return BSN("You are not entitled to remove anything from the cabinet.");
}

int
open(object to_open)
{
    if (!IS_MEMBER(TP))
    {
        write(BSN("You are not entitled to " + query_verb() +
            " the cabinet."));

        /* Impossible to manipulate, but message in this function. */
        return 3;
    }

    last_manip = TP;

    /* Possible to manupilate, message is default. */
    return 0;
}

void
reset_container()
{
    object *all_inv = all_inventory();
    int    i, j;
    int    num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
        if ((num_found = sizeof(filter(all_inv, "object_filter", TO,
            ({ to_check[i][0], to_check[i][1] }) ))) < to_check[i][2])
        {
            for (j = num_found; j < to_check[i][2]; j++)
            {
                clone_object(to_check[i][1])->move(TO, 1);
            }
        }
    }
}

/*
 * extra = ({ function_name, filename }) ... given from reset_room()
 */
int
object_filter(object obj, mixed extra)
{
    return (function_exists(extra[0], obj) == extra[1]);
}

/*
 * This function returns who opened the cabinet the last time. If the player
 * tries to leave the room, he is called to close it before leaving.
 */
object
query_last_manip()
{
    return last_manip;
}
/*
 * /d/Gondor/mordor/obj/torchstand.c
 *
 * The torch stand in the tower at Cirith Ungol. (It also contains a torch)
 *
 * /Mercade 12 October 1993
 *
 * Revision history:
 */

inherit "/std/container";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>

/*
#define TORCH_OBJECT MORDOR_DIR + "obj/torch"
*/
#define IN_TEXT BSN("There already is a torch in the stand.")

/*
 * Prototype
 */
void reset_container();

/*
 * Called to create the torch stand.
 */
void
create_container()
{
    set_name("stand");
    add_name("bracket");
    set_pname("stands");
    add_pname("brackets");
    set_adj("torch");
    set_adj("iron");
    set_long(BSN("The iron torch stand is mounted to the wall."));

    add_prop(OBJ_M_NO_GET,
        BSN("The iron torch stand is secured to the wall."));
    add_prop(OBJ_I_VALUE, 132 + random(25));

    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 11000);
    add_prop(CONT_I_MAX_VOLUME, 11000);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

    reset_container();
  enable_reset();
}

void
init()
{
    add_action("do_light",      "light");
    add_action("do_extinguish", "extinguish");
}

/*
 * Reset the torch stand from time to time.
 */
void
reset_container()
{
    object torch = present("torch", TO);

    if (!objectp(torch))
    {
        seteuid(getuid(this_object()));
        torch = clone_object(MORDOR_DIR + "obj/torch");
        torch->move(TO, 1);
        add_prop(CONT_M_NO_INS, IN_TEXT);
    }
}

/*
 * The short description dependant on whether a torch is in it.
 */
string
short()
{
    object torch = present("torch", TO);

    if (objectp(torch))
    {
        if (torch->query_prop(OBJ_I_HAS_FIRE))
        {
            return "iron torch stand containing a lit torch";
        }
        else
        {
            return "iron torch stand containing a torch";
        }
    }

    return "iron torch stand";
}

/*
 * The plural short description dependant on whether a torch is in it.
 */
string
pshort()
{
    object torch = present("torch", TO);

    if (objectp(torch))
    {
        if (torch->query_prop(OBJ_I_HAS_FIRE))
        {
            return "iron torch stands containing a lit torch";
        }
        else
        {
            return "iron torch stands containing a torch";
        }
    }

    return "iron torch stands";
}

/*
 * If the torch is removed from the stand, it is possible to add a new torch
 * to the stand.
 */
void
leave_inv(object ob, object from)
{
    remove_prop(CONT_M_NO_INS);
}

/*
 * You can only put a torch in the stand.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!(ob->id("torch")))
    {
        set_alarm(2.0, 0.0, "drop_non_torch", ob);
        return;
    }

    add_prop(CONT_M_NO_INS, IN_TEXT);
}

/*
 * If you put another object than a torch in the stand, it will fall out.
 */
void
drop_non_torch(object ob)
{
    tell_room(ENV(TO), BSN("The torch stand is only meant for torches and " +
        "therefor the " + check_call(ob->short()) + " falls onto the " +
        "ground."));
    ob->move(ENV(TO));
}

/*
 * If you try to light the torch in the stand, it will probably happen.
 * All it does is call the light function in the torch itself.
 */
int
do_light(string str)
{
    object torch = present("torch", TO);
    int result;

    if (objectp(torch))
    {
        torch->move(ENV(TO));
        result = torch->do_light(str);
        torch->move(TO);

        return result;
    }

    return 0;
}

/*
 * If you try to extinguish the torch in the stand, you will probably succeed.
 * All this function does is call the extinguish function in the torch itself.
 */
int
do_extinguish(string str)
{
    object torch = present("torch", TO);
    int result;

    if (objectp(torch))
    {
        torch->move(ENV(TO));
        result = torch->do_extinguish(str);
        torch->move(TO);

        return result;
    }

    return 0;
}

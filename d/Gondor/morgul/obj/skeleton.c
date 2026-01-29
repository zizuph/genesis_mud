/*
 * /d/Gondor/morgul/obj/skeleton.c
 *
 * The sad remains of a dead orc in a deadend tunnel in
 * Shelob's Lair.
 *
 * Olorin, 1-nov-1993
 * 
 * Modification log:
 * 15-aug-1997, Olorin: General revision.
 */
#pragma strict_types

inherit "/std/object";

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void    add_stuff();
public string  long_desc();

static object  Tied_Rope;

public void 
reset_object()
{
    set_alarm(1.0, 0.0, add_stuff);
}

public void 
add_stuff()
{
    object  env = ENV(TO);

    if (!objectp(Tied_Rope) && 
	(!objectp(env) || !objectp(present("rope", env))))
    {
	seteuid(getuid());
        Tied_Rope = clone_object(MORGUL_DIR + "obj/rope");
        Tied_Rope->move(ENV(TO));
        Tied_Rope->add_prop(OBJ_M_NO_GET,"It is tied too hard.\n");
        Tied_Rope->add_prop(OBJ_M_NO_DROP,"It is tied to hard.\n");
        Tied_Rope->set_tied_to(TO);
        Tied_Rope->set_tied_to_text(short());
        Tied_Rope->set_no_show();
    }
    if (!objectp(env))
        return;
    if (sizeof(FILTER_LIVE(all_inventory(env))))
        return;
    set_no_show();
}
    
public int 
tie_object(object rope, string str)
{
    if (!objectp(Tied_Rope))
    {
        Tied_Rope = rope;
        Tied_Rope->set_no_show_composite(1);
        return 1;
    }
    NF("There is already something tied around the "+short()+".\n");
    return 0;
}

public int 
untie_object(object rope)
{
    NF("There is nothing you can untie here.\n");
    if (!objectp(Tied_Rope))
        return 0;
    if (Tied_Rope->query_no_show())
        Tied_Rope->unset_no_show();
    if (Tied_Rope->query_no_show_composite())
        Tied_Rope->unset_no_show_composite();
    Tied_Rope = 0;
    return 1;
}

public void
create_object()
{
    set_name("skeleton");
    add_name(({"warrior","orc","corpse"}));

    set_short("skeleton of an orc warrior");
    set_long(long_desc);

    set_adj(({"orc"}));
    add_prop(OBJ_I_WEIGHT, 40000);
    add_prop(OBJ_I_VOLUME, 25000);
    add_prop(OBJ_M_NO_GET, "Let him rest in peace, even if he was only an orc!\n");

    set_no_show();

    reset_object();
}

public string 
long_desc()
{
    string  desc =
        "These are the sad remains of what once must have been a large and mighty " +
        "orc warrior. This skeleton is lying on the top of the heap, so it is probably " +
        "the latest addition to the pile of victims in this deadly trap. ";

    if (objectp(Tied_Rope))
        desc += "Still tied around the dead bones is an old rope. He probably used " +
            "it to climb down here. But then either it snapped, or someone up the " +
            "slope cut it. ";

    return BSN(desc);
}

public object query_tied_rope() { return Tied_Rope; }

/*
 *  /d/Genesis/login/new/obj/sign.c
 *
 *  The signpost which prints out the tutorial for new
 *  players in Genesis.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>


/* Global Variables */
public int         Chapter;


/* Prototypes */
public void        create_object();
public string      describe();

public void        set_chapter(int i) { Chapter = i; }

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("sign");
    add_name( ({ "_tutorial_sign" }) );
    add_adj( ({ "large", "mounted", "tutorial" }) );

    set_short("large sign");
    set_long(describe);

    add_item( ({ "post", "signpost" }),
        "The sign is mounted on a sturdy post.\n");

    add_cmd_item( ({ "sign", "large sign",
                     "signpost", "large signpost",
                     "tutorial sign", "large tutorial sign" }),
                  ({ "read" }), describe);

    setuid();
    seteuid(getuid());

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_GET, "The sign is mounted on a sturdy post,"
     + " and cannot be taken.\n");
} /* create_object */


/*
 * Function name:        describe
 * Description  :        give a text description of the plaque
 * Returns      :        string - the description
 */
public string
describe()
{
    return read_file("/d/Genesis/login/death_message", 0);
} /* describe */

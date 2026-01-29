/*
 *  /d/Genesis/login/new/obj/sign.c
 *
 *  A signpost that players get to read when they have finished the
 *  pre-creation tutorial experience.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

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
    set_long("A tutorial sign has been posted here. To see what is written"
      + " on it, you can use the command <read sign>.\n");

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
    object  room = environment(this_object());

    room->summon_portal(this_player());

    return read_file(TEXT_DIR + "pre_creation.txt", 0);
} /* describe */
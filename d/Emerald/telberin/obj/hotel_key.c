/*
 *  /d/Emerald/telberin/obj/inn_key.c
 * 
 *  This key is required to allow players to spend the night
 *  in the Silver Swan Inn in Telberin.
 *
 *      location: /d/Emerald/telberin/arts/inn.c
 *
 *  Copyright (c) March 2003, by Cooper Sherry (Gorboth)
 */
inherit "/std/key";

#include <stdproperties.h>


/*
 * Function name:        create_key
 * Description  :        set up the object
 */
create_key()
{
    ::create_key();

    set_name("key");
    add_name("_the_key_to_the_silver_swan_inn_");
    set_pname("keys");
    set_short("slender alabaster key");
    set_pshort("slender alabaster keys");
    set_adj( ({ "slender", "alabaster" }) );
    set_long("This key is extremely elegant, and looks to have been" 
      + " carved from alabaster. Engraved on the shaft are the words:"
      + " The Silver Swan Inn.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_NO_DROP, "The innkeeper told you to keep the key! You"
      + " had best hang on to it.\n");
} /* create_key */

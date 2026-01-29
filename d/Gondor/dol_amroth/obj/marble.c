/* -*- Mode: C -*-
 * marble.c
 *
 * Skippern 20(c)01
 *
 * a marble block, who is suposed to turn into a statue.
 *
 */
#pragma strict_types

inherit "/std/object";

#include "../defs.h"
#include <stdproperties.h>

/* Prototypes */
public void     chip();

/*
 * Function name:    create_object
 * Description  :    Creates the object
 */
void
create_object()
{
    set_name("DolMarbleBlock");
    set_short("marble block");
    add_name("stone");
    add_name("marble");
    add_name("block");

    add_prop(OBJ_M_NO_GET, "The marble block is to heavy.\n");
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_WEIGHT, (85 * query_prop(OBJ_I_VOLUME) / 10));
    add_prop(OBJ_I_VALUE, (24 * query_prop(OBJ_I_WEIGHT) / 10));

    add_adj("marble");
    add_adj("of");
    add_adj("stone");

    set_long("It is a block of marble. It looks like somebody is " +
	"working on it.\n");
}

/*
 * Function name:    crumble
 * Description  :    Oh, that damn crack!!!!! Now the damn block crumbled.
 */
void
crumble()
{
    object o;
    int i;

    tell_room(environment(this_object()), "Oh no! The marble block crumbled " +
	      "into dust and pieces.\n", 0, this_object());



    for (i = 0; i < (2+random(5)); i++)
    {
	o = clone_object(DOL_OBJ + "m_chip");
	o->add_prop(OBJ_I_VOLUME, random(100)+100);
	o->move(environment(this_object()));
    }

    remove_object();

    return;
}

/*

 * Function name:    chip
 * Description  :    Chips of a piece from the marble block and produces
 *                   pebbels.
 */
public void
chip()
{
    int p = random(125)+75+random(100);
    object o;
  
    if (query_prop(OBJ_I_VOLUME) < 4000)
    {
        crumble();
	return;
    }

    add_prop(OBJ_I_VOLUME, (query_prop(OBJ_I_VOLUME) - p));

    tell_room(environment(this_object()), "A small piece of marble falls " +
	      "off and lands on the ground.\n", 0);

    o = clone_object(DOL_OBJ + "m_chip");
    o->add_prop(OBJ_I_VOLUME, p);
    o->move(environment(this_object()));
}



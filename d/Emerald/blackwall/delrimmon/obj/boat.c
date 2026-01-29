/*
 *  /d/Emerald/blackwall/delrimmon/obj/boat.c
 *
 * This is the boat which has been used by the orcs who have invaded
 * Del Rimmon. It seems unclear as to whether they traveled here in
 * the boat, or simply have used it to travel upstream.
 *
 * Copyright (c) June 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void
create_object()
{
    set_name("boat");
    add_adj( ({ "wooden", "rowing", "row", "large" }) );

    set_short("large wooden boat");
    set_long("Thick wooden planks comprise the hull of this large"
      + " row boat. Metal pivots are in place along the upper keel"
      + " which hold three oars on each side. Inside, long planks"
      + " form benches of sorts, which look as if they could carry"
      + " about fifteen large people.\n");

    add_item( ({ "plank", "planks", "hull", "bottom",
                 "bottom of the boat" }),
        "The wood which comprises the hull of the boat is very"
      + " thick, and is covered with a great deal of mud along the"
      + " bottom of the boat.\n");
    add_item( ({ "mud", "great deal of mud" }),
        "Though dried, the mud suggests that this boat has been used"
      + " in the water lately.\n");
    add_item( ({ "pivot", "pivots", "metal pivot", "metal pivots",
                 "keel", "upper keel" }),
        "Metal pivots along the upper keel hold oars in place for"
      + " rowing this boat.\n");
    add_item( ({ "oar", "oars", "wooden oar", "wooden oars" }),
        "There are a total of six wooden oars in the boat. Three"
      + " line the upper keel along each side, held in place by"
      + " metal pivots.\n");
    add_item( ({ "bench", "benches", "seat", "seats" }),
        "The benches inside the boat look as if they could hold at"
      + " least fifteen large people.\n");

    add_cmd_item( ({ "boat", "wooden boat", "the boat" }),
                  ({ "enter", "climb" }),
        "You climb in the boat and sit down for a bit. The planks feel"
      + " sturdy beneath your feet, and you suspect that this boat"
      + " could still perform its job quite well. Satisfied, you get"
      + " out and stand once more on the outside of the vessel.\n");
    add_cmd_item( ({ "boat", "wooden boat", "the boat" }),
                  ({ "move", "push", "pull" }),
        "The boat is extremely heavy, and you stand no chance of"
      + " moving it anywhere.\n");
    add_cmd_item( ({ "boat", "wooden boat", "the boat" }),
                  ({ "drag" }),
        "You strain with all your strength in an attempt to drag"
      + " the boat, but are unable to move it an inch.\n");
    add_cmd_item( ({ "oar", "oars", "wooden oar", "wooden oars" }),
                  ({ "get", "take", "remove" }),
        "The oars are securely held in place by the metal pivots, and"
      + " you cannot remove them.\n");
    add_cmd_item( ({ "boat", "wooden boat", "the boat" }),
                  ({ "search" }),
        "You poke around the boat, inspecting it closely. Its hull is"
      + " covered with mud, and you notice that it does not appear to"
      + " have been very well treated by its owners. Otherwise, it looks"
      + " fairly unremarkable.\n");

    add_prop(OBJ_I_WEIGHT, 200000);
    add_prop(OBJ_I_VOLUME, 220000);
    add_prop(OBJ_M_NO_GET,
        "The boat is quite massive, and you are not able to move it.\n");
} /* create_object */

/*
 * /d/Gondor/dveirr/sroad/obj/pillar.c
 * Description:   Makes the standard Rathon_gondor road pillar
 * Made by: Stein Eldar Johnsen (Dveirr) (C) May 1999
 */
#pragma strict_types

inherit "/std/object";
inherit "/d/Gondor/common/lib/time.c";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <language.h>
#include <composite.h>

/* Global variables */
public mixed directions = ({});

/* prototypes */
public void      create_object();
public void      add_direction(string dest, string city, string dist);
public void      read_plaque();


/*
 * Function name:  create_object
 * Description:    creates the standard properties and descriptions
 *                 for rathon_gondor_pillar
 */
public void
create_object()
{

    set_short("large pillar");

    add_item( ({ "foot", "basement" }), BSN(
        "The pillar's foot. There is a brass plaque here, surrounded "+
        "by figures carved into the stone."));
    add_item( "top", BSN(
        "the top of the pillar rises about fifteen feet up in the " +
        tod() + " sky."));

    add_item( ({ "carvings", "figures", "figure" }), BSN(
        "The carvings are heavily worn by the weather and variation in "+
        "temperature."));
    add_item( ({ "men", "man", "horse", "man at horse",
                 "large stout horses", "men at horse", "large horses",
                 "stout horses" }), BSN(
        "There are many carvings of men at horse. The men wear a large "+
        "shield and a lance each, riding in formation on large stout "+
        "horses."));
    add_item( ({ "shield", "shields", "lance", "lances", "arms",
                 "armour" }), BSN(
        "The men in the carvings wear heavy arms."));
    add_item( "formation", BSN(
        "The horses rides in a square formation"));

    add_item( ({ "arrow", "arrows" }), BSN(
        "Which arrow do you want to examine?"));
    add_item( ({ "plaque", "copper plaque", "red copper plaque",
                 "red plaque", "text" }),
                  read_plaque );
    add_item( ({ "pattern", "border" }), BSN(
        "The pattern reminds of text in some ancient language, but you "+
        "cannot make any sense out of it."));

    add_cmd_item( ({ "plaque", "copper plaque", "red copper plaque",
                     "red plaque", "text" }),
                     "read",
                      read_plaque );
    add_cmd_item( ({ "arrow", "any arrow" }),
                     "read",
                 BSN("Read on which arrow?"));
    add_cmd_item( ({ "carvings", "figure", "figures" }),
                     "study", BSN(
        "The carvings seem to show men at horse, and the cutting of "+
        "large trees. Toward the top the figures fade away, and some "+
        "eagles are forcefully carved into the stone."));

    set_name(({"Gondor_Pillar"}));
    add_name(({"pillar"}));

    add_adj("large");
    add_adj("tall");

    add_prop(OBJ_I_WEIGHT,30000000);
    add_prop(OBJ_I_VOLUME,30000000);
    add_prop(OBJ_I_VALUE,0);

} /* create_object */


public void
add_direction(string dest, string city, string dist)
{
    directions += ({ ({ dest, city, dist }) });

    add_item( ({ LANG_WORD(sizeof(directions)) + " arrow", dest + " arrow",
                "arrow pointing " + dest }), BSN(
                "The arrow points " + dest + " and has text saying: " +
                "To " + city + ", " + dist + " miles."));
    add_cmd_item( ({ LANG_WORD(sizeof(directions)) + " arrow", dest + " arrow",
                "arrow pointing " + dest }),
             ({ "read" }), BSN(
                "The arrow points " + dest + " and has text saying: " +
                "To " + city + ", " + dist + " miles."));

    set_long("A large pillar set on the side of the road. A"
               + " plaque is placed at its foot, shining in red"
               + " copper from the pale white stone. There " 
               + ((sizeof(directions) == 1) ? "is one arrow" :
                 "are " + LANG_WNUM(sizeof(directions)) + " arrows")
               + " pointing "
               + COMPOSITE_WORDS(map(directions, &operator([])(, 0)))
               + ". The pillar rises at least fifteen feet up in the air.\n");

}


/*
 * Function name:  read_plaque
 * Description:    returns the text on the plaque
 * Returns:        string -- the text
 */
public string
read_plaque()
{
    return BSN(
        "The plaque has a text saying: THIS IS THE RATHON GONDOR, "+
        "IT PASSES DOL AMROTH AND LINHIR BEFORE ENDING IN PELARGIR "+
        "IN THE EAST. It is made of copper and shines of cold metal "+
        "in the " + tod() + ". The plaque is finely carved with "+
        "a strange pattern around the edge.");
} /* read_plaque */


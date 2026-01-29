/*
 *  /d/Emerald/blackwall/delrimmon/obj/raeldu.c
 * 
 *  This is the skeletal remains of Raeldu, who died from a
 *  wound he recieved at the battle with the Darkling Forces.
 *  After seeing his commrades killed, he made his way back
 *  to the Crystal Tower, to finally die from loss of blood.
 *
 *  Copyright (c) August 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public void    create_container();


/*
 * Function name:        create_container
 * Description  :        set up the corpse
 */
public void
create_container()
{
    set_name("skeleton");
    add_name( ({ "body", "corpse", "bone", "bones" }) );
    add_name("corpse_of_raeldu");
    add_adj( ({ "skeletal", "elven", "elf", "male", "armoured" }) );
    set_short("armoured skeleton");
    set_long("An extremely ancient looking skeleton sits propped"
           + " against the southern wall here. Though its flesh"
           + " has long ago deteriorated, the armour and clothing"
           + " which was worn by this unfortunate individual still"
           + " rest mostly intact on the dusty bones. This was"
           + " probably once an elf, though it is difficult to"
           + " tell for sure.\n");

    add_item( ({ "raeldu" }),
        "Could this skeleton be the remains of Raeldu? It seems"
      + " very plausible, indeed.\n");
    add_item( ({ "elf", "human" }),
        "It seems impossible to determine the race of the skeleton,"
      + " though it was almost certainly either human or elf.\n");
    add_item( ({ "armour", "armor", "clothing", "clothes" }),
        "The armour worn by the skeleton looks to be of extremely"
      + " fine make. It is covered with a great deal of dust and"
      + " cobwebs, and has obviously not been disturbed. You notice"
      + " what appears to be a serious gash in the region of the"
      + " abdomen, which was perhaps inflicted by the wound which"
      + " caused the death of this person. You also notice some"
      + " kind of jewelry which rests on the skull.\n");
    add_item( ({ "dust", "cobwebs" }),
        "A great deal of dust and cobwebs have accumulated near"
      + " to a skeleton which rests against the southern wall.\n");
    add_item( ({ "south wall", "southern wall", "south",
                 "wall to the south" }),
        "A skeleton sits propped against the wall to the south.\n");
    add_item( ({ "ghash", "abdomen", "serious ghash" }),
        "There is a ghash ripped in the abdomen of the armour worn"
      + " by the skeleton. It looks as if a large slashing weapon"
      + " tore through the metal into the very belly of the now"
      + " dead individual. Perhaps the wound was not immediately"
      + " fatal, which would explain the sitting position of the"
      + " skeleton.\n");
    add_item( ({ "skull", "head", "head of the skeleton" }),
        "Beautiful jewelry of some kind rests on the skull of the"
      + " skeleton. It shines with a faint magical aura.\n");
    add_item( ({ "torque", "luminous torque",
                 "luminous fair-stoned torque",
                 "luminous crystal torque", "very beautiful torque",
                 "luminous fair-stoned crystal torque",
                 "fair-stoned torque", "beautiful torque",
                 "fair-stoned crystal torque",
                 "crystal torque", "jewelry", "beautiful jewelry" }),
        "A luminous fair-stoned crystal torque is set upon the skull"
      + " of this long-dead individual. It is a truly breathtaking"
      + " piece of jewelry. It appears to pulse with a faint magic"
      + " force of some kind.\n");

    add_cmd_item( ({ "armour", "armor", "clothing", "clothes" }),
                  ({ "get", "take", "remove", "lift", "pick" }),
        "Some strange magical force seems to prevent you from doing"
      + " that.\n");

    add_prop(OBJ_I_WEIGHT, 22000);
    add_prop(OBJ_I_VOLUME, 30000);
    add_prop(CONT_I_WEIGHT, 22000);
    add_prop(CONT_I_MAX_WEIGHT, 26000);
    add_prop(CONT_I_VOLUME, 23000);
    add_prop(CONT_I_MAX_VOLUME, 30000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "Trying to lift the skeleton would only"
                         + " destroy it.\n");

    FIX_EUID

} /* creat_object */

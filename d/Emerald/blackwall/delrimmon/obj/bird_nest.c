/*
 *  /d/Gondor/emyn-mui/obj/bird_nest.c
 *
 *  This is a bird nest which has a 1 in 20 chance of falling from
 *  a tree and ending up in the forest rooms in the Blackwall Mountains.
 *  There is furthermore a small chance that the nest will be filled
 *  with interesting things such as eggs.... or a jewel.
 *
 *  Copyright (c) March 1998, by Cooper Sherry (Gorboth)
 *
 *  Revision Feb 2000 Stern: adapted to genesis gem system
 */
#pragma strict_types
inherit "/std/container";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define GEM_DIR "/d/Genesis/gems/obj/"
#define RIMMON_GEMS     ({ ("quartz"),\
                           ("agate"),\
                           ("jasper"),\
                           ("coral"),\
                           ("turquoise"),\
                           ("amber"),\
                           ("onyx"),\
                           ("carnelian"),\
                           ("garnet"),\
                           ("amethyst"),\
                           ("aquamarine"),\
                           ("jade"),\
                           ("lapis"),\
                           ("opal"),\
                           ("pearl_black"),\
                           ("sapphire"),\
                           ("ruby"),\
                           ("beryl_red"),\
                           ("alexandrite"),\
                           ("diamond"),\
                        })

void  fill_nest();

void
create_container()
{
    set_name("nest");
    add_name( ({"birds nest", "bird's nest"}) );
    add_adj( ({"small"}) );

    set_short("small birds nest");
    set_long(BSN("This is a small nest comprised of moss, grass, and"
            + " tree bark which has been formed into a woven bowl."));

    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_MAX_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(CONT_I_MAX_VOLUME, 900);

    FIX_EUID

    fill_nest();
}

void
fill_nest()
{
    object  gem;

    if (present("egg", this_object()))
    {
        return;
    }

    if (!random(2))
    {
        clone_object(DELRIMMON_DIR + "obj/bird_egg")->move(TO);
        
        if (!random(2))
        {
            gem = clone_object(GEM_DIR + ONE_OF_LIST(RIMMON_GEMS));
            gem->move(TO);
        }
    }
}

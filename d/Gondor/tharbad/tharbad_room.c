/*
 *	/d/Gondor/tharbad/tharbad.c
 *
 *	Master room for Tharbad, using area_room.c
 *
 *	Zephram, Sep 1995
 */
inherit "/d/Gondor/common/lib/new_area_room.c";

#include <language.h>

#include "/d/Gondor/defs.h"

public void
create_tharbad()
{
}

nomask void
create_area_room()
{
    create_tharbad();
}

string
short_desc()
{
    string  desc;

    if (areatype == 12)
    {
        if ((!item_id("ground")) && (!item_id("hill")) && (!item_id("hills"))
            && (!item_id("height")) && (!item_id("heights")))
            add_item(({"ground", "hill", "hills", "height", "heights"}),
                "A few sparse "+treetype+" trees struggle up the lower slopes.\n");
        desc = "the "+mountain+" above "+LANG_ADDART(areadesc)+" in the "
           + area + " parts of "+areaname+" in "+land;
    }
    else
        desc = ::short_desc();

    return desc;
}



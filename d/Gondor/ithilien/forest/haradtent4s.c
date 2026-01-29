/*
 * /d/Gondor/ithilien/forest/haradtent1.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

//inherit "/d/Gondor/std/room";
inherit "/d/Gondor/ithilien/forest/camp";


#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

object	*Haradrim = allocate(3);

public void
create_camp()
{
    add_prop(ROOM_I_INSIDE,1);

    set_short("Inside a Haradrim tent");
    set_long("The canvas roof of this tent is high above you. It is " +
        "cleaner than the other tents and appears to belong to someone " +
        "of importance. A cot and a table are set up in the tent. Some " +
        "clothes are stacked in a corner. A brazier gives off some heat " +
        "and masks the smell of the camp.\n");

    add_item(({ "cot"}), 
	    "The cot is a low bed set against a wall of the tent. It is a " +
        "temporary bed and is easily collapsible. The cot looks more " +
        "comfortable then the bedrolls the soldiers must use.\n");
    add_item("clothing", 
        "The clothing is coloured brightly in reds and yellows and " +
        "other garish colours.\n");
    add_item(({"brazier"}),
        "This is a small, rectangular bowl full of burning coals. It " +
        "provides heat for the tent and masks the odors of the camp.\n");
    add_item(({"coals"}),
        "They are hot and irregular shaped. They burn slowly in the " +
        "brazier and give off heat and a pleasant fragrance.\n");
    add_item(({"table"}),
        "The table is small but sturdy. It is easily broken down and " +
        "yet functional. The table is clean and has a chair next to it.\n");
    add_item(({"chair"}),
        "It is made of wood and easily collapsible. The chair is plain " +
        "looking yet comfortable.\n");  

    add_exit(ITH_DIR+"forest/haradcamp4s","out",0);
    reset_room();
}

public void
reset_room()
{
    ::reset_room();
    make_haradrim(random(3));
}

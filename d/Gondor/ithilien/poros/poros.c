/*
 *   /d/Gondor/ithilien/poros/poros.c
 *
 *   Standard outdoor room for the Poros river area.
 *
 *   Talisan,  December 1995
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

public void
create_poros()
{
}

nomask void
create_area_room()
{
    set_land("Gondor");
    set_areaname("Ithilien");
    set_area("southern");
    set_areadesc("path");
    set_areatype(1);

    create_poros();
}

public void
add_path(string extra = 0)
{
    string  desc =
        "The narrow walkway is little more than a game trail. It seems "
      + "to be rarely used, if at all, and is overgrown in many places "
      + "with scrub and briar.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"path", "ground", "trail", "game trail"}),
        BSN(desc));
}

public void
add_river(string extra = 0)
{
    string  desc =
        "This is the river Poros, a tributary of the mighty Aduin. Its "
      + "source lies somewhere unknown, high in the Ephel Duath. The "
      + "river itself forms the border between Ithilien to its north, "
      + "and Harondor to the south.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"river", "river poros", "poros"}),
        BSN(desc));
}

public void
add_region(string where, string extra = "")
{
    string  desc = "";

    if (where == "one")
        desc += "Beyond the river basin are the plains of Southern "
      + "Ithilien to the north. Scattered woodlands and an occasional hill "
      + "dot this semi-arid land that remains largely uninhabited. Low "
      + "grass and scrub brushes are the main type of vegetation that "
      + "cover the region. Somewhere far to the west lies the great river "
      + "Anduin, while in the distance to the east rises the Ephel Duath "
      + "mountain range. Across the river to the south is the mostly barren "
      + "region of Harondor.";

    else if (where == "two")
        desc += "Scattered woodlands and an occasional hill dot this "
      + "semi-arid land that remains largely uninhabited. Low grass and "
      + "scrub brushes are the main type of vegetation that covers the "
      + "region. Somewhere far to the west lies the great river Anduin, "
      + "while in the distance to the east rises the Ephel Duath mountain "
      + "range. Across the river Poros, somewhere to the south lies the "
      + "mostly barren region of Harondor.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"region", "surrounding region", "plains", "ithilien",
        "southern ithilien", "countryside", "surrounding countryside"}),
        BSN(desc));
}

/*
 *	/d/Gondor/ithilien/nforest/sstream6.c
 *
 *	Coded by Olorin 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include "/d/Gondor/defs.h"

#include <stdproperties.h>

static object  Rabbit,
               Deer;

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("stream");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cypress");
    set_extraline("Cypress and cedar trees and tamarisks grow here in thickets, and " +
    "bushes cling to the mossy crags of the hillside. " +
    "The stream itself has grown to a swift torrent here, entering a narrow gorge here " +
    "so that you cannot follow it any further. " +
    "Looking southwest across the gorge, you can see the Vale of the Anduin "+
    "with its lowlands and broad meads along the wide waters of the river. " +
    "The path to the west is blocked by a dark wide rock rising in the forest.");

    add_exit(ITH_DIR + "nforest/sstream5", "northeast", 0, 4);
    add_exit(ITH_DIR + "nforest/sstream7", "northwest", 0, 4);

    set_up_herbs( ({ HERB_DIR + "tyelka",  HERB_DIR + "astaldo",
		     HERB_DIR + "suranie", HERB_DIR + "sage",
		     HERB_DIR + "mint",    HERB_DIR + "basil", }),
		  ({ "herbs", "flowers", "thickets", "stones", "woods", 
		     "groves"}), 3);

    add_item(({"mountains","mountain-range","mountain","ephel duath"}),BS(
    "From here the mountains named Ephel Duath appear as dark grey shadows beyond the green hills to the east. "+
    "You judge the mountains to be between 5000 to 7000 feet tall, "+
    "and you guess they are several miles away now.\n"));
    add_item(({"forest","wood","woods","herbs","thickets","thicket"}),BS(
    "Many great trees are growing here, planted long ago, falling into untended age amid a riot " +
    "of careless descendants. There are olive and cedar, junipers and cypress, " +
    "sages of many kinds putting forth blue flowers, or red, or pale green; and many other herbs of different " +
    "forms and scents. \n"));
    add_item(({"flower","flowers","primerole","anemones","lily","asphodel"}),BS(
    "Primeroles and anemones are awake in filbert-brakes; asphodel and many lily-flowers are nodding their " +
    "half-opened heads in the grass. \n"));
    add_item(({"gorge", "stream","pool","water"}),BS(
    "The stream has grown to a swift torrent here, leaping down over many stones " +
    "in a deep-cloven bed, overhung with ilex and dark bow-woods. It rushes ever on " +
    "towards the great river in the vale below, but you cannot follow its path into the narrow " +
    "gorge.\n"));
    add_item(({"river","anduin","vale"}), BS(
    "The Vale of the Anduin opens before you to the southwest. You can see lowlands and " +
    "broad meads, and glinting far off the wide waters of the Anduin.\n"));
    add_item(({"rock","hill"}), BS(
    "A dark wide rock blocks both the view and the path to the west. The stream runs in its narrow gorge " +
    "close to the foot of the rock. The sheer cliff face of the rock would make it impossible " +
    "to climb it, even if you managed to cross the gorge. \n"));

    reset_room();
}

public void
reset_room()
{
    set_searched(-random(3));

    Rabbit = clone_npc(Rabbit, NPC_DIR + "rabbit");
    Rabbit->set_restrain_path(ITH_DIR + "nforest/");

    Deer = clone_npc(Deer, NPC_DIR + "deer");
    Deer->set_restrain_path(ITH_DIR + "nforest/");
}

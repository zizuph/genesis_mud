/*
 * /d/Gondor/pelargir/rooms/belfalas09.c
 *
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 * 
 */

#pragma strict_types

inherit "/d/Gondor/pelargir/pelargir_room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/pelargir_room.h"

public void	create_pelargir_room();
public string	long_func();

/*
 * Function name:	create_pelargir_room
 * Description	:	set up the room
 */
public void
create_pelargir_room()
{
    set_part(PART_WEST);
    set_street_name("Belfalas Square");
    set_room_type(TYPE_STREET);

    set_short("in Belfalas Square");
    set_extra_desc("In the center of the square stands a beautiful " +
    	"statue of a great lord of the sea; at his feet, a fleet of " +
        "ships is carved. Most of the traffic here comes from the " +
        "Gates of Pelargir to the north, and the Pelargir docks to " +
        "the east. West of the square is the city hall.");


    add_item(({"statue","lord", "lord of the sea",}), 
        BSN(
        "The statue is carved from finest marble, rising high into " +
        "the sky on its mighty pedestal of black granite. Hewn into " +
        "the granite are letters of an inscription which at one " +
        "time were inlaid with gold, but little remains of it now."));

    add_item( ({ "letters", "inscription", "pedestal", }),
    	"The inscription reads:\n\n" +
        "\t    Ciryaher son of Ciryandil, Hyarmendacil\n\n" +
        "\t    Fifteenth King of Gondor TA 1015 - 1149\n" +
        "\tVictorious in Battle in Endor and on the Belegaer\n" +
        "\t               Conqueror of Harad\n\n" +
        "\t   Lord of Harad, Lord of Umbar, Lord of Rhun,\n" +
        "\tLord of Rhovanion, Lord over Greenwood the Great.\n\n" +
        "\t       Erected in memory of his father by\n" +
        "\t      Atanatar Alcarin son of Hyarmendacil\n" +
        "\t        in the tenth year of his reign.\n\n");

    add_cmd_item(({"letters", "inscription", "pedestal",}),
        "read",
    	"The inscription reads:\n\n" +
        "\t    Ciryaher son of Ciryandil, Hyarmendacil\n\n" +
        "\t    Fifteenth King of Gondor TA 1015 - 1149\n" +
        "\tVictorious in Battle in Endor and on the Belegaer\n" +
        "\t               Conqueror of Harad\n\n" +
        "\t   Lord of Harad, Lord of Umbar, Lord of Rhun,\n" +
        "\tLord of Rhovanion, Lord over Greenwood the Great.\n\n" +
        "\t       Erected in memory of his father by\n" +
        "\t      Atanatar Alcarin son of Hyarmendacil\n" +
        "\t        in the tenth year of his reign.\n\n");

    add_item( ({ "fleet", "ships", "fleet of ships", }),
        BSN("At the feet of the Lord depicted by the statue, " +
        "a fleet of ships was carved from the marble. It shows the ship " +
        "of the fleet which Hyarmendacil led towards Harad to conquer it."));
    add_item("gates", BSN("The gates leading to the road to the Harlond " +
        "and to Minas Tirith are to the north, past the bridge. The " +
        "gates leading to the road to Linhir are to the south."));

    add_item( ({ "hall", "city hall", }),
        BSN(
        "The city hall is a large stone building. In the city hall the " +
        "citizen of Pelargir assemble for festivities or when they are " +
        "summoned by the authorities. The city hall also contains the " +
        "offices of the City Council and the Lord Councillor."));
    add_item( ({ "gate", "city gate", "gate of pelargir" }), BSN(
        "The Gate of Pelargir is far to the north, as one follows"
      + " the length of " + STREET_BELFALAS + " to the boundaries"
      + " of the city."));

    add_exit((PELAR_DIR + "test/belfalas08"),  "north",0);
    add_exit((PELAR_DIR + "test/market01"), "east",0);
    add_exit((PELAR_DIR + "test/belfalas10"), "south",0);
    add_exit((PELAR_DIR + "misc/cityhall"), "west",0);
} /* create_pelargir_room */


/*
 * Function name:	long_func
 * Description	:	VBFC for room long
 * Returns	:	string -- the desc
 *
 */
public string
long_func()
{
    return BSN("In Belfalas Square in the " + Part +
            " parts of Pelargir. It is " + tod() +
            ". " + Extra_desc);
} /* long_func */


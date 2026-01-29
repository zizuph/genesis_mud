/*
 *  /d/Emerald/telberin/west_gate.c
 *
 *  This is the entrance to the City of Telberin.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_street";


/* 
 * Function name:        create_telberin_street
 * Description  :        set up the street room
 */
public void
create_telberin_street()
{
    config_street_room("mercantile",
        "a wide avenue leading from the City Gates");

    set_em_long("You stand on a wide avenue which leads into the city"
      + " from beneath the daunting Main Gate which towers overhead"
      + " directly to the west. The street here is closely guarded"
      + " with a certain portion of the military which has been put"
      + " on full alert in light of recent raids on the city. Guards"
      + " pass to and fro along the cobblestones, and wagons bearing"
      + " various goods make their way in and out of the city.\n");

    add_item( ({ "wide avenue", "here", "area" }), long);
    add_item( ({ "daunting gate", "daunting main gate", "gate",
                 "city gate", "gate of the city", "gates of the city",
                 "main gates of the city", "main gate of the city",
                 "west", "gates", "western gate", "west gate",
                 "western gates of the city", "telberin gates",
                 "gates of telberin", "main gate" }),
        "The Main Gate of Telberin yawns over the city with its"
      + " vast arch concealing a portcullis which is currently raised."
      + " This gate has stood for centuries, serving as the only"
      + " entrance to the city, and thus is heavily fortified with"
      + " battlements and watchtowers which rim the great city wall.\n");
    add_item( ({ "arch", "vast arch", "archway", "arch of the gate" }),
        "The arch of the gate is at least fifty feet in height, and"
      + " contains a huge portcullis which is currently receded into"
      + " the upper region of the main gate.\n");
    add_item( ({ "portcullis" }),
        "The sharp points of a portcullis protrude from beneath the"
      + " upper rim of the archway to the west.\n");
    add_item( ({ "battlement", "battlements", "tower", "watchtower",
                 "watchtowers", "towers" }),
        "A number of fortified areas along the walls provide support"
      + " for the defence of this gate should the need arise. Currently,"
      + " all positions are manned by guards who have been stationed"
      + " at this western gate.\n");
    add_item( ({ "guard", "guards", "military" }),
        "Guards are everywhere you look, manning various stations"
      + " along the wall and road in defence of the entrance to"
      + " Telberin. It would take quite an army to breach this key"
      + " position.\n");
    add_item( ({ "wagon", "wagons", "cart", "carts" }),
        "Wagons and carts are making their way along the avenue"
      + " heading both in and out of Telberin. Though heavily guarded,"
      + " the way of life along this street has not changed.\n");

    add_exit("/d/Emerald/telberin/dock/telberin_gates", "west");
    add_exit("artisans_plaza", "east");
} /* create_telberin_street */

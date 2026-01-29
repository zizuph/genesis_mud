#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

//A room of the school, however is 'open' to observe outside.
inherit POOLBOTTOM_OUT;

void
reset_poolbottom_room()
{
	return;
}

create_poolbottom_room()
{
    set_short("observatory of the school of High Magic");
    set_long("You stand in a large room with a domed ceiling. At the apex " +
       "of the dome is a large open circular skylight, allowing a clear view " +
       "of the sky above. In the centre of the room raised on a circular platform " +
       "of marble is an impressive orrery, showing the relative positions and motions " +
       "of the planets and moons in relation to the sun. Next to it stands a " +
       "celestial sphere, providing a projection of what you should see in the " +
       "night sky.\n");

    add_item(({"circular platform","platform","marble platform","platform of marble","marble"}),
       "In the centre of the room is a circular platform of marble, where an impressive " +
       "orrery and celestial sphere have been placed.\n");

    add_item(({"open circular skylight","skylight","circular skylight","dome","ceiling",
       "domed ceiling","apex","apex of the dome"}),
       "At the apex of the domed ceiling is an open circular skylight. This allows " +
       "skygazers a clear view of the heavens.\n");

    remove_item("sky");
    add_item(({"sky","heavens","stars","constellations"}),"@@sky_desc");

    add_item(({"planets","reorx","chislev","zivilyn","sirrion"}),
         "@@exa_planets");

    add_item(({"celestial sphere","sphere"}),"@@exa_sphere"); 

    add_item(({"orrery","impressive orrery"}),
       "In the centre of the room on a raised marble platform is a detailed orrery, " +
       "an enchanted or sophisticated mechanical model of the solar system. You can " +
       "<examine orrery in detail> if you wish.\n");
    add_item("orrery in detail","@@exa_orrery");

    add_exit(ROOM + "landing","east",0);

    reset_poolbottom_room();
}

string
exa_planets()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Referencing the orrery, in the night sky above you can make out the deep red " +
             "planet Sirrion near the constellation of the Rose. The planet Reorx glows sullenly next " +
             "to the constellation of the Condor, while the planets Chislev and Zivilyn seem to be " +
             "passing near the Infinity constellation.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You cannot make out any planets through the skylight, as the sky is not dark enough.\n";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Referencing the orrery, in the night sky above you can make out the deep red " +
             "planet Sirrion near the constellation of the Rose. The planet Reorx glows sullenly next " +
             "to the constellation of the Condor, while the planets Chislev and Zivilyn seem to be " +
             "passing near the Infinity constellation.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You cannot make out any planets through the skylight, as the sky is not dark enough.\n";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Referencing the orrery, in the night sky above you can make out the deep red " +
             "planet Sirrion near the constellation of the Rose. The planet Reorx glows sullenly next " +
             "to the constellation of the Condor, while the planets Chislev and Zivilyn seem to be " +
             "passing near the Infinity constellation.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You cannot make out any planets through the skylight, as the sky is not dark enough.\n";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You cannot make out any planets through the skylight due to the winter " +
              "storm clouds covering the night sky.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You cannot make out any planets through the skylight, as the sky is not dark enough.\n";
	    break;
	}
	break;
    }
    return str;
}

string
exa_sphere()
{
  return "Standing next to the orrery is a large smooth sphere with the constellations " +
         "of Krynn mapped out on it and named after the old Gods:\n\n" +
         "At the south celestial pole are six stars known as the constellation Book of Souls, " +
         "representing the neutral god of knowledge, Gilean.\n\n" +
         "Circling the Book of Souls are two diametrically opposed constellations - the Valiant " +
         "Warrior representing the good god Paladine, and the Queen of Darkness representing " +
         "the evil goddess Takhisis.\n\n" +
         "Circling at a distance the three constellations of the major gods are the constellations " +
         "of the lesser good and evil old gods:\n" +
         "The Harp constellation - Branchala, the Bard King.\n" +
         "The Phoenix constellation - Habbakuk, the Skylord.\n" +
         "The Bison's Head constellation - Kiri Jolith, the Sword of Justice.\n" +
         "The Rose constellation - Majere, the Dreamsender.\n"+
         "The Infinity constellation - Mishakal, the Light Bringer.\n"+
         "The Goat's Skull constellation - Chemosh, Lord of Bones.\n"+
         "The Broken Scale constellation - Hiddukel, Prince of Lies.\n" +
         "The Diseased Hood constellation - Morgion, the Black Wind.\n" +
         "The Condor constellation - Sargonnas, the Bull God.\n" +
         "The Dragon Turtle constellation - Zeboim, the Sea Witch.\n";
}


string
exa_orrery()
{
   return "The orrery is a fascinating model of the solar system. Whether it is a true reflection, " +
      "the dreamchild of a kender, or a madman's fanciful creation you have no idea.\n\n" +
      "In the centre of the orrery is the sun. Orbiting the sun are six planets:\n\n" +
      "The first planet orbiting the sun seems to be a fire body named Sirrion - after " +
      "the neutral god of fire.\n\n"+
      "The second planet is an earth body depicted as having steep mountains and deep chasms. " +
      "It is named Reorx, after the neutral god of creation. Reorx has one moon orbiting it, " +
      "Ora - the Hammer.\n\n"+
      "The third planet is Krynn, depicted as a water body with two large continents " +
      "- Ansalon in the southern hemisphere and Taladas in the northern hemisphere - " +
      "and a handful of smaller landmasses and islands. Orbiting Krynn are three moons named after " +
      "the three gods of magic -  Nuitari, Lunitari, and Solinari.\n\n"+
      "The fourth planet is depicted as a jungle planet named Chislev after the neutral " +
      "goddess of the wild.\n\n"+
      "The fifth planet is depicted as a gaseous planet containing continent-sized boulders - " +
      "a shattered world perhaps? - named Zivilyn the neutral god of wisdom.\n\n"+
      "The sixth planet is a mysteriously undepicted planet named Nehzmyth.\n\n"+
      "Beyond the six planets orbit a cluster of asteroids referred to as the Stellar Islands.\n";
}


string
sky_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight and the sky is clear above you. You can clearly make out through the " +
            "skylight the constellation of the Book of Souls, but disturbingly the constellations " +
            "of the Queen of Darkness and the Valiant Warrior are missing. " + moon_desc();
	    break;
	case NIGHT:
	    str = "It is night and the sky is clear above you. You can clearly make out through the " +
            "skylight the constellation of the Book of Souls, but disturbingly the constellations " +
            "of the Queen of Darkness and the Valiant Warrior are missing. " + moon_desc();
	    break;
	case EARLY_MORNING:
	    str = "Through the skylight you see the sky starts to lighten as the " +
            "sun sheds its first rays for the day.\n";
	    break;
	case MORNING:
	    str = "The sun's morning rays spill down through the skylight above you.\n";
	    break;
	case NOON:
	    str = "Through the skylight the sun shine down upon you.\n";
	    break;
	case AFTERNOON:
	    str = "Shadows lengthen in the observatory as the sun begins to descend from the heavens. " +
            "The sky above you begins to darken as night approaches.\n";
	    break;
	case EVENING:
	    str = "Through the skylight you notice the evening sun begins its descent beyond the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the sun sets.\n";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night and the sky is clear above you. You can clearly make out through the " +
            "skylight the constellation of the Book of Souls, but disturbingly the constellations " +
            "of the Queen of Darkness and the Valiant Warrior are missing. " + moon_desc();
	    break;
	case EARLY_MORNING:
	    str = "Looking through the skylight you notice the stars have retreated as " +
            "the sun's first rays appear over the horizon.\n";
	    break;
	case MORNING:
	    str = "The sun's morning rays spill down through the skylight above you.\n";
	    break;
	case NOON:
	    str = "Through the skylight the sun shine down upon you.\n";
	case AFTERNOON:
	    str = "Shadows lengthen in the observatory as the sun begins to descend from the heavens. " +
            "The sky above you begins to darken as night approaches.\n";
	    break;
	case EVENING:
	    str = "Through the skylight you notice the evening sun begins its descent beyond the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the sun sets.\n";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night and the sky is clear above you. You can clearly make out through the " +
            "skylight the constellation of the Book of Souls, but disturbingly the constellations " +
            "of the Queen of Darkness and the Valiant Warrior are missing. " + moon_desc();

	    str = "While black clouds gather in the sky to the north, the night sky above you is clear. " +
            "Through the skylight you can make out the constellation of the Book of Souls, but disturbingly " +
            "the constellations of the Queen of Darkness and the Valiant Warrior are missing. " + 
            "The light from the silver moon Solinari and the smaller moon Lunitari illuminate the floor, " +
            "casting eerie pale red shadows around you.\n";
	    break;
	case EARLY_MORNING:
	    str = "Looking through the skylight you notice the stars have retreated as " +
            "the sun's first rays appear over the horizon.\n";
	    break;
	case MORNING:
	    str = "The cool rays of the morning sun shine through the skylight above you.\n"; 
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The cool rays of the sun shine through the skylight above you.\n";
	    break;
	case EVENING:
	    str = "Through the skylight you notice the evening sun beginning its descent " +
	    "beyond the horizon, and the skies darkening as night approaches.\n";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Looking through the skylight above you a jagged fork of lightning " +
            "illuminates the night sky, briefly revealing roiling black clouds " +
            "above you. A mighty clap of thunder echoes around the observatory's stone " +
            "walls, however surprisingly you feel none of the storms rage pass through " +
            "the open skylight.\n";
	    break;
	case EARLY_MORNING:
	    str = "Through the skylight above you black storm clouds roll ominously, " +
            "covering the sky from view.\n";
	    break;
	case MORNING:
	    str = "Looking through the skylight, winter clouds block your view of the morning sky.\n";
	    break;
	case NOON:
	    str = "Looking through the skylight, winter clouds block your view of the sky.\n";
	    break;
	case AFTERNOON:
	    str = "Looking through the skylight, winter clouds block your view of the afternoon sky.\n";
	    break;
	case EVENING:
	    str = "Looking through the skylight, winter clouds block your view of the evening sky. " +
            "In the distance the echo of " +
            "thunder makes its way to you from the gathering of angry black clouds in " +
	    "the north, harkening another winter storm on the way.\n";
	    break;
	}
	break;
    }
    return str;
}
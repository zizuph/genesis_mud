/*
 *  /d/Gondor/minas/lib/street_funcs.c
 *
 *  Functions that contain base-room repeats for Minas Tirith rooms.
 *
 *  Alto 15 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/lib/street.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/w/alto/minas"


/* These are add_items that are common to all streets in the city */

void
add_street_items()
{
    add_item(({"building", "buildings", "pavements", "halls", "doorway"}),
        "Many great Men and kindreds "
        + "once dwelt here. Now many buildings are silent, and no footsteps "
        + "ring on their wide pavements, nor are voices heard in their "
        + "halls.\n");
    add_item(({"window", "windows"}), "Many great houses in the city have "
        + "been left vacant in its latter days. Although you "
        + "see many windows facing the street, most are empty with no faces "
        + "looking through them.\n");
    add_item(({"citizen", "citizens"}), "The men of Gondor can be seen "
        + "moving through the streets. Most are wearing armour and have "
        + "grim faces. They have the look of people bracing for a storm.\n");
    add_item(({"sky", "clouds"}), "The walls and buildings block much of "
        + "the sky from view. The western sky, however, is dominated by "
        + "Mount Mindolluin. The eastern sky seems filled with black "
        + "clouds.\n");
    add_item(({"western sky"}), "It is dominated by Mount Mindolluin.\n");
    add_item(({"eastern sky"}), "It is filled with black clouds.\n");
    add_item(({"mountain", "mount mindolluin"}), "The city of Minas Tirith "
        + "is built upon its eastern knee. It dominates the western sky.\n");
    add_item(({"street", "stones"}), "The street is cobbled with large "
        + "smooth stones. Although the streets of Minas Tirith have endured "
        + "millenia of use, they are well-maintained.\n");
    add_item(({"minas tirith", "city"}), "Around you rises the great city "
        + "of Minas Tirith, seat of Gondor, Tower of the Guard. It faces "
        + "to the east, ever vigilant against the darkness there.\n");
    add_item(({"moon"}), "It rides through the night sky, a great white "
        + "face in the darkness.\n");
    add_item(({"sun"}), "A big yellow ball of light. It keeps you from "
        + "bumping into dangerous corners and other sharp objects.\n");
    add_item(({"drops", "rain drops", "raindrops"}), "The first drops of "
        + "looks to be a mighty storm are beginning to fall upon the city.\n");


}


/* These are add_items that are common to all streets in the sixth-circle */

void
add_sixth_circle_items()
{
    add_item(({"sixth wall"}), "This is the sixth wall of Minas Tirith. "
        + "Unlike the "
        + "outer walls, this wall forms a complete circle around the "
        + "inner parts of the city.\n");
    add_item(({"tower", "white tower", "tower of ecthelion"}), "From here "
        + "only the pinnacle of the Tower of Ecthelion can be seen.\n");
    add_item(({"pinnacle", "banner"}), "From the top of the tower flies "
        + "the great banner of the Stewards.\n");
    add_item(({"sixth circle", "circle"}), "This is the Sixth Circle of "
        + "Minas Tirith.\n");
    add_item(({"fifth circle", "seventh circle"}), "It lies on the other "
        + "side of the wall.\n");

}


/* These are add_items that are common to all rooms of the Rath Dinen */

void
add_rath_dinen_items()
{
    add_item(({"path", "street", "rath dinen", "silent street"}),
        "The thick fog makes it very hard to see the path or its "
        + "surroundings.\n");
    add_item(({"pebbles", "white pebbles"}), "Although you can feel "
        + "them crunching beneath your feet, it is very difficult "
        + "to see them through the fog.\n");
    add_item(({"surface"}), "Dropping to your hands and knees, you "
        + "explore the path by sense of touch. The pebbles appear to "
        + "be undisturbed ahead of you, and displaced only by your own "
        + "footprints from behind.\n");
    add_item(({"hedge", "tall hedge"}), "You cannot see the hedge through "
        + "the fog, but reaching out you can feel it on either side of "
        + "the path.\n");
    add_item(({"hallows", "house of stewards", "house of kings"}),
        "The fog makes it impossible to see even the length of your "
        + "arms held blindly in front of you, or the path beneath your "
        + "feet. No matter how hard you try, you cannot see things "
        + "further away.\n");
    add_item(({"gravel"}), "It feels like small rounded pebbles.\n");
    add_item(({"shadow"}), "Maybe it was just your imagination.\n");
    add_item(({"sky"}), "It is up there somewhere, but you cannot see "
        + "it through the fog.\n");
    add_item(({"mountain", "mount mindolluin"}), "It looms as a darker "
        + "shadow through the fog above you.\n");
    add_item(({"clouds"}), "They appear to be gathering in the "
        + "eastern sky and form a darker shadow through the fog to "
        + "the east.\n");
    add_item(({"hand"}), "You must have imagined it.\n");
    add_item(({"fog", "mist"}), "The fog has grown so thick that you "
        + "cannot even see your hands before your face.\n");

}


/* These are add_tells that are common to all streets in the city */

void
add_street_tells()
{
    add_tell("A window closes somewhere nearby.\n");
    add_tell("A citizen passes swiftly by.\n");
    add_tell("Quiet voices can be heard from one of the buildings.\n");
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("Wind whistles through an empty doorway.\n");
    add_tell("The street grows quiet.\n");
    add_tell("A few drops of rain spatter here and there on "
        + "the street.\n");
    add_tell("Marching feet can be heard beyond the wall.\n");
    add_tell("A soldier enters a nearby building.\n");
    add_tell("Dust blown up by a sudden breeze moves around your feet.\n");
    add_tell("A carrier pigeon darts by overhead.\n");
}

/* These are add_tells that are common to all streets in the sixth-circle */

void
add_sixth_circle_tells()
{
    add_tell("A carrier-pigeon flies overhead from the direction of "
        + "the tower and disappears over the sixth wall.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");


}


/* These are add_tells that are common to all rooms of the Rath Dinen */

void
add_rath_dinen_tells()
{
    add_tell("A few drops of rain spatter on your shoulders.\n");
    add_tell("A shadow crosses the hedge to your left. When you turn "
        + "to look it is gone.\n");
    add_tell("Wind howls mournfully down the path, churning the fog.\n");
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Something rustles in the hedge to your right.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("You hear the sound of gravel crunching underfoot "
        + "somewhere nearby.\n");
    add_tell("Lightning flashes in the distant east.\n");
    add_tell("Low voices can be heard whispering somewhere nearby.\n");
    add_tell("Someone moans.\n");
    add_tell("Suddenly the noises cease. The silence is thick with "
        + "unseen menace.\n");
    add_tell("You feel a hand on your shoulder.\n");
    add_tell("A mighty warhorn can be heard in the distance.\n");
    add_tell("The air grows noticeably colder.\n");
    add_tell("You feel a presence behind you.\n");
    add_tell("You hear a small child crying somewhere nearby.\n");
    add_tell("Something groans. You feel certain it came from the "
        + "other side of the hedge.\n");
    add_tell("The wind suddenly stops. Everything is quiet.\n");
    add_tell("The mist grows even thicker.\n");

}

/* These are add_tells that are common to the tunnels of Minas Tirith */

void
add_tunnel_tells()
{
    add_tell("A citizen passes swiftly by.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("A sudden gale blows through the tunnel from the north.\n");
    add_tell("The tunnel suddenly grows quiet.\n");
    add_tell("Footsteps echo from the north end of the tunnel.\n");
    add_tell("Footsteps echo from the south end of the tunnel.\n");
    add_tell("Marching feet can be heard outside the tunnel.\n");
    add_tell("A rat scurries away into the shadows.\n");
}

/* These are add_items that are common the tunnels of Minas Tirith */

void
add_tunnel_items()
{
    add_item(({"citizen", "citizens"}), "The men of Gondor can be seen "
        + "moving through the streets. Most are wearing armour and have "
        + "grim faces. They have the look of people bracing for a storm.\n");
    add_item(({"street", "stones", "passage", "tunnel"}), "The street is "
        + "cobbled with large "
        + "smooth stones. Although the streets of Minas Tirith have endured "
        + "millenia of use, they are well-maintained.\n");
    add_item(({"sky", "clouds"}), "These kinds of things are generally "
        + "very difficult to see when you are inside a tunnel.\n");
    add_item(({"wall", "walls"}), "The walls of the tunnel arch over "
        + "your head. They are smooth with the passage of many years. "
        + "Attached to the white stone walls is an iron torch stand.\n");
    add_item(({"rock", "pier", "bastion"}), "The rock of the bastion "
        + "is all around you. It is white and worn smooth from many "
        + "years of use.\n");
}


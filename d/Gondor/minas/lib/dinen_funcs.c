/*
 *  /d/Gondor/minas/lib/dinen_funcs.c
 *
 *  Functions that contain base-room repeats for non-street Minas Tirith rooms.
 *
 *  Alto 15 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

#define INNER_MINAS "/w/alto/minas"

public int  test_obv();


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
    add_item(({"mountain", "mount mindolluin", "hill"}), "It looms as "
        + "a darker "
        + "shadow through the fog above you.\n");
    add_item(({"clouds"}), "They appear to be gathering in the "
        + "eastern sky and form a darker shadow through the fog to "
        + "the east.\n");
    add_item(({"hand"}), "You must have imagined it.\n");
    add_item(({"fog", "mist"}), "The fog has grown so thick that you "
        + "cannot even see your hands before your face.\n");

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

/* These are add_items that are common to all stairs on the battlement */

void
add_battlement_items()
{
    add_item(({"stairs", "flight", "steps"}), "Great steps are cut into "
        + "the rock of the bastion. It looks like quite a climb from down "
        + "here, but the view from the Battlement is well worth the climb.\n");
    add_item(({"battlement", "bastion", "stone", "peak"}), "Partly from "
        + "the primeval "
        + "shaping of the hill, partly from the mighty craft and labour of "
        + "old, the towering bastion of stone stands up from the First Gate, "
        + "rising up even to the level of this, the Seventh Circle. It is "
        + "crowned with a battlement that can be reached by climbing the "
        + "wide flight of stairs before you.\n");
    add_item(({"first gate"}), "It lies far below and six great circles "
        + "of the city outward. Although it cannot be seen from this landing, "
        + "it can be looked straight down upon from the Battlement atop "
        + "the great bastion of stone.\n");
    add_item(({"darkness", "grey darkness"}), "From the east, dark clouds "
        + "creep ever westward, seeking to blot all light from the sky.\n");
    add_item(({"clouds", "sky"}), "Although the sky is clear to the west, "
        + "where Mount Mindolluin rises high above the city, "
        + "great clouds appear to be drawing ever closer from the east. A "
        + "storm will soon fall upon Minas Tirith.\n");
    add_item(({"mountain", "mount mindolluin", "hill"}), "Rising "
        + "behind the "
        + "White Tower is the dark mass of Mount Mindolluin. The deep "
        + "purple shadows of its high glens and its tall face "
        + "are so large that you cannot take it all in at a single "
        + "glance.\n");
    add_item(({"glens", "face"}), "The mountain towers so huge about "
        + "the Citadel that you get dizzy looking up at it.\n");
    add_item(({"tower", "tower of ecthelion", "white tower"}), "The White "
        + "Tower of Ecthelion spikes fifty fathoms high into the sky in the "
        + "center of the Citadel. It looks as though it is made "
        + "of pearl and silver, and its pinnacle glitters as if "
        + "wrought of crystals.\n");
    add_item(({"pinnacle"}), "With a sense of vertigo, your eyes rise "
        + "to the heights of the White Tower. Just before you look "
        + "away, you think you notice a strange flash of light from "
        + "inside its highest east-facing window.\n");
    add_item(({"window"}), "There are many windows about the Citadel. "
        + "The only one that catches your interest is the highest window "
        + "in the Tower of Ecthelion.\n");
    add_item(({"highest window"}), "There it is again, a strange flash "
        + "of bright light. Who knows what secrets are to be found in "
        + "the ancient rooms high in the tower?\n");
    add_item(({"banner", "banner of the stewards"}), "The great banner of "
        + "the Stewards is raised atop the pinnacle "
        + "of the tower. It floats a thousand feet above the plain "
        + "before the city.\n");
    add_item(({"plain"}), "The large open land before the city cannot "
        + "be seen over the bastion from here. A better view might be "
        + "gained on the Battlement at the top of the stairs.\n");
    add_item(({"gull", "gulls"}), "White seagulls with broad wingspans "
        + "circle and glide through the skies here. In times past, the "
        + "folk of Minas Tirith would provide corn for them to eat. Of "
        + "late, however, food is kept carefully stored and guarded "
        + "in the event of siege.\n");
    add_item(({"seventh circle", "citadel"}), "The innermost "
        + "circle of Minas Tirith "
        + "lies below and to the west of the bastion. In its center stands "
        + "the White Tower of Ecthelion.\n");
    add_item(({"minas tirith", "city"}), "Around you rises the great city "
        + "of Minas Tirith, seat of Gondor, Tower of the Guard. It faces "
        + "to the east, ever vigilant against the darkness there.\n");
    add_item(({"moon"}), "It rides through the night sky, a great white "
        + "face in the darkness.\n");
    add_item(({"sun"}), "A big yellow ball of light. It keeps you from "
        + "bumping into dangerous corners and other sharp objects.\n");
    add_item(({"drops", "rain drops", "raindrops"}), "The first drops of "
        + "looks to be a mighty storm are beginning to fall upon the city.\n");
    add_item(({"pavement"}), "It lies below your feet and is made from the "
        + "native stone of Mount Mindolluin.\n");

}


/* These are add_tells common to the stair rooms of the battlement */

void
add_battlement_tells()
{
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("A gust of crisp mountain wind blows through your hair.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("The low sounds of Minas Tirith can be heard from below.\n");
    add_tell("The banner of the Stewards snaps in the wind high atop the "
        + "White Tower.\n");
    add_tell("A sentry passes swiftly by in the direction of the tower.\n");
    add_tell("A few drops of rain spatter here and there on the pavement.\n");
    add_tell("Marching feet can be heard somewhere below.\n");
    add_tell("A trumpet call can be heard ringing on the plain.\n");
    add_tell("White gulls wheel and cry above the bastion.\n");
    add_tell("A gull hovers nearby but then climbs away and upward.\n");
}


/* These are add_items common to the lane rooms around the White Tower */

void
add_lane_items()
{
    add_item(({"lane"}), "The lane is so narrow that three men would "
        + "have difficulty walking abreast here. It is paved with octagonal "
        + "blocks of white native stone.\n");
    add_item(({"octagonal blocks", "blocks", "stone", "native stone"}),
        "Most of the structures here have been made with native stone "
        + "quarried in the foothills of Mount Mindolluin. The lane is "
        + "paved with octagonal blocks of the white stone. The Tower also "
        + "appears to be made of the same material, but it appears "
        + "to be constructed from one colossal piece of stone. Its "
        + "smooth and unbroken surface shows no sign of break or mortar.\n");
    add_item(({"base", "tower", "white tower", "white tower of ecthelion"}),
        "The White "
        + "Tower of Ecthelion spikes fifty fathoms high into the sky. "
        + "Although from a distance it looks as though it is made "
        + "of pearl and silver, from here it can be seen to be "
        + "constructed entirely of white native stone. You are so "
        + "close to it that the great banner of "
        + "the Stewards can no longer be seen flapping in the breeze. "
        + "Now and then, however, it can be heard snapping against "
        + "the wind gathering in the east.\n");
    add_item(({"surface"}), "The surface of the tower is smooth and "
        + "unblemished. As unbelievable as it may seem, you can find no "
        + "evidence that it is made from more than a single piece of stone.\n");
    add_item(({"pinnacle"}), "With a sense of vertigo, your eyes rise "
        + "to the heights of the White Tower. Just before you look "
        + "away, you think you notice a strange flash of light, but you "
        + "are too close to make out where it came from.\n");
    add_item(({"hedge", "curved hedge", "evergreen hedge"}), "Standing "
        + "several feet higher "
        + "than even the tallest of men, the evergreen hedge encircles "
        + "the White Tower at its base. It has been kept well-tended and "
        + "groomed by the Master Gardener of the city and his crew. It "
        + "is broken only by the Court of the Fountain to the east of the "
        + "tower.\n");
    add_item(({"mountain", "mount mindolluin"}), "Dwarfing the western sky "
        + "is the dark mass of Mount Mindolluin. The deep "
        + "purple shadows of its high glens and its tall face "
        + "are so large that you cannot take it all in at a single "
        + "glance.\n");
    add_item(({"glens", "face"}), "The mountain towers so huge about "
        + "the area that you get dizzy looking up at it.\n");
    add_item(({"sky"}), "The sky is dominated by the tower rising before "
        + "you and the massive mountain to the west. To the east, dark "
        + "clouds are gathering.\n");
    add_item(({"clouds", "thunderheads"}), "The eastern sky seems to grow "
        + "darker by the minute as massive black thunderheads gather in the "
        + "distance.\n");
    add_item(({"court of the fountain", "fountain"}), "The Court of the "
        + "Fountain cannot be seen from here, but the fountain can be "
        + "heard as it plays in the distance.\n");
    add_item(({"wall", "walls"}), "The wall rising beyond the hedge "
        + "completely encloses the "
        + "Citadel. The dull murmur of city life rises from the six circles "
        + "descending beyond it.\n");
    add_item(({"bird", "birds"}), "A number of birds seem to have made "
        + "a home out of the encircling hedge. Now and then one will suddenly "
        + "take flight and dark across the lane.\n");
    add_item(({"chipmunk"}), "These small brown rodents with white stripes "
        + "across their backs can now and then be seen peeking out of the "
        + "hedge.\n");
    add_item(({"minas tirith", "city"}), "Around you rises the great city "
        + "of Minas Tirith, seat of Gondor, Tower of the Guard. It faces "
        + "to the east, ever vigilant against the darkness there.\n");
    add_item(({"moon"}), "It rides through the night sky, a great white "
        + "face in the darkness.\n");
    add_item(({"sun"}), "A big yellow ball of light. It keeps you from "
        + "bumping into dangerous corners and other sharp objects.\n");
    add_item(({"drops", "rain drops", "raindrops"}), "The first drops of "
        + "looks to be a mighty storm are beginning to fall upon the city.\n");
    add_item(({"pavement"}), "It lies below your feet and is made from the "
        + "native stone of Mount Mindolluin.\n");


}

/* These are tells common to the lane rooms around the White Tower */

void
add_lane_tells()
{
    add_tell("Dark clouds drift across the sky from the east.\n");
    add_tell("Crisp mountain wind whispers through the lane.\n");
    add_tell("Thunder rumbles in the distance.\n");
    add_tell("The low sounds of Minas Tirith rise from below the "
        + "encircling walls.\n");
    add_tell("The banner of the Stewards snaps in the wind high "
        + "above.\n");
    add_tell("A bird rustles suddenly in the hedge.\n");
    add_tell("A few drops of rain spatter here and there on the pavement.\n");
    add_tell("Marching feet can be heard somewhere to the east.\n");
    add_tell("Footsteps can be heard retreating just around the curve of "
        + "the tower.\n");
    add_tell("A chipmunk dashes across the lane and scurries beneath "
        + "the hedge.\n");
    add_tell("Lightning flashes in the eastern sky.\n");
}


/* These items are common to the stairs inside the White Tower */

void
add_stair_items()
{
    set_short("Stairwell in the White Tower");
    set_long("This stairwell has hundreds of steps and rises fifty "
        + "fathoms in a spiral around the inside of the tower wall.\n");
    add_item(({"stairwell", "stairs", "steps", "tower", "spiral"}), 
        "Many broad steps "
        + "climb up from this place. They hug the inside wall of the "
        + "tower in a tight spiral.\n");
    add_item(({"wall", "walls", "tower wall", "stone", "native stone"}), 
        "The wall is made of smooth white native stone.\n");


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, -1);
}

/*
 * Function name: test_obv
 * Description:   compare player's location sense to random number
 * Returns:       add_exit flag 0/1
 */
public int
test_obv()
{
    if (TP->query_skill(SS_LOC_SENSE) >= random(50))
        return 0;
    else
        return 1;
}


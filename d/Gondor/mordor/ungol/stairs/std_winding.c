/*
 * /d/Gondor/mordor/ungol/stairs/std_winding.c
 *
 * This file is the default file for the Winding Stair leading to Torech
 * Ungol, Shelobs lair. It defines several functions that are very handy,
 * allowing me to keep the actual room files to the absolute minimum.
 *
 * /Mercade, 21 November 1993
 *
 * Revision history:
 *
 *    Toby, 10th-Sept-2007: Added terrain.h
 *
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <terrain.h>

#define LIVE_I_I_RECOGNIZED_THE_TOWER_FROM_THE_STAIR \
      "_live_i_i_recognized_the_tower_from_the_stair"
#define AWARENESS_NEEDED_TO_SEE_TOWER 35

/*
 * Global variable;
 */
int do_red_light; /* Whether messages about the red light should be added. */
int red_light_alarm;

/*
 * Function name: add_cliff
 * Description  : This function add description of the cliff on the south
 *                side of the path on the Winding Stair.
 */
void
add_cliff()
{
    switch(random(4))
    {
    case 0:
	add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	    BSN("The walls on either side of the stairs make you feel a " +
	    "little secure for they give you some hold."));
	break;
    case 1:
	add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	    BSN("Ever as the stair cuts its way deeper into the sheer " +
	    "mountain the rocky walls rise higher and higher above your " +
	    "head."));
	break;
    case 2:
	add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	    BSN("The walls on either side of the stairs are very steep. " +
	    "There is no way to climb them. The stair is the only way to " +
	    "get up to whichever perils may lay beyond it."));
	break;
    case 3:
    default:
	add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	    BSN("The walls these stair is cut out of is rather smooth. " +
	    "However there are some ruggednesses that give you some hold " +
	    "in your struggle with the stairs."));
	add_item( ({ "ruggedness", "ruggednesses", "bulge", "bulges" }),
	    BSN("There are several bugles or ledges that an experienced " +
	    "climber might use to get some hold other than on the stairs " +
	    "themselves."));
    }
}

/*
 * Function name: add_wall
 * Description  : This function add description of the walls on either side
 *                of the path on the Winding Stair.
 */
void
add_wall()
{
    string str;

    if (do_red_light == 1)
    {
	switch(random(4))
	{
	case 0:
	    str = "The walls on either side of the ravine make you feel a " +
		"little secure they prevent you from falling into great " +
		"depth.";
	    break;
	case 1:
	    str = "Ever as the stair cuts its way deeper into the sheer " +
		"mountain the rocky walls rise higher and higher above your " +
		"head.";
	    break;
	case 2:
	    str = "The walls on either side of the ravine are very steep. " + 
		"There is no way to climb them. The stair is the only way " +
		"to get up to whichever perils may lay beyond it.";
	    break;
	case 3:
	default:
	    str = "The walls along the ravine are rocky and steep. The " +
		"only way to leave it is on the north of the south side.";
	}
    }
    else
    {
	switch(random(4))
	{
	case 0:
	    str = "The walls on either side of the stairs make you feel " +
		"a little secure for they give you some hold.";
	    break;
	case 1:
	    str = "Ever as the stair cuts its way deeper into the sheer " +
		"mountain the rocky walls rise higher and higher above your " +
		"head.";
	    break;
	case 2:
	    str = "The walls on either side of the stairs are very " +
		"steep. There is no way to climb them. The stair is the only " +
		"way to get up to whichever perils may lay beyond it.";
	    break;
	case 3:
	default:
	    str = "The walls along the ravine are rocky and steep. The " +
		"only way to leave it is on the north of the south side.";
	}
    }

    if (strlen(str))
    {
	add_item( ({ "wall", "walls", "rocky wall", "rocky walls" }),
	    BSN(str));
    }
}

/*
 * Function name: add_mountain
 * Description  : This function adds some add_items to this room.
 */
void
add_mountain()
{
    add_item( ({ "rocky mountains" }),
	BSN("Aren't they somewhere else?"));

    switch(random(4))
    {
    case 0:
	add_item( ({ "mountain", "rocky mountain" }),
	    BSN("The mountain the stair is hewn out of is a part of the " +
	    "Mountains of Shadow, also known as Ephel Duath."));
	break;
    case 1:
	add_item( ({ "mountain", "rocky mountain" }),
	    BSN("The mountain rises high over your head. Inside this cleft " +
	    "all you can see is dark rock."));
	break;
    case 2:
	add_item( ({ "mountain", "rocky mountain" }),
	    BSN("You are deep inside the Mountains of Shadow, Ephel Duath. " +
	    "The stairs lead up into the mountains, in the direction of the " +
	    "Nameless Land."));
	break;
    case 3:
    default:
	add_item( ({ "mountain", "rocky mountain" }),
	    BSN("You are inside a narrow chasm in the Mountains of Shadow, " +
	    "Ephel Duath."));
    }

    switch(random(4))
    {
    case 0:
	add_item( ({ "rock", "rocks", "stone", "stones" }),
	    BSN("The solid rock walls are smooth and steep. The there are " +
	    "some small rocks, or rather fragments or stone, on the steps."));
	break;
    case 1:
	add_item( ({ "rock", "rocks", "stone", "stones" }),
	    BSN("You are standing on solid rock... In fact you are " +
	    "surrounded by stone walls and the cleft is so small you cannot " +
	    "see entrance nor exit."));
	break;
    case 2:
	add_item( ({ "rock", "rocks", "stone", "stones" }),
	    BSN("Little rocks are on the stone steps. They make the steps " +
	    "less smooth than they actually are, but when you climb you are " +
	    "likely to kick them down maybe hurting those that are down."));
	break;
    case 3:
    default:
	add_item( ({ "rock", "rocks", "stone", "stones" }),
	    BSN("The rocky steps look strong, yet they are worn and some " +
	    "are broken."));
    }
}

/*
 * Function name: add_stair
 * Description  : This function adds the add_items on the stair to the room.
 */
void
add_stair()
{
    switch(random(4))
    {
    case 0:
	add_item( ({ "stair", "stairs", "stairway", "straight stair" }),
	    BSN("The stairway is almost at steep as a ladder. It is hewn " +
	    "out of the rocky mountain, leading up, deep into the mountain."));
	break;
    case 1:
	add_item( ({ "stair", "stairs", "stairway", "straight stair" }),
	    BSN("The stair consists of numerous steps. There is no way to " +
	    "tell when this stair will come to an end."));
	break;
    case 2:
	add_item( ({ "stair", "stairs", "stairway", "straight stair" }),
	    BSN("On one side, the stair goes up high into the mountain and " +
	    "on the other side it is a long way down. Better make sure you " +
	    "do not fall."));
	break;
    case 3:
    default:
	add_item( ({ "stair", "stairs", "stairway", "straight stair" }),
	    BSN("Steps. Lots of steps, hewn out of the rocky mountain. That " +
	    "is all there is to this stair."));
    }

    switch(random(4))
    {
    case 0:
	add_item( ({ "step", "steps" }),
	    BSN("The steps are narrow and unevenly spaced. They are hewn " +
	    "out of this rocky mountain."));
	break;
    case 1:
	add_item( ({ "step", "steps" }),
	    BSN("Many of the steps are treacherous. They are worn and " +
	    "smooth at the edges; some are broken and some may crack as " +
	    "you set foot upon them."));
	break;
    case 2:
	add_item( ({ "step", "steps"}),
	    BSN("The steps look dangerous. One slip might be fatal since " +
	    "the foot of the stairs may be a long way down. Better be " +
	    "careful."));
	break;
    case 3:
    default:
	add_item( ({ "step", "steps"}),
	    BSN("The narrow and unevenly spaced steps are smooth at the " +
	    "edges, which make it hard to climb them."));
    }
}

/*
 * Function name: set_long_description
 * Description  : This function sets the long description of this room. It
 *                will add a possible extra long description. It will also
 *                create a little random in the description.
 * Arguments    : extra_long - the extra text to add to the long description.
 */
void
set_long_description(string extra_long)
{
    string str;
/*
    switch(random(4))
    {
    case 0:
*/
	str = "You are on the Winding Stair deep in the Mountains of " +
	    "Shadow, Ephel Duath. Great black shapeless masses and deep " +
	    "grey shadows loom above you and about you.";
/*
	break;
    case 1:
	break;
    case 2:
	break;
    case 3:
    default:
    }
*/
    if (do_red_light == 1)
    {
	str += " Here the red light is in the sky seems stronger; though " +
	    "you cannot tell whether a dreadful morning is indeed coming to " +
	    "this place of shadow, or whether you see only the flame of " +
	    "some great violence of Sauron in the torment of Gorgoroth " +
	    "beyond.";
    }

    set_long(BSN(str + (strlen(extra_long) ? (" " + extra_long) : "")));
}

/*
 * Function name: set_short_description
 * Description  : This function sets the short description of the room to a
 *                randomized room description.
 */
void
set_short_description()
{
    string str;

    switch(random(5))
    {
    case 0:
	str = "Somewhere on the Winding Stair in Ephel Duath";
	break;
    case 1:
	str = "On the Winding Stair in the Mountains of Shadow";
	break;
    case 2:
	str = "Near a cleft in the Mountains of Shadow on the Winding Stair";
	break;
    case 3:
	str = "The Winding Stair, somewhere in Ephel Duath";
	break;
    case 4:
    default:
	str = "On a passage on the Winding Stair";
    }

    set_short(str);
}

/*
 * Function name: add_red_light
 * Description  : Adds a few descriptions to the room that are related to
 *                the red light that people see from time to time. Most of
 *                the messages are anti-messages, telling you that you cannot
 *                see a thing. It is only called in the lower part of the
 *                Winding Stair.
 */
void
add_red_light()
{
    add_item( ({ "cloud", "clouds", "sky" }),
	BSN("The massive grey clouds hold almost all light here. They seem " +
	"to have always been here and they will probably remain here as " +
	"the Nameless One rules over the land of the East."));

    add_item( ({ "peak", "peaks" }),
	BSN("It is much too dark to see far here. The peaks of the " +
	"Mountains are way beyond visibility."));

    add_item( ({ "pillar", "pillars" }),
	BSN("The pillars that you might have thought you saw, are just " +
	"the peaks of the high mountains."));

    add_item( ({ "roof" }),
	BSN("High up in the mountains the only roof is the sky above, " +
	"covered with dark clouds."));

    add_item( ({ "light", "red light" }),
	BSN("Every now and then a dull red light becomes visible through " +
	"the dark clouds, allowing only a glimpse at the mountains, the " +
	"path and the deep ravine below. Currently there is no such light " +
	"to be seen."));
}

/*
 * Function name: add_visible_tower
 * Description  : This function is used to add the description of the tower
 *                to the room. It is only called in the upper part of the
 *                Winding Stair.
 */
void
add_visible_tower()
{
    add_item( ({ "light", "red light", "redness", "sky" }),
	BSN("The red light is stronger here. You must have come closer to " +
	"source of it. Looking up you see the very crown of this bitter " +
	"road against the sullen redness of the eastern sky."));

    add_item( ({ "crown", "eastern sky", "ridge", "topmost ridge" }),
	"@@crown_description@@");

    add_item( ({ "shoulder", "shoulders" }),
	"@@shoulder_description@@");

    add_item( ({ "tower", "towers" }),
	"@@tower_description@@");
}

/*
 * Function name: make_the_room
 * Description  : This function will set up the room, setting the long
 *                description and adding several nice add_items.
 * Arguments    : extra_long - the text to add to the long desctiption.
 */
varargs void
make_the_room(string extra_long = "")
{
    set_short_description();
    set_long_description(extra_long);

    if (do_red_light == 1)
    {
	add_visible_tower();
    }
    else
    {
	add_red_light();
    }

    add_cliff();
    add_wall();
    add_stair();
    add_mountain();

    set_terrain(TERRAIN_SHADOWS | TERRAIN_STEEP | TERRAIN_COLD | TERRAIN_ROCK | TERRAIN_OUTSIDE);

    add_prop(ROOM_I_NO_ME_SUN, 1);
    add_prop(OBJ_S_WIZINFO,
	   "You are on the Winding Stair. This is the second stair to " +
	   "climb when walking towards Torech Ungol and Shelob... There is no " +
	   "special danger on the Stair at this point. ");
}

/*
 * Function name: crown_description
 * Description  : If a player has enough awareness, he will see recognize
 *                the tower and see it. Otherwize he will only get a partial
 *                description.
 * Returns      : string - the description to tell him.
 */
string
crown_description()
{
    string str;

    str = "Against the sullen redness of the eastern sky a cleft was " +
	"outlined in the topmost ridge, narrow, deep-cloven between two " +
	"black shoulders; and on either shoulder was a horn of stone.";

    if ((TP->query_skill(SS_AWARENESS) >= AWARENESS_NEEDED_TO_SEE_TOWER) ||
	(TP->query_prop(LIVE_I_I_RECOGNIZED_THE_TOWER_FROM_THE_STAIR)))
    {
	TP->add_prop(LIVE_I_I_RECOGNIZED_THE_TOWER_FROM_THE_STAIR, 1);
	str += " Looking more attentively you see that the horn upon the " +
	    "left was tall and slender; and in it burned a red light, or " +
	    "else the red light in the lang beyond was shining though a " +
	    "hole. It is a black tower poised above the outer pass.";
    }

    return BSN(str);
}

/*
 * Function name: shoulder_description
 * Description  : This returns what you see if you look at the shoulder(s).
 * Returns      : string - the description
 */
string
shoulder_description()
{
    if (TP->query_prop(LIVE_I_I_RECOGNIZED_THE_TOWER_FROM_THE_STAIR))
    {
	return BSN("One of the shoulders on the topmost ridge is in fact a " +
	    "black tower built to guard the pass and surrounding area.");
    }

    return BSN("You examine your shoulders as good as possible in these " +
	"hard circumstances, but you discover nothing new.");
}

/*
 * Function name: tower_description
 * Description  : This returns the desctiption of the tower, if you saw it
 *                before.
 * Returns      : string - the description
 */
string
tower_description()
{
    if (TP->query_prop(LIVE_I_I_RECOGNIZED_THE_TOWER_FROM_THE_STAIR))
    {
	return shoulder_description();
    }

    return BSN("You are not aware of any towers within range of visibility.");
}

/*
 * Function name: set_red_light
 * Description  : Called to notify the room that it should give messages
 *                about a red light comming through the clouds from time to
 *                time.
 * Arguments    : i - 0 = see some red light from time to time
 *                    1 = see red light and be able to see the tower.
 */
void
set_red_light(int i)
{
    do_red_light = i;
}

/*
 * Function name: red_light
 * Description  : Make the sky flicker from time to time and tell everybody
 *                in the room about the flickering.
 */
void
red_light()
{
    switch(random(3))
    {
    case 0:
	tell_room(TO, BSN("Suddenly a dull red light flickers up under the " +
	    "lowering clouds and for a moment you are aware of tall peaks, " +
	    "in front and on either side, like pillars holding up a vast " +
	    "sagging roof."));
	break;
    case 1:
	tell_room(TO, BSN("The massive clouds covering the sky make it " +
	    "almost impossible see anything, but every now and then a dull " +
	    "red light breaks the jet black sky, showing gruesome forms of " +
	    "deep scarlet red clouds."));
	break;
    case 2:
    default:
	tell_room(TO, BSN("Suddenly the area is lighted by a dull red light " +
	    "that managed to break through the dark grey clouds that cover " +
	    "the sky. It creates some gloomy shadows and then the light " +
	    "disappears again, leaving you in the darkness."));
    }

    red_light_alarm = 0;
}

/*
 * Function name: enter_inv
 * Description  : If a player enters this room, he might get to see a red
 *                light, giving away little about the environment.
 * Arguments    : obj  - the entering object
 *                from - where the object came from
 */
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if ((!random(10)) &&
	(!do_red_light) &&
	(living(obj)) &&
	(!red_light_alarm))
    {
	set_alarm(3.0, 0.0, "red_light");
    }
}

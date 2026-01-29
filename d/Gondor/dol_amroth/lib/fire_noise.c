/* -*- Mode: C -*-
 *
 * lib/firenoise.c
 *
 * By Skippern 20(c)02
 */

void
fire_noise(string fire = "fireplace")
{
    string str;

    switch(random(12))
    {
    case 0..1:
	str = "The fire in the "+fire+" sparkles.\n";
	break;
    case 2..4:
	str = "Flames dances lively in the "+fire+".\n"; 
	break;
    case 5..6:
	str = "A hissing noise comes from the "+fire+" as some wet wood " +
	    "burns.\n";
	break;
    case 7..8:
	str = "A dump sound is heard from the "+fire+" as some logs falls.\n";
	break;
    case 9..10:
	str = "Something flames up inside the "+fire+".\n";
	break;
    default:
	str = "You hear some sounds from the "+fire+".\n";
    }

    tell_room(this_object(), str, 0);
}

/*
 * Standard time and sky defs for the Shire. Inherit this file
 * so the rooms get standard time and sky descriptions, and so these
 * descriptions don't have to be in multiple files.
 *
 * Be sure to have the following in your file first, otherwise you will get errors:
 *
 *      #include "/d/Shire/sys/defs.h"
 *      inherit AREA_ROOM;
 *
 * Finwe, March 2019
 */

inherit "/lib/commands.c";

#define ROOM_TELL_TIME      180
#define NPC_TELL_TIME        90

// Sets up time defs for area.
#define LATE_NIGHT		0..5	/*12am-5am*/
#define EARLY_MORNING	6..7	/*6am-7am*/
#define MORNING			8..10	/*8am-10am*/
#define NOON			11..13	/*11am-1pm*/
#define AFTERNOON		14..17	/*2pm-5pm*/
#define EVENING			18..21	/*6pm-9pm*/
#define EARLY_NIGHT		22..24	/*10pm-12am*/

string
daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Gentle sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Blazing afternoon sunlight";
        case EVENING:
            return "Evening light";
    }
}

/*
 * Function name : set_add_sky
 * Description   : adds descr of sky
 */
void set_add_sky()
{
    add_item("sky",
        "It is @@day_desc@@, with @@light_type@@ filling " +
        "the sky.\n");
}

string
day_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}

string
light_type()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle night light";
    }
}



/*
 *  This is the base room inherited by all inside rooms in Imladris.           
 *  Original idea Fangorn
 *  Updated by Finwe, December 1997
 *  
 */
 
inherit "/d/Shire/std/room.c";
 
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
 
#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */
 
int num_of_windows = 0; /* number of windows in house */
 
int     win_n_u, win_n_d,   /* window existance  0/no, 1/yes */
        win_s_u, win_s_d,
        win_e_u, win_e_d,
        win_w_u, win_w_d = 0;
 
/*
 * Extra descr for walls and floor
 */
static string extra_wall   = "",
              extra_window = "",
              extra_floor  = "";
 
 
void
create_house_room()
{
}
 
public void
create_shire_room()
{
    add_prop(ROOM_S_MAP_FILE, "rivendell.txt");

    add_item(({"lamp","lamps"}),
        "They are attached to the walls and radiate a soft, " +
        "white light throughout the room.\n");
    add_item("ceiling",
        "Large richly carved beams hold up the roof high " +
        "above you.\n");
    add_item(({"walls", "wall"}),
        "The walls are an off-white color and lightly textured. " +
        "Lamps are attached to the walls.\n");
    add_item(({"floor"}),
        "The floor is made from dark hardwoods and is very " +
        "clean.\n");
    add_item(({"beams", "carved beams", "richly carved beams"}),
        "The beams are large and square shaped. They are spaced " +
        "evenly across the ceiling and support it. They are " +
        "stained a deep color and glow from the reflected light.\n");
 
    add_prop(ROOM_I_LIGHT, 100);  // Lamps add extra light.
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room

    add_prop(ROOM_I_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT, 
        "A great elven power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents that from happening.\n");
    add_prop(ROOM_M_NO_TELEPORT_FROM, 
        "A great elven-power prevents that from happening.\n");


    add_prop(ROOM_M_NO_STEAL,
        "Evil acts like that are not permitted in Imladris."); 
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 
    create_house_room();
}
 
 
void
set_extra_wall(string str)
{
//      remove_item(({"wall", "walls"}));
 
        add_item(({"wall", "walls"}),
            "The walls are an off-white color and lightly textured. " +
            "Lamps are attached to the walls. " + str + "\n");
}

void
set_extra_window(string str)
{
    add_item(({"windows","window"}),
        str + " @@window_count@@ large and equally " +
        "divided vertically into two sections with each " +
        "vertical section divided horizontally into four " +
        "squares. Large curtains cover them. Looking " +
        "out, you notice it is @@day_desc@@.\n");
    add_item("curtains",
        "They are made from a heavy fabric and are open, " +
        "letting @@daylight_desc@@ fill the room.\n");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
	    "@@open_curtains@@");
    add_item("cord",
        "The cord is silver. It gathers the curtains and " +
		"attaches to the wall, keeping them open.\n");
    add_item(({"mountains", "misty mountains"}),
        "The mountains rise up in the distance from the valley. " +
        "They are imposing even though their tops can't be " +
        "seen from here.\n");
    add_item("path",
        "It looks smooth from here as it meanders out into the " +
        "valley.\n");

}

string close_curtains()
{
    return "Just as you are about to close the curtains, you " +
	    "discover a cord ties them to the wall, preventing them " +
		"from being drawn closed.\n";
}

string open_curtains()
{
    return "You notice they are open already.\n";
}


string move_rug()
{
    return "You lift up the rug and look under it. There's " +
	    "nothing under it, so you put it back.\n";
}


string open_dresser()
{
    return "You try to open the drawers in the dresser but " +
	    "discover they won't open. They must be locked.\n";
}


string open_drawers()
{
    return "Open what, the dresser drawers or the vanity drawers?\n";
}


void
set_extra_floor(string str)
{
        add_item(({"floor", "down", "ground"}),
            "The floor is made from dark hardwoods and is very " +
            "clean. " + str + "\n");
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
daylight_desc()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "moonlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle starlight";
    }
}
 
 
string
window_count()
{
    if(num_of_windows >1)
        return "They are";
    else
        return "It is";
}

string
window_position()
{
    if(num_of_windows >1)
        return "The windows are";
    else
        return "The window is";
}

 
string
window_check()
{
    if(win_n_u == 1 || win_n_d == 1) return "north";
    if(win_s_u == 1 || win_s_d == 1) return "south";
    if(win_e_u == 1 || win_e_d == 1) return "east";
    if(win_w_u == 1 || win_w_d == 1) return "west";
}

string north_up()
{
    return "The valley slowly rises up towards the mountains. " +
        "Trees dot the landscape and the mountaintops are bathed " +
        "in "+daylight_desc()+". You see a path meander past the " +
        "house and some rooftops of a few buildings nearby. ";
}

string north_down()
{
    return "A wide road wanders past the house and some " +
        "buildings stand in the distance. ";
}

string south_up()
{
    return "The valley looks lower in the south where the " +
        "river Bruinen runs. Trees dot the landscape on " +
        "either side of the river. A path runs along the " +
        "northern side of the river and a lush garden " +
        "obscures your view of the land under the window. ";
}

string south_down()
{
    return "A lush garden grows outside. It blocks your view " +
        "of most everything beyound the window. Nonetheless, " +
        "you see a path beyond the garden and occasionally " +
        "water spray up in the air. ";
}


string east_up()
{
    return "The valley spreads out before your view. Some of " +
        "the taller trees in the garden obscure your view " +
        "but you can see the mountains rising in the distance. " +
        "The tops of the mountains are bathed in " +
        daylight_desc()+". ";
}

string east_down()
{
    return "A bounteous garden grows outside the window. " +
        "Thick trees and plants fill your view of the valley. " +
        "Just beyond the garden, you think you see a path " +
        "winding up into the mountains. "; 
}

string west_up()
{
    return "Looking through the window, you realize that you " +
        "are gazing westwards toward the lowlands. The valley " +
        "of Imladris continues in this direction, and far to " +
        "the west you know there is the Shire and Bree. You " +
        "see a stone path lead out of the mountains and run " +
        "over a bridge that crosses the river. ";
}

string west_down()
{
    return "Gazing out the window, you look onto the porch. " +
        "Beyond the porch you see a straight path that leads " +
        "out into the valley. ";
}

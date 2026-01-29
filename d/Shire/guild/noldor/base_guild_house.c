/*
 * This is the base indoor room for the Noldor guild
 * By Finwe, August 2000
 *  
 */
 
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define LATE_NIGHT      0..3        /* 12am -  3am */
#define EARLY_MORNING   4..7        /*  4am -  7am */
#define MORNING         8..10       /*  8am - 10am */
#define NOON            11..13      /* 11am -  1pm */
#define AFTERNOON       14..17      /*  2pm -  5pm */
#define EVENING         18..21      /*  6pm -  9pm */
#define EARLY_NIGHT     22..24      /* 10pm - 12am */
 
#define SETTEE_CHAIR     "large maroon settee"
#define DIVAN_CHAIR     "golden coloured divan"

public string	look_at(string arg);    /* VBFC for chairs */
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);    /* VBFC for chairs */


/*
 * Extra descr for walls and floor
 */
static string extra_wall   = "",
              extra_window = "",
              extra_floor  = "";
 
 
void
create_guild_room()
{
}
 
public void
create_shire_room()
{
    add_item(({"lamp","lamps"}),
        "The lamps are slender free-standing pedestal fixtures " +
        "of varying heights. The tops are made of pear shaped " +
        "crystals that fill the room with soft, relaxing light. " +
        "The pedestals are silver and gold, resembling elegant " +
        "tree trunks. The bases fan out and resemble the roots " +
        "of great trees growing into the lawn.\n");
    add_item(({"chairs", "chair"}),
        "There are settees, divans scattered about the room.\n");
    add_item("ceiling",
        "The ceiling rises above you to a peak. It is made " +
		"of polished white stone.\n");
    add_item(({"floor", "ground"}),
        "The ground is a carpet of trimmed lush green grass. " +
		"The grass extends from the garden outside to " +
        "throughout the guild. Small wild flowers grow in small " +
        "clusters about the room.\n");
	add_item(({"flowers", "wildflowers"}), 
		"Various wildflowers grow scattered about the grass " +
		"floor. They are low growing and are various colors, " +
		"but primarily pink, white, or yellow and have either " +
		"three, four or five petals.\n");
    add_item(({"grass", "lawn"}),
        "The lawn is a rich verdant emerald green. The grass " +
        "is thick and neatly clipped. Some small wildflowers " +
        "grow in scattered about the room.\n");
    add_cmd_item("pick", ({"flowers", "wildflowers", "wildflower"}),
        "@@pick_flowers@@");
    add_item(({"arch", "arches", "doorways", "gateway"}),
        "The arches are large, intricately carved gateways set " +
        "into the walls. Two large trees are expertly carved " +
        "on both sides of each arch. Their branches twine up and " +
        "over the top of the arch.\n");
    add_item(({"trees", "carved trees"}),
        "The trees are expertly carved by skilled elven hands. " +
        "They look lifelike as the frame the arches. Their bark " +
        "and branches are a silver color with the leaves being " +
        "a contrasting silver colour. Some of the branches " +
        "twine over the top of the arch.\n");
    add_chair(SETTEE_CHAIR,
        "[down] [on] / [in] [the] [long] [maroon] 'settee'", 4);
    add_item( ({ "settee"}), &look_at(SETTEE_CHAIR) );

    add_chair(DIVAN_CHAIR,
        "[down] [on] / [in] [the] [large] 'divan'", 1);
    add_item( ({ "divan", }), &look_at(DIVAN_CHAIR) );


    set_room_tell_time(random(180)+60);
    add_room_tell("A Noldo walks by, acknowledging you.");
    add_room_tell("The smell of clean grass fills the air.");
    add_room_tell("The fragrance of the flowers wafts past you.");
    add_room_tell("The melodic sound of the River Bruinen drifts by.");
    add_room_tell("A refreshing breeze blows past.");
    add_room_tell("Some Noldor greet you and walk by.");
    add_room_tell("A Noldo pauses with a smile on her face, " +
        "and rests here.");
    add_room_tell("Some Noldor pause, noticing you, and continue " +
        "talking quietly.");
    add_room_tell("Joyful laughter echoes lightly through the room.");
    add_room_tell("A Noldo sits down on a nearby divan and relaxes.");
    add_room_tell("A Noldo stands up from a nearby divan, " +
        "smiles, and leaves the room.");
    add_room_tell("Some Noldor walk in, talking among " +
        "themselves and sit down on a settee.");
    add_room_tell("Some Noldor stand up from the settee, wave, " +
        "and walk away.");
    

     
    add_prop(ROOM_I_LIGHT, 3);  // These bright lamps add extra light.
    add_prop(ROOM_I_INSIDE, 0); // outdoor room even though it has a roof.
    add_prop(ROOM_M_NO_TELEPORT_TO, 
        "A great elven-power prevents teleporting there.\n");
    add_prop(ROOM_M_NO_STEAL,
        "Evil acts like that are not permitted in Imladris."); 
    add_prop(ROOM_I_ALLOW_STEED, 0); // no horsies in the house. They're messy. 
    create_guild_room();
}
 

void
init()
{
    ::init();
    init_room_chairs(); /* add chair verbs */

}

 public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


void
set_extra_wall(string str)
{
    add_item(({"wall", "walls"}),
        "The walls are made of white stone that has been polished " +
		"to a bright luster. Elven workmanship is evident here " +
		"as the seams cannot be made out between the blocks, " +
		"yet the walls appear to be made up of many stones. " + 
        str + "\n");
}

void
set_extra_window(string str)
{
    add_item(({"windows","window"}),
        str + " They are large and equally divided " +
        "vertically into two sections. Each vertical section is " +
        "further divided horizontally into four squares. It is " +
        "@@day_desc@@.\n");
    add_item(({"mountains", "misty mountains"}),
        "The mountains rise up in the distance from the valley. " +
        "They are imposing even though their tops can't be " +
        "seen from here.\n");
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
 
/*
string
window_position()
{
    if(num_of_windows >1)
        return "The windows are";
    else
        return "The window is";
}
*/

string
pick_flowers()
{
    return "The flowers can't be picked. Doing so could mar the " +
    "beauty of the guild house.\n";
}


/*
 * Function name:   look_at
 * Description  :   VBFC to describe chair/sofa + occupants
 * Arguments    :   string arg -- what's being looked at
 *                  null str -> it's the room
 * Returns      :    string -- the description
 */
public string
look_at(string arg)
{
    switch ( arg )
    {
    case SETTEE_CHAIR:
    return "They are chairs with arms and a back. The settees are " +
        "covered wth a dark maroon fabric and design for elves " +
        "to sit or lay on.\n"+
    sitting_on_chair(SETTEE_CHAIR, this_player(), 0);
    break;

    case DIVAN_CHAIR:
       return "The divan is a long, backless couch. It is covered " +
        "with a pale golden colored fabric and has four " +
        "elegantly carved legs.\n"+
    sitting_on_chair(DIVAN_CHAIR, this_player(), 0);
    break;


    }
} /* look_at */

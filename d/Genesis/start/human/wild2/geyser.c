/*
 *  /d/Genesis/start/human/wild2/geyser.c
 *
 *  Styles.   3 Mar 1993
 *
 *  Modified - Finwe,  April 2015 (?)
 *           - Varian  March, 2016 (improved descriptions)
 *           - Gorboth October, 2018 (added geyser quest)
 */

#pragma strict_types

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
inherit "/d/Genesis/start/human/wild2/base";

int gstatus;

/* definitions */
#define PUB_QUEST_ITEM      ("_sparkle_pub_quest_item")

/* prototypes */
public void        quest_object_check();
public int         query_geyser_eruption() { return gstatus; }

void geyser(int arg);

/*
 * Function name:        create_wild_room()
 * Description  :        Creates a wild room from the base file
 *                       /d/Genesis/start/human/wild2/base.c
 */
void
create_wild_room()
{
    set_items_sparkle();
    
    set_short("Site of the geyser");
    set_long("The trail you were following has ended up in a damp and " +
        "misty area in the southwest corner of a small valley. The tall " +
        "grasses and wildflowers gradually give way to small steaming " +
        "pools, with puddles forming in the cracks and hollows. All around " +
        "you, rocky cliffs reach upward, growing into the craggy peaks " +
        "of the Grey Mountains that surround the valley. You notice that " +
        "someone has erected a short wooden sign in the ground beside a " +
        "large hole from which fumes of sulphur arise. It appears that " +
        "the only way out from here is to follow the winding dirt trail " +
        "back down east into the valley.\n");

    add_trees(0);

    add_exit(THIS_DIR + "trail_hi","east");

    set_no_exit_msg(({"northeast","north","northwest","southwest",
            "south","southeast"}),
        "The rocky cliffs that make up the steep mountainsides here " +
        "prevent you from going in that direction. You will have to find " +
        "another way around.\n");
    set_no_exit_msg(({"west"}),
        "A large avalanche has blocked any passage west into the " +
            "mountains. It seems you cannot travel that way.\n");

    add_item(({"foothill","foothills","rugged foothills","rugged foothill",
            "hill","hills"}),
        "You are in the foothills of the Grey Mountains, atop a small " +
        "plateau overlooking a small valley that spreads out to the east. " +
        "The rugged foothills slope steadily upwards all around, rising " +
        "up into rocky cliffs.\n");
    add_item(({"mountain","mountains","grey mountains","mountainside",
            "mountainsides"}),
        "The Grey Mountains rise up all around you here, surrounding " +
        "the small valley before you. The rocky mountainside is " +
        "filled with steep cliffs and rugged foothills that make " +
        "travel away from the trail almost impossible.\n");
    add_item(({"vale","valley","small valley"}),
        "Stretching out to the east, a small valley full of " +
        "tall grasses and colourful wildflowers spreads out before " +
        "you.\n");
    add_item(({"path","dirt path","small path","small dirt path","trail",
                "small trail","dirt trail","small dirt trail"}),
        "The trail is almost unrecognizable as it ends in a mass of " +
        "big footprints that seem to circle around a large meeting " +
        "place that sits in the middle of the plateau.\n");
    add_item(({"area","misty area","ground","mist"}),
        "The air here is very damp, making it a little difficult to " +
        "breathe. It seems like most of the mist is coming from the " +
        "large hole in the ground here.\n");
    add_item(({"pools","puddles","pool","puddle"}),
        "There are several different pools and puddles here that fill all " +
        "of the cracks and hollows with hot water. Some of them " +
        "are actually quite deep!\n");
    add_item(({"cracks","hollows","crack","hollow"}),
        "There are many different cracks and hollows in the land around " +
        "the geyser here, most of them forming puddles and pools of hot " +
        "water\n");
    add_item(({"sign","short sign","wooden sign","short wooden sign"}),
        "There is something written on it, maybe you should read it " +
        "instead?\n");
    add_item(({"hole","large hole"}),
        "This is a rather large hole in the ground, a geyser actually. " +
        "Wet sulphurous fumes rise up to form a warm mist around the " +
        "geyser, giving this part of the valley an unpleasant smell.\n");
    add_item(({"fumes","fume","sulphur","sulphurous fumes"}),
        "These are fumes of sulphur and water vapor, bearing a distinctly " +
        "unpleasant sticky smell.\n");
    add_item(({"water","warm water","hot water"}),
        "The water is not very pure and not recommended for drinking. " +
        "Besides, it is also very hot.\n");
    add_item(({"vapour","vapours","mist","mists"}),
        "The vapour here smells unplesantly of sulphur, creating an " +
        "uncomfortable mist around you.\n");
    add_item(({"avalanche","boulder","boulders"}),
        "It appears that a large avalanche has disloged many rocky " +
        "boulders, sealing off the western edge of the valley beyond the " +
        "geyser.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");

    set_alarm(itof(random(10) + 5), 0.0, &geyser(1));
}


/*
 * Function name:        read
 * Description  :        Returns a string for reading the sign
 * Returns      :        int 1 - Reads the sign
 *                       int 0 - Prompts for syntax
 */
int
read(string what)
{
    if (what != "sign") {
        notify_fail("Read what? The sign?");
        return 0;
    }
    say(QCNAME(this_player())+ " reads the sign.\n");
    write("\n"+
          "Warning. The geyser erupts at fairly regular intervals.\n"+
          "Normally at about every 15 minutes.\n");
    return 1;
}
/* read */

void
init()
{
    ::init();

    add_action(read,"read");
}

int query_gstatus() { return gstatus; }
string query_time_left() { return "Not yet implemented.\n"; }

/*
 * Function name:        geyser
 * Description  :        The geyser erupting!
 */
void
geyser(int arg)
{
    int delay;

    switch(arg) {
    case 1:
        tell_room(this_object(),
            "\n\nThe ground begins to rumble.\n");
        delay = random(10) + 15;
        break;
    case 2:
        tell_room(this_object(),
            "\nThe ground shakes and hot vapour fumes from the hole.\n");
        delay = random(10) + 8;
        break;
    case 3:
        tell_room(this_object(),
            "\nWith a tremendous roar a enormous geyser spurts high up in the air. The air is filled with hot vapour, making it hard to breathe.\n");
        add_item("geyser", "The geyser spurts high up in the air.\n");
        delay = random(15) + 35;
        break;
    case 4:
        tell_room(this_object(),
            "\nThe roar from the geyser seems to subside a little.\n");
        delay = 8;
        break;
    case 5:
        tell_room(this_object(),
            "\nSlowly the geyser loses its strength and within not too long all that remains is a few puddles on the steaming ground.\n");
        remove_item("geyser");
        delay = random(100) + 850;
        break;
    default:
        tell_room(this_object(),
                  "\nFumes rise from the pools around you, making you dizzy.\n");
        delay = 0;
        break;
    }

    quest_object_check();

    if (!delay) return;

    if (arg == 5) {
        gstatus = 1;
        set_alarm(itof(delay), 0.0, &geyser(gstatus));
    }
    else {
        gstatus = arg + 1;
        set_alarm(itof(delay), 0.0, &geyser(gstatus));
    }
}
/* geyser */


/*
 * Function name:        quest_object_check
 * Description  :        Check to see if there are any funnel-jugs either
 *                       in the room or in the (not deep) inventory
 *                       of playeres standing here. If there are, they
 *                       will be filled up with spray unless they are
 *                       already filled with water.
 */
public void
quest_object_check()
{
    mixed  *jugs_present = ({});

    foreach (object ob: all_inventory(this_object()))
    {
        if (ob->id(PUB_QUEST_ITEM))
        {
            jugs_present += ({ ob });
        }
        else
        {
            foreach (object inv_ob: all_inventory(ob))
            {
                if (inv_ob->id(PUB_QUEST_ITEM))
                {
                    jugs_present += ({ inv_ob });
                }
            }
        }
    }

    jugs_present->geyser_fill(gstatus);
    return;
} /* quest_object_check */


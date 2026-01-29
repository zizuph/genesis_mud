/*
 * /d/Gondor/morgul/tower/tower_7c.c
 * The central room on the seventh floor of the Morgul Tower.
 * But really its the roof where the Nazgul can call upon their
 * winged steeds.
 *
 * Most descriptions are created by the Nine themselves as I 
 * asked them to 'place an order' from the masons and build 
 * this place.
 *
 * The place is intended to be a master piece and in due time 
 * almost anything should be able to get examined from here.
 * With combined efforts of the Mages themselves and myself.
 *
 *                             Toby, 22-July-2007
 *
 * ==============================================================
 * Modification log:
 *
 *    Toby, 23-Sept-2007: Added a bunch of descriptions and fixed 
 *                        with the command word. Opened on this day.
 *    Toby, 24-Sept-2007: Added a bunch of descriptions by suggestion
 *                        and own. I think the Nine will have a competition
 *                        to write 'points of interest', I look forward to 
 *                        the results.
 *    Toby, 18-June-2008: Added descriptions for descending
 *    Eowul, 08-Okt-2008: Removed some of the descriptions due to the long
 *                        delay in movement. Also added a notification to
 *                        people inside Minas Morgul when a winged steed
 *                        arrives at the top.
 */

#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower.c";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

/* These are for viewing the surrounding area */
#define TOWER_ENTRANCE  ("/d/Gondor/morgul/city/mmr3")
#define INNER_GATE      ("/d/Gondor/morgul/city/i_ngate")
#define OUTER_GATE      ("/d/Gondor/morgul/city/o_ngate")
#define CROSSROADS      ("/d/Gondor/ithilien/road/crossroads")

string *notification_rooms = ({
        "/d/Gondor/morgul/city/*",
        "/d/Gondor/morgul/road/*",
    });
/* Prototypes */
public string	exa_down(string desc, string street_file);
void		preload_files();

void create_morgul_tower_room()
{
    set_level(7);
    set_room_type("flat space");
    set_extra_long("It opens to the ever black " +
         "skies of Mordor. The floor, upon which you stand high atop " +
         "the Black Tower appears to be constructed of a single sheet " +
         "of black obsidian. The minimal light that makes it through " +
         "the ever-present clouds swirling about the pinnacle of the " +
         "Tower appears to be drawn into the stone and dissipated in " +
         "its inky depths. At the far end of the roof several posts " +
         "of the same obsidian material jut up from the stone that " +
         "makes up the floor. Looking into the distance from the " +
         "roof, you cannot help but knowing that the Elvenkind and " +
         "Etani would tremble at the power of the Dark Lord that " +
         "brought this Tower into existence in generations past.");

    add_item(({"roof"}), 
       "If you want to examine the roof, simply take a look arround you. " +
       "Atop the pinnacle of the world as you stand you might see points of " +
       "interest in the distance and most certainly the gates as well as " +
       "the quite near crossroads.\n");

    add_item(({"floor", "obsidian floor", "sheet", "obsidian sheet", "black obsidian",
               "flat space", "space", "obsidian", "black obsidian", "sheet", 
               "single sheet", "single sheet of obsidian", "single sheet of black obsidian",
               "stone"}), 
       "Upon first glance, the floor's ebony black surface appears to be " +
       "completely unmarred. However, upon closer inspection, fine grooves " +
       "are barely perceptible under the scrutiny of your gaze and in the very " +
       "center of the floor a faint outline can be traced that resembles " +
       "a hatch leading down below into the inner darkness of the Black Tower. " +
       "The single sheet of obsidian, making out the floor, extends to the " + 
       "edge of the roof where it ends suddenly in a sheer drop off to the " +
       "ground far, far below.\n");

    add_item(({"hatch", "outline"}),
       "As you lean down to examine the outline more closely, you discern no " +
       "physical means of moving the stone of the hatch that seems almost " +
       "perfectly embedded into the single sheet of obsidian making up the " +
       "roof. You realize with dark pleasure that this portal, constructed by " +
       "the Master for his servants, will likely open magically when one of " +
       "his Chosen attempts to proceed down through it into the Tower.\n");

    add_item(({"ground"}), 
       "As you step fearlessly to the edge of the roof and glance " +
       "downward you only see the swirling mists surrounding the " +
       "Black Tower's lower parapets.\n");

    add_item(({"mists", "swirling mists", "dark mists", "clouds", "dark clouds",
               "cloud", "massive cloud", "massive clouds", "massive dark cloud",
               "massive dark clouds"}), 
       "The dark mists move with the winds gusting about the Tower, " +
       "but never seem to thin out as they snake their way around " +
       "the Tower. The inky blackness they cast is nearly suffocating, " +
       "yet you feel quite comfortable as they swirl violently about you " +
       "knowing that from afar these mists strikes fear appearing as a " +
       "massive cloud threatening to overwhelm the lands..\n");

    add_item(({"mist", "swirling mist", "dark mist"}), 
       "Perhaps it is the swirling mists snaking around the Tower you are looking for?\n");

    add_item(({"parapets", "lower parapets", "tower", "Tower", "tower of black sorcery",
               "pinnacle"}),
       "Wall upon wall, battlement upon battlement, black, " +
       "immeasurably strong, mountain of iron, gate of steel, tower of " +
       "adamant. You stand upon the culmination of centuries of work that " +
       "only the Black Master could have orchestrated. The sense of power " +
       "emanating from this perch, seemingly atop the world, is invigorating " +
       "beyond description.\n");

    add_item(({"grooves", "furrows"}), "As you bend down to examine the " +
       "grooves more carefully, you quickly conclude that the furrows in " +
       "the floor must have been made by the rending of the claws of the " +
       "Nazgul beasts that regularly alight here.\n");

    add_item(({"post", "posts", "obsidian post", "obsidian posts"}), 
       "Upon closer inspection, it is clear that these posts are used to " +
       "tether the massive winged beasts of the Nazgul to the roof when " +
       "not in use.  You also notice several deep channels that appear to " +
       "be have been dug into the floor near these posts.\n");

    add_item(({"channel", "channels", "shallow channels"}), 
       "The black of the obsidian is tainted slightly by the copper tones " +
       "of spilt blood. The troughs are clearly deep enough to keep anything " +
       "from easily escaping once deposited there by the mighty beasts. " +
       "It appears that the beasts regularly bring back whatever prey they " +
       "capture to the roof of the Tower to consume when not serving their " +
       "Masters. Peering into the depths of the channel nearest you, you " +
       "notice remnants of an arm perhaps elven or a younger human.\n");

    add_item(({"arm", "elf", "hobbit", "mess", "disgusting mess", "filth", "remnants"}), 
       "From this distance, which is absolutely as close as you wish to come " +
       "to the disgusting mess of filth within the trough, it appears as if " +
       "one of the beasts has deposited a leftover meal, perhaps an elven arm " +
       "or youthful human arm or even that of a hobbit, to be consumed when " +
       "the urge strikes it.\n");

// ================================================================================
// ========== Here are the 'exa directions' and 'exa points of interest' ==========
// ==========             Place them all last please.                    ==========
// ================================================================================

    add_item(({"down", "entrance"}),"@@exa_down|" +
      "As you step fearlessly to the northeastern edge of the roof, " +
       "glancing downward you see the entrance to the Black Tower.|"+
      TOWER_ENTRANCE+"@@" + "\n");

    add_item(({"inner gate"}),"@@exa_down|" +
      "Stepping closer to the edge of the roof gazing to the north you can see "+
      "inside the gates of His dreaded city.|"+
      INNER_GATE+"@@" + "\n");

    add_item(({"outer gate"}),"@@exa_down|" +
      "Stepping closer to the edge of the roof gazing to the north you can see "+
      "just beyond the gates of the Dark City.|"+
      OUTER_GATE+"@@" + "\n");

    add_item(({"gate", "gates"}), "Is it the outer or inner gate you wish to investigate?\n");

    add_item(({"crossroads"}),"@@exa_down|" +
      "Turning your attention to the north you gaze far into the distance " +
      "you see the crossroads outside of Minas Morgul.|"+
      CROSSROADS+"@@" + "\n");

    add_item(({"east", "mordor"}),"You turn your gaze towards the east and in " +
      "silent contemplation you stare into the eye of your Master.\n");

    add_item(({"west", "minas tirith"}),"You turn your gaze towards the west, " +
      "beyond the road Morannon and over the Ithilien forest, a forest where " +
      "a bobbing light can be seen every now and then, towards Minas Tirith. " +
      "In silent contemplation you think of how to crush the feeble rebel " +
      "resistance.\n");

    add_item(({"lair", "shelobs lair", "shelob's lair"}), 
       "Eventhough you stand upon what feels like the pinnacle of the world " +
       "you can not view any details from here. You would have to enter the " +
       "tunnels of Torech Ungol to get a view of Shelob's lair. Perhaps by " +
       "climbing the winding stairs or by other means entering them.\n");

    add_item(({"stair", "stairs", "winding stairs", "winding stair", "reaches",
               "upper-most reaches", "straight stair"}), 
       "From here, you can see the upper-most reaches of the straight stair, " +
       "and the infinitely winding staircase ascending to Teroch Ungol. You " +
       "smile darkly as you think of the dangers lurking within the nest of " +
       "dark rank tunnels.\n");

    add_item(({"camp", "haradrim camp", "haradrim"}), 
       "From your vantage point you can see bobbing lights in the southern " +
       "Ithilien forest where you know the Haradrim have made camp. The lights " +
       "trace out changing terrestrial constellations, in contrast to those in " +
       "the heavens.\n");
    
    add_item(({"lights", "bobbing lights"}), 
       "Through intense scrutiny these bobbing lights seem to be torches in " +
       "the vast Haradrim camp west of road Morannon in the Ithilien forest. " +
       "The camp seem to have massed forces to be a veritable army.\n");

    add_item(({"haradrim torch", "haradrim torches"}), 
       "They are too far away to get a good look.\n");
    
    add_item(({"haradrim army", "veritable army", "forces of harad", "forces of Harad"}), 
       "These are the massed forces of Harad summoned to do the Dark Lord's bidding.\n");

    add_item(({"torch", "torches"}), 
       "Are intent on studying the haradrim torches west of the road Morannon?\n");

    add_item(({"army"}), 
       "Are intent on studying the haradrim army west of the road Morannon or the " +
       "army of Mordor?\n");

    add_item(({"mordor army", "army of mordor", "Mordor army", "army of Mordor"}), 
       "The army of Mordor is by far too large and spread out to be seen even from here. " +
       "If you are intent on scruitinizing them, you need to ender Mordor for a close " +
       "encounter. Alas! Be prepared to be on the road for quite a few days in any such case.\n");
    
    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 3);

    preload_files();
}

void
preload_files()
{
    INNER_GATE->teleledninganka();
    OUTER_GATE->teleledninganka();
    CROSSROADS->teleledninganka();
    TOWER_ENTRANCE->teleledninganka();
}


int check_time(string str)
{
    int     hour, day, month, year;
    string  time, shour;
    object  clock;

    clock = find_object(CLOCK);
    time = (string)clock->query_time_of_day();
    hour = (int)clock->query_hour();

    if (hour == 12)
       shour = "noon";
    else if (hour == 0)
       shour = "midnight";
    else
    {
       if (hour > 12)
           hour -= 12;
       shour = hour + " o'clock in the " + time;
    }

    day = (int)clock->query_day();
    month = (int)clock->query_month();
    year = (int)clock->query_year();

    write("You gaze into the skies of Mordor and think that it is about "+
    shour+" of day "+day+", month "+ month+" in the year "+year+".");
    say(QCTNAME(TP)+" gazes to the skies of Mordor, trying to decide "+
      "what time it is.\n",TP);

    return 1;
}

public string
exa_down(string desc, string street_file)
{
    object  street = find_object(street_file),
    *people;

    people = FILTER_LIVE(all_inventory(street));

    if (!CAN_SEE_IN_OTHER_ROOM(TP,street_file))
    {
       desc += " It is too dark to see anything in that area.";
       return 0;
    }

    if (sizeof(people))
       desc += " You can see " + COMPOSITE_LIVE(people)+
       " in the area.";
    else
       desc += " There is no one near that area.";

    return desc;
}                                                                              

void
move_mage(object mage)
{
    mage->move_living("M", MAGES_DIR  + "tower/tower_6c", 1);
}

int
rasp_command(string str)
{
    /*  panta adj. -- open
     *  assa n. -- hole, mouth, perforation, opening (any form)
     */

    if (!strlen(str))
        return 0;

    str = lower_case(str);

    if (str != "panta assa")
        return 0;

    write("Feeling a sudden sense of power flowing through your " +
          "undead veins, you turn your gaze toward the center of " +
          "the beastiary and rasp: Panta assa!\n");

    say(QCTNAME(this_player()) + " turns " + this_player()->query_possessive() + 
          " gaze toward the center of the beastiary rasping: Panta assa!\n");
/*
    set_alarm(1.0, 0.0, &tell_room(TO, "The clouds swirling about the pinnacle " +
                        "of the Tower gain speed and the wind momentum.\n\n"));

    set_alarm(2.0, 0.0, &tell_room(TO, "Within the eye of the swirling clouds " +
                        "tendrils of shadows reach for you and a heaviness " +
                        "descend upon your undead body!\n\n"));

    set_alarm(3.0, 0.0, &tell_room(TO, "The clouds keep swirling madly and the " +
                        "preassure remains, almost immobilizing your undead body.\n\n"));

    set_alarm(4.0, 0.0, &tell_room(TO, "Suddenly the swirling clouds slows down " +
                         "and the preassure lifts.\n\n"));
*/
    set_alarm(2.0, 0.0, &write("The hatch silently glides open and you descend into the " +
          "darkness of the Black Tower.\n\n"));
    set_alarm(2.0, 0.0, &say("The hatch in the middle of the floor silently glides open and " +
          QTNAME(this_player()) +" descends into the darkness of the Black Tower.\n\n"));

    set_alarm(2.0, 0.0, &tell_room(MAGES_DIR  + "tower/tower_6c", 
          "Suddenly the hatch in the ceiling opens and " + 
          QTNAME(this_player()) + " enters the room walking down the " +
          "spiral staircase.\n"));

    TP->add_mana(-30);

    set_alarm(2.1, 0.0, &move_mage(TP) );

   set_alarm(2.6, 0.0, &tell_room(TO, "The hatch silently glides shut and the floor's ebony black " +
          "surface appears to be completely unmarred once again.\n"));

    return 1;
}

void
init()
{
    ::init();

    add_action(rasp_command, "rasp");
}

int valid_room(string filename, object player)
{
	object env;

	env = environment(player);
	if(!objectp(env)) return 0;
	return wildmatch(filename, file_name(env));
}

object *get_notification_users()
{
    object *all_users, *ignored_users, *remaining_users;
    int i;

    all_users = users();
    ignored_users = all_users;

    // Find all players in this region
    for(i=0;i<sizeof(notification_rooms);i++)
    {
        // Keep all users that are not in this region
        ignored_users = filter(ignored_users, not @
            &valid_room(notification_rooms[i]));
    }

    // All users that are not ignored are the ones in our region
    remaining_users = all_users - ignored_users;

    // Filter out all inside users
    remaining_users = filter(remaining_users,
        not @ &->query_prop(ROOM_I_INSIDE) @ environment);

    return remaining_users;
}

void notify_winged_steed_take_off()
{
    get_notification_users()->catch_msg(
          "At the top of the black tower, a dark, winged shape rises into "
        + "the sky like a dark cloud and flies off into the distance.\n");
}

void notify_winged_steed_landing()
{
    get_notification_users()->catch_msg(
          "With a last mighty beating of its pinions the huge winged beast "
        + "decends and lands smoothly on top of the black tower.\n");
}

void notify_winged_steed_approach(int distance)
{
    if(distance == 2) 
    {   
        get_notification_users()->catch_msg(
              "A dark shape, like a cloud and yet not "
            + "like a cloud, for it moves far too quickly, is coming " 
            + "out of the sky, speeding towards the Tower of Black "
            + "Sorcery.\n");
    }
}
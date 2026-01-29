/**********************************************************************
 * - office.c                                                       - *
 * - This is the Raumdor domain office.                             - *
 * - Created by Damaris 8/2002                                      - *
 * - It is based upon  /d/Genesis/room/info_office.c which was      - *
 * - created by Maniac 7/1/97.                                      - *
 * - Updated by Nerull. 29/5/10                                     - *
 **********************************************************************/

#include "/d/Genesis/start/human/town/tower.h"
#include "/d/Raumdor/defs.h"
#include <stdproperties.h>
#include <std.h>
#include <filter_funs.h>
inherit TOWER_OFFICE;
int alarmid;
int eventnumber = 0;
int events_is_on = 0;

string *events = (({
  "There is a battle-torn city surrounded by hordes of dreadful "+
  "undead.",

  "A darkened forest rises in the distance and there is unimaginable " +
  "movement within the trees. A long road twists and turns through " +
  "the forest. A terrifying death knight is slaughtering an unlucky "+
  "traveller on the road.",

  "A rotting skeletal corpse hangs in a rusty cage, dangling in the "+
  "shifting wind.",
  
  "The mural almost seems to emanate screams as a darkened city of undead "+
  "appears. Shadowy figures of darkness move fluidly through "+
  "the streets seeking those of light to awaken them unto "+
  "malevolence.",
  
  
  "A trail of corpses litters a dirty cobblestone road, " +
  "leading to a burning city in the distance."
}));

void
create_tower_office()
{
    set_long("This is a dark chamber filled with macabre devices. " +
            "A vast mural stretches across the full width of the far wall, " +
            "its ghastly image strangely fluid and active. Amidst this " +
            "atmosphere of death and despair, a shimmering haze bespeckles " +
            "the room, its tiny motes of light pulsing radiantly. There is " +
            "a sign dangling from the ceiling.\n");
    add_item(({"area", "chamber", "room", "dark chamber"}), query_long);
    add_item(({"mural", "vast mural", "far wall"}),
      "The mural on the far wall extends from ceiling to floor and "+
      "from one edge of a wall to the other. Oddly, the image "+
      "appears to be moving.\n");
    add_item(({"ghastly image", "image", "images"}),
      "The images in the mural shift and transform, now and again offering " +
      "a glimpse of clarity before returning to a blur.\n");
    add_item(({"floor", "ground", "flooring"}), "The flooring is " +
      "made up of the same dark stone as the rest of the room.\n");
    add_item(({"wall", "walls"}), "The walls are " +
      "made up of the same dark stone as the rest of the room.\n");
    add_item("ceiling", "The ceiling is " +
      "made up of the same dark stone as the rest of the room.\n");
    add_item(({"macabre devices", "device", "devices"}),
      "The devices all appear to be designed for different methods of " +
      "torture, restraining and maiming victims in different ways. Each " +
      "shows significant signs of use, though they look to be in working " +
      "condition.\n");
    add_item(({"haze", "shimmering haze", "cloud"}), "Like a cloud of " +
      "stars, the shimmering haze permeates the entire chamber.\n");
    add_item(({"mote", "motes", "star", "stars", "point", "light"}),
      "Each point of light floats still, occassionally flaring brightly " +
      "for a brief moment before quickly subsiding again. Although no " +
      "single mote could light the room, together they manage to " +
      "repel total darkness.\n");
    add_item("sign", OFFICE_SIGN_TEXT);
    add_cmd_item("sign", "read", OFFICE_SIGN_TEXT);
    add_item( ({ "graph", "player graph" }), "@@graph@@");
    disable_logged_in_display();
    set_project_dir("/d/Raumdor/open/projects/");
    add_tower_link("tower");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");
    // Temporary portal to the Gentleman/Ladies clubs - Nerull.
    //clone_object("/d/Raumdor/guilds/gc/portal4")->move(this_object(), 1);
    
    reset_room();
}
/*
 * start_events()
 * Starts the alarm that echoes text-events to the players in this room.
 *
*/
void
start_events()
{
    alarmid = set_alarm(30.0,60.0,"do_event");
    events_is_on = 1;
    return;
}

/*
 * do_event()
 * Echoes the next text in a list of texts to all players in the room.
 * Will turn off the alarm calling this function if no players are
 * present here.
 *
*/
void
do_event()
{
    object *all_players_here;

    all_players_here = FILTER_LIVE(all_inventory(TO));
    if (!sizeof(all_players_here))
    {
        remove_alarm(alarmid); /* remove the repeating alarm! */
        events_is_on = 0;
        return;
    }

    eventnumber = eventnumber + 1;
    if (sizeof(events) < (eventnumber + 1))
        eventnumber = 0;

    tell_room(TO, "The image within the mural suddenly shifts into clarity. " +
        events[eventnumber] +
        " The fluctuation within the image continues and soon it returns " +
        "to blurry motion once again.\n");
    return;
}

/*
 * init()
 * Is called when an object enters this room.
 * Is used here to start events if the events are not already on.
 *
*/
void
init()
{
    object *all_in_room;
    ::init();

    all_in_room = FILTER_LIVE(all_inventory(TO));
    if (sizeof(all_in_room) && events_is_on == 0)
    {
        start_events();
    }
    return;
}

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */

public void
reset_room()
{
    object quest_orb;
    
    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Raumdor");
        quest_orb->set_extra_line("The dark crystal orb is floating"
          + " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }    
}

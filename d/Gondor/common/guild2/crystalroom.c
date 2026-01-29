/*
 *  The Tower of the Society of the Morgul Mages
 *
 *  The meditation room of the Morgul Mages.
 *
 *  By Randor in March -93. Minor changes by Soermo.
 *  Modification log:
 *  - Olorin, 11-jan-1994 : tower master
 *  - Gorboth, 21-apr-1997: added ROOM_I_NO_CLEANUP prop
 *                          for droproom purposes
 *  - Gorboth, 20-oct-1997: changed desc to reflect mudlib support for
 *                          <list guilds>
 *  - Toby, 06-jan-2007   : Removed the text on estimate since it is obsolete.
 *  - Toby, 13-sept-2007  : Tixed a typo in exa_window.
 */
 
#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower";
inherit "/lib/guild_support";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
 
/* Function declaration */
 
void create_morgul_tower_room()
{
    set_level(4);
    set_room_type("dim, tiny room");
    set_extra_long("In the middle of the room is a crystal on a"
                 + " pedestal into which the mages of Minas Morgul"
                 + " may <stare> to redefine their personal learning"
                 + " priorities. One may also call upon the dark powers"
                 + " of the tower to <list guilds> here. On the east"
                 + " wall is a small window. A doorway leads west"
                 + " to the dark staircase.");

    add_prop(ROOM_I_LIGHT,1);

    add_exit(MAGES_DIR + "tower/tower_4c", "west", 0, 0);

    create_guild_support();

    ROOF
    WALLS
    FLOOR
    add_item(({"crystal"}), 
	"This dark crystal is the Crystal of Gorgoroth. You can see your "
      + "mirror image on its surface. You may enter a trance by staring "
      + "into the crystal to attune yourself to Darkness.\n");
    add_item("window","@@exa_window");
    add_item("pedestal","This pedestal is about three feet high. It is made "+
             "of white marble.\n");

    add_prop(ROOM_I_NO_CLEANUP, 1); // For droproom purposes
}
 
void init()
{
    add_action(gs_list, "list");
    add_action("stare_hook","stare");
    add_action("enter_window","enter");
    ::init();
    add_action("check_time", "time");
}
 
/* This is modified from /d/Gondor/elessar/lib/time.c */
 
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
    write("You look through the window and think that it is about "+
    shour+" of day "+day+", month "+ month+" in the year "+year+".\n");
    say(QCTNAME(TP)+" looks through the window, trying to decide "+
        "what time it is.\n",TP);
    return 1;
}
 
string tod()
{
    string time;
    object clock;

    clock = find_object(CLOCK);
    time = (string)clock->query_time_of_day();
    return time;
}
 
int enter_window(string str)
{
    if (str == "window" || str == "the window")
    {
        NF("No, you would hurt yourself!\n");
        return 0;
    }
    NF("Enter what?\n");
    return 0;
}
 
string exa_window()
{
    string  desc,
            todtxt;

    todtxt = tod();
    desc = "As you look through the window, you see the eastern part "+
           "of Minas Morgul. ";
 
    if (todtxt == "early morning" || todtxt == "morning")
        desc += "You know that the sun has risen already, as it is early "+
            "morning now, but you can't see it because of the murky clouds "+
            "that are above the Ephel Duath. Many orcs are walking within " +
            "the walls of Minas Morgul.";
 
    if (todtxt == "noon" || todtxt == "afternoon")
        desc += "The sun is probably trying to break through the heavy "+
            "clouds of the sky, because there isn't much light outside. "+
            "Still, a few orcs are outside, as they destest the light.";
 
    if (todtxt == "evening" || todtxt == "night")
        desc += "It is quite dark out there, neither stars nor the moon " +
            "shine through the clouds covering the sky. The streets of "+
            "Minas Morgul are full of noisy, restless orcs.";
 
    desc += "\n";

    return desc;
}
 
int stare_hook(string at)
{
    if (at == "into crystal" || at == "crystal")
    {
        if (TP->query_wiz_level() || TP->query_guild_name_occ() == GUILD_NAME)
        {
            if (TP->query_prop(LIVE_I_MEDITATES))
            {
                write(gs_hook_already_meditate());
                return 1;
            }
            return gs_meditate(at);
        }
        write("You dare not stare into the crystal.\n");
    }
    NF("Stare into what?\n");
    return 0;
}
 
void gs_hook_already_meditate()
{
    write("You are already staring into the crystal. If you want to "+
          "finish your meditating you can do so by typing 'rise'.\n");
}
 
void gs_hook_start_meditate()
{
  write("You start staring into the crystal. First you cannot see "+
        "anything but darkness, but as you stare deeper and deeper, you "+
        "slowly fall into trance. You sense that you can change something "+
        "in your mind. You find yourself able to <set> your different "+
        "preferences at your own desire. Just <rise> from your trance "+
        "when you have finished. ");
}
 
void gs_hook_rise()
{
  write("As if ascending from a great depth, you return to the surface "+
        "of your consciousness. You exhale and feel very relaxed as "+
        "you rise out of your trance and turn your face away from the crystal.\n");
}

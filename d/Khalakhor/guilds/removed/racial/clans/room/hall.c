/* File         : /d/Khalakhor/guilds/racial/clans/room/hall.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : Main Hall to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the hall to the default Clansmen guildhome.
 * Modifications: 
 */
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <composite.h>
#include <const.h>
#include <ss_types.h>
#include <tasks.h>

inherit GUILD_ROOM;

#include "hall_seated.c"


public mixed
banner_desc(string BANNER)
{

    switch(BANNER)
    {
        case "first":
            return "The long black and white banner " + MACDUNN_BADGE;
            break;
        case "second":
            return "The long purple and white banner " + LOHRAYN_BADGE;
            break;
        case "third":
            return "The long blue and white banner " + MACTABOR_BADGE;
            break;
        case "fourth":
            return "The long green and purple banner " + MACFADDEN_BADGE;
            break;
        case "fifth":
            return "The long green and red banner " + MACVAY_BADGE;
            break;
        case "sixth":
            return "The long crimson and green banner " + MACFAOLAIN_BADGE;
            break;

                default: return "Which banner? <first, second, etc.>\n";
                        break;
    }

}


void
create_guild_room()
{
    set_short("Within the Great hall of Clans of Khalakhor");
    set_long("The great hall is an agreed upon neutral location for " +
             "various Clans to meet, celebrate and discuss issues. " +
             "The hall is decorated with varied coloured streamers, " +
             "flags and tapestries. The arched ceiling looms high above "+
             "you. The most noticable thing about the ceiling are the " +
             "giant candelabra which hang from chains providing light " +
             "throughout the hall. " +
             "Inset within the eastern wall is large fireplace. Just above " +
             "the large fireplace mantle, hang six long banners dyed in " +
             "distinctive colours of the six Clans of Khalakhor. " +
             "A giant square-shaped table rests in the middle of the hall. ");

     add_item(({"candelabra","candles","candle"}),
             "The giant iron candelabra hang from strong chains precariously " +
             "above you. Several large candles set within provide much needed " +
             "light to the hall.\n");
     add_item(({"flags","flag","streamers","streamers"}),
             "The hall is filled with multi-coloured flags and streamers. " +
             "Its your best guess that they represent the various Clans " +
             "of the past and present.\n");
     add_item(({"tapestries","tapestry"}),
             "Various tapestries hang from the walls. The scenes upon the " +
             "tapestries are mainly of mythical creatures, demons and heros " +
             "doing battle in various situations.\n");
     add_item(({"square-shaped table","table"}),
             "The giant square-shaped table is large enough to seat a large " +
             "party. Its deep wood grain finish is mirror quality, yet strong " +
             "enough to handle heavy blows from its members pewter mugs.\n");
     add_item(({"mug","mugs","pewter mug","pewter mugs"}),
             "Alas, you dont see any mugs at the moment.\n");
     add_item(({"high-backed chair","chair","chairs","high-backed chairs"}),
             "Several high-backed leather cushioned chairs surround the " +
             "giant square-shaped table. Perhaps you might <sit down> in " +
             "one of them and take a rest..\n");
     add_item(({"large fireplace","fireplace"}),
             "The large fireplace looks large enough to hold several tall men " +
             "side by side. Or a large tree trunk. Its carved mantlepiece " +
             "lines the top of the fireplace.\n");
     add_item(({"mantlepiece","mantle"}),
             "The long mantlepiece was carved from a single piece of dark grained " +
             "wood which resembles same wood of the table.\n");
     add_item(({"banner","banners"}),"Which banner? <first, second, etc.>\n");
     add_item("first banner", &banner_desc("first"));
     add_item("second banner", &banner_desc("second"));
     add_item("third banner", &banner_desc("third"));
     add_item("fourth banner", &banner_desc("fourth"));
     add_item("fifth banner", &banner_desc("fifth"));
     add_item("sixth banner", &banner_desc("sixth"));


     add_cmd_item(({"sign","scroll", "tapestry", "chair", "table",
                    "banners","banner"}),
                   (({"get","take","burn","climb"})),
         "You fail to do so and should be ashamed for even trying.\n");

    add_exit("entrance", "west");
    add_exit("start", "north");
    add_exit("board", "south");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
  
    add_my_desc(seat_desc, this_object());
}




void
init()
{
    ::init();
    init_seat();
}


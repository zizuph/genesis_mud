/* File         : /d/Khalakhor/guilds/racial/clans/room/entrance.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : Entrance room to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the entrance to the default Clansmen guildhome.
 * Modifications: 
 */

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

public int
members_only()
{
    if (IS_MEMBER(this_player()) || this_player()->query_wiz_level())

    {
        /* Is a member, pass through as normal */

        return 0;
    }

    write("A magical force prevents you from entering.\nYou are not a "+
      "member of Clans of Khalakhor!\n");
    return 1;
}

void
create_guild_room()
{

    set_short("Clans of Khalakhor Entrance Foyer");
    set_long("You are standing in the foyer leading to the " +
             "hall of the Clans of Khalakhor. Several various " +
             "grey and green banners hang from the ceiling and " +
             "the walls. The floor was made with varyed shades " +
             "of granite flagstone forming the Celtic Cross with " +
             "two impressive looking golden lions back to back facing outward. " +
             "to the west is the exit leading to the street, to the east " +
             "is a massive open archway leading further into the hall.\n");

    add_item(({"lions","lion","floor","celtic cross","cross"}),
       "The floor within the foyer was pieced together with varied shades " + 
       "of flagstones creating an awesume image of the Celtic Cross with " +
       "two impressive looking golden lions standing before it facing outward.\n");

    add_item(({"flagstone","flagstones"}),"Granite flagstones fit tightly together " +
       "forming the floor below you.\n");

    add_item(({"arch","archway"}),"The archway is made from solid granite blocks. " +
       "Past the archway is the Hall of the Clans of Khalakhor.\n");

    add_item(({"entrance", "foyer"}),
      "This is the foyer leading to the Hall of the Clans of Khalakhor.\n");
      
    add_cmd_item(({"flags","banners"}),(({"get","take","burn","climb"})),
       "You fail to do so and should be ashamed for even trying.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  

    add_exit("hall", "east", members_only);
    add_exit("/d/Khalakhor/se_speir/port/room/road_12_6", "west");
  }

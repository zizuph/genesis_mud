/*
 * File Name        : pirate_drop_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : The drop room for the pirates guild.
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "../local.h"
#include <macros.h>
#include <std.h>

inherit MITHAS_IN;

object table;

void 
reset_mithas_room()
{
   if(!objectp(table))
   {
      table = clone_object(GUILD_OBJ + "table");
      table->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Underground treasure room");
    set_long("@@long_descr");

    add_exit("pirate_center_room","east",0,0);

    add_item(("table"),"This is a large oakwood table, that has been reinforced with "+
                       "tempered steel. It is on this table that the Pirates of the "+
                       "Bloodsea drop all of their loot and equipment, for others to "+
                       "enjoy.\n");
    reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing in a dark underground cave, beneath the isle of Mithas. The "+
          "black rock walls are drenched with water and the smell of the fresh seawater "+
          "and wet soil dominate this place. This might be a good place to hide yourself "+
          "or something. This room is the treasury of the Pirates of the Bloodsea, it is "+
          "here they drag all their loot and other treasures that they have "+
          "'acquired' during their adventures.\n";
}



#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include "/d/Ansalon/guild/dwarf/guild.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit DWARF_IN;

#define SB_OBJS    "/d/Ansalon/guild/shieldbearers/obj/"

object cabinet, chest, rack;

public void
reset_dwarf_room()
{
    if(!objectp(cabinet))
    {
	cabinet = clone_object(SB_OBJS + "cabinet");
	cabinet->move(TO);
    }

    if(!objectp(chest))
    {
	chest = clone_object(SB_OBJS + "armour_chest"); 
	chest->move(TO);
    }

    if(!objectp(rack))
    {
	rack = clone_object(SB_OBJS + "weapon_rack");
	rack->move(TO);
    }
}

public string
long_description()
{
    return "You stand in a spacious room just north of the Hall of " +
        "Warriors. This is where Neidars meet with other Shieldbearers to " +
        "discuss things that are important not only for the Clan. " +
        "There are several reinforced wooden, iron or steel shields " +
        "hanging on the walls, serving as a decoration. This is why " +
        "dwarves call this place the Hall of Shields.\n";
}

public void
create_dwarf_room()
{
    set_short("The Hall of Shields");
    set_long(long_description);
        
    add_item( ({ "shield", "shields", "decoration" }),
        "There are several shields decorating the walls of this room. " +
        "Some of them are ordinary, reinforced and wooden, but you " +
        "also notice a few made of iron or steel. These are a great " +
        "example of the dwarven craftsmanship.\n");
                        
    add_item( ({ "wooden shield", "wooden shields", "reinforced wooden shield",
        "reinforced wooden shields", "reinforced shields",
        "reinforced shield" }),
        "These shields look really ordinary, but you have no doubt that " +
        "they could last much more than a single hit by an ogre club.\n");
          
    add_item( ({ "iron shields", "iron shield", "steel shields",
        "steel shield" }),
        "The iron and steel shields, hanging on the walls are serving " +
        "as a decoration. All of them have been marked with a symbol of " +
        "two twin peaks, what means that they were crafted by the best " +
        "smiths of Iron Delving.\n");
        
    add_exit(GUILD_NEIDAR_ROOM_PATH + "start", "south", 0);

    clone_object(EPATH + "/obj/shield_board")->move(TO);
    reset_dwarf_room();

}


#include "/d/Ansalon/goodlund/nethosak/circle/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit GUILD_IN;

void
create_guild_room()
{    

    //THE BRIEF DESCRIPTION OF THE ROOM
    set_short("The equipment store.");

    //STANDARD DATE AND TIME DESCR + FULL DESCR.
    set_long("A dry warm heat prevails in this room. It is dimly lit with a couple "+
       "of torches attached to the walls. The entire room is cut from rough "+
       "dark grey stone, and seem no more than three meters across, with the "+
       "ceiling also hanging very low. "+
       "On the westwall is a several rows of shelves, and the north wall is "+
       "filled with a large wooden cabinet. Both of these is filled with "+
       "various tools. You notice that the floor is strewn with a thin "+
       "layer of hay, and a deadly silence hangs in the room."+
       "On the west wall is a low arch leading into a dark corridor going "+
       "north. And behind you is a staircase going up.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"wall", "walls"}),
       "The walls are all roughly cut from a dark grey stone. The stone "+
       "feels icy to the touch. Tiny patches of moss can be seen in the "+
       "cracks between the stones in the walls.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"floor"}),
       "The floor is roughly cut from a dark grey stone. The stone feels "+
       "very cold to the touch. The entire floor is strewn with a thin "+
       "layer of hay.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"hay"}),
       "A thin layer of hay is strewn through out the room.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ceiling"}),
       "The ceiling is roughly cut from a dark grey stone. It is "+
       "hanging very low. You can see tiny roots appearing through the"+
       "cracks in the stones of the ceiling.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"shelves", "shelf"}),
       "The entire wall is covered with shelves from top to bottom. "+
       "On each shelf is a small name tag. You quickly find the shelf "+
       "belonging to you. There you find your guild equipment "+
       "available to you. There is:\n "+
       "A herb pouch\n "+
       "A pair of herbalist gloves\n "+
       "A roughly made backpack\n "+
       "A dark grey mortar\n "+
       "You can take one of each if you require it.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"name tags", "tags"}),
       "You see each shelf has a name tag.\n "+
       "You see tags bearing the name:\n "+
       "Mortimor\n "+
       "Ruben\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"cabinet"}),
       "This is a large wooden cabinet. It fills most of the "+
       "northwall, and stands from the top of the room to the bottom. "+
       "You can see a small row of ornamentation a the top of the cabinet. "+
       "Inside you see many items nicely arranged: "+
       "A jagged black scimtar\n "+
       "A double morningstar\n "+
       "A huge mithril shield\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"ornamentation", "row"}),
       "You see a small row of carvings in the top of the cabinet. "+
       "It seems to depict rats running from east to west in a straight line.\n");

//AN ITEM THAT THE PLAYER CAN EXAMINE AND SEARCH.
    add_item(({"arch"}),
       "A low stone arch leading into the corridor. Along it is carved into "+
       "the stone:\n "+
       "'Obey thy Master, lest the Black Wind devour you'\n");

    //THE EXITS OUT OF THE ROOM.
    add_exit(GROOM + "storage1","up",0);
    add_exit(GROOM + "corridor1","east",0);
}
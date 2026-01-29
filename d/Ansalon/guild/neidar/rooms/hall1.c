#include "/d/Ansalon/common/defs.h"
#include "../guild.h"
#include "/d/Ansalon/estwilde/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit DWARF_IN;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"passageway","hallway"}),
      "You stand in a hallway decked with trophies that mark the glory of " +
      "the dwarven clan of Iron Delving.\n");
    add_item(({"audience chamber","chamber","hall","hall of the thane"}),
      "To your southeast opens the Hall of the Thane, " +
      "the audience chamber of the leader of the hill dwarves.\n");
    add_item(({"trophies","trophy"}),
      "On either side of the hallway rest a number of trophies " +
      "marking the glories of the dwarven clan. Among them you notice " +
      "a giant battleaxe, a blood-red battle standard, the head " +
      "of a wyvern, a wolf-skin tunic, and a wicked barbed spear.\n");
    add_item(({"giant battleaxe","battleaxe"}),
      "This is the battleaxe of the frost giant Fnorsk, who was " +
      "slain by two dwarven warriors in the Khalkist Mountains " +
      "90 years ago.\n");
    add_item(({"battle standard","standard","blood-red battle standard"}),
      "This is the battle standard of the Blood Mountain goblin horde, " +
      "defeated and routed by the dwarven clan of Iron Delving.\n");
    add_item(({"head of a wyvern","wyvern head","head"}),
      "This wyvern terrorised the livestock of Iron Delving " +
      "for many years, before being caught and slain by a young " +
      "dwarven warrior, who survived the poison of many of its " +
      "stings to victoriously bring back the corpse of this fell beast.\n");
    add_item(({"wicked barbed spear","barbed spear","spear"}),
      "This wicked barbed spear was once held by the human chieftain " +
      "of the tribe of the Black Ravens of Southern Estwilde.\n");
    add_item(({"wolf-skin tunic","tunic"}),
      "This rough wolf-skin tunic was that worn by the ogre tyrant of " +
      "Kern some 150 years ago. It was taken from his corpse after being " +
      "defeated singlehandedly by the renown giantslayer Shale Ironfist of " +
      "the Hollowlands.\n");

    add_exit(GUILD_ROOMS + "joinroom","southeast",0);
    add_exit(IRON + "r16","northwest",0);

    reset_dwarf_room();
}

string
short_descr()
{
    return "The passageway of Glory";
}

string
long_descr()
{
    return "You stand at the entrance to the Hall of the Thane " +
    "before the passageway that leads to the main audience " +
    "chamber. On either side of this large hallway hang the " +
    "trophies of clan victories, thus giving name to this room as " +
    "'The passageway of Glory'.\n";
}

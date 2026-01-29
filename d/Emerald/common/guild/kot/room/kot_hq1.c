/*
 * KOT_HQ1.c
 * This is the Common Room of the Keepers of Telberin
 * - Alaron January 1997
 */

#include "../guild.h"
#include "/d/Emerald/telberin/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";

void
create_room()
{
    set_short("Common Room");
    set_long("   The small, wood-walled room basks in the flickering "+
      "amber glow of dozens of thick, white candles. Each of the "+
      "candles is supported by a gleaming golden candle-holder "+
      "coming out of the wall. The walls are a fine, polished "+
      "mahogany which reflects the flickering candlelight across "+
      "the sparsely decorated room. Centered in the middle of "+
      "the southern wall is an enormous, ancient-looking parchment "+
      "with a map of the city of Telberin on it.\n"+
      "   There are two narrow doorways leading off into dimly "+
      "lit rooms to the northwest and northeast. There is a closed "+
      "oak door in the east wall, and a depression in the west "+
      "wall which denotes the location of the exit.\n\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({"walls", "wooden walls", "wood", "mahogany",
	"polished mahogany", "wood walls"}),
      "The walls of the room are a finely polished mahogany. You "+
      "wonder at the expense of lining this room with wood when "+
      "you know that beneath the wooden walls lies the cold stone "+
      "of the castle.\n");

    add_item( ({"candles", "thick candles", "white candles", 
	"thick white candles"}),
      "Thick, white candles provide ample light for manuevering "+
      "through this room. The flickering amber glow creates "+
      "dancing shadows in the corners and on the ceiling. The "+
      "shadows disappear down the hallways leading northwest "+
      "and northeast.\n");

    add_item( ({"holders", "candle holders", "gleaming candle holders",
	"golden candle holders", "gleaming golden candle holders",
	"holder", "candle holder", "candle-holders",
	"candle-holder"}),
      "The golden candle holders gleam reflectively in the wavering "+
      "candlelight of the room. Each of the holders just out of "+
      "the wooden wall from a gold plate with a curved golden arm "+
      "holding the candle itself.\n");

    add_item( ({"parchment", "map", "map of telberin", "telberin map",
	"ancient parchment"}),
      "The map contains drawings and depictions of various points "+
      "throughout the city of Telberin. The map looks to be very "+
      "helpful for planning strategies of defending the city.\n");

    add_item( ({"doorway", "door", "doors", "doorways", "narrow doorways"}),
      "The narrow doorways lead out of the room into dimly lit "+
      "corridors heading northwest and northeast.\n");

    add_item( ({"oak door", "east door"}),
      "The huge oak door in the east wall seems to be extremely "+
      "sturdy.\n");

    add_item("depression",
      "The depression in the west wall marks the location of the "+
      "false fireplace that conceals the true location of the "+
      "Keepers.\n");

//  add_exit(CASTLE_DIR + "3k3", "west");
    add_exit("kot_hq3", "northwest", "@@no_Order@@");
    add_exit("kot_hq2", "northeast", "@@no_Prot@@");
    add_exit("shop", "east");
}

int
block_east()
{
    write("It looks like this door has been sealed shut. Perhaps it "+
      "will be opened in the future.\n");
    return 1;
}

int
no_Order()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    if (this_player()->query_kot_caste() != WARRIOR_CASTE)
    {
	write("You sense that you should not be entering the training "+
	  "room of the Protectorate.\n");
	return 1;
    }
    if (this_player()->query_race() != "elf")
    {
	write("You look in the room and see elves training in spiritual "+
	  "rituals. Obviously not a place for a "+
	  this_player()->query_race_name()+"\n");
	return 1;
    }
    if (this_player()->query_guild_name_race() != GUILD_NAME)
    {
	write("You hesitate before entering and realize that the "+
	  "training room is only for the appointed protectors "+
	  "and you aren't one!\n");
	return 1;
    }
}

int
no_Prot()
{
    if (this_player()->query_wiz_level())
    {
        return 0;
    }

    if (this_player()->query_kot_caste()!=CLERIC_CASTE)
    {
	write("You sense that you should not be entering the training "+
	  "room of the Order.\n");
	return 1;
    }
    if (this_player()->query_race() != "elf")
    {
	write("You look in the room and see elves training in combat "+
	  "abilities. Obviously not a place for a "+
	  this_player()->query_race_name()+"\n");
	return 1;
    }
    if (this_player()->query_guild_name_race() != GUILD_NAME)
    {
	write("You hesitate before entering and realize that the "+
	  "training room is only for the appointed protectors "+
	  "and you aren't one!\n");
	return 1;
    }
}

int
block_council()
{
    if (!this_player()->query_kot_council())
    {
	write("As you place your hand upon the council chamber door, you "+
	  "feel a surge of pain going through your arm, and hear a voice "+
	  "echo through your soul accompanied by a pang of nausea:\n"+
	  "\t\"None but those chosen to rule the Keepers may pass!\"\n");
	return 1;
    }
    else {
	write("You push open the council chamber door, making sure to "+
	  "seal it shut behind you.\n");
	say(QCTNAME(this_player())+" pushes open the oak door, quickly closing it shut "+
	  "behind "+this_player()->query_objective()+".\n");
	return 0;
    }
}

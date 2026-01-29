#include "defs.h";

inherit LAKESHORE_ROOM;


string *elf_adj_descs = ({"fair-skinned", "dark", "pale", 
			  "tanned", "green-eyed", "blue-eyed",
			  "brown-eyed", "hazel-eyed", "purple-haired",
			  "blue-haired", "blond-haired", "brown-haired",
			  "dark-haired", "red-haired", "green-haired"});

string *elf_adj_descs_2 = ({"beautiful", "stunning", "slender",
			    "vivacious", "lively", "tall",
			    "plain", "merry", "mysterious",
			    "charming", "excited", "jolly",
			    "delicate", "petite", "pretty"});

string *painter_adj_descs = ({"frustrated", "calm", "charming",
			      "zany", "crazy", "energetic"});

string *painter_adj_descs_2 = ({"arrogant", "haughty", "friendly",
				"philosophical", "demure", "engenious"});

string *painting_descs = ({"an abstract landscape", "a still life of the city",
			   "a warped image of the surroundings",
			   "a reflection of the crystal blue lake water"});

object *painter;

void 
create_lakeshore_room()
{
    set_short("Artist gathering");
    set_em_long("Many artists gather here. Painters " +
		"setup canvases on the cobblestone path to paint " +
		"the beautiful landscape. Some are here to " +
		"draw inspiration from the spectacular view, others " +
		"are here here to make a living. A couple elves are " +
		"getting their portraits painted with the majestic " +
		"peaks and crystal blue lake as the background.\n");
    add_item(({"lake", "waters", "water"}),
	     "The lake water is crystal pure.\n");
    add_item(({"path", "cobblestone", "cobblestone path"}),
	     "The cobblestone path is somewhat messy. Spots of paint " +
	     "drippings dot the path here.\n");
    add_item(({"peak", "peaks", "landscape", "view"}),
	     "The majestic white peaks seem to rise out of the water " +
	     "on the far end of the lake. It is no wonder so many " +
	     "artists gather here.\n");
    add_item(({"artists", "painters"}),
	     "Most painters are concentrating hard on capturing " +
	     "the essence of the beauty of the landscape on canvas. " +
	     "@@query_painters@@\n");
    
    set_tell_time(50);
    add_tell("@@paint_tell@@");
    add_tell("@@artist_tell@@");
    
    add_exit("beach04", "southeast");
    add_exit("beach02", "northwest");
}

string 
query_painters()
{
    if (debug(painter) == O_DESTRUCTED)
      {
	return "";
      }
    
    return "However you spot a painter eager to paint something " +
      "for you for a small fee.";
}

init()
{
    /*
      painter = clone_object(LAKESHORE_NPC_DIR + "painter");
    */
    start_room_tells();
    ::init();
}

void 
reset_room()
{
    /*
      if (debug(painter) == O_DESTRUCTED)
      {
      painter = clone_object(LAKESHORE_NPC_DIR + "painter");
      }
    */
    ::reset_room();
}


string 
paint_tell()
{
    return "A " + elf_adj_descs[random(15)] + " " + 
      elf_adj_descs_2[random(15)] +
      " female elf sits down on a chair and gets her portrait painted " +
      "with the lake and mountain in the background.\n";
}

string
artist_tell()
{
    return "A " + painter_adj_descs[random(6)] + " " +
      painter_adj_descs_2[random(6)] + " male elf dabbles " +
      "some paint onto a canvas. The canvas seems to be transforming " +
      "into " + painting_descs[random(4)] + ".\n";
}

#pragma strict_types;
#pragma save_binary;

inherit "/d/Shire/std/room";

#include "defs.h"
#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <filter_funs.h>


void
create_shire_room()
{
    set_short("Glinghant, the gardens of Annuminas");
    set_long("@@my_long@@");

    add_item(({"pillars", "pillar", "tall pillars"}),
        "The pillars are massive, and stand symmetrically in two " +
        "rows along the east, west, north and south walls of the " +
        "hall. The pillars to the east appear to be most intact, " +
        "while the others are crumbling in various stages of decay.\n");
    add_item(({"floor", "marble floor", "tiled marble floor", "slabs",
        "marble slabs"}), 
        "The floor is blackened, yet mostly intact. Here and there the " +
        "slabs of marble tiles have been shattered as if with great " +
        "force. Most of the floor is covered in brackish water.\n");
    add_item(({"ceiling"}),"The ceiling extends overhead into the " +
        "overarcing darkness above. Since it blocks any light from sun " +
        "or stars, you assume that it must be mostly intact.\n");
	add_item("hole", "@@hole_desc@@");
	add_item(({"exit","northern exit","north","north exit"}),
        "You can just make out the archway along the northern side " +
        "of the great hall. It appears to be blocked by a large pile " +
        "of rubble and debris.");
	add_item(({"walls","wall"}), "The stone walls have been " +
        "stripped bare of decoration.\n");
	add_item(({"statue"}),"@@test_statue@@");
	add_item(({"vine","vines"}), "@@test_vines@@");
	add_item(({"flower","flowers","red flowers","red flower",
              "white flower","white flowers"}), "@@test_flowers@@");
	add_item(({"water","brackish water"}), "A sheen of dark, stale " +
         "smelly water covers the floor. It appears to be shallow, but " +
         "you can't be certain due to the indeterminable condition of " +
         "the floor.\n");  
	add_item(({"mirror pool","pool","pond"}),"The mirror pool extends " +
   		"from the southern entrance to the northern entrance, splitting " +
   		"about three quarters of the way east and west. It resembles a " +
   		"large cross-like pattern. The pool once reflected rays from " +
   		"the glass domed ceiling about throughout the great hall. " +
        "Its once sparkling mosaic patterned tile can be seen in bits " +
        "and pieces throughout the debris. However, Small brackish " +
        "pools of water can be seen at the center and pooled along the " +
        "edges. Several large holes from fallen pieces of the domed " +
        "ceiling have damaged have shattered the once stunning mosaic " +
        "surface of the pool.\n");
	add_item(({"mosaic","surface","pool mosaic"}),"From the bits and " +
   		"pieces, you determine the tiles were made from small squares " +
   		"of multi-colored tiles with bits of shiny mica mixed in to  " +
   		"help reflect the sun rays throughout the hall.\n");
	add_item(({"mica"}),"a shiny silicate mineral with a layered " +
   		"structure, found as minute scales in granite and other " +
   		"rocks, or as crystals.\n");
   
	add_cmd_item("mica", "get", "the minute pieces are far too small " +
   		"and are mixed directly into the tiles. Its impossible for you " +
   		"to collect any.\n");      
	add_cmd_item("flower", "smell", "You're too far away to smell the " +
   		"flowers.\n");
	add_cmd_item("flower","pick","You're too far away to smell the " +
   		"flowers.\n");
	add_cmd_item("vine","cut","You're too far away to cut the vine.\n");

	add_exit(ANN_CASTLE_DIR + "01_01", "south", 0, 0);
    
	add_prop(ROOM_I_INSIDE,1);
	add_prop(ROOM_I_LIGHT, 1);

	set_room_tell_time(random(900));
	add_room_tell("You sense something moving in the shadows.");
	add_room_tell("You hear a subtle rustling sound, coming from the " +
		"floor.");
   add_room_tell("Its quiet, too quiet..");
}

int
test_vines()
{
	if (CASTLE_GLINGHANT_VINEROOM->query_vinecreeper())
	{
		write "The vines form and wind long the base of a " +
          "large statue standing in the center of the great " +
          "hall. They continue  to twist along the two sets " +
          "of pillars that run the length of the pool extending " +
          "in every direction to the walls of the great hall, " +
          "climbing to the cracked dome ceiling above.\n";
		return 1;
    }
}


int
test_statue()
{
	if (CASTLE_GLINGHANT_VINEROOM->query_vinecreeper())
	{
        write  "From this distance, and poor lighting, you can just " +
               "just make out bits and pieces of a tall marble statue " +
               "at the center of the great hall. Its mostly covered in " +
               "vines.\n";
        return 1;
    } else
        write "From this distance, and poor lighting, you can just " +
               "just make out bits and pieces of a tall marble statue " +
               "at the center of the great hall.\n";
		return 1;
}
        
        
string
test_flowers()
{
	if (CASTLE_GLINGHANT_VINEROOM->query_vinecreeper())
	{
       if (TP->query_skill(SS_HERBALISM) > 80)
       {
			write "Tiny red and white flowers grow along " +
                 "some of the vines. Red flowers grow closer to " +
                 "the source of the vine, whereas, white flowers grow " +
                 "closer to their tips. However.. Your herbalist " +
                 "training tells you that these don't appear to be " +
                 "flowers at all. The stems appear to be more veinlike, " +
                 "and the petals far to leathery It looks more like " +
                 "animal than plantlike. Upon closer inspection, the red " +
                 "flowers seem to pulse in concert with one another.\n";
			return 1;
       } 
       else 
			write	"Tiny red flowers can just be seen beginning from " +
					"the origin of the vine, turning white towards " +
					"the ends of the vines.";
			return 1;
    }
}


int
my_long()
{
	if (CASTLE_GLINGHANT_VINEROOM->query_vinecreeper())
    {
		write (
        "You stand at the top of a great marble stairway, descending into " +
        "the great hall of the Glinghant, the gardens of Annuminas. Once " +
        "a place of great beauty, now overgrown and fallen into ruin. " +
        "The marble tiled floor is still somewhat intact, as are four rows " +
        "of tall pillars running south to north, and another two rows running, " +
        "east to west converging at the center of the hall. Between the pillars " +
        "is a shallow rectangle mirror pool. Portions of a large statue " +
        "in decay rests at the pool cross center. Small brackish " +
        "pools of water can be seen at the center and pooled along the edges. " + 
        "Plants of different types seem to thrive in the brackish water that " +
        "covers most of the marble tiled floor. The walls and various surfaces " +
        "are stained by years of mold and mildew. Flowery thorned vines seem " +
        "cover everything from the floor to the cracked dome above. " +
        "Several large holes from fallen pieces of the domed ceiling have damaged " +
        "the mosaic surface of the pool.  The stone walls have been stripped bare of decoration, " +
        "and what was once a graceful room full of light, beauty and music " +
        "is dark and still as a tomb. The hall extends in all directions. " +
        "Its hard to make out from this distance in this poor lighting, but " +
        "another exit can be seen at the end of the hall to the north, but " +
        "appears blocked by rubble. Its very humid here.\n");
		return;
    } else 
    write (
        "You stand at the top of a great marble stairway, descending into " +
        "the great hall of the Glinghant, the gardens of Annuminas. Once a " +
        "place of great beauty, now overgrown and fallen into ruin. " +
        "The marble tiled floor is still somewhat intact, as are four rows " +
        "of tall pillars running south to north, and another two rows running, " +
        "east to west converging at the center of the hall. Between the pillars " +
        "is a shallow rectangle mirror pool. Portions of a large statue " +
        "in decay rests at the pool cross center. Small brackish " +
        "pools of water can be seen at the center and pooled along the edges. " +
        "Plants of different types seem to thrive in the brackish water that " +
        "covers most of the marble tiled floor. The walls and various surfaces " +
        "are stained by years of mold and mildew. " +
        "Several large holes from fallen pieces of the domed ceiling have damaged " +
        "the mosaic surface of the pool.  The stone walls have been stripped bare of decoration, " +
        "and what was once a graceful room full of light, beauty and music " +
        "is dark and still as a tomb. The hall extends in all directions. " +
        "Its hard to make out from this distance in this poor lighting, but " +
        "another exit can be seen at the end of the hall to the north, but " +
        "appears blocked by rubble.\n");
	return 1;
}

void
reset_glinghant_room()
{
}


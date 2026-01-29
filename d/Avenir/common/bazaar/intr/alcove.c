
inherit "/std/room";
#include "../bazaar.h"

static object qalita;

void
reset_room()
{
    if (!qalita)
    {
         qalita = clone_object(NPC + "dancer");
         qalita->arm_me();
         qalita->move_living("M", this_object());
    }      
}

void
create_room()
{
    set_short("Alcove with brazier and musician");
    set_long("A small, softly illuminated room draped from floor-to-"+
        "ceiling with brocaded silks. Satin cushions in an array of "+
        "sizes and colours lie upon plush carpets. Upon a low table "+
        "rests a brazier with burning incense. A manservant sits in "+
        "a corner, his fingers gently strumming a sitar."+
        "\n");
    add_item(({"brazier", "incense"}),
        "A circular brass recepticle containing coals for warming "+
        "the room. Incense has been sprinkled on the coals, creating "+
        "a spicy-musk scent in the air.\n");
    add_cmd_item(({"air"}), "smell", "It smells good.\n");
    add_item(({"ceiling", "curtains", "silk", "silks", "brocaded silks"}),
        "The silks are luxurious and very heavy. They muffle the sounds "+
        "from the dance-floor while enhancing the feeling of "+
        "seclusion.\n");
    add_item(({"cushions", "pillows", "cushion", "threads"}),
        "There are cushions for sitting and cushions for reclining. "+
        "Some are patterned with geometric shapes, others are em"+
        "broidered with gold and silver threads.\n");
    add_item(({"carpets", "carpet", "floor"}),
        "The floor is covered by several layers of carpets. The carpets "+
        "are plush and sewn by hand. The designs on the carpets are "+
        "both intricate and vibrant with colour.\n");
    add_item(({"manservant", "man", "servant"}),
       "Slender and dark-haired, he has nimble fingers and a "+
       "quiet, unobtrusive manner. In his lap he holds a sitar.\n");
    add_item(({"sitar", "instrument"}),
       "It is a type of lute with a small, pear shaped body and "+
       "a long, broad, fretted neck.\n");
    add_item(({"beads", "beaded doorway"}),
       "The beads are made of coloured glass. They are hung in long "+
       "strings and provide an effective screen for the exit east.\n");
  
    add_prop(ROOM_M_NO_ATTACK,"You have no desire to interrupt the "+
       "tranquility of this room.\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "You have no desire to interrupt "+
       "the tranquility of this room.\n");

    add_exit(INTR + "gogo", "south", 0);
    add_exit(INTR + "clubroom","north","@@thru_beads");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

reset_room();
}

int
thru_beads()
{
    write("You push your way through the long strands of beads "+
        "which screen the doorway.\n\n");
    return 0;
}


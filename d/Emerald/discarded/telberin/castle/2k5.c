/*
 * 2k5.c
 * Second floor hallway, Castle Telberin
 *   - Alaron September 11, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway");
    set_long("   The noise of the unseen crowd is loud here, resembling "+
	     "the din of a group of people loudly discussing an issue "+
	     "of some sort. The dim, amber glow of the lamplight "+
	     "is reflected in the emerald green walls. The walls have "+
	     "been so expertly carved and fitted that you have to "+
	     "squint and struggle to see the lines where the stones "+
	     "are joined. This is a sharp-angled corner in the hallway. It "+
	     "proceeds to the northwest and to the southwest, both "+
	     "continuing on into the faint, comforting glow of the "+
	     "wall-hung lamps.\n\n");

    add_item( ({"glow", "comforting glow","lamps", "wall-hung lamps", "lamplight"}),
	     "The beautiful (and probably very expensive) wall-hung "+
	     "lamps provide a soft, comforting and warm glow throughout "+
	     "the hallway. The only thing that disturbs the solemn, "+
	     "peaceful glow are the noises echoing from the crowd "+
	     "gathered to the southwest.\n");

    
   add_exit(CASTLE_DIR + "2k13","southwest",0);
   add_exit(CASTLE_DIR + "2k4","northwest",0);
}

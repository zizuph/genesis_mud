inherit "/std/object";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/cmdparse.h"
#define QUEST_AMULET "_quest_amulet_"

void
create_object()
{
    	::create_object();
    	set_name("amulet");
    	set_adj("steel");
    	add_adj("rough");
    	set_short("rough steel amulet");
    	set_long("This rough steel amulet has strange grooves "
		+"etched into its surface.  Looking at the back of "
		+"it you notice some words written in a rough semblance "
		+"of the common tongue.\n");
	add_prop(QUEST_AMULET, 1);
   	add_item("words","They look like they spell a name: Kranj'k. "
		+"It also appears to say freedom.\n");
   	add_prop(OBJ_I_VALUE,750);

}


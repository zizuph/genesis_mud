/* File: /d/Shire/common/trollsh/rivend1.c */

#include "defs.h"

inherit "/d/Shire/common/lib/eastroad";	/*master object*/

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going east of Bree. "+
	  "You are standing southeast of the Last Bridge, the path "+
	  "continues eastwards deeper into the Trollshaw. The forest "+
	  "is getting darker as you move on into it, and it "+
	  "looks a little frightening here. Lots of strange noises "+
	  "can be heard, but it is hard to make out where they come from.\n");

    add_item(({"eastroad", "road" }),
	"The road is narrower here then at the bridge, only about 2 meters wide.\n"+
	"It looks like it has been used a lot. \n"
  );
    add_item(({"sand"}),
	"The sand seems to be dry. Hmm...you wonder where it came from.\n");

   "/d/Shire/common/trollsh/shaws16"->teleledningsanka();
    SOUTHEAST("rivend2");
    add_exit(ERE_DIR + "erb38", "northwest", 0);
}

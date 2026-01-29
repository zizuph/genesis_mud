inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in the northwest corner of a huge dry plain just in front "+
        "of a large tower. It it is quite high although it seem to have lost one or two levels. "+
	"Many tales are told about these fields and you have to be a little stupid to force yourself "+
	"to enter them. The only thing you can make out is that there are some hills on a far distans. "+
	"In the southern parts many battles were fought many years ago. Maybe some warriors still raid "+
        "this area. You think you can live with the loss of that knowledge. If you continue to the west "+
        "you will end up on a large hill. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(BARBHILL+"bh26","west");
	add_exit(DRYPLAIN+"dpc8","east");
}

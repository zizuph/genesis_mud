inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are standing in high grass in and you should have felt quite  "+
	"lost if it hasn't been for the large tower to your northwest and the crossing to northeast. "+
	"To the north you look down in a valley with high steps on three sides. It is impossible to "+
	"climb down however it seem that you can enter it from the east. When you turn to face towards  "+
        "the south you feel happy you you don't have to walk the long way up here. \n",70));
	add_item((("gras")),"maybe you can pick it up");
	add_exit(DRYPLAIN+"dpc6","northwest");
	add_exit(DRYPLAIN+"dpc2","northeast");
}

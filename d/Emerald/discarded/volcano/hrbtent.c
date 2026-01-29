// Herbshop
// run by one of native women who specializes in herbal healing
// she may eventually be able to sell home-made remedies ?

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"

create_room()
{
	set_short("Herb Shop");
	set_long(break_string("A large roomy tent set up by one of the native women. " +
	"Here she has establishes a storing place for herbs she has gathered in the surrounding " +
	"area.  This is one of the few enterprises of the camp " +
	"and the shopkeeper is quite willing to buy or sell you herbs.\n",75));

	add_exit("cp5.c", "out");
	add_exit("storerm.c", "back", "@@wiz_check@@");

add_prop(ROOM_I_LIGHT,1); 
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_M_NO_ATTACK, 1);


}

int
wiz_check()
{
    if (this_player()->query_wiz_level())
        return 0;
	write("Only the merchant and wizards are allowed to go back there!\n");
    return 1;
}

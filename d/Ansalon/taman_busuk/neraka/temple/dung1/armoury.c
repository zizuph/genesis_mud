/* This is the PoT droproom.
 * It would be ever so nice if there were racks for weapons, shelves for 
 * armour and a chest for other stuff.
 */

#pragma strict_types

#include "../defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    ::create_temple_room();

     set_short("In the Armoury");
    set_long("This is a neat and clean room with racks and shelves along " +
        "two walls and a chest by the third. In one corner a rubbish " +
        "bin stands. In another corner exists an ominous, black hole. "+
	"Everything is kept in perfect " +
        "order as each thing is standing in its place.\n");

    setuid();
    seteuid(getuid());

    clone_object(GUILDDIR + "obj/trash")->move(this_object());
    clone_object(GUILDDIR + "obj/rack_wep")->move(this_object());
    clone_object(GUILDDIR + "obj/rack_armour")->move(this_object());
    clone_object(GUILDDIR + "obj/rack_misc")->move(this_object());
    clone_object(GUILDDIR + "obj/rack_garbage")->move(this_object());

    clone_object( DOOR + "armoury2")->move(this_object());
//    add_exit( DUNGONE + "corr8.c", "east" );
}

// creator(s):  Kazz    Feb '95
// last update:
// purpose:     connects the ledge from the piers to the outpost
// note:
// bug(s):
// to-do:  

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";


void
init()
{
    ::init();
    add_action( "do_eat", "eat" );
}


create_room()
{
	SHORT("Inside tunnel near ledge");
	LONG( "You stand within a dimly lit tunnel. Damp wind "+
	      "blows down from the northwest, where you can see a ledge "+
	      "through hazy light. The tunnel walls are damp, providing "+
	      "a home for lichen. The tunnel continues southeast, down "+
	      "into darkness.\n" );

	add_exit(LEDGE + "ledge9","northwest",0);
	add_exit(OUTPOST + "path2","southeast",0);

	add_item(({"tunnel"}), 
		 "The tunnel's walls and floor glisten with moisture.\n");
	add_item(({"floor"}),
		 "The tunnel floor isn't as wet or slippery as the ledge, " +
		 "but nearly.\n" );
	add_item(({"wall", "walls"}),
		 "The eastern side is " +
		 "naturally smooth, yet the west is chiseled. The walls are "+
		 "damp from the air, and yellow-ish " +
		 "lichen grows in spots on the western wall.\n" );
	add_item(({"moisture"}),
		 "The walls seem to be damp from the air,\n" );
	add_item(({"lichen", "yellow lichen", "yellow-ish lichen"}),
		 "It's yellow. If you were starving you might be able to " +
		 "eat it.\n" );
	add_item(({"ledge"}),
   		"The ledge is not very wide, and looks rather slippery.\n" );
	add_item(({"wind", "damp wind", "air"}),
   		"The wind feels damp and may indicate a water source.\n");

	LIGHT
	IN

} // create_room()


int
do_eat( string str )
{

    NF( "Eat what?\n" );
    
    if ((str == "lichen") || (str == "yellow lichen") ||
	(str == "yellow-ish lichen")) {
       
        clone_object(OBJ + "lichen_taste")->move(this_player());

	this_player()->catch_msg (
			"You pull some lichen off the damp tunnel wall "+
			"and place it in your mouth. As you chew, a "+
			"foul, warm taste fills your mouth. You swallow "+
			"and feel the lichen slide greasily down your "+
			"throat.\nYour tongue now tastes like something "+
			"died on it.\n");
  	say (QCTNAME(this_player()) +
	     " eats something from the tunnel wall." );
	return 1;
    } // if they want to eat lichen

    // they want to eat something else?
    return 0;
    
} // eat()

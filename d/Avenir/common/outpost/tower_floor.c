// file name: d/Avenir/common/outpost/tower_floor.c
// creator(s):  Kazz    Feb '95
// purpose:     bottom room of the tower
// note:
// revisions:   Lilith Apr 2022: updates for Fort makeover	

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit OUTPOST +"fort_base";
inherit "/d/Genesis/lib/post";

void
create_fort_room()
{
    set_short("the Fort Sybarus Postal Center, ground floor");
    set_long("You are on the ground floor of the largest "+
      "tower of Fort Sybarus. "+
      "There is something both reassuring and oppressive "+
      "about the thickness and weight of the stone used "+
      "to build it. "+
	  "This appears to be a postal processing center for "+
	  "mail between Sybarus and the rest of the world. "+
      "Stone stairs lead up into flickering light. "+
	  "The door in the north wall is the only other exit.\n" );

    add_exit(OUTPOST + "tower_middle1", "up",0);
    add_fort_room();   
    add_exit_views();
	
    add_item(({"fort", "large fort", "black fort"}),
      "The fort is built with the blackest, smoothest "+
      "stone and seems very solid.\n" );
    add_item(({"tower", "black tower"}), 
      "The tower is made of the same black rock as much of the "+
      "fort. You can't determine how high it is.\n" );
    add_item(({"door", "north"}),
      "The black stone door is closed. It seems to lead out of "+
      "the tower.\n");
    add_item(({"stairs", "stone stairs"}),
      "The stairs lead up to another room in the tower. Based on "+
      "the view from the cavern, it probably doesn't lead to the "+
      "top floor.\n" );

    add_prop(ROOM_M_NO_ATTACK, "You get a feeling that the goddess "+
      "Nantur disapproves of fighting in this place.");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "You get a feeling that the goddess "+
      "Nantur disapproves of fighting in this place.");
    add_prop(ROOM_M_NO_ATTACK, "Mmmm... on second thought, maybe not.\n");

    IN_IN;
	LIGHT;

    room_add_object(OUTPOST +"obj/seats/basalt_bench", 1);
    room_add_object(OUTPOST +"obj/seats/obsidian_bench", 1);
	add_npc(OUTPOST +"mon/dw_guard", 2);

} // create_room()


int 
do_open( string str )
{
    object tp = this_player();
    object fort_room;

    notify_fail( "Open what?\n" );

    if ((str == "door") || (str == "north door") || (str == "tower door")){
	tp->catch_msg( "You open the tower door and leave.\n" );
	tp->move_living( "M", OUTPOST + "fort2", 1 );
	tell_room( this_object(), QCTNAME(tp) +
	  " opens the tower door and leaves.\n" +
	  "The door closes silently.\n", tp );
	tp->catch_msg("The wide wooden door closes behind you.\n" );
	fort_room = find_object( OUTPOST + "fort2.c" );
	tell_room( fort_room, QCTNAME(tp) + " arrives from the tower.\n", tp);
	return 1;
    }

    return 0;
} // do_open()



void
init()
{
     ::init();
    post_init();

    add_action("do_open", "open" );
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}

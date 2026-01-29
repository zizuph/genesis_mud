// file name: d/Avenir/common/outpost/fort2.c
// creator(s):  Kazz    Feb '95
// last update: Cirion, Feb 1996
//                Added Kilnar to this area, see 
//                   ~Avenir/private/QUESTS/outpost_water.doc
// purpose:     first fort room entered via the gate (from cave2)
// note:	
// bug(s):
// to-do:       show the person standing on the ledge

# pragma strict_types
# include "/d/Avenir/common/common.h"
# include "/d/Avenir/common/outpost/outpost.h"

inherit "/std/room";

void reset_room();
int do_open(string str);

object kilnar;

void
init()
{
    ::init();
    add_action(do_open, "open" );
}

void
create_room()
{
    set_short("Inside fort, near gate");
    set_long("You stand within the black stone fort. Before you, the " +
             "large, black, stone gate of the fort. It stands open, and " +
             "leads out into the cavern. Several armoured dwarves wander " +
	     "around. More dwarves can be seen and heard through the open " +
	     "doorway to the north. The tall black tower stands immediately " +
	     "to your south. The dark, black door of the tower is closed. " +
	     "The fort continues into a wider room to the east. A large " +
	     "black, stone gate is open to the west, and leads out of " +
	     "the fort.\n");

    add_exit(OUTPOST + "cave2","west",0);
    add_exit(OUTPOST + "fort1","north",0);
    add_exit(OUTPOST + "fort5","east",0);

    add_item(({"fort", "tall fort", "black fort", "tall black fort"}),
      "The fort is built with the blackest, smoothest "+
      "stone and seems very solid.\n" );
    add_item(({"gate", "fort gate", "stone gate"}),
      "The black stone gate is open, providing exit to the west. "+
      "A closed metal window is visible on the north side of the "+
      "door, about eight feet off the ground.\n" );
    add_item(({"dwarves"}),
      "The dwarves walk from the north room to the east. They "+
      "are dressed for fighting.\n" );
    add_item(({"doorway"}),
      "It leads to a busy room to the north.\n");
    add_item(({"door", "tower door"}),
      "The black tower door is closed. You don't hear any noise "+
      "coming from behind it.\n" );
    add_item(({"tower", "black tower"}),
      "The tower stands high above the fort. "+
      "The curving cavern ceiling meets the tower just above "+
      "a high window.\n" );
    add_item(({"tower window", "high window"}),
      "It looks out over the fort. You can't see within the "+
      "tower window, it is too high.\n" );
    add_item(({"metal window", "window"}),
      "It is closed, but probably looks out into the cavern. "+
      "Beneath the window is a ledge to stand on.\n" );
    add_item(({"ledge"}),
      "If you stand on it, you can probably reach the window.\n" );

    LIGHT
    IN

    reset_room();

} // create_room()

int do_open( string str )
{
    object tower_room;
    object tp = this_player();

    notify_fail( "Open what?\n" );

    if ((str == "door") || (str == "the door") || (str == "tower door"))
    {

	tp->catch_msg("You open the tower door and enter.\n" );
   tell_room("/d/Avenir/common/outpost/fort2", QCTNAME(tp) +
	  " opens the tower door and enters it.\nThe door closes.\n", tp);
	tp->move_living("M", OUTPOST + "tower_floor", 1 );
	tp->catch_msg("The black stone door closes behind you.\n" );
	tower_room = find_object( OUTPOST + "tower_floor.c" );
	tell_room(tower_room, QCTNAME(tp) +
		  " enters through the black door.\n", tp);
	return 1;
    }

    return 0;
} // do_open()

void
reset_room()
{
    if (!kilnar)
    {
	kilnar = clone_object(MON+"kilnar");
	kilnar->move(TO);
    }
    kilnar->reset_wangle();
    kilnar->reset_quest();
}

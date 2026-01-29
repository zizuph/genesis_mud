// file name:   /d/Avenir/common/outpost/tower_office.c
// creator(s):  Kazz    May 1995
// purpose:     Bank and Delivery Office at the top floor of tower
// note:	    this room is a 'delivery room' as invented by Krynn/Aridor
// to-do:   	use new office function:   add_content( <filename> );
// last update: use the new Genesis paths instead of Krynn
//              Lucius, Jan 2008: Added Bank ID.
//              Lilith, April 2022: overhaul for update to the Fort.
//                 room exits to tower_middle2 which looks like it 
//                 should be tower_middle3 but due to all of the 
//                 quest-related code, keeping the file-name.



#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/macros.h"
#include "/d/Genesis/delivery/delivery.h"
#include <money.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <files.h>

inherit "/std/room";
inherit "/lib/bank";
inherit "/d/Genesis/delivery/office";
inherit "/d/Avenir/inherit/sair_wall";

#define TOSS_ROOM       "/d/Avenir/common/outpost/tower_middle2"
#define PACKET_COUNT	3
#define OFFICE_NAME	"the outpost manager's office in Avenir"
// OFFICE_NAME needs to be the same as open/delivery.c   *ponder header file*

object manager_npc;

void
fee()
{
    // very small break for non-outlanders.
    if (IS_SYBARITE(TP) || IS_DANCER(TP) || IS_MUMMER(TP) ||
      QRACE(TP) == "drow" || QRACE(TP) == "elf")
    {
	set_bank_fee(18);
	config_trade_data();
	return;
    }
    else
    {
	set_bank_fee(20);
	config_trade_data();
	return;
    }
}

public void
init(void)
{
    ::init();
    // load office add_actions()
    init_office();
    bank_init(); 
    sair_init(); 	
    add_action( "do_sit", "sit" );	    // yell & scream & kick out of office
    add_action( "do_open", "open" );	// 'not' open the cabinet or safe

} // init()

public void
reset_room()
{
    // create tomato target npc & move it to proper starting room
    if (!objectp( manager_npc )) 
    {
	manager_npc = clone_object( MON + "manager" );
	manager_npc->equip_me();
	manager_npc->move(this_object()); 
    }
    reset_office();
} // reset_room()

public void
create_room()
{
    set_short("Fort Sybarus Bank and Delivery Office");
    set_long("This is the bank and delivery office for Fort Sybarus. "+
      "The walls have been washed stark white with many layers of lime, "+
      "but the floor is smooth black stone. "+
      "The room is dominated by a large desk, upon which sits a small "+
      "plaque. "+
      "Behind the desk is a comfortable looking, plush chair along "+
      "with a cabinet and safe. "+
      "There are two windows, one facing east and one west. "+
      "To your left, a poster is attached to the wall. "+
      "The black stone stairs along the south wall lead down into the "+
      "lower levels of the tower.\n" );
	  
	add_sair_wall();
    set_sair_dest(({OUTPOST+"tower_top"}));

    add_exit("tower_middle2", "down",0);

    add_item(({"tower", "black tower"}), 
      "The tower is made of the same black basaltic rock as much of the "+
      "fort.\n");
    add_item(({"stone", "black stone", "basalt", "basaltic rock", "floor" }),
      "The stone is very smooth and black. Little light reflects "+
      "from it. It appears to be basaltic rock.\n" );
    add_item(({"wall", "walls", "lime", "white walls" }),
      "The stone walls have been washed white, which makes this "+
      "room much brighter than the others in the tower.\n" );	
    add_item(({"door", "black stone door", "stone door"}),
      "The door is made of the same stone as the rest of the "+
      "tower. It is open.\n" );
    add_item(({"desk", "wooden desk", "large desk"}),
      "The desk is huge, and completely empty of any papers.\n" );
    add_item(({"window", "windows"}),
      "The windows provide a nice view of the cavern. One faces east, "+
      "the other, west.\n" );
    add_item( ({ "east window", "east facing window"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"fort2@@");
	add_item( ({ "west window", "west facing window"}), 
      "@@exa_window|You look through the window.\n|" + OUTPOST +"cave2@@");
    add_item(({"chair", "plush chair"}),
      "It looks very comfortable.\n" );
    add_item(({"cabinet"}),
      "The wood cabinet is closed.\n" );
    add_item(({"safe"}),
      "The safe is very solid, and quite closed.\n" );
    add_item("plaque", 
      "It tells you how to exchange your money.\n");
    add_cmd_item("plaque", "read", 
      "@@standard_bank_sign");	
    add_item("poster","@@delivery_poster@@");

    set_office( OFFICE_NAME, PACKET_COUNT );

    config_default_trade();
    config_trade_data();

    object gndep = clone_object("/d/Genesis/obj/deposit");
    gndep->set_short("deposit");
    gndep->set_bank_id(3902, "Sybarus Outpost");
    gndep->set_no_show_composite(1);
    gndep->move(this_object());

    add_prop(ROOM_M_NO_MAGIC_ATTACK, "The Gods of Sybarus brook no "+
       "such magick in this place.\n");
    add_prop(ROOM_M_NO_ATTACK, "Mmmm... on second thought, maybe not.\n");
    IN_IN;  // Inside room so no flux msg, no steeds
    reset_room();

} // create_room()


// attempt to open the door to the archers
do_sit( string str )
{
    notify_fail( "Sit where?\n" );

    if ((str != "in chair") && (str != "chair")) {
	return 0;
    }

    if (!manager_npc) {
	// successful sit... manager dead/missing?
	say( QCTNAME(TP) + " sits in the comfortable chair, and stands back up after a moment.\n" );
	TP->catch_msg( "You sit in the chair ... Ahhh.\n" );
	TP->catch_msg( "But! You have more important things to do, so you stand up again.\n" );
	return 1;
    }

    manager_npc->command( "emote bellows loudly." );
    manager_npc->command( "say You arrogant fool! "+
      " Get the hell out of my office!");
    say( QCTNAME(manager_npc) + " lifts "+ QCTNAME(TP) +
      " out of the chair and throws him from the room.\n" );
    TP->catch_msg( QCTNAME(manager_npc) +
      " plucks you from the chair and throws you down the stairs.\n" );
    TP->move_living("M", TOSS_ROOM, 0, 0);
    tell_room( TOSS_ROOM, "You hear shouting coming from above.\n"+
      QCTNAME(TP) +" stumbles down the stairs.\n", TP );
    return 1;

} // do_sit()

int
do_open( string str )
{
    notify_fail( "Open what?\n" );

    if (str == "")
	return 0;

    if ((str == "cabinet") || (str == "safe"))
    {
	TP->catch_msg( "You can't open it.\n" );
	return 1;
    }
    return 0;

} // do_open()


int
change(string str)
{
    fee();
    return ::change(str);
}

int
test(string str)
{
    fee();
    return ::test(str);
}

int
minimize(string str)
{
    fee();
    return ::minimize(str);
}

string
standard_bank_sign()
{
    fee();
    return ::standard_bank_sign();
}

/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */
#define FILTER_SHOWN_COMPOSITE(x) \
    filter((x), &not() @ &->query_no_show_composite())
public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
        this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
          ".\n");

    if (sizeof(in_room_o))   
        this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
          ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 

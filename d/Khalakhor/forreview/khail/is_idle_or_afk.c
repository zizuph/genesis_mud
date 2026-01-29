/*
 * PROOFED BY: Khail (19) 
 * ON: Mon Mar 11 07:47:21 1996
 */
/* 
  /std/workroom.c

  Generic workroom, just change it to your fit your tastes 
*/
#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>

#define NAME_WIZ capitalize(creator(this_object()))
/*
 * Prototypes
 */
object load_board();

/*
 * Function name: create_workroom
 * Description  : Called to create the workroom. You may redefine this
 *                function to create your own.
 */
void
create_workroom()
{
    set_short(NAME_WIZ + "'s workroom");
    set_long("You are on a vast battlefield.  The ground has risen slightly "+
	"here, you are atop a rocky hill which stands about thirty feet "+
	"above the battlefield.  Strewn about the battlefield like the "+
	"crumpled remains of warriors, some of demonic proportions. Broken "+
	"weapons and shattered armour lie scattered about, creating an "+
	"eerie blood-stained glow about the field from the reflections off "+
	"the setting sun.\n");
    if (SECURITY->query_domain_number(creator(this_object()))>=0)
	load_board();
    add_prop(ROOM_I_INSIDE, 0);
    add_exit("/d/Khalakhor/se_speir/port/room/village_hub","port");
  add_exit("/d/Immortal/volcano/citadel/landing", "citadel");
    add_exit("/d/Genesis/wiz/admin", "admin");
  add_exit("/d/Calia/khail/eldoral/mountain/mshore2", "shore");
  add_exit("/d/Genesis/start/human/town/tower","lobby");
  add_exit("/d/Calia/gelan/rooms/t_par", "tattoos");
  add_exit("/d/Calia/khail/eldoral/ruins/south_entry", "castle");
  setuid(); seteuid(getuid());
}    

/*
 * Function name: create_room
 * Description:   Create the room
 */
nomask void
create_room()
{
    create_workroom();
}

/*
 * Function name: reset_workroom
 * Description  : Called to make the room reset from time to time. You
 *                should redefine this function if you want your workroom
 *                to reset.
 */
public void
reset_workroom()
{
}

/*
 * Function name: reset_room
 * Description  : Called to make the room reset from time to time.
 */
nomask void
reset_room()
{
    reset_workroom();
}

/*
 * Function name: load_board
 * Description  : Load a bulletin board into the room.
 * Returns      : object - the bulletin board.
 */
object
load_board()
{
    object bb;
    string *file;
    string name;

    file = explode(MASTER + "/", "/");
    file = slice_array(file, 0, sizeof(file) - 2);

    seteuid(getuid());
    bb = clone_object("/std/board");

    name = implode(file, "/") + "/log";
    if (file_size(name) != -2) 
	mkdir(name);

    bb->set_board_name(name + "/board_data");
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object());

    return bb;
}

/*
 * Function name: goto_start
 * Description  : Find and return the default start location of the player
 *                who uses the 'startloc' exit.
 * Returns      : string - the filename of that room.
 */
string
goto_start()
{
    return this_player()->query_default_start_location();
}

void
init()
{
  ::init();
  add_action("removeshadow","removeshadow");
}

int
removeshadow(string str)
{
  this_player()->remove_autoshadow(str);
  return 1;
}

#pragma save_binary

inherit "/std/room";

void
create_room()
{
    object bb;

    set_short("arch boardroom");
    set_long("This is a room in which the arch-boards are kept. You have " +
	"no business here. Use a board-tool to read them.\n");
    
    add_exit("/d/Genesis/wiz/virtual", "virtual");

    bb = clone_object("/w/postmaster/private/arch_boards/balance");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/domain");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/gd");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/mudlib");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/player");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/rules");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/council");
    bb->move(this_object());
    bb = clone_object("/w/postmaster/private/arch_boards/aod_board");
    bb->move(this_object());
}

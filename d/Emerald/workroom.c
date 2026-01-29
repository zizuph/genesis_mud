inherit "/std/room";

#define BOARD_DIR "/d/Emerald/log/board_data"

public void
create_room()
{
    object bb;

    set_short("Emerald's workroom");
    set_long("This is Emerald's workroom.\n");
    add_exit("/d/Genesis/wiz/virtual", "virtual");
    add_exit("/d/Emerald/common/domain_entr", "north");

    setuid();
    seteuid(getuid());
    bb = clone_object("/std/board");
    bb->set_board_name(BOARD_DIR);
    bb->set_num_notes(30);
    bb->set_silent(0);
    bb->set_show_lvl(0);
    bb->move(this_object(), 1);
}


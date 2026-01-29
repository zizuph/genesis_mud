inherit "/std/room";

object board;

void create_room()
{
    set_short("Announcement room for Middle Earth");
    set_long("Announcement room for Middle Earth. Notes posted on this "
        + "board will automatically be displayed as announcements on the "
        + "various boards in the Gondor/Shire domain. Each note is "
        + "automatically removed after 3 months.\n");
        
    board = clone_object("/d/Gondor/private/boards/announceboard");
    board->move(this_object(), 1);
    
    add_exit("/d/Gondor/workroom", "workroom");
}

object query_board()
{
    return board;
}
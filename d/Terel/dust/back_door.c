/* Silver door, back way, without the coloured buttons */
inherit "/std/door";

#define DUSTDIR    "/d/Terel/dust/"
#define OTHER_ROOM (DUSTDIR + "door_room")

void
create_door()
{
    ::create_door();
    
    set_door_id("testdoor");
    set_door_desc("This is a door made of silver.\n");
    set_pass_command(({"e","east"}));
    set_door_name(({"silver door","door"}));
    set_other_room(OTHER_ROOM);
    set_lock_name("lock");

    set_open(0);
    set_locked(1);
}

public void
close_and_lock_door()
{
    
    if (!other_door) load_other_door();
    
    if (open_status && other_door)
    {
        do_close_door("The silver door closes.\n");
        other_door->do_close_door("The silver door closes.\n");
    }
    
    if (!lock_status && other_door)
    {
        do_lock_door("You hear a soft 'clic' from the silver door.\n");
        other_door->do_lock_door("You hear a soft 'clic' from the silver door.\n");
    }
}

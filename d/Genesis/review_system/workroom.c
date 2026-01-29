inherit "/std/workroom";

create_workroom()
{
    ::create_workroom();

    set_long("This is Debugwiz' workroom.\n" + break_string("It has been " +
        "turned into a review centre; through a small, open doorway to the " +
        "west, you can see a bare room containing a board and a shimmering " +
        "doorway leading through to another bare room with yet another " +
        "board! There also is an entrance to a room marked 'Warning' north " +
        "of here. It looks like somewhere to be wary of! To the east is " +
        "the well known lounge of the wizards.", 78) + "\n");

    add_exit("/d/Debug/debugwiz/request",  "west",  0);
    add_exit("/d/Debug/debugwiz/rev_room", "north", 0);
    add_exit("/d/Genesis/wiz/lounge", "east", 0);
}

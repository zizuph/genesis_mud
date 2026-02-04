// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

inherit "/d/Terel/common/moor/cottage/gpath_room";

void
create_room()
{
    ::create_room();
    add_exit("gpath02", "north", 0);	  
    add_exit("cottage_graveyard", "south", 0);
}


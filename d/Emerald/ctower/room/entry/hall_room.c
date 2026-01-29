inherit "/d/Emerald/ctower/room/ctower_base";

void
create_hall_room()
{
}

nomask void
create_ctower_room()
{
    set_short("Tower hall");
   
    set_long("The walls of this hallway give off a soft "+
	"glow\nthat gives everything an unreal appearance.\n");
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
	"milky crystal that is cold to the touch.\n");

    create_hall_room();
}

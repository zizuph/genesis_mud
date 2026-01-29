
inherit "/std/room";

public void
create_room()
{
    setuid();
    seteuid(getuid());
	set_short("This is a " + getuid());
	set_long("This is the long.\n");
}

public void test_save() 
{
	save_map(([]), "/d/Sparkle/area/city/auction/data//blank_room");
}

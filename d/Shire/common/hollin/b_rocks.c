#include "rom.h"

create_rom()
{
    set_short("Behind rocks");
    set_long("Behind rocks. This is a place for small trolls only.\n");
}

init()
{
    ::init();
    add_action("heal_me", "trollheal");
}

int
heal_me(string str)
{
    if(TP->query_race_name()=="troll")
    {
	TP->heal_hp(random(1000));
	return 1;
    }
}

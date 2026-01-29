
#pragma strict_types
#include "/d/Ansalon/common/defs.h"

inherit "/d/Ansalon/estwilde/std/inside_base";
inherit "/lib/guild_support";

#include "../guild.h"

#define  SHIELDBEARERS      "Shieldbearers of Iron Delving"

public int  check_access();

void
reset_dwarf_room()
{
    return;
}

void
create_dwarf_room()
{
    set_short("The Hall of Warriors");
    set_long("You stand in the Hall of Warriors, the house where " +
      "the warriors of the Neidar Clan gather to rest and discuss " +
      "matters. This room is decked out with comfortable wooden chairs " +
      "positioned near a large fireplace, where members retire to " +
      "after a hard day smashing goblins and giants. Clan members " +
      "may <start here>, if they wish to enter these realms " +
      "in the Hall of Warriors, as well as <meditate> to see how " +
      "they are advancing.\n");

    add_item(({"chairs","wooden chairs","comfortable wooden chairs"}),
      "Comfortable wooden chairs are positioned around the room " +
      "for those dwarves that wish to rest after a hard day " +
      "beating up goblins and giants.\n");
    add_item(({"fireplace","large fireplace"}),
      "A large burning fireplace keeps the room warm for warriors " +
      "resting here.\n");

    add_exit("/d/Ansalon/estwilde/iron_delving/r13","west",0);
    add_exit("/d/Ansalon/estwilde/iron_delving/sbearer_board", "north", 0);
    add_exit(GUILD_ROOMS + "board", "east", check_access);
    add_exit(GUILD_ROOMS + "library", "south", 0);

    reset_dwarf_room();
}

public int
check_access()
{
    if(BANISHED(TP))
    {
	write("You are no longer welcome in the Hall of " +
	  "Warriors. Best if you just left.\n");
	return 1;
    }
    
    if ( !TP->query_guild_member(GUILD_NAME) )
    {
        write("You are not a member of the Clan, so you are not " +
            "allowed to enter that part of the Hall of Warriors.\n");
        return 1;
    } 

    return 0;
}

int
start(string str)
{
    if (str != "here") 
    {
	notify_fail("Start here?\n");
	return 0;
    }
find_player("navarre")->catch_msg("THe guild start location is : "+GUILD_STARTLOC+"\n");    if ( !this_player()->query_guild_member(GUILD_NAME) &&
        !this_player()->query_guild_member(SHIELDBEARERS) )
    {
        write("You are not a member of this guild!\n");
	return 1;
    }




    if(BANISHED(TP))
    {
	write("You are banished from the clan! You " +
	  "cannot start here.\n");
	return 1;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
	write("You now start in the Hall of Warriors.\n");
    }
    else
    {
	write("Sorry, some problem prevents you from starting here.\n");
    }

    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(ob->test_bit("Ansalon",3,3) && ob->test_bit("Ansalon",3,4))
    {
	write("You are in disgrace! You may no longer start " +
	      "here!\n");
	ob->set_default_start_location(ob->query_def_start());
    }
}

void
init()
{
    ::init();

    add_action(start, "start");
    init_guild_support();
}

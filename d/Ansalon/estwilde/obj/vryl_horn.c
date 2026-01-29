inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/guild/dwarf/guild.h"
#include "/d/Ansalon/common/defs.h"

int blown;

#define RUNE_OBJ  "ansalon_rune_object"

void
create_object()
{
    set_name("horn");
    set_short("dwarven horn");
    set_long("This horn is made of a strange dark wood, and " +
      "has been carved by dwarven hands. It looks like a warning " +
      "horn of some kind, and if one knows how to use it, can " +
      "create varying deep soundings on it.\n");
}

init()
{
    ADA("blow");
}

void
regain_wind()
{
    blown = 0;
}

blow(str)
{
    object *players;
    int i;

    NF("Blow what?\n");
    if(str != "horn" && str != "giant" && str != "ogre" && str != "Lord Soth's undead force")
	return 0;

    if(blown == 1)
    {
	write("Wait a moment until you catch your breath.\n");
	return 1;
    }

    write("You take a deep breath and blow hard on the " +
      "horn.\n");
    SAY(" takes a deep breath and blows mightily on " +
      "a dwarven horn. Its deep sounding is carried into " +
      "the distance by the wind.");
    blown = 1;
    set_alarm(5.0, 0.0, "regain_wind");

    if(E(TO)->query_npc())
    {
	players = users();
	for (i = 0; i < sizeof(players); i++)
	{
	    if( MEMBER(players[i]) || P(RUNE_OBJ, players[i]) )
		players[i]->catch_msg("\n\n"+
		  "You can faintly make out the sound of " +
		  "the warning horn of Vryl. Its deep sounding " +
		  "carrying to you on the back of a mysterious wind, " +
		  "warning you that " +str+ "s are " +
		  "on their way to Iron Delving!!!\n\n\n");
	}
    } 
    return 1;

}


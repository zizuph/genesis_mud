inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/guild/dwarf/guild.h"
#include "/d/Ansalon/common/defs.h"

int blown;

#define RUNE_OBJ "ansalon_rune_object"

void
create_object()
{
    set_name("horn");
    add_name("warhorn");
    add_adj("dwarven");
    set_short("dwarven warhorn");
    set_long("This is a huge warhorn of ancient dwarven " +
      "design. Runes inlaid with silver depicting the forge indicate " +
      "that this object is one that has probably been blessed " +
      "by priests of Reorx, the patron god of dwarves, back in " +
      "the days before the cataclysm when such priests " +
      "still walked the lands.\n");
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
    if(str != "horn" && str != "warhorn")
	return 0;

    if(blown == 1)
    {
	write("Wait a moment until you catch your breath.\n");
	return 1;
    }

    write("You take a deep breath and blow hard on the " +
      "warhorn.\n");
    SAY(" takes a deep breath and blows mightily on " +
      "a dwarven warhorn. Its deep sounding is carried into " +
      "the distance by the wind.");
    blown = 1;
    set_alarm(5.0, 0.0, "regain_wind");

    if(MEMBER(TP) || E(TO)->query_npc())
    {
	players = users();
	for (i = 0; i < sizeof(players); i++)
	{
	    if(MEMBER(players[i]) || P(RUNE_OBJ, players[i]))
		players[i]->catch_msg("\n\n"+
		  "You can faintly make out the sound of " +
		  "a dwarven warhorn, its deep sounding carrying " +
		  "to you on the back of a mysterious wind, " +
		  "warning you that Iron Delving is under attack!\n\n\n");
	}
    } 
    return 1;

}


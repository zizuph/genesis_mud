/* quechua */

inherit "/std/monster";
#include "/sys/stdproperties.h" 
void
create_monster()
{
	set_race_name("elmo");
	set_adj("red");
	add_adj("fuzzy");
	set_short("elmo");
	set_name("tickle-me-elmo");
	set_long("   A small, red, fuzzy elmo doll. In his hands, he clutches " +
	"a purple handglider.\n\n");
}

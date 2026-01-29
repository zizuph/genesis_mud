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
	set_long("   A very large red fuzzy elmo doll. It is so big " +
	"that it stands even higher then u do.\n\n");
	set_stats(({100,100,100,100,100}));
}

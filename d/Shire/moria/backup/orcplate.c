inherit "/d/Shire/common/armour/rtrplate";

int weight_proc() { return 60; }   /* 60 % weight when compared to trolls. */
int volume_proc() { return 60; }

create_random_armour()
{
    set_long(
	"This is a @@short@@ made for orcs. It has a sign or emblem "+
	"of a red claw on it.");
    set_race_type("orcish");
    add_item(({"sign","emblem","claw","red claw"}),
	"This is the sign of the Red Claw-tribe of Moria-orcs living in the "+
	"Mines of Moria.\n");
}

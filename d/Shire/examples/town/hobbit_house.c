//  add the includes first then we can use the marcos for the inherits.
#include "../local.h"
#include HOBBIT_FILE

inherit TOWN_BASE;

object hobbit;

void
create_town_room()
{
    set_short("a small hobbit dwelling");
    set_long("This is a small house which belongs to a hobbit and "+
      "his family.  Within the house is a small table with chairs "+
      "and some scattered rugs cover the floor.\n");

    add_item(({"chair","chairs"}),"They look like ordinary chairs.\n");
    add_item(({"rugs","rug"}),"The rugs are beutifully woven and do a "+
      "good job of covering the floor.\n");
    add_item("table","A small wooden table which is probably used "+
      "for eating on.\n");
    add_exit(EXAMPLE_ROAD + "road4", "out");
    reset_shire_room();
}

void
reset_shire_room()
{
    FIXEUID;
    if (!hobbit)
    {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_power(100);
	hobbit->set_type(TWEENS);
	hobbit->move(TO);
    }
}





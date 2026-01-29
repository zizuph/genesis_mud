/* The new Vingaard Keep by Morrigan, 11/11/96 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit IN_BASE;

object guard, guard2, guard3, guard4;

public void
reset_vin_room()
{
    if (!guard)
    {
	guard = clone_object(VNPC + "guard");
	guard->move(TO);
	guard->set_block_dir("out");
    }
    if (!guard2)
    {
	guard2 = clone_object(VNPC + "guard");
	guard2->move(TO);
	guard2->set_block_dir("out");
    }
    if (!guard3)
    {
	guard3 = clone_object(VNPC + "guard");
	guard3->move(TO);
	guard3->set_block_dir("out");
    }
    if (!guard4)
    {
	guard4 = clone_object(VNPC + "guard");
	guard4->move(TO);
	guard4->set_block_dir("out");
    }
}


public void
create_vin_room()
{
    set_short("Guardroom west of the archway");
    set_long("This is a guardroom, where Solamnian guards are typically on " +
      "duty in the event of an attack. To your east is an archway which you can "+
      "enter by going out. The room is sparsely decorated, suitable for a " +
      "guard's post. The only adornment is an oak table and several chairs.\n");

    AE(VROOM+"archway", "out", 0);

    AI(({"wall","walls"}),"The walls of the archway and this room " +
      "are made of stone, typical of the entire fortress.\n");
    AI(({"ceiling","floor"}),"It is made of the same stone as the walls.\n");
    AI("stone","The stone somehow has an air of timeless sturdiness.\n");
    AI("archway", "The archway leads north towards the inner portcullis. "+
      "It lies to your east, and is simple in design\n");
    AI(({"oak table", "table"}),"The table is made of solid oak, and it " +
      "would be an excellent barrier if lain on its side.\n");
    AI(({"chair","chairs","oak chair","oak chairs"}),"This would be where " +
      "the guards rest when they are not standing.\n");
    ACI(({"on chair","chair","on oak chair"}),"sit","Unless you are " +
      "volunteering for guard duty, you don't belong there.\n");
    ACI(({"table","oak table"}),"lay","It is too heavy for you to lift.\n");

    reset_vin_room();
}


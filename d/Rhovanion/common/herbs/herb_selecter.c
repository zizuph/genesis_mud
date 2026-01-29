/*
 * Erane 23 Jan 95
 *
 * This is the naming file for the herbs for the Esgaroth armour quest
 *
 * I'm changing this file all the time so any changes should be made in 
 * another file and mail me your suggestions - thanks
 */

inherit "/std/object";

#include "/d/Rhovanion/defs.h"

/*
 * Global variables
 */
private static mapping herbs = ([ "/d/Rhovanion/erane/workroom" : 
			      ({(HERB_DIR + "belakin"),(HERB_DIR + "caldire")}),
			         "/d/Rhovanion/blackstaff/workroom" :
			      ({(HERB_DIR + "belienthas")}) ]);
object *need = ({ }); // these are the randomly selected herbs

/*
 * Prototypes
 */
private void select_herbs();

void
create_object()
{
    set_short(0);
    set_long("No long desc\n");

    seteuid(getuid(TO));
}

private void
select_herbs()
{
    int i;

    for (i = 0; i < m_sizeof(herbs); i++)
	need[i] = herbs[i][random(sizeof(herbs[i]) - 1)];
    return;
}

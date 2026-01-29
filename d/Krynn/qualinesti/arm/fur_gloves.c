/* File name  : fur_gloves.c
 * Original Description: The pair of fur gloves that increase pick pocket skill.
 * Creator    : Blizzard
 * Date       : 23.03.2004
 *
 * Note by Navarre, November 22th 2005:
 *
 * This item was one of many inappropriate items that was created.
 * It originally raised your pick pocket skill by 20 levels.
 * I added a log file to the item, when a player wears it, his name
 * will be written to a log file, since the artifact was extremely 
 * well hidden, this will give us an idea about who is actually getting
 * this artifact.
 *
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

inherit  "/lib/keep";
inherit  "/std/armour";

public void
create_armour()
{
    set_name("gloves");
    add_name("armour");
    set_adj("fur");
    set_short("pair of soft fur gloves");
    set_long("The insides of these gloves are tanned to a soft and supple " +
	"consistency, to allow freedom of movement for your fingers. The " +
	"velvety white hair on the outside has been cut short enough to " +
	"allow more dexterous movements, while still being thick enough " +
	"to provide protection from the climate.\n");
    set_at(A_HANDS);
    set_ac(8);
    set_af(TO);

    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VALUE, 20);
}




private void
write_to_log()
{
    if(!TP->query_wiz_level())
    {
      setuid();
      seteuid(getuid());
      log_file("suspicious_items/suspicious_items.log",ctime(time())+": "+TP->query_name()+
                " wore this suspicious item: "+
                this_object()->query_short()+" located at: "+
                file_name(this_object())+
               "\nThe suspicious effects has been removed, but we keep "+
               "track of the item for abusers.\n\n", 0);
    }
}

public int
wear(object what)
{
   write_to_log();
   return 0;
}
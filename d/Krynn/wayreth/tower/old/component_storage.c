/*
 * Storage room for the component shop
 *
 * by Rastlin
 */
inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <files.h>

#define COMPFILE	        WLOG + "compsave"

mixed gItems = ({ ([]), ([]) });

public void
create_room()
{
   set_short("The shop's store room");
   set_long("The shop's store room, be gone.\n");

   /* set max # of obs in store and max # of identical obs */
   set_max_values(200, 10);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   restore_object(COMPFILE);
}

public void
remove_sold_object(object ob)
{
    ob->remove_object();
}

public void
remove_components(object *ob)
{
    int size = sizeof(ob);
    string fname;
 
    while (size--)
    {
        fname = MASTER_OB(ob[size]);
        if (IS_HERB_OBJECT(ob[size]))
        {
	      gItems[0][fname]--;
	      if (!gItems[0][fname])
                gItems[0] = m_delete(gItems[0], fname);
        }
        else if (IS_POTION_OBJECT(ob[size]))
	{
	    gItems[1][fname]--;
	    if (!gItems[1][fname])
            gItems[1] = m_delete(gItems[1], fname);
        }
    }
    save_object(COMPFILE);
}

public void
save_leftovers(object ob)
{
	mixed *furbles;
	int i;

	for (i = 0; i < sizeof(furbles); i++)
	  {
		if(furbles[i][1] == "decay_fun")
		  {
			remove_alarm(furbles[i][0]);
			find_player("karath")->catch_msg("removed alarm "+
				furbles[i][0] + "\n");
		  }
	  }
}


public void
enter_inv(object ob, object from)
{
   int    n, savealarm;
   string fname;

   ::enter_inv(ob, from);

   if (!objectp(from))
       return;

   if (!living(ob))
   {
       mixed *furbles = ob->query_alarms();
       fname = MASTER_OB(ob);
       if (IS_LEFTOVER_OBJECT(ob))
	{
	    savealarm = set_alarm(2.0, 0.0, &save_leftovers(ob));
	 }
       if (IS_HERB_OBJECT(ob))
       {
	   gItems[0][fname]++;

	   set_alarm(0.0, 0.0, &remove_sold_object(ob)); 
       }
       else if (IS_POTION_OBJECT(ob))
	{
	   gItems[1][fname]++;
	   set_alarm(0.0, 0.0, &remove_sold_object(ob));
       }
   }
   save_object(COMPFILE);
}

/*
 * Function name: query_items
 * Description:   Return an array with everything in the store
 */
public mixed
query_items()
{
    return ({ gItems, all_inventory(TO) });
}


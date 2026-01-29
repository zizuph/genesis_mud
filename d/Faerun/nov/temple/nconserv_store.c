
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <files.h>
#include "../nov.h"


inherit "/lib/store_support";
inherit NOV_DIR +"temple/std_room";

#define COMPFILE                NOV_DIR +"log/conserved"

mixed gItems = ({ ([]), ([]) });

public void
create_room()
{
   set_short("The conservative room");
   set_long("The conservative room.\n");

   set_max_values(200, 10);

   

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
    string fname, func;
 
    while (size--)
    {
        fname = MASTER_OB(ob[size]);
        func = function_exists("create_object", ob[size]);
  
        if (func == HERB_OBJECT)
        {
              gItems[0][fname]--;
              if (!gItems[0][fname])
                gItems[0] = m_delete(gItems[0], fname);
        }
        else
        {
              if (func == POTION_OBJECT)
              {
                  gItems[1][fname]--;
                  if (!gItems[1][fname])
                    gItems[1] = m_delete(gItems[1], fname);
              }
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
                        find_player("tilorop")->catch_msg("removed alarm "+
                                furbles[i][0] + "\n");
                  }
          }
}


public void
enter_inv(object ob, object from)
{
   int    n, savealarm;
   string fname, func;

   ::enter_inv(ob, from);

   if (!objectp(from))
       return;

   if (!living(ob))
   {
       mixed *furbles = ob->query_alarms();
       func = function_exists("create_object", ob);
       fname = MASTER_OB(ob);

       if (function_exists("leftover_init", ob) == "/std/leftover")
         {
        savealarm = set_alarm(2.0, 0.0, &save_leftovers(ob));
         }

       if (func == HERB_OBJECT)
       {
           gItems[0][fname]++;

           set_alarm(0.0, 0.0, &remove_sold_object(ob)); 
       }
       else
       {
           if (func == POTION_OBJECT)
           {
               gItems[1][fname]++;
               set_alarm(0.0, 0.0, &remove_sold_object(ob));
           }
       }
   }
   save_object(COMPFILE);
}


public mixed
query_items()
{
    return ({ gItems, all_inventory(this_object()) });
}

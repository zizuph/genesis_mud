/* Stralle @ Genesis 020703
 *
 * It used to save recover strings for each and every herb stored.
 * This led to datafiles of several megabytes and eval_cost problems
 *
 * Now only saves the number of herbs in store.
 */
 
 /*
  * Navarre, March 2013 - Added support for buying multiple herbs.
  *                       Cleaned up the code a little and fixed bugs.
  */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pot/guild.h"

#define REBOOTABLE
#define IDLE_TIME   30

#define M_NAME      0
#define M_VALUE     1
#define M_QUOTA     2

mapping gHerbs;
int gAlarm, gDeleteAlarm;
object *gDelete;

mapping query_herb_list() { return gHerbs; }
void clear_herb_list() { gHerbs = ([]); }

#ifdef 0
int
prevent_enter(object ob)
{
    string master;
    
    if (!IS_HERB_OBJECT(ob))
    {
        return 0;
    }
    master = explode(ob->query_recover(), ":")[0];

#ifdef 0
    if (pointerp(gHerbs[master]) && gHerbs[master][M_QUOTA] >= 5500)
    {
        return 1;
    }
#endif
    
    return 0;
}
#endif

int
do_convert(string file)
{
    mapping smap;
    int x, size;
    string *herbfiles;

    if (file_size(file + ".o") <= 0)
    {
        write("Can't find file.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    
    write("[] \"" + file + "\"\n");
    write("[] " + file_size(file + ".o") + "\n");
    smap = restore_map(file);
    
    herbfiles = m_indices(smap);
    write("[] " + sizeof(herbfiles) + "\n");
    for (x = 0, size = sizeof(herbfiles) ; x < size ; x++)
    {
        gHerbs[herbfiles[x]] = allocate(3);
        gHerbs[herbfiles[x]][M_NAME] = smap[herbfiles[x]][0];
        gHerbs[herbfiles[x]][M_VALUE] = smap[herbfiles[x]][1];
        gHerbs[herbfiles[x]][M_QUOTA] = sizeof(smap[herbfiles[x]]) - 2;
    }
    return 1;
}

void
save_inventory()
{
#ifdef REBOOTABLE
    setuid();
    seteuid(getuid());
    save_map(gHerbs, MASTER);
#endif
}

void
restore_inventory()
{
#ifdef REBOOTABLE
    setuid();
    seteuid(getuid());
    gHerbs = restore_map(MASTER);
#endif
}

void
create_room()
{
    set_short("Herb store room");
    set_long("This is the store room for the herb shop in the temple.\n");
    clear_herb_list();
    restore_inventory();
}

int
delayed_save_inventory()
{
    if (!get_alarm(gAlarm))
    {
	    gAlarm = set_alarm(itof(IDLE_TIME), 0.0, &save_inventory());
    }
}

void
remove_herbs()
{
    gDelete->remove_object();
    gDelete = ({ });
}

void
delayed_remove_herb(object ob)
{
    if (!gDelete)
    {
        gDelete = ({ });
    }
    gDelete += ({ ob });

    if (!get_alarm(gDeleteAlarm))
    {
        gDeleteAlarm = set_alarm(2.0, 0.0, &remove_herbs());
    }
}


void
herb_store_update(object herb)
{
    string master;
    
    if (!IS_HERB_OBJECT(herb))
    {
        return;
    }
    
    master = MASTER_OB(herb);
    
    if (!pointerp(gHerbs[master]))
    {
        gHerbs[master] = ({ herb->query_herb_name(),
            herb->query_herb_value(), 0 });
    }
    gHerbs[master][M_QUOTA] += herb->num_heap() || 1;

    delayed_save_inventory();
    delayed_remove_herb(herb);
}

mixed
list_herb_files()
{
    int i, size;
    string result = "", *herbfiles = m_indices(gHerbs);
    
    if (!herbfiles)
    {
        return 0;
    }
    
    for (i = 0, size = sizeof(herbfiles) ; i < size ; i++)
    {
        result += " " + gHerbs[herbfiles[i]][M_QUOTA] + " " +
                  herbfiles[i] + "\n";
    }
    return result;
}

int
query_sell_price(string master)
{
    if (gHerbs[master])
    {
        return gHerbs[master][M_VALUE];
    }

    // We should never reach here
    return -1;
}
                
int
query_buy_price(object ob)
{
    string master;
    
    if (!objectp(ob))
    {
        return 0;
    }
    master = MASTER_OB(ob);

    return ob->query_herb_value() * ob->num_heap();
}
        
varargs mixed
purge_herbs(string herb, int test = 0)
{
    int i;
    string result = "", *herbfiles = m_indices(gHerbs) + ({ });
    
    if (!herbfiles)
    {
        return 0;
    }
    
    for (i = 0 ; i < sizeof(herbfiles) ; i++)
    {
        if (wildmatch(herb, herbfiles[i]))
        {
            result += herbfiles[i] + "\n";
            if (!test)
            {
                gHerbs = m_delete(gHerbs, herbfiles[i]);
            }
        }
    }
    
    if (!test && result != "")
    {
        delayed_save_inventory();
    }
    return result;
}

object
extract_several_herbs(string name, int amount_requested)
{
    int i, j;
    string *herbfiles = m_indices(gHerbs) + ({ });
    object herb;
    
    if (!herbfiles)
    {
        return 0;
    }
    
    for (i = 0 ; i < sizeof(herbfiles) ; i++)
    {
        string available_herbname = gHerbs[herbfiles[i]][M_NAME];
        
        if (available_herbname == name)
        {
            setuid();
            seteuid(getuid());
            
            // If we cannot clone the herb from the herbshop, delete the
            // faulty entry in the shop.
            if (catch(herb = clone_object(herbfiles[i])))
	        {
		        // problem cloning herb. Old filename? We can remove it.
		        gHerbs = m_delete(gHerbs, herbfiles[i]);
		        delayed_save_inventory();
		        return 0;
	        }

            if (herb)
            {
                int available_amount = gHerbs[herbfiles[i]][M_QUOTA];
                
                // If there aren't enough herbs in the store, only sell the
                // available_amount
                if (available_amount > 0 &&
                    available_amount < amount_requested)
                {
                    amount_requested = available_amount;
                }
                
                // If we just sold the last one, delete the herb entry in the
                // mapping.
                gHerbs[herbfiles[i]][M_QUOTA] =
                    (available_amount - amount_requested);
                
                if ((available_amount - amount_requested) <= 0)
                {
                    gHerbs = m_delete(gHerbs, herbfiles[i]);
                }
                delayed_save_inventory();
                herb->set_heap_size(amount_requested);
                return herb;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

object
extract_herb(string name)
{
    return extract_several_herbs(name, 1);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    herb_store_update(ob);
}

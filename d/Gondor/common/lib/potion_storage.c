/*
 * /d/Gondor/common/lib/potion_storage.c
 *
 *   The storage room of the potion shop.
 *   Original by Falke; rehacked by Laurelin.
 *
 *   Modified for Minas Morgul in Gondor@Genesis by Olorin.
 *
 *   Modifiction log:
 *    3-Dec-1996: Added support for ranger potions, Olorin.
 */
#pragma save_binary
#pragma strict_types

inherit "/lib/store_support.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define POTION_NUM	0
#define POTION_SOFT	1
#define POTION_ALCO	2

static  int     restore_alarm,
                remove_alarm;
static  object *remove_potions = ({ });
static  string  save_file;
	mapping potions = ([]);

void
set_save_file(string str)
{
    save_file = str;
}

public mapping
query_potions()
{
    return secure_var(potions);
}

public mixed
query_potion_values(string name)
{
    return secure_var(potions[name]);
}

/*
 * Function name:	reduce_sold_potion
 * Description:		Will remove the sold potion from the mapping
 * Arguments:		filename: the index
 *			soft: the soft value of the sold potion
 *			alco: the alco value of the sold potion
 */
varargs void
reduce_sold_potion(string filename, int soft, int alco, int xtra)
{
    potions[filename][POTION_NUM]--;

    if (!potions[filename][POTION_NUM])
        m_delkey(potions, filename);
    else
    {
        potions[filename][POTION_SOFT] -= soft;
        potions[filename][POTION_ALCO] -= alco;
    }

    save_object(save_file);
}

/*
 * Function name: remove_potion_file
 * Description  : Called externally to remove a particular potion from the
 *                potion store.
 */
void
remove_potion_file(string filename)
{
    if (potions[filename][POTION_NUM])
    {
        m_delkey(potions, filename);
    }
    save_object(save_file);
}

void
create_potion_storage()
{
   /* set max # of obs in store and max # of identical obs */
   set_max_values(100, 10);

   if (file_size(save_file + ".o") >= 0)
       restore_object(save_file);
}

void
remove_potion()
{
    remove_potions->remove_object();
    remove_potions = ({ });
    remove_alarm = 0;
}

public void
enter_storage_inv(object ob, object from)
{
   int    n;
   string name;

   if (!objectp(from))
       return;

   if (!living(ob) && stringp(ob->query_potion_name()))
   {
       name = MASTER_OB(ob);
       if (!sizeof(potions[name]))
           potions[name] = ({ 0, 0, 0, });

       potions[name][POTION_NUM] += ob->num_heap();
       potions[name][POTION_SOFT] += ob->query_soft_amount() * ob->num_heap();
       potions[name][POTION_ALCO] += ob->query_alco_strength() * ob->num_heap();

       // remove potion
       remove_potions += ({ ob });
       if (remove_alarm)
           remove_alarm = set_alarm(1.0, 0.0, remove_potion);
   }
   save_object(save_file);
}

/*
 *   The storage room of the herb shop.
 *   Original by Falke; rehacked by Laurelin.
 *
 *   Mopdified for Minas Morgul in Gondor@Genesis by Olorin.
 *   Used for standard herb shop, Olorin, 15-nov-1994
 */
inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static  int     restore_alarm;
static  string  save_file;
        mapping herbs = ([]);

mapping
query_herbs()
{
    return herbs;
}

void
reduce_herb_number(object * sold)
{
    int     i,
            sh;
    string  herb_file;

    if (!(sh = sizeof(sold)))
        return;

    for (i = 0; i < sh; i++)
    {
        herb_file = MASTER_OB(sold[i]);
        herbs[herb_file]--;
        if ((int)herbs[herb_file] == 0)
            herbs = m_delete(herbs, herb_file);
    }
    save_object(save_file);
}

void
remove_herb(object herb)
{
    herb->remove_object();
}

public void
enter_storage_inv(object ob, object from)
{
   int    n;
   string name;

   if (!objectp(from))
       return;

   if (!living(ob) && stringp(ob->query_herb_name()))
   {
       name = MASTER_OB(ob);
       herbs[name]++;

       /* remove herbs */
       set_alarm(0.0, 0.0, "remove_herb", ob);
   }
   save_object(save_file);
}

int
query_herb_number(string herb_name)
{
    int     i,
            sh;
    string *herb_files;

    if (!strlen(herb_name))
        return 0;

    herb_name = LOW(herb_name);
    if (!(sh = sizeof(herb_files = m_indexes(herbs))))
        return 0;

    for (i = 0; i < sh; i++)
        if (herb_files[i]->query_herb_name() == herb_name)
            return herbs[herb_files[i]];
    return 0;
}

void
set_save_file(string str)
{
    save_file = str;
}

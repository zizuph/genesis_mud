  /*
 *   The storage room of the herb shop.
 *   Original by Falke; rehacked by Laurelin.
 *
 *   Modified for Minas Morgul in Gondor@Genesis by Olorin.
 *   Used for standard herb shop, Olorin, 15-nov-1994
 *
 *   Modification Log:
 *   - 24.08.2004 Raven: added heap support in enter_storage_inv()
 *   - 25.03.2009 Eowul: Increase the maximum number of herbs to 50000
 *   - Jan 13, 2019 Finwe: Reduced max herbs to 25000. 
 *     There's no reason to have 50k herbs
 */
#pragma save_binary
#pragma strict_types

inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_MAX     50

static  int     restore_alarm,
                remove_alarm,
                max_herbs = 25000;
static  object *remove_herbs = ({ });
static  string  save_file;
        mapping herbs = ([]);

static int
filter_herb_name(string herb_file)
{
    if (file_size(herb_file + ".c") <= 0)
        return 1;

    return 0;
}

static void
set_max_herbs(int i)
{
    if (i > 50)
        max_herbs = i;
}

public mapping
query_herbs()
{
    return herbs;
}

void
reduce_herb_number(object *sold)
{
    int     i, s,
            sh;
    string  herb_file;
    string *indices;

    if (!(sh = sizeof(sold)))
        return;

    for (i = 0; i < sh; i++)
    {
        herb_file = MASTER_OB(sold[i]);
        herbs[herb_file]--;

        if ((int)herbs[herb_file] == 0)
            herbs = m_delete(herbs, herb_file);
    }

    indices = filter(m_indexes(herbs), filter_herb_name);
    for (i = 0, s = sizeof(indices); i < s; i++)
    {
        m_delkey(herbs, indices[i]);
    }

    save_object(save_file);
}

void
remove_herb()
{
    int     i, s;
    mapping reduce_herbs;
    string *hnames;

    remove_herbs->remove_object();
    remove_herbs = ({ });

    reduce_herbs = filter(herbs, &operator(<)(max_herbs, ));
    hnames       = m_indexes(reduce_herbs);

    for (i = 0, s = sizeof(hnames); i < s; i++)
        herbs[hnames[i]] = max_herbs;
}

public void
enter_storage_inv(object ob, object from)
{
    int    n, i, s;
    string name;
    string *indices;

    if (!objectp(from))
        return;

    if (!living(ob) && stringp(ob->query_herb_name()))
    {
        name = MASTER_OB(ob);
        herbs[name] += (ob->num_heap() || 1);
        /* remove herbs */
        remove_herbs += ({ ob });

        if (!sizeof(get_alarm(remove_alarm)))
            remove_alarm = set_alarm(1.0, 0.0, remove_herb);
    }

    indices = filter(m_indexes(herbs), filter_herb_name);
    for (i = 0, s = sizeof(indices); i < s; i++)
    {
        m_delkey(herbs, indices[i]);
    }

   save_object(save_file);
}

public int
query_herb_number(string herb_file)
{
    if (!strlen(herb_file) || (file_size(herb_file + ".c") <= 0))
        return 0;

    return herbs[herb_file];
}

void
set_save_file(string str)
{
    save_file = str;
}

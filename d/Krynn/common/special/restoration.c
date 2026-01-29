/*
 * This object handles smarter registration of restoration of
 * auto loading objects.
 *
 * It basically just lets domain objects register them by themselves.
 * 
 * Cotillion@Genesis 2003-11-17
 */
#include <files.h>

static mapping restorable_items = ([ ]);

nomask void
register_restorable(string id, string desc, function query, function recover)
{
    string domain;

    domain = SECURITY->domain_object(this_object());
        
    /* Only objects in our domain can register restorables */
    if (SECURITY->domain_object(calling_object()) != domain)
        return;

    if (!wildmatch(lower_case(domain) + "_*", id))
        id = lower_case(domain) + "_" + id;
    
    restorable_items[id] = ({ desc, query, recover });
}

/*
 * Function name: query_restore_items
 * Description  : Find out which items can be restored to a player in this
 *                domain.
 * Arguments    : object player - the player to test for.                      
 * Returns      : mapping - the mapping with items that can be restored.
 */
public mapping
query_restore_items(object player)
{
    mapping items;
    string *ids;
    int index, size;
    function query;

    items = ([ ]);
    ids = m_indexes(restorable_items);

    index = -1;
    size = sizeof(ids);

    while (++index < size)
    {
        query = restorable_items[ids[index]][1];
        
        if (functionp(query) && query(player))
        {
            items[ids[index]] = restorable_items[ids[index]][0];
        }
    }
    
    return items;
}

/*
 * Function name: restore_item
 * Description  : Called to restore a single item into a player.
 * Arguments    : object player - the player to which to restore an item.
 *                string item - the code of the item to restore.
 * Returns      : int 1/0 - success/failure.
 */
public int
restore_item(object player, string item)
{
    function recover, query;

    if (!restorable_items[item])
        return 0;

    query = restorable_items[item][1];
    recover = restorable_items[item][2];
     
    /* Can the player really get this item? */
    if (!functionp(query) || !functionp(recover) || !query(player))
    {
        return 0;
    }
    
    return recover(player);
}

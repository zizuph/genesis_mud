/*
 *    equip.c  
 *
 *  Inherit this module to your NPC and it is possible
 *  to easily equip it with weapons, armours and other
 *  items. It will automatically wield/wear the items
 *  unless you set the not_wield flag to 1.
 *
 *  It contains two easy to use functions, read the
 *  function headers for more information on usage, or
 *  check out equip_ex.c in this directory.
 *
 * Baldacin@Genesis, Dec 2003. 
 *
 */

inherit "/lib/unique";
#include <files.h>

/*
 * Function name: equip_this
 * Description  : Makes the NPC clone and wield/wear 
 *                items that it can, unless the not_wield
 *                flag has been set.
 * Arguments    : mixed list    - the list of files to clone.
 *                int not_wield - Don't wield/wear? 1/0
 *                default is 0(wear/wield everything).
 * Example      : equip_this(({"/std/weapon", "/std/armour", "/std/object"}));
 */
public void
equip_this(mixed list, int not_wield = 0)
{
    object item;
    int    i;

    setuid();
    seteuid(getuid());

    if(stringp(list))
        list = ({ list });
    
    for (i = sizeof(list) - 1; i >= 0; i--)
    {
        item = clone_object(list[i]);
        
        if (!item)
            continue;
        
        item->move(this_object(), 1);

        if (not_wield)
            continue;
            
        if (IS_ARMOUR_OBJECT(item))
        {
            item->wear_me();
        }
        else if (IS_WEAPON_OBJECT(item))
        {
            item->wield_me();
        }
    }
}

/*
 * Function name: equip_unique
 * Description  : Makes the NPC clone and wield/wear 
 *                items that it can, unless the not_wield
 *                flag has been set. (uses the clone_unique()
 *                function)
 * Arguments    : mapping list    - the map of files to clone.
 *                the first argument in the array is how many
 *                unique items it can be before it clones the
 *                alternative item.
 *                int not_wield   - Don't wield/wear? 1/0
 *                default is 0(wear/wield everything).
 * Example      : equip_unique( (["/path/unique_item":({3, "/path/alt_item"}) ]));
 */
public void
equip_unique(mapping list, int not_wield = 0)
{
    object item;
    int    i;
    mixed indexes;

    setuid();
    seteuid(getuid());
       
    indexes = m_indexes(list);
    
    for (i = sizeof(indexes) - 1; i >= 0; i--)
    {
        item = clone_unique(indexes[i], list[indexes[i]][0],
               ({list[indexes[i]][1], 100}), 1, 100);

        if (!item)
            continue;
        
        item->move(this_object(), 1);

        if (not_wield)
            continue;
            
        if (IS_ARMOUR_OBJECT(item))
        {
            item->wear_me();
        }
        else if (IS_WEAPON_OBJECT(item))
        {
            item->wield_me();
        }
    }
}
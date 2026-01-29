/*
 * /d/Krynn/std/equip.c
 *
 * Provides efficient equipment cloning and wearing/wielding 
 * routines.
 *
 * Hopefully replacing some of the more ugly constructs scatterd
 * throughout the world.
 *
 * Cotillion 2002-05-26
 *
 * Example Usage:
 *
 * equip(({ "/std/weapon", "/std/armour" }));
 *
 * This makes the npc clone the items, wield the weapons and wear the
 * armour. This function must be called AFTER skills have been set.
 */

#include <files.h>

int
wield_wear_item(object ob)
{
    switch (function_exists("create_object", ob))
        {
        case WEAPON_OBJECT:
            ob->wield_me();
            break;
        case ARMOUR_OBJECT:
            ob->wear_me();
            break;
        default:
            break;
        }
    return 0;
}

/*
 * Function name:  equip
 * Description:    clones weapons, armour or other objects and makes
 *                 the npc wield and wear all.
 * Arguments:      equiplist: string, or array of strings with the
 *                       filenames of the equipment to clone
 *                 dont_wield: if this flag is set the npc will
 *                       not attempt to wield or wear any of the
 *                       equipment cloned. [optional]
 * Note:           It doesn't hurt to leave off the dont_wield flag even
 *                 when the things you are cloning are not weapons and
 *                 armour. The npc only attempts to wield or wear legit
 *                 weapons and armour. The only use for the flag is when
 *                 you for some reason want the npc to have some weapon
 *                 or armour in his inv. but not worn/wielded.
 * Returns:
 */
public varargs object *
equip(mixed equiplist, int dont_wield = 0)
{
    object otp;
    
    setuid();
    seteuid(getuid());

    otp = this_player();
    set_this_player(this_object());
    
    if (!pointerp(equiplist))
        equiplist = ({ equiplist });
    
    equiplist = filter(equiplist, objectp) + 
        map(filter(equiplist, stringp), clone_object);
    equiplist->move(this_object(), 1);
    
    if (!dont_wield)
        filter(equiplist, wield_wear_item);
    
    set_this_player(otp);
    return equiplist;
}

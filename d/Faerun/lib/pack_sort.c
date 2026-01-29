inherit "/d/Faerun/lib/pack_list.c";
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>
#include <config.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

/*
 * Function name: sort_objects_to_list
 * Description:   Sort the list of objects through sort_array
 * Arguments:     a, b - arrays of identical objects
 * Returns:       1 if a after b, else -1
 */

public int
sort_objects_to_list(object *a, object *b)
{
//// weapons
////    if (b[0]->check_weapon())
////        if (a[0]->check_weapon())
//    if(IS_WEAPON_OBJECT(b[0]))
//        if(IS_WEAPON_OBJECT(a[0]))
//        {
//            if (figure_category(a[0]) < figure_category(b[0])) return -1;
//            if (figure_category(a[0]) > figure_category(b[0])) return 1;
//            if (a[0]->short() < b[0]->short()) return -1;
//            return 1;
//        }
//        else
//            return 1;
//    else
////        if (a[0]->check_weapon())
//        if(IS_WEAPON_OBJECT(a[0]))
//            return -1;
//// armours
////    if (b[0]->check_armour())
////        if (a[0]->check_armour())
//    if(IS_ARMOUR_OBJECT(b[0]))
//        if(IS_ARMOUR_OBJECT(a[0]))
//        {
//            if (figure_category(a[0]) < figure_category(b[0])) return -1;
//            if (figure_category(a[0]) > figure_category(b[0])) return 1;
//            if (a[0]->short() < b[0]->short()) return -1;
//            return 1;
//        }
//        else
//            return 1;
//    else
//        if (a[0]->check_armour())
//            return -1;

// Weapons
    if(IS_WEAPON_OBJECT(b[0]))
        if(IS_WEAPON_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_WEAPON_OBJECT(a[0]))
             return -1;
// Armours
    if(IS_ARMOUR_OBJECT(b[0]))
        if(IS_ARMOUR_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ARMOUR_OBJECT(a[0]))
             return -1;
// Arrows
    if(IS_ARROW_OBJECT(b[0]))
        if(IS_ARROW_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ARROW_OBJECT(a[0]))
             return -1;
// Books
    if(IS_BOOK_OBJECT(b[0]))
        if(IS_BOOK_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_BOOK_OBJECT(a[0]))
             return -1;
// Coins
    if(IS_COINS_OBJECT(b[0]))
        if(IS_COINS_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_COINS_OBJECT(a[0]))
             return -1;
// Containers
    if(IS_CONTAINER_OBJECT(b[0]))
        if(IS_CONTAINER_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_CONTAINER_OBJECT(a[0]))
             return -1;
// Drinks
    if(IS_DRINK_OBJECT(b[0]))
        if(IS_DRINK_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_DRINK_OBJECT(a[0]))
             return -1;
// Foods
    if(IS_FOOD_OBJECT(b[0]))
        if(IS_FOOD_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_FOOD_OBJECT(a[0]))
             return -1;
// Gems
    if(b[0]->query_gem())
        if(a[0]->query_gem())
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(a[0]->query_gem())
             return -1;
// Herbs
    if(IS_HERB_OBJECT(b[0]))
        if(IS_HERB_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_HERB_OBJECT(a[0]))
             return -1;
//Keys
    if(IS_KEY_OBJECT(b[0]))
        if(IS_KEY_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_KEY_OBJECT(a[0]))
             return -1;
// Body Parts and Leftovers
    if(IS_LEFTOVER_OBJECT(b[0]))
        if(IS_LEFTOVER_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_LEFTOVER_OBJECT(a[0]))
             return -1;
//Potions
    if(IS_POTION_OBJECT(b[0]))
        if(IS_POTION_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_POTION_OBJECT(a[0]))
             return -1;
// Projectiles
    if(IS_PROJECTILE_OBJECT(b[0]))
        if(IS_PROJECTILE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_PROJECTILE_OBJECT(a[0]))
             return -1;
// Ropes
    if(IS_ROPE_OBJECT(b[0]))
        if(IS_ROPE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_ROPE_OBJECT(a[0]))
             return -1;
// Scrolls
    if(IS_SCROLL_OBJECT(b[0]))
        if(IS_SCROLL_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_SCROLL_OBJECT(a[0]))
             return -1;
// Torches and Lights
    if(IS_TORCH_OBJECT(b[0]))
        if(IS_TORCH_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_TORCH_OBJECT(a[0]))
             return -1;
// Wearable Items
    if(IS_WEARABLE_OBJECT(b[0]))
        if(IS_WEARABLE_OBJECT(a[0]))
        {
            if (figure_category(a[0]) < figure_category(b[0])) return -1;
            if (figure_category(a[0]) > figure_category(b[0])) return 1;
            if (a[0]->short() < b[0]->short()) return -1;
            return 1;
        }
        else
            return 1;
    else
        if(IS_WEARABLE_OBJECT(a[0]))
             return -1;


    if (a[0]->short() < b[0]->short()) return -1;
    return 1;
}

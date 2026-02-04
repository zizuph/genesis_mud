/*
 * Food/Drink Shadow
 *
 * By default, vampires can eat and drink, but never get full or fill
 * up on mortal thirst. The reason for this is thematic, since they
 * can roleplay as a normal person and eat and drink thinsg in front
 * of others. 
 *
 * However, the flip side of this theme must be true as well. They
 * must gain no benefit to the food or drink that they consume. This
 * is not currently the case.
 *
 * This shadow will shadow any food or drink object and ensure that the
 * special_effect() function doesn't actually do anything.
 *
 * Created by Petros, August 2009
 */

#pragma strict_types

#include <files.h>
inherit "/std/shadow";

/*
 * Function:    has_food_drink_shadow
 * Description: This will identify whether the object has this shadow
 *              or not.
 */
public int
has_food_drink_shadow()
{
    return 1;
}

/*
 * Function:    remove_food_drink_shadow
 * Description: Removes the food/drink shadow from the object.
 */
public void
remove_food_drink_shadow()
{
    remove_shadow();
}

/*
 * Function:    special_effect
 * Description: This shadow will make sure that special_effect never
 *              does anything for food and drinks.
 */
public void
special_effect(int amount)
{
    // Do absolutely nothing for food and drinks
    if (IS_FOOD_OBJECT(shadow_who) || IS_DRINK_OBJECT(shadow_who))
    {
        return;
    }
    
    shadow_who->special_effect(amount);
}

/*
 * Function:    remove_drink
 * Description: Gets called whenever the drink is actually consumed.
 */
public void
remove_drink()
{
    shadow_who->remove_drink();
    remove_food_drink_shadow();
}

/*
 * Function:    remove_food
 * Description: Gets called whenever the food is actually consumed.
 */
public void
remove_food()
{
    shadow_who->remove_food();
    remove_food_drink_shadow();
}

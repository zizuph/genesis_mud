/*
 * Support for MMORPG-like item drops.
 *
 * Examples:
 *
 * add_drop("/std/sword", 0.03)
 *
 * There is a 3% chance the monster will drop a sword each time it's
 * killed.
 *
 * add_drop("/d/Foo/quest_ring", 0.5, "DOING_RING_QUEST", 1);
 *
 * Each player who participates in the kill and has the prop
 * "DOING_RING_QUEST" has a 50% chance of getting a ring from
 * the corpse.
 *
 */

mixed item_drop;

#define INDIVIDUAL "/d/Krynn/common/shadows/individual"

/*
 * Function Name: add_drop
 * Description: Adds an item that might drop from the monster.
 *              
 * Arguments  : string - The item to drop.
 *              float  - The drop chance. 1.0 = 100%
 *              fun    - A function that must
 *                       return true for drop to be possible.
 *                       If the drop is individual the player object
 *                       will be sent as function argument.
 *              int(0) - If this is true the drop will only be
 *                       visible for one player. And the drop is 
 *                       calculated for all players who participated
 *                       in the kill. If the chance is 100% and 5 people
 *                       helped kill it, there will be 5 items.
 *                       For this to work the item has to inherit
 *                       the soulbound module.
 */
varargs void
add_drop(string file, float chance, mixed access = 1, int individual = 0)
{
    if (!item_drop)
    {
        item_drop = ({ });
    }

    item_drop += ({ ({ file, chance, access, individual }) });
}

/*
 * Function Name: clear_drop
 * Description  : Removes all item drops in the monster
 */
void
clear_drop()
{
    item_drop = ({ });
}

/*
 * Function Name: remove_drop
 * Description  : Remove an item from the drop list.
 * Arguments    : string - the item
 */
void
remove_drop(string file)
{    
    item_drop = filter(item_drop, &operator(!=)(, file) @
        &operator([])(, 0));    
}

/*
 * Function Name: drop_items
 * Description  : Executes the item drops.
 */
void
drop_items()
{
    object ob, player, shad, *killers;
    int index, kid;
    function fun;

    /* Who should get the item if it's an individual drop? */
    killers = filter(all_inventory(environment()),
        &operator(==)(, this_object()) @ &->query_attack());
    
    index = sizeof(item_drop);
    while (index--)
    {
        fun = item_drop[index][2];
        if (item_drop[index][3])
        {            
            /* Individual drops need to be executed for all
             * killers */
            kid = sizeof(killers);
            while (kid--)
            {
                player = killers[kid];
                if (item_drop[index][1] > rnd() &&
                    (!functionp(fun) || fun(player)))
                {
                    ob = clone_object(item_drop[index][0]);
                    ob->move(this_object(), 1);

                    /* Add the shadow that prevent the wrong
                     * people from getting it. */
                    shad = clone_object(INDIVIDUAL);
                    shad->individual(ob, player);
                }
            }
            
        }
        else
        {
            if (item_drop[index][1] > rnd() &&
                (!functionp(fun) || fun()))
            {
                ob = clone_object(item_drop[index][0]);
                ob->move(this_object(), 1);
            }
        }
    }
}

void
hook_killed(object killer)
{
    drop_items();
}

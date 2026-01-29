/*
 * /d/Gondor/mordor/ungol/tower_desc.c
 *
 * This file is only used to describe the tower at Cirith Ungol. I have used
 * the description J.R.R. Tolkien used in his book The Lord of the Rings and
 * changed it slightly for use in the game. For I wanted to be free to change
 * the description and I didn't want to use copy and paste all the time, I
 * put the description in a separate file. To use it, just make a call to
 *
 * ADD_ITEM_TOWER;
 *
 * in your create_room() function. This call will then add several add_item()
 * descriptions to your room:
 * - tower stronghold
 * - cliff cliffs
 * - mountain mountains
 * - court yard courtyard
 * - gate arch
 * - turret tier
 * - tiers
 * - wall walls
 * - bastion bastions
 *
 * In case you want to use some of those names for your own definitions, be
 * advised to add ADD_ITEM_TOWER; before you add any other calls to add_item()
 * yourself.
 *
 * /Mercade, 24 September 1993
 *
 * Revision history:
 */

#define ADD_ITEM_TOWER add_item_tower_at_cirith_ungol()

/*
 * Function name: add_item_tower_at_cirith_ungol
 * Description  : Adds various add_item descriptions to the room. For more
 *                information, read the header of this file :-)
 */
void
add_item_tower_at_cirith_ungol()
{
    add_item( ({ "tower", "stronghold" }),
        break_string("From this place you can see the tower in all its " +
        "strength. From the other side of the mountains, only the topmost " +
        "turret can be seen as a horn. Its eastern face stands up in three " +
        "tiers from a shelf in the mountain-wall far below; its back is to " +
        "a great cliff behind, from which it juts out in the pointed " +
        "bastions, one above the other, diminishing as they rise, with " +
        "sheer sides of cunning masonry that looks northeast and southeast. " +
        "About the lowest tier there is a battlemented wall enclosing a " +
        "narrow court. On the near southeastern side of the wall is its " +
        "gate. You realize that this stronghold is not built to keep " +
        "enemies out of Mordor, but to keep them in. It was indeed one of " +
        "works of Gondor long ago, an eastern outpost of the defences of " +
        "Ithilien, made when Man of Westernesse kept watch on the evil land " +
        "evil land of Sauron where his creatures still lurk. But as with " +
        "Narchost and Carchost, the Towers of the Teeth, so here too the " +
        "vigilance had failed, and treacery had yielded up the Tower of the " +
        "Lord of the Ringwraiths, and now for long years it had been held " +
        "by evil things.", 77) + "\n");
/*
    add_item( ({ "" }),
        break_string("", 77) + "\n");
    add_item( ({ "" }),
        break_string("", 77) + "\n");
 */
}

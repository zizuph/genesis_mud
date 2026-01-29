/*
   /d/Kalad/lib/arm_me.c
 
   Inherit this to add armours and weapons to your npc.
 
   Fysix@Genesis, Nov 1997
 */
#pragma strict_types

inherit "/std/act/add_things";

/* Function name: add_equipment
 * Description:   Set the equipment to wear/wield later.
 *                Have to call arm_me to really clone, wield and wear.
 * Arguments:     mixed - a filename, or an array of filenames of the
 *                        equipment to be cloned
 */
public void
add_equipment(mixed equipment)
{
    equip(equipment);
}

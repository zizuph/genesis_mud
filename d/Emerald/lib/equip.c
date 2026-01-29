/* A simple module used to equip npcs.
 *
 * Created by Shiva@Genesis
 */

public void equip_action(object *eq);

/* Function name: add_equipment
 * Description:   add an item to the npc's inventory.  All armours
 *                and weapons added via add_equipment will be wielded/worn.
 * Arguments:     mixed eq - the path to the object to be cloned or
 *                           an array of paths.
 */
void
add_equipment(mixed eq)
{
    if (!pointerp(eq))
    {
        eq = ({ eq });
    }

    setuid();
    seteuid(getuid());

    eq = map(eq, clone_object);
    eq->move(this_object(), 1);
    
    equip_action(eq);
}

/*
 * Function name: equip_action
 * Description:   Ready the npc's equipment.
 * Arguments:     object *eq - the equipment to ready.
 */
public void
equip_action(object *eq)
{
    command("wield all");
    command("wear all");
}

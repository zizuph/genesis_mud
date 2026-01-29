/*
 * /d/Raumdor/common/beach/bountiful/obj/damon_key.c
 *
 * Key for the Damon Skragg's loot-chest.
 * Nerull, 2015
 *
 */

inherit "/std/key";

/*
 * Function name: destroy_me()
 * Description  : Destroys the key.
 */
void
destroy_me()
{
    write("The black metal key breaks!\n");
    remove_object();
}

/*
 * Function name: create_key()
 * Description  : Constructor. Creates the key.
 */
void
create_key()
{
    add_name("_damon_chest_key");
    set_adj("black");
    add_adj("metal");
    set_long("This is a key made of black corroded metal. It"
    +" may fit in a lock somewhere.\n");

    // This key don't last forever.
    set_alarm(600.0, 0.0, &destroy_me());
}

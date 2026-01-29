/* Called in /d/Emerald/sanctuary/center/c5.c */

inherit "/d/Emerald/std/clone_handler";

void create_clone_handler()

{

    set_default_area("/d/Emerald/sanctuary/center/");

    add_clone("/d/Emerald/sanctuary/center/npc/mercenary", 1, 6);

    set_clone_handler_id("Sanctuary clone handler");

}

/*
 * Spellbook
 */

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/spellcasting";

create_object()
{
    set_name("book");
    set_long("Test spellbook.\n");
    set_short("book");

    add_spell("airblast", "air_blast", "Air Blast");
    add_spell("fireblast", "fire_blast", "Fire Blast");
}

/*
#include "air_blast.c"
*/
#include "fire_blast.c"

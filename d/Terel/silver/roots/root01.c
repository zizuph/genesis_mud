/* File         : /d/Terel/silver_new/roots/root01.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Root File in the Root System
 * Related Files: /d/Terel/silver/include/root_base.c
 * Comments     : Basic Room in the Root System
 * Modifications: 
 */


#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "root_base";

public void
create_room()
{
    ::create_room();
    set_short("A small intersection below the oak");
	add_exit(FOREST_AG + "oak", "up", 0);
    reset_room();
}

/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon(void)
{
    string *arr = ({
	"barbed", 20, "cruel", 12, "vicious", 15, "wicked", 9,
	"sharp", 10, "long", 13, "hideous", 17, "large", 13,
    });
    int n = random(sizeof(arr) / 2) * 2;

    set_name("spear");
    set_adj(arr[n]);
    set_short(arr[n] + " spear");
    set_pshort(arr[n] + " spears");
    set_long("You see nothing special about the "+ short() +".\n");

    set_default_weapon(20, arr[n + 1] + 3, W_POLEARM, W_IMPALE, W_BOTH, 0);
}

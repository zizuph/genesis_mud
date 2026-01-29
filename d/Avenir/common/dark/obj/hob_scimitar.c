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
	"curved", 10, "cruel", 8, "vicious", 15, "wicked", 6,
	"blood stained", 11, "jagged", 14, "black", 12,
	"rusty", 7, "long", 13, "ornate", 17, "large", 13
    });
    int n = random(sizeof(arr) / 2) * 2;

    set_name("sword");
    add_name("scimitar");
    set_adj(arr[n]);
    set_short(arr[n] + " scimitar");
    set_pshort(arr[n] + " scimitars");
    set_long("You see nothing special about the "+ short() +".\n");

    set_default_weapon(25, arr[n + 1] + 5, W_SWORD, W_IMPALE | W_SLASH, W_ANYH, 0);
}

/* The key NOT :) for the drawer
 *
 * Aridor 09/95
 */

#include "local.h"

inherit "/std/key";


void
create_key()
{
    string color;

    set_name("key");
    switch(random(5))
      {
	case 0:   color = "silver";
	  break;
	case 1:   color = "gold";
	  break;
	case 2:   color = "iron";
	  break;
	case 3:   color = "small";
	  break;
	case 4:   color = "shimmering";
	  break;
	default:  color = "brass";
      }
    set_adj(color);
    set_long("This is a normal " + color + " key.\n");
    set_key(random(1000000) + 100000);
}

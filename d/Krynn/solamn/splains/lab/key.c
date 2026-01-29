/* The key for the drawer
 *
 * Aridor 09/95
 */

#include "local.h"


inherit "/std/key";


void
create_key()
{
    set_name("key");
    set_adj("bronze");
    set_long("This is a normal bronze key.\n");
    set_key(DRAWER_KEY);
}

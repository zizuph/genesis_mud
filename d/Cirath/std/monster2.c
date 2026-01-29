/* monster.c: The Cirath replacement for /std/monster.
 *     Largely based on the Krynn version, with other odd
 *     bits inserted/removed here and there.
 *                           -- Serpine, 2/23/96.
 *
 * WARNING: Don't mess with this file, its going to be
 *          used all over the place in this domain.
 *--------------------------------------------------------
 */
 
#pragma strict_types
#pragma save_binary
 
inherit "/std/monster";
#include <options.h>
 
string assist_cry="";
 
 
/* Function name: set_assist_cry & query_assist_cry
 * Description:   These functions set and query the current thing said
 *                by someone when they move to defend a teammate.
 * Arguments:     cry - what is to be said
 */
void set_assist_cry(string cry) { assist_cry = cry; }
string return_assist_cry() { return assist_cry; }
 
 
/* Function name: create_monster & init_living
 * Description:   The standard create and init_living, do ::create_monster()
 *                and ::init_living in them respectively to use them
 */
void
create_monster()
{
    ::create_monster();
    set_assist_cry("How dare you attack my associate!");
    set_default_answer("Sorry, I have no idea.\n");
}
 
 
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


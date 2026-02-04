/* The key that unlocks the writing desk, hidden in the
 * ashes of the old fire in library_1.c
 */

inherit "/std/key";

create_key()
{
  set_name("key");
  set_pname("keys");
  set_adj("small");
  add_adj("brass");
  set_long("A small key made out of brass. Too small, it seems, for a door lock.\n");
  add_name("writing_desk_key");
}
 

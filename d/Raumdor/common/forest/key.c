/* A simple key to the door examples by Nick */

inherit "/std/key";

create_key()
{
  set_adj("golden");
  add_adj("odd-shaped");
  set_long("It is an odd shaped golden key.\n");
  set_key(782);
}

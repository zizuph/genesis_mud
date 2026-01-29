/* A simple key to the door examples by Nick */

inherit "/std/key";

void
create_key()
{
  set_adj("black");
  add_adj("jeweled");
  set_long("This key is made of black stone. On it, you see many "+
  "dark jewels on it, which gleam darkly in the light.\n");
  set_key("free_goblin_quest_kalad");
}

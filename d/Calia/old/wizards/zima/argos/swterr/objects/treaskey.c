/*   Temple of Dephonia, Key to treasure room, door from minotaur pit
 *       to treasure room.
 *   Location: Kept by minotaur in the pit; must kill to get
 *   HISTORY:
 *   CODER         DATE             ACTION
 *  ------------ -------- -----------------------------------------------
 *   Zima         3/12/94   Created
 *
 */
 
inherit "/std/key";
 
create_key()
{
  set_adj("cumbersome");
  add_adj("brass");
  set_long("It is a large, cumbersome brass key, very inornate.\n");
  set_key(960);
}

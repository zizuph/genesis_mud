/*   Temple of Dephonia, Library key, door from library to upper room
 *   Location: Kept by Keeper of the Chronicles in library; must kill to get
 *   HISTORY:
 *   CODER         DATE             ACTION
 *  ------------ -------- -----------------------------------------------
 *   Zima         1/1/94   Created
 *
 */
 
inherit "/std/key";
 
create_key()
{
  set_adj("small");
  add_adj("silver");
  set_long("It's a small key made out of silver.\n");
  set_key(959);
}

/*   Temple of Dephonia, Key to pit of the minoutaur, from hallway to pit
 *   Location: Kept by Hierophant; must kill to get; so hard to get
 *             because we don't want newbies walking in on minotaur...
 *             instant death!
 *   HISTORY:
 *   CODER         DATE             ACTION
 *  ------------ -------- -----------------------------------------------
 *   Zima         3/12/94   Created
 *
 */
 
inherit "/std/key";
 
create_key()
{
  set_adj("black");
  add_adj("iron");
  set_long("A heavy black iron key with a bull's head engraved on it.\n");
  set_key(961);
}

/* This is /d/Gondor/common/npc/wrabbit.c
 * A white rabbit
 * Dunstable, Septembet 1993
 */
inherit "/d/Gondor/common/npc/rabbit";

void
create_creature()
{
  ::create_creature();
  set_short("small white rabbit");
  set_long("A small white rabbit with large eyes and long ears, looking quite harmless. \n");
  remove_adj("brown");
  add_adj("white");
}

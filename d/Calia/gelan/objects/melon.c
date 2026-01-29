/* A huge melon for the grocery shop in Gelan */

inherit "/d/Calia/std/fruit";

void
create_fruit()
{
   set_name("melon");
   set_adj(({"huge", "ripe", "juicy"}));
   set_short("huge melon");
   set_pshort("huge melons");
   set_long("A huge ripe juicy melon.\n");
   set_fruit_amount(10);
   set_mana_add(6);
   set_hp_add(20);
   set_fatigue_add(0);
}


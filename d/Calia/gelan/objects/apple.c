/* A large apple for the grocery shop in Gelan */

inherit "/d/Calia/std/fruit";

void
create_fruit()
{
   set_name("apple");
   set_short("large apple");
   set_adj(({"large", "ripe", "red"}));
   set_long("A large ripe red apple.\n");
   set_fruit_amount(2);
   set_mana_add(0);
   set_hp_add(0);
   set_fatigue_add(10);
}


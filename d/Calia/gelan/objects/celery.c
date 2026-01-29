/* A stick of celery for the grocery shop in Gelan */

inherit "/d/Calia/std/fruit";

void
create_fruit()
{
   set_name("celery");
   set_pname("celeries"); 
   add_name("stick"); 
   add_pname("sticks"); 
   set_short("stick of celery");
   set_pshort("sticks of celery");
   set_long("A long stick of celery.\n");
   set_fruit_amount(1);
   set_mana_add(10);
   set_hp_add(0);
   set_fatigue_add(0);
}


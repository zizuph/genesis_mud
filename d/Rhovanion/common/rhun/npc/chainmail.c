inherit "/std/armour";

void create_armour()
{
  set_name(({"chainmail","mail","armour"}));
  set_adj(({"black","rusty","chain"}));
  set_short("black rusty chainmail");
  set_long("This is a simple black chainmail. It is a bit rusty.\n");
  set_default_armour();
  set_ac(12);
  set_at(2);
}

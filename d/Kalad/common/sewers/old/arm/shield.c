/*
   shield.c

   A sample armour
*/
inherit "/std/armour";

create_armour()
{
    set_name("shield");
    set_short("leather shield");
    set_adj("leather"); add_adj("rugged");
    set_long("It is a very large shield, but it's made from leather.\n");
    
    set_default_armour();
    set_ac(2);
    set_at(-1);
}

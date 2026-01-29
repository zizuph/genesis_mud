inherit "/std/armour";

create_armour()
{
 set_name("shirt");
 set_short("stained shirt");
 set_long("This shirt smells almost as bad as it's owner. It has food stains "+
  "on various places, as well as a few nice sized holes.\n");
 set_adj("cloth");
 add_adj("stinking");
add_adj("worn");

 set_default_armour(2);

}

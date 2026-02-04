inherit "/std/herb";
#include <stdproperties.h>
#include <herb.h>


create_herb(){

set_name("flower");
add_name("wildflower");
add_name("wild_flower");
set_short("@@my_short");

set_id_long("It is a plain wildflower, its only value is beauty.\n");
set_unid_long("It is a beautiful flower.\n");
set_herb_name("wildflower");
add_prop(OBJ_I_VALUE, 5);
  desc();
}

desc(){
  string *descs;
   descs = ({ "savory blue", "fiery yellow", "heroic red", "pure white", 
      "fiery violet", "spicy orange" });

   add_adj(descs[random(sizeof(descs))]);
}

my_short(){
  return query_adj() + " flower";
}

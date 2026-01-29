inherit "/std/object";

#include "/sys/stdproperties.h";

create_object() 
{
  set_short("brown pinecone");
  set_name("pinecone");
  add_name("cone");
  add_name("_dunlending_object");
  add_adj("pine");
  add_adj("brown");
  set_long("This is a pinecone. It's a about the size of your closed "
	+ "fist. Small spikes surround it, making you hold it carefully. "
	+ "Pinecones like this are often found in pine forests.\n");

  add_prop(OBJ_I_WEIGHT,500);
  add_prop(OBJ_I_VOLUME,5000);
  add_prop(OBJ_I_VALUE, 0);
}


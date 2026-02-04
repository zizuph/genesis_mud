// This is the "new" coffin the player sees that looks like it is theirs/
// -- Lilith

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
	
    set_name("coffin");
	add_name("_terel_tomb_coffin");
	set_adj(({ "new", "wood" }));
	add_adj(({"newer", "newest"}));
    set_short("new wood coffin");
    set_long("This new coffin is made of wood. It is open.\n"+  
        "The coffin's interior is lined with fine velvet. It actually " +
	    "looks rather comfortable and inviting. The lid of the coffin " +
        "is riddled with holes. The edges of the holes have " +
        "deposits of crusted blood around them. The coffin has an " +
	    "inscription on it.\n"); 

    add_item(({"inscription"}), 
        "The inscription on the coffin bears the unmistakable letters "+
        "of YOUR name!\n");
		
    add_cmd_item(({"inscription"}), "read", 
        "The inscription on the coffin bears the unmistakable letters "+
        "of YOUR name!\n");   

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 100000);
}
     

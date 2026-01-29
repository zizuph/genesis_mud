inherit "/std/monster";

#include <macros.h>
#include "/d/Faerun/defs.h"


create_monster()
{
    set_name("nerissa");

    set_race_name("human");

    set_adj( ({"happy"}) );

    set_stats( ({39, 79, 58, 68, 68, 30}) );

    set_alignment(0);

    set_gender(G_FEMALE);
    
    set_size_descs("tall","lean"); 
}

public string query_height_desc(){return "willowy"; }
		
public string query_width_desc() { return "slender"; }

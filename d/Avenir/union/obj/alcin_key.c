// file name:    /d/Avenir/union/obj/alcin_key
// creator(s):   Lilith, Dec 2003
// purpose: 	used in Akram dagger quest	
// cloned by:     /d/Avenir/union/npc/alcintaron	
/*
 * Revisions:
 * 	Lucius: Jul 2017: Re-Code.
 */
#pragma strict_types

inherit "/std/key";
#include <stdproperties.h>

public void
create_key() 
{
    set_name(({ "key", "_alcin_key"}));
    set_adj(({"brass", "large", "union"}));
    set_short("large brass key");
    set_long("This key is made of brass. It is rather large, "+
      "with a thick rounded barrel and three teeth at the end. "+
      "The handle is engraved with the image of a book opened "+
      "at the center, with a sphere above it.\n");

    add_item(({"barrel"}),
	"It is as thick around as your smallest finger.\n");
    add_item(({"teeth"}),
	"There are three teeth at the end of the barrel, each "+
	"one cut slightly differently.\n");
    add_item(({"handle", "image"}),
	"On the ornate handle is the image of a book opened "+
	"at the center, with a sphere above it.\n");

    add_prop(OBJ_I_WEIGHT, 100);    
    add_prop(OBJ_I_VOLUME, 100);  
    add_prop(OBJ_I_VALUE,  100); 
}

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h" 

create_camproom()
{
    ::create_room();
    add_item(({"tent","tents"}), 
      "These tents are all alike, crudely patched together from scraps "+ 
      "of uncured hide, canvas, and leather.  Their basic shape is a "+ 
      "large A-frame, made of four support poles and a center ridge "+ 
      "pole.  The tents have large gaps between the poorly attached "+ 
      "materials, and most likely do a terrible job of keeping out the "+ 
      "weather.\n"); 
    add_item(({"ground","dirt"}), 
      "The ground here alternates between hard, packed dirt and a "+ 
      "thick, sticky stew where things have been spilt or left out to "+ 
      "rot in the air.  It is fairly obvious this area receives regular "+ 
      "traffic from many booted feet that care not what they trample. "+ 
      "Little vegetation has survived the occupation, with sparse clumps "+ 
      "of grass and weeds poking up through the debris occasionally.\n");  
    add_item(({"trash","debris","rubbish","stew", 
	"puke","fecal matter","food","flesh","materials"}), 
      "This is a morass of fecal matter, puke, food, shreds of flesh "+ 
      "and many other types of materials all churned into the ground "+ 
      "by the occupying forces.  The stench is horrible.\n"); 
    add_item(({"vegetation","grass","weeds","weed"}), 
      "What little there is of it barely survives off what little "+ 
      "sunlight, water, and nutrients reach it in this hellhole.\n");
    add_item(({"fire","campfire","fires","campfires"}),
      "Small campfires are scattered throughout the campsite, "+
      "providing some light in the heavy mist.  However, they also "+
      "cause lots of dancing shadows to confuse the eyes.\n");
}


void create_room()
{
    ::create_room();
    create_camproom();
}


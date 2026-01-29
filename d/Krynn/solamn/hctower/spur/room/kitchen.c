// Knights' Spur kitchen
// wood/water quest here with cook
// grace 05 Apr 1995

#include "../local.h"
inherit SPURRM;

object cook;

create_spur_room()
{
   SHORT("kitchen");
   LONG("This large room is quite obviously a kitchen.\n"+
	"   A huge hearth dominates the north wall, flanked on "+
	"either side by stone ovens.  Hanging from a tripod "+
	"placed over the fire, a blackened iron pot bubbles "+
	"merrily.  Shelves and counters line the south wall.  "+
	"There is a large wooden tub set into one of the "+
	"counters, and over it, a hand-pump stands sentinel."+
	"  Various herbs dangle from the high ceiling, contri"+
	"buting their scents to the general aroma of baking "+
	"bread, roasting meat, and woodsmoke.\n");

   AE(ROOM + "inn", "south", 0);

   AI(({"hearth", "fireplace", "grate"}), "A large fireplace which "+
	"covers most of the north wall. Its interior is lined "+
	"with burning logs and glowing embers. A tripod sits "+
	"in the center.\n");

   AI(({"log", "logs", "ember", "embers", "fire"}),
	"The logs are rather large, the type which take two "+
	"strong men to carry and throw into the grate. They "+
 	"burn for so long and so hotly that they leave behind "+
        "big glowing embers which radiate intense heat.\n");
 
   AI(({"north wall"}), "Heat rolls off of this wall in waves, "+
	"parching your exposed skin and making your lungs "+
	"long for moist, cool air. The source of the heat "+
	"is a large hearth and four stone ovens, all of "+
	"which seem to be in use.\n");

   AI("tripod", "Made of a black metal which seems well-able "+
	"to withstand the heat of the fire, a pot is suspended "+
	"from a chain in its center.\n");

   AI(({"pot", "cauldron"}),
	"A bubbling cauldron which looks like something from "+
	"a faerie tale. The liquid inside it contains various "+
	"vegetables and aromatic and flavour-enhancing herbs. "+
	"It smells delicious.\n");

   AI("air", "It is hot and dry, and scented with herbs.");

   ACI("air", "smell", "You inhale deeply through your nose.\n"+
	"The first scent to distinguish itself from the others "+
	"is that of tomato sauce.\nThere is a subtle blending "+
	"of herbs that amounts to a mouth-watering aroma, and "+
	"then the rich smell of roasting capon.\n");

   AI(({"tub", "bucket"}),	
 	"This wooden tub looks like a receptacle for water. "+
	"Near the bottom of it is a circular hole with a cork "+
	"in it, most likely for draining the bucket of water.\n");

   AI(({"cork", "plug", "plugh", "bung"}),
 	"It is used to plug the hole near the bottom of the tub.\n");
    
   ACI(({"cork", "plug", "plugh", "tub", "bucket"}),
      	({"uncork", "remove", "get"}),
	"The piece of cork is wedged too tightly into the hole. "+
	"You suspect that the cook must have some special tool "+
	"she uses both to remove it and drive it back in.\n");

   AI(({"hand-pump", "pump", "handle", "spigot"}),
	"This is one of the latest inventions of the "+
	"gnomes of Mount Mevermind. Using it, the cook can raise "+
	"water up into the kitchen from the river which runs "+
        "below the Spur.\n   There is a handle which can be lifted "+
	"up at a right angle to the hollow pipe against which it "+
	"rests. Water is expected to run up the pipe and out "+
	"through the spigot opposite the handle\nYou are dubious "+
	"as to whether or not it will actually work.\n");
   ACI(({"handle", "pump"}), ({"raise", "pump"}), 
	"You raise and lower the handle in a furious pumping "+
	"motion.\n   You are rewarded with a hollow gurgling "+
	"sound and a small splash of water.\n");

   AI(({"counters", "counter"}),
 	"Smooth dark wood, scarred in some places "+
	"with knife-marks. The counters are dusted with flour "+
	"and dried herbs. In long, rectangular pans bread "+
	"dough rises, giving off a yeasty smell.\n");

   AI(({"shelves", "shelf"}),
	"The shelves are lined with canisters "+
	"containing everything from flour and sugar to "+
	"common and rare herbs. Despite the relative chaos "+
	"of the rest of the kitchen, these are well-organized.\n");

   AI(({"herb", "herbs"}),
	"Herbs ranging from freshly cut to well-dried "+
	"hang upside-down from the ceiling.\n");

set_tell_time(4);
   add_tell("Steam rises from the ovens.\n");
   add_tell("Sweat forms in beads on your skin.\n");
   add_tell("Flames flicker wildly for a moment, casting "+
	"golden shadows on the walls.\n");
   add_tell("A droplet of stew falls, sizzling, into the flames.\n");
   add_tell("The tantalizing smells cause your mouth to water.\n");

     add_prop(ROOM_I_TYPE, ROOM_BEACH);
   reset_spur_room();
}

reset_spur_room()
{   
   if (!cook)
      (cook = clone_object(SNPC + "cook"))->move_living(0, TO);
}

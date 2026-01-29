inherit "/d/Krynn/common/area/area_handler";

#include <stdproperties.h>
#include "local.h"


void
create_area()
{
    set_map(MAP);
    add_desc("p", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "On the plains of Solamnia", 
			  "Bushes and the occasional tree block most of the view of the distant grasslands, but " +
                          "that doesn't lessen the feeling of the great size of the land before you. " +
			  "The land seems unusually wild and untamed, a consequence of the devestation " +
                          "brought to these lands many years ago by the Catalclysm.",
			  "A few trees and plenty of grass and bushes make up " +
			  "the Plains of Solamnia in this part. Vegetation is so high that you cannot see " +
			  "more than a couple of metres into the distance. The ground seems fertile enough " +
			  "to sustain this greenery, too." }),
		       ({ "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			  "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains.",
			  ({"tree","trees"}),"Trees, from ancient and gnarled oaks to young saplings, " +
			    "grow from the rich Solamnian soil here.",
			  ({"greenery","vegetation"}),"It's made up of grass, bushes and the scattered tree.",
			  ({"plains", "grasslands"}), "Spreading out before you as far as the eye can see is the " +
                            "eastern plains of Solamnia." }),
		       ({ })  }));
    add_desc("s", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia", 
			  "Before you is a small stream leading east and west across " +
			  "the Plains of Solamnia. Bushes and " +
			  "grass surround you and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("t", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading southeast and west " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surround you and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("u", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia", 
			  "Before you is a small stream leading southeast and northwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surround you, the plains stretching out in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("v", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading east and southwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surround you, the plains stretching out in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("w", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia", 
			  "Before you is a small stream leading northeast and west " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surrounds you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("x", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading northeast and southeast " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surround you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("y", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia", 
			  "Before you is a small stream leading northwest and southwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surrounds you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("z", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading southeast and southwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surrounds you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along in the grass.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("a", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia", 
			  "Before you is a small stream leading northeast and northwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surrounds you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("b", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading east and northwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surrounds you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    add_desc("c", ({ ({ ROOM_NORMAL, 0, 1, 4 }),
		       ({ "A stream on the plains of Solamnia",
			  "Before you is a small stream leading northeast and southwest " +
			  "across the Plains of Solamnia. Bushes and " +
			  "grass surround you, and the plains continue in all directions." }),
		       ({ "stream", "This is a small stream, barely more than a trickle, bubbling " +
			    "merrily along through the plains.",
			    "bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.",
			    "grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains." }),
		       ({ })  }));
    
    add_desc("r", ({ ({ ROOM_NORMAL, 0, 3 }),
		       ({ "On the bank of the Vingaard River", "You are standing on the shore of " +
			  "a great river, uncrossable at this place. " +
			  "From the river southeastwards, the plains of Solamnia stretch " +
			  "out as far as you can see. To the east, far in the distance, " +
			  "something dark and menacing rises on the horizon." }),
		       ({ ({"river","shore","water"}),
			  "The shore is down at the bottom a small cliff, " +
			  "and you can't see any way to reach the water " +
			  "from here.",
			  ({ "horizon", "dark", "something dark" }),
			  "Squinting, you make out the dark and menacing form " +
                          "of the Dargaard Mountains far over to the east."}),
		       ({ }) }));
    add_desc("m", ({ ({ ROOM_NORMAL, 0, 4 }),
		       ({ "Foot of the mountains", "You are standing at the reaches of the Dargaard Mountains " +
			  "which rise up high to your east. It is impossible to travel the rugged cliffs and " +
			  "step slopes of these mountains. To you north and west, the Plains of Solamnia " +
			  "stretch out as far as you can see, the higher elevation at the foot of the mountains" +
			  "allow a view across the landscape.",
			  "These are the foothills of the Dargaard Mountains which rise up high to your east." +
			  "The Plains of Solamnia stretch out to your north and west, while the impassable cliffs " +
			  "and steep slopes of the mountains block your way east." }),
		       ({({"plains","landscape"}),"You can see several hundreds of metres, but the view is all the " +
			   "same. Greenery, trees, bushes mark the area.",
			   ({"bushes","bush","tree","trees","greenery"}),"You cannot see anything special about it.",
			   ({"mountains","dargaard mountains","foothills","cliffs","slopes"}),"The Dargaard Mountains " +
			     "loom above you, dark and sinister. A scent of evil hangs in the air.",
		     }),
		       ({ }) }));
    add_desc("1", ({ ({ ROOM_NORMAL, 0, 1 }),
		       ({ "A road across the plains", "This is a road across the plains. The plains, covered " +
			    "with bushes and an occasional tree stretch out in all directions from here.", 
			    "The plains stretch out in all directions from here. The plains " +
			     "are covered with green bushes and trees, making it difficult for you to look very far." +
                            "in the distance." }),
		       ({ "road","This road is laid out with gravel and it is very dusty and dirty. " +
			      "It is about two metres wide."}),
		       ({ }) }));
    add_desc("2", ({ ({ ROOM_NORMAL, 0, 1 }),
		       ({ "A road through the Eastern Solamnian Plains", "The plains stretch out in all directions from here.", 
			    "The plains " +
			      "are covered with green bushes and trees, making it difficult for you to look very far." }),
		       ({ "road","The road is approximately two metres in width, wide enough so that a cart can " +
			    "easily travel along it. It looks like it was once well travelled, but is now in disrepair and " +
                            "is rather overgrown." }),
		       ({ }) }));
    add_desc("3", ({ ({ ROOM_NORMAL, 0, 1 }),
		       ({ "A track across the plains", "Greenery extends in all directions around you " +
			    "except directly on the track.", "You are on a dirty track on the plains. Green bushes and " +
			      "trees extend in all directions, the ground is covered with grass." }),
		       ({ ({"track","road"}),"It's a dirty track, about one metre wide, enveloped by green vegetation all " +
			    "around.",
			  ({ "grass","bushes","trees","bush","tree","greenery"}),"The vegetation is fully developed, and " +
			    "the only thing disturbing the rich greenery is the track here." }),
		       ({ }) }));
    add_desc("4", ({ ({ ROOM_NORMAL, 0, 1 }),
		       ({ "A track across the plains", "This is a track across the plains. Greenery extends in all " +
			    "directions around you except directly on the track.", 
			    "You are on a dirty track on the plains. Green bushes and " +
			      "trees extend in all directions, the ground is covered with grass." }),
		       ({ ({"track","road"}),"It's a dusty track, about one metre wide.",
			    ({ "grass","bushes","trees","bush","tree","greenery"}),"The vegetation is fully developed, and " +
			      "the only thing disturbing the rich greenery is the track here." }),
		       ({ }) }));
    
    add_bound("V", VKEEP);
    add_bound("K", KALAMAN);
    add_bound("D", DARGAARD);
    add_bound("T", THROTL);
    add_bound("W", WATERFALL);
    add_bound("S", SOLANTHUS);
    add_bound("Q", SPRING);
    add_bound("R", REFUGEES);
    add_bound("U", RUINS);
    add_bound("F", FORD);
    add_bound("C", DRACCAMP1);
    add_bound("E", DRACCAMP2);
    add_bound("X", STREAMRIVER);
    add_bound("P", CROSSROADS);
    
    add_linev("V12K");
    add_linev("S2P34D");
    add_linev("U2T");
}


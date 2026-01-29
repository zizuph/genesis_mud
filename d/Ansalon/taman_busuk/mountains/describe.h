#define VALLEY_TOD "@@valley_tod_desc@@"
#define MOUNTAIN_TOD "@@mountain_tod_desc@@"
#define VALLEY_SEASON "@@valley_season_desc@@"
#define MOUNTAIN_SEASON "@@mountain_season_desc@@"

#define R1_S "on a mountain road"
#define R1_L1 MOUNTAIN_TOD + "This is a road crossing " +\
	"the Taman Busuk mountain range. The serpentine " +\
	"road twists and turns as it follows the easiest " +\
	"route through the mountains. " + MOUNTAIN_SEASON

#define R1_L2 MOUNTAIN_TOD + "This is a road crossing " +\
	"the Taman Busuk mountain range. The road heads " +\
	"down into a valley here. " + MOUNTAIN_SEASON

#define R2_S "on a road in a mountain valley"
#define R2_L1 VALLEY_TOD + "This is a road through a " +\
	"mountain valley. Both sides of the road are " +\
	"covered with a forest of conifers and a " +\
	"thick growth of underbrush. " + VALLEY_SEASON

#define V1_S "in a mountain valley"
#define V1_L1 VALLEY_TOD + "This is a valley in the " +\
	"Taman Busuk mountain range. Tall conifers " +\
	"form a forest here, and thick underbrush cover " +\
	"the ground. " + VALLEY_SEASON

#define V1_L2 VALLEY_TOD + "This is a valley in the " +\
	"Taman Busuk mountain range. Tall conifers " +\
	"form a forest here, and thick underbrush cover " +\
	"the ground. You find yourself near the edge of " +\
	"the valley, and steep cliffs form a natural " +\
	"barrier. " + VALLEY_SEASON

#define VALLEY_ITEMS ({"mountain","mountains","mountain range",\
        "Taman Busuk mountain range"}),\
        "The vast Taman Busuk mountain range stretches out " +\
        "like reaching fingers across the land. The immensity " +\
        "of the landscape is daunting.",\
        "peaks",\
        "The highest peaks of the mountain range reach well " +\
        "above the clouds.",\
        "clouds",\
        "A thin layer of clouds surround the highest peaks, making " +\
        "them difficult to see.",\
        "ground",\
        "@@ground_desc@@",\
        "snow",\
        "@@snow_desc@@",\
        "valley",\
        "This valley is sheltered from the worst winter storms, " +\
        "and here trees and other plants find the soil necessary " +\
        "to grow.",\
        ({"conifers","tree","trees"}),\
        "The trees here in the valley do not grow to any remarkable " +\
        "height, but they look sturdy. They offer some protection " +\
        "against the harsh mountain climate.",\
        ({"bush","bushes"}),\
        "The low leafy bushes grow everywhere in the valley, carpeting " +\
        "the ground.",\
        "undergrowth",\
        "The undergrowth consists mostly of different kinds of moss."

#define MOUNTAIN_ITEMS ({"mountain","mountains","mountain range",\
        "Taman Busuk mountain range"}),\
        "The vast Taman Busuk mountain range stretches out " +\
        "like reaching fingers across the land. The immensity " +\
        "of the landscape is daunting.",\
        "peaks",\
        "The highest peaks of the mountain range reach well " +\
        "above the clouds.",\
        "clouds",\
        "A thin layer of clouds surround the highest peaks, making " +\
        "them difficult to see.",\
        "ground",\
        "@@ground_desc@@",\
        "snow",\
        "@@snow_desc@@"

#define ROAD1_ITEMS ({"road","mountain road","path"}),\
        "The road is little more than a cleared path " +\
        "through the mountains. It twists and turns, " +\
        "following the easiest route."

#define ROAD2_ITEMS ({"road","mountain road","path"}),\
        "The road is little more than a cleared path " +\
        "through the valley."

#define ROAD_LIGHT 3
#define VALLEY_LIGHT 1
#define MOUNTAIN_LIGHT 3

#define ROAD_FATIGUE        1
#define VALLEY_FATIGUE      5
#define MOUNTAIN_FATIGUE    20

#define ROAD_TYPE ({ ROOM_NORMAL, 0, ROAD_LIGHT, ROAD_FATIGUE })
#define VALLEY_TYPE ({ ROOM_NORMAL, 0, VALLEY_LIGHT, VALLEY_FATIGUE })
#define MOUNTAIN_TYPE ({ ROOM_NORMAL, 0, MOUNTAIN_LIGHT, MOUNTAIN_FATIGUE })

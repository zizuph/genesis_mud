/*
 * This is the general file for definitions in Helm's Deep
 *
 * This file should be updated, so the item descriptions
 * are put into an inheritable file.
 * Olorin, 7-Feb-1997
 */
 
#define TRACK_LOW 12
#define TRACK_HIGH 50

#define FOUND_ORC "_helmsdeep_found_orc_spy"
#define MADE_REPORT "_helmsdeep_made_report"
#define SHOWN_MAP "_helmsdeep_shown_map"
#define FOUND_TRACK "_helmsdeep_found_orc_track"
#define SCARED_ORC "_helmsdeep_orc_is_scared"

#define HIDE_OUT	(ROH_DIR + "horn/hide_out")
#define TOW_ROOM	(ROH_DIR + "horn/burg/tow_entr")
#define WALL_ROOM	(ROH_DIR + "horn/on_walls/o_wall7")
#define FOOTPRINT_ROOM	(ROH_DIR + "horn/gorge/n_path4")
#define COURTYARD_ROOM	(ROH_DIR + "horn/burg/outer_court1")

#define BRINK add_item("brink", "The edge of the Rock.\n")

#define CLIFFS add_item(({"cliff", "cliffs"}), BSN( \
        "The stony cliffs on either side of the gorge rise high and steep."))

#define COBBLESTONES add_item("cobblestones", \
	"These appear to be ordinary cobblestones.\n")

#define COOMB add_item("coomb", BSN( \
        "A green dale with grassy slopes lapping the ever-mounting hills. "+\
        "To the south and east rise sheer mountains, while to the "+\
        "north and west low hills spread out."))

#define COOMB_MOUNTAINS add_item(({ "mountain", "mountains" }), BSN( \
        "To the south are three jagged horns, the peaks of "+\
        "Thrihyrne, against the sky."))

#define COOMB_STREAM add_item(({ "stream", "deeping-stream" }), BSN( \
        "The Deeping-stream flows gently in a gully out towards the "+\
        "Westfold Vale."))

#define COURTYARD add_item("courtyard",BSN( \
        "The large open area between the walls is used as an exercise "+\
        "yard by the guards."))

#define DIKE add_item(({"dike", "helm's dike"}), BSN( \
        "The Dike extends across the mouth of the Deep in a half-circle. "+\
        "It is the outer fortification of the fortress."))

#define FIELD add_item(({ "field", "fields" }), \
        "The fields are covered by grass.\n")

#define GORGE add_item(({ "gorge", "Deep" }), BSN( \
        "The gorge winds into the mountains, under the shadow "+\
        "of the Thrihyrne, ever deeper and narrower."))

#define GRASS add_item("grass", \
        "The deep and springy grass looks fresh and green.\n")

#define GUARDS add_item(({"guards","guard"}), BSN(\
	"The guards cannot be seen clearly from here."));

#define GULLY add_item("gully", "The Deeping-stream flows here.\n")

#define H_WALL add_item(({"wall", "helm's wall"}), BSN( \
        "The wall stretches from the Hornburg to the southern "+ \
        "cliff, barring the entrance to the gorge. "+ \
        "The wall was made long ago by the sea-kings from Gondor."))

#define INNER_WALL add_item(({ "inner walls", "inner wall" }), BSN( \
        "The walls give an impression of ancient guardianship, "+\
        "a guardianship that never has failed. "))

#define KEEP add_item(({ "keep", "hornburg" }), BSN( \
        "The Hornburg has high walls with a lofty tower within. "+\
        "The fastness was built long ago by the sea-kings from Gondor."))

#define MOUNTAINS add_item("mountains", BSN( \
        "The gorge is starkly beautiful. Cliffs "+\
        "obstruct the view of the rest of the mountains."))

#define BOTH_WALLS add_item(({ "inner wall", "outer wall",\
	"inner walls", "outer walls" }),\
        BSN("The inner wall is somewhat higher than the outer one. "+\
        "The walls give an impression of ancient guardianship, "+\
        "a guardianship that never has failed."))

#define ON_WALL add_item( ({ "wall", "walls" }), BSN(\
	"The wall is about ten feet thick at "+\
        "the top. The top is sheltered by a parapet so high only the tallest "+\
        "can look over it. The great stones are set with great "+\
        "skill, making the wall almost impossible to break "+\
        "down with siege engines."))

#define PATH add_item("path", "It seems to be well used.\n")

#define PARAPET add_item(({"parapet","battlement"}), BS("Here and there "+\
        "are clefts in the battlement through which archers can shoot.\n"))

#define PEAKS add_item(({ "peaks", "horns", "thrihyrne" }), \
        "The peaks are snow-capped.\n")

#define ROAD add_item("road", "The road is paved with stone.\n")

#define ROCK add_item(({"rock", "spur", "heel"}), BSN( \
        "There is a heel of rock thrusting outward from the northern "+\
        "cliff. Upon its spur stands a keep."))

#define STAIRS add_item(({ "stairs", "stairway", "staircase", "steps" }), BSN( \
        "A narrow stairway made of stone. The steps are high and only "+\
        "a tall person can comfortably use them."))

#define STREAM add_item(({ "stream", "deeping-stream" }), BSN( \
        "The Deeping-stream flows gently in a gully out towards the Coomb."))

#define TOWER add_item("tower", BSN("The central tower of the "+\
        "keep was built by the sea-kings of Gondor in ages past. "+\
	"The tower is very tall, and its windows high and narrow."));

#define WALL add_item( ({ "wall", "walls" }), BSN(\
	"The stones are set with such skill "+\
        "that no footholds can be found."))

#define WALLTOWER add_item("tower", BSN( \
        "At the very end of the wall, a small round tower "+\
	"allows more archers to protect the most vulnerable part of "+\
        "the wall. "))

#define WINDOWS add_item(({ "window", "windows" }), BSN( \
        "The windows resemble arrow-slits more than anything else."))

/* Long desc for outer courtyard */
#define LONGDESC1 \
       "Walls rise high on either side, and "+\
       "a high tower can be seen inside the inner wall. "

/* Long desc for inner courtyard */
#define LONGDESC2 \
	"In the center of the courtyard rises a lofty tower. "

/* Long desc for outer wall */
#define LONG_DESC1 "The outer courtyard is below. "+\
	"In the center of the courtyard, the inner wall rises "+\
	"around a lofty tower. "

/* Long desc for inner wall */
#define LONG_DESC2 "Within the wall, the inner courtyard circles a "+\
	"lofty tower. "


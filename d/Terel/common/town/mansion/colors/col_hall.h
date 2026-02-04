#define ADD " The room is lighted by the fire burning in the tripod. " + \
	"Besides that, this room is quite featureless. The walls are quite " + \
	"dirty and dusty however, and many cobwebs are hanging down from " + \
	"the ceiling. The floor cracks and groans under your weight..."

add_item("tripod",break_string("This is a metal tripod, a sort of " +
	"basket-like thing standing on three legs and filled with " +
	"burning wood. The fire inside the tripod fills the room " +
	"with light. But you assume the tripod should also give " +
	"some light to the room immediately behind the window in front " +
	"of which the tripod stands.\n",70));
add_item("fire",break_string("There's nothing unusual about the fire, " +
	"which burns inside a sort of tripod. The fire gives light to " +
	"this room, but probably also to the room behind the window.\n",70));
add_item("window",break_string("The window with the tripod in front of it " +
	"is located so high on the wall that you can't examine it very well. " +
	"you notice however its unusual color and wonder how the room behind " +
	"it might look if the only light comes from the fire behind this " +
	"colored window...\n",70));
add_item("glass",break_string("You notice that this is not normal, but " +
	"stained glass. It probably lets through light, but it isn't " +
	"transparent enough to see what's behind because it consists of " +
	"round glas bricks surrounded by lead frames, as you often find it " +
	"on very old windows.\n",70));
add_item("cobwebs",break_string("The cobwebs hanging from the ceiling " +
	"let you shudder, mainly if they touch your neck... they look very " +
	"old, and you wonder if there are also some spiders " +
	"somewhere...\n",70));
add_item("ceiling",break_string("The ceiling is very dirty, but you can't " +
	"see any details on it from here, just that there are hanging " +
	"cobwebs from it.\n",70));
add_item("floor",break_string("The wooden floor cracks under your weight " +
	"and you suppose that nobody walked on them for centuries.\n",70));
add_item("walls",break_string("The walls are quite featureless, except for " +
	"all the dirt and dust covering it.\n",70));


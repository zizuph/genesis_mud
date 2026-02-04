#define ADD " You can't see where the hallways are leading to from here. " + \
	"The light in this room seems to come from " + \
	"them however, at least you can't make out any light " + \
	"source in this room. " + \
	"Besides that, this room is quite featureless. The walls are quite " + \
	"dirty and dusty however, and many cobwebs are hanging down from " + \
	"the ceiling. The floor cracks and groans under your weight..."

add_item("hallways",break_string("It's difficult to make out any details " + 
	"from here, as the hallways are very long and there's not much " +
	"light in them. Moreover, the light is very unregular, just as if " +
	"its origin would be a normal fire.\n",70));
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


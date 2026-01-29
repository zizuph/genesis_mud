// file name: d/Avenir/common/outpost/cave.h
// creator(s):  Kazz    Jan '95
// last update:
// purpose:     cavern items
// note:
// bug(s):
// to-do:  



#define CAVERN	\
        add_item(({"cavern"}), \
		 "The cavern is huge and extends into the darkness "+ \
		 "beyond the dark chasm.\n");
#define FORT \
	add_item(({"fort", "tall fort", "black fort", "tall black fort"}), \
		 "The fort is built into the cavern wall, and is only "+ \
		 "approachable by the path.\n");

#define TOWER \
	add_item(({"tower", "lone tower"}), \
		 "The black tower's two windows stare out over the "+ \
		 "cavern floor as if watching all movement.\n" );

#define WALL \
	add_item(({"wall", "curving wall"}), \
		 "The cavern wall eventually curves to form a ceiling "+ \
		 "higher than the flames can reveal.\n" );

#define FLAME \
	add_item(({"flame", "flames", "huge flames"}), \
            "The huge flames burn higher than a house, lighting much " +\
		 "of this cavern with a dancing, shadow-casting, light.\n" );

#define PATH \
	add_item(({"path"}), \
		 "The path leads between the flames, up to the fort gate.\n");

#define GATE \
	add_item(({"gate", "fort gate", "stone gate"}), \
		 "The black stone gate is closed. It seems to provide "+ \
		 "the only entrance into the fort.\n" );
#define FLOOR \
	add_item(({"floor"}), \
		 "Various shattered rocks, large and small, are scattered "+\
		 "on the cavern floor. Paths to the southeast and south "+\
		 "have been cleared.\n");
#define CHASM \
	add_item(({"chasm", "dark chasm"}), \
		 "The dark chasm to the south seems too wide to cross.\n");

#define ROCKS \
	add_item(({"rocks"}), \
		 "The rocks seem to have fallen from the hidden ceiling.\n");
	


#include "/d/Gondor/defs.h"

#define  CELLAR_DIR	(MORGUL_DIR + "cellar/")
#define  TOWER_DIR 	(MORGUL_DIR + "tower/")

#define FLOOR_ARRAY ({ \
    "The floor is made out of large dark stone slabs.", \
    "Large slabs of black stone make up the floor here.", \
    "The floor is covered by large black stone slabs.", \
    "The floor is made from large black cobblestones.", \
    })
#define FLOOR \
    add_item(({"floor", "ground"}), BSN(\
        ONE_OF_LIST(FLOOR_ARRAY) ));
#define CEILING_ARRAY ({ \
    "The vaulted ceiling is several feet above your head.", \
    "The vaulted ceiling is made from large black stone blocks.", \
    "The large black stone slabs of the ceiling are expertly " + \
        "hewn and finely polished.", \
    "Large blocks of black stone form the ceiling here. They " + \
        "have been put together without any mortar and they " + \
        "are held together only by their own weight.", \
    "The vaulted ceiling several feet above your head " + \
        "is made from large black stone blocks The stones " + \
        "fit together so closely that there are hardly any " + \
        "visible joints.", \
    })
#define CEILING \
    add_item(({"ceiling", "roof"}), BSN(\
        ONE_OF_LIST(CEILING_ARRAY) ));
#define WALL_ARRAY ({ \
    "The walls are made from large black stone blocks.", \
    "The large stone blocks which make up the walls are smoothly " +\
        "hewn and polished.", \
    "The walls are made of large stone blocks which fit together " +\
        "so well that there are hardly any joints visible between " +\
        "them.", \
    "Large stone blocks hewn from black rock, fitted together so " +\
        "expertly that there are hardly any joints visible.", \
    })
#define WALLS \
    add_item(({"wall", "walls"}), BSN(\
        ONE_OF_LIST(WALL_ARRAY) ));
#define STONE_ARRAY ({ \
    "The stone blocks that make up the walls and the ceiling have " +\
        "been hewn from black rock.", \
    "Great blocks hewn from black rock make up the walls and the " +\
        "ceiling here. They have been fitted together so smoothly " +\
        "that there are hardly any joints visible between them.", \
    "The walls and the ceiling are made from large black stone blocks " +\
        "that have been fitted together so expertly that there are " +\
        "hardly any joints visible between them.", \
    })
#define STONES \
    add_item(({"stones", "stone blocks", "joints"}), BSN(\
        ONE_OF_LIST(STONE_ARRAY) ));
#define PASSAGE(dir) \
    add_item(({"passage", "dark passage", "tunnel"}), BSN(\
        "A dark tunnel is going of to the " + dir + ". All one can see " +\
        "of it is a dark gaping hole."));
#define C_PASSAGE(dir) \
    add_item(({"passage", "dark passage", "tunnel"}), BSN(\
        "The dark tunnel is continuing to the " + dir + ". One cannot " \
      + "see more than a few feet in that direction, impenetrable " \
      + "darknees seems to fill the passage like a black cloud."));
#define C_PASSAGES(dir1, dir2) \
    add_item(({"passages", "dark passages", "tunnel"}), BSN(\
        "The dark tunnel runs from "+dir1+" to "+dir2+". In neither " \
      + "direction can one see more than a few feet, impenetrable " \
      + "darknees seems to fill the passages like a black cloud."));
#define ARCHWAY(dir) \
    add_item(({"arch", "archway", "opening", "door"}), BSN(\
        "An archway opens in the wall to the the "+dir+". Through the " + \
        "opening falls some light, and you wonder what you will find if " + \
        "you pass under the arch."));
#define ARCHWAYS(dir1, dir2) \
    add_item(({"arches", "archways", "openings", "doors"}), BSN(\
        "Two arches open in the walls here. One is leading to the " + \
        dir1 + ", the other to the " + dir2 + ". Through the openings " + \
        "falls some light, and you wonder what you will find if you " + \
        "go through the archways."));\
    add_item(({"arch", "archway", "door", "opening"}), BSN(\
        "Which archway do you mean, the one to the " + dir1 + " or the " + \
        "one to the " + dir2 + "?"));\
    add_item(({dir1+"ern arch", dir1+"ern archway", dir1+"ern door", \
               dir1+" arch", dir1+" archway", dir1+" door"}), BSN(\
        "An opening in the wall leading to the " + dir1 + ". Faint " +\
        "light is falling through it, but you cannot make out what " +\
        "fate is awaiting you beyond the archway.")); \
    add_item(({dir2+"ern arch", dir2+"ern archway", dir2+"ern door", \
               dir2+" arch", dir2+" archway", dir2+" door"}), BSN(\
        "An opening in the wall leading to the " + dir2 + ". Faint " +\
        "light is falling through it, but you cannot make out what " +\
        "fate is awaiting you beyond the archway."));
#define D_ARCHWAY \
    add_item(({"arch", "archway", "opening", "hole", }), BSN( \
        "You can see the top of a flight of stairs leading down inside " \
      + "the dark archway.")); \
    add_item(({"stairs", "flight of stairs", }), BSN( \
        "The flight of stairs inside the dark archway is leading down " \
      + "towards an even lower level of these dungeons beneath Minas " \
      + "Morgul. The stone steps look worn down from centuries of " \
      + "frequent use."));
#define U_ARCHWAY \
    add_item(({"arch", "archway", "opening", "hole", }), BSN( \
        "You can see the bottom of a flight of stairs leading up " \
      + "inside the dark archway.")); \
    add_item(({"stairs", "flight of stairs", }), BSN( \
        "The flight of stairs inside the dark archway is leading up " \
      + "towards a higher level of these dungeons beneath Minas " \
      + "Morgul. The stone steps look worn down from centuries of " \
      + "frequent use."));
    


/*
 *   Properties added to players or which may be used outside the central area
 *   begin with "_calia".
 */

#define CALIA_DETECTED            "_calia_detected"
#define CALIA_KNOCKDOWN           "_calia_knockdown"
#define CALIA_COMBAT_INVENTORY    "_calia_combat_inventory"

#define CENTRAL                   "/d/Calia/central/"

#define AREA         implode(explode(file_name(this_object()),"/")[0..5],"/")

#define BELOW        AREA + "/below/"
#define GROUND       AREA + "/ground/"
#define LOW          AREA + "/low/"
#define MIDDLE       AREA + "/middle/"
#define UPPER        AREA + "/upper/"

/*
 *   The following directories contain files that may be used in any of the
 *   central sub-areas.  If you are working in central Calia and make an object
 *   that would be suitable for widespread use, please put it in one of these
 *   shared directories.  Particularly important files may be listed here after
 *   the directories.
 */

#define CENTRAL_ANIMALS           CENTRAL + "animals/"
#define CENTRAL_NPCS              CENTRAL + "npcs/"
#define CENTRAL_OBJECTS           CENTRAL + "objects/"
#define CENTRAL_WEAPONS           CENTRAL + "weapons/"
#define CENTRAL_ARMOURS           CENTRAL + "armours/"
#define CENTRAL_SPECIALS          CENTRAL + "specials/"

#define GROUND_COMBAT_OBJECT      CENTRAL_SPECIALS + "ground_combat"
#define DRUDGE                    CENTRAL_SPECIALS + "drudge"

/*
 *   End of general-purpose directories and objects.
 */

#define FOREST                    CENTRAL + "forest/"
#define FOREST_EAST               FOREST + "east/"         /* rooms */
#define FOREST_NORTH              FOREST + "north/"        /* rooms */
#define FOREST_NORTHEAST          FOREST + "northeast/"    /* rooms */
#define FOREST_NORTHWEST          FOREST + "northwest/"    /* rooms */
#define FOREST_SOUTH              FOREST + "south/"        /* rooms */
#define FOREST_SOUTHEAST          FOREST + "southeast/"    /* rooms */
#define FOREST_SOUTHWEST          FOREST + "southwest/"    /* rooms */
#define FOREST_WEST               FOREST + "west/"         /* rooms */
#define FOREST_NPCS               FOREST + "npcs/"
#define FOREST_ANIMALS            FOREST + "animals/"
#define FOREST_OBJECTS            FOREST + "objects/"
#define FOREST_ARMOURS            FOREST + "armours/"
#define FOREST_WEAPONS            FOREST + "weapons/"
#define FOREST_SPECIALS           FOREST + "specials/"

#define BOG                       CENTRAL + "bog/"
#define BOG_ANIMALS               BOG + "animals/"
#define BOG_NPCS                  BOG + "npcs/"
#define BOG_OBJECTS               BOG + "objects/"
#define BOG_ARMOURS               BOG + "armours/"
#define BOG_WEAPONS               BOG + "weapons/"
#define BOG_INNER                 BOG + "inner/"        /* rooms */
#define BOG_OUTER                 BOG + "outer/"        /* rooms */
#define BOG_SPECIALS              BOG + "specials/"

#define FROGGY                    CENTRAL + "froggy/"
#define FROGGY_ANIMALS            FROGGY + "animals/"
#define FROGGY_NPCS               FROGGY + "npcs/"
#define FROGGY_OBJECTS            FROGGY + "objects/"
#define FROGGY_ARMOURS            FROGGY + "armours/"
#define FROGGY_WEAPONS            FROGGY + "weapons/"
#define FROGGY_ROOMS              FROGGY + "rooms/"
#define FROGGY_SPECIALS           FROGGY + "specials/"

#define GLADE                     CENTRAL + "glade/"
#define GLADE_ANIMALS             GLADE + "animals/"
#define GLADE_NPCS                GLADE + "npcs/"
#define GLADE_OBJECTS             GLADE + "objects/"
#define GLADE_ARMOURS             GLADE + "armours/"
#define GLADE_WEAPONS             GLADE + "weapons/"
#define GLADE_ROOMS               GLADE + "rooms/"
#define GLADE_SPECIALS            GLADE + "specials/"

#define RUST                      CENTRAL + "rust/"
#define RUST_ANIMALS              RUST + "animals/"
#define RUST_NPCS                 RUST + "npcs/"
#define RUST_OBJECTS              RUST + "objects/"
#define RUST_ARMOURS              RUST + "armours/"
#define RUST_WEAPONS              RUST + "weapons/"
#define RUST_VILLAGE              RUST + "village/"
#define RUST_KEEP                 RUST + "keep/"
#define RUST_SPECIALS             RUST + "specials/"

#define TOAD_IN_OAK               CENTRAL + "toad_in_oak/"
#define TOAD_IN_OAK_ANIMALS       TOAD_IN_OAK + "animals/"
#define TOAD_IN_OAK_NPCS          TOAD_IN_OAK + "npcs/"
#define TOAD_IN_OAK_OBJECTS       TOAD_IN_OAK + "objects/"
#define TOAD_IN_OAK_ARMOURS       TOAD_IN_OAK + "armours/"
#define TOAD_IN_OAK_WEAPONS       TOAD_IN_OAK + "weapons/"
#define TOAD_IN_OAK_ROOMS         TOAD_IN_OAK + "rooms/"
#define TOAD_IN_OAK_SPECIALS      TOAD_IN_OAK + "specials/"

/*
 * Some standard definitions for the rooms in the swamp:
 */

#define SWAMP_NAT_SHORT "In the Black Bog Swamp"
#define SWAMP_FOR_SHORT "In a swamp"

#define SWAMP_BRINK_NAT_LONG \
  "You are standing at the brink of the enormous Black Bog Swamp. "+\
  "Black mud and putrescent "+\
  "green-slimy water glitters in the sunlight "+\
  "between tufts of sickly, pale yellow grass, and a miasma of decay boils "+\
  "from the ground.\n"
#define SWAMP_BRINK_FOR_LONG \
  "You are standing at the brink of the enormous swamp. "+\
  "Black mud and putrescent "+\
  "green-slimy water glitters in the sunlight "+\
  "between tufts of sickly, pale yellow grass, and a miasma of decay boils "+\
  "from the ground.\n"


/*
 * Room items:
 */

#define WATER_ITEM ({"water", "swamp water", "green-slimy water", "ruts", "rut"})
#define WATER_DESC \
  "The water is filled with tendrils of green slime, and it carries a not "+\
  "so faint odor akin to rotten eggs.\n"

#define GRASS_ITEM ({"grass", "yellow grass", "sickly grass"})
#define GRASS_DESC \
  "The grass is looks dried and dying in spite of the wettness around, "+\
  "and its blades are sharp and brittle.\n"

#define SLIME_ITEM ({"slime", "slimes", "green slime"})
#define SLIME_DESC \
  "The slime is an unhealthy green color, and it seems to move "+\
  "slowly by itself, "+\
  "without any current to carry it.\n"

#define SUNLIGHT_ITEM ({"sunlight"})
#define SUNLIGHT_DESC \
  "The light from above is filtered to a grey-metal "+\
  "diffuse ambience by the vapours rising above the swamp.\n"

#define MUD_ITEM ({"mud", "wet mud"})
#define MUD_DESC \
  "It is black and watery, and now and then a bubble of gas boils up "+\
  "from below, bursting with a wet sound.\n"

#define SWAMP_STD_ITEMS \
  add_item( GRASS_ITEM, WRAP( GRASS_DESC));   \
  add_item( SLIME_ITEM, WRAP( SLIME_DESC));   \
  add_item(SUNLIGHT_ITEM, WRAP(SUNLIGHT_DESC));   \
  add_item(   MUD_ITEM, WRAP(   MUD_DESC));   \
  add_item( WATER_ITEM, WRAP( WATER_DESC))

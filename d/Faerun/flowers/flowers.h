/*
 * Local defines for flowers
 * Created by Finwe, February 2005
 *
 */


#define FLOWERS_DIR     "/d/Faerun/flowers/"
#define BASE_FLOWER     (FLOWERS_DIR + "flower_base.c")

#define IS_ARE      ((num_heap() == 1) ? " is " : "s are ")
#define IT_THEY     ((num_heap() == 1) ? " it is " : " they are ")
#define CIT_THEY    ((num_heap() == 1) ? " It is " : " They are ")
#define PLURAL      ((num_heap() == 1) ? " of " : "es of ")
#define PROP_BASE   "_faerun_flower_"

// Flowers
#define COLUMBINE           "columbine"
#define CONEFLOWER          "coneflower"
#define COREOPSIS           "coreopsis"
#define FREESIA_LAVENDER    "freesia_lavender"
#define FREESIA_PINK        "freesia_pink"
#define FREESIA_WHITE       "freesia_white"
#define FREESIA_YELLOW      "freesia_yellow"
#define HEATHER_LAVENDER    "heather_lavender"
#define HEATHER_WHITE       "heather_white"
#define MILKWEED            "milkweed"
#define ROSE_RED_BUD        "rose_red_bud"
#define STAR                "star"
#define WILD_ROSE_LAVENDER  "rose_wild_lavender"
#define WILD_ROSE_PINK      "rose_wild_pink"
#define WILD_ROSE_RED       "rose_wild_red"
#define WILD_ROSE_WHITE     "rose_wild_white"

#define WILD_ROSES (({WILD_ROSE_LAVENDAR, WILD_ROSE_PINK, WILD_ROSE_RED, WILD_ROSE_WHITE, }))

#define WILDFLOWERS (({COLUMBINE, CONEFLOWER, COREOPSIS, FREESIA_PINK, FREESIA_LAVENDER, FREESIA_WHITE, FREESIA_YELLOW, HEATHER_LAVENDER, HEATHER_WHITE, MILKWEED, STAR,}))

#define GARDEN_FLOWERS (({COLUMBINE, FREESIA_LAVENDER, FREESIA_PINK, FREESIA_WHITE, FREESIA_YELLOW,}))

#define FARM1_FLOWERS (({COLUMBINE, FREESIA_LAVENDER, FREESIA_PINK, FREESIA_WHITE, FREESIA_YELLOW, STAR, }))

#define MAX_FLOWERS     5


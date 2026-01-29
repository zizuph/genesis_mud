#include "../defs.h"

#define ISLAND_DIR KARG_DIR+"island/"

#define ISLAND_ROOMS ISLAND_DIR+"rooms/"
#define ISLAND_FOREST ISLAND_ROOMS+"forest/"
#define ISLAND_SHORE ISLAND_ROOMS+"shore/"
#define ISLAND_STRHOLD ISLAND_ROOMS+"stronghold/"
#define ISLAND_ITEM ISLAND_DIR+"item/"
#define ISLAND_LIV ISLAND_DIR+"living/"
#define ISLAND_STD ISLAND_DIR+"std/"
#define ISLAND_ARM ISLAND_DIR+"arm/"
#define ISLAND_WEP ISLAND_DIR+"wep/"
#define ISLAND_TXT ISLAND_DIR+"txt/"

#define HAS_PATH_HINT "_has_path_hint"
#define HAS_TREE_HINT "_has_tree_hint"

#define STR(l) l->query_stat(0)
#define DEX(l) l->query_stat(1)
#define CON(l) l->query_stat(2)
#define INT(l) l->query_stat(3)
#define WIS(l) l->query_stat(4)
#define DIS(l) l->query_stat(5)


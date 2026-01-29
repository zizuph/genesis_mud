#include "/d/Roke/common/qbits.h"

#define THIS_DIR	"/d/Roke/varl/atuan/cape/guild/"

#define GUILD_NAME      "Traveller guild"
#define GUILD_TYPE      "race"
#define GUILD_STYLE     "wanderer"
#define GUILD_SHADOW    THIS_DIR + "trav_shadow"
#define TRAV_SOUL       THIS_DIR + "trav_soul"
#define TRAV_INSIGNIA   THIS_DIR + "insignia"
#define TAX     1
#define IS_MEMBER(ob)   (ob->test_bit("Roke",TRAV_GROUP,TRAV_MEMBER))	

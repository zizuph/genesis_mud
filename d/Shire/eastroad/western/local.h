//   Local defines for the Great East Road west of Bree

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

//  Undefine ER_DIR because it's in /d/Shire/common/defs.h and we
//  don't want to use that one ;)
#define EAST_R_BASE "/d/Shire/eastroad/"
#define EAST_R_DIR  EAST_R_BASE + "western/"
#ifdef VILLAGE_DIR
#undef VILLAGE_DIR
#define VILLAGE_DIR "/d/Shire/eastroad/western/villages/"
#endif


#define B_DOWNS_DIR "/d/Shire/common/downs/"
#define BUCK_L_DIR "/d/Shire/buckland/"
#define ER_NPC "/d/Shire/eastroad/npc/"
#define ER_OBJ "/d/Shire/eastroad/obj/"
#define EVEN_DIM_DIR "/d/Shire/evendim/"
#define GIRDLEY_DIR "/d/Shire/eastroad/girdley/"
#define GREY_H_DIR "/d/Shire/common/greyhaven/"
#define HOBTON_DIR "/d/Shire/common/hobbiton/"
#define MD_DIR "/d/Shire/michel/"
#define ROCK_DIR "/d/Shire/common/obj/"

#define ANIMALMAKER "/d/Shire/eastroad/animalmaker"
#define BASE_COMMON "/d/Shire/eastroad/western/base_common.c"
#define EAST_ROAD "/d/Shire/eastroad/std/er_base.c"
#define H_MAKER "/d/Shire/hobbitmaker/hobbitmaker.h"
#define MILK_QUEST "/d/Shire/eastroad/milk_quest.c"
#define SANIMALMAKER "/d/Shire/eastroad/sanimalmaker"
#define VILLAGE   "/d/Shire/eastroad/std/vill_base.c"


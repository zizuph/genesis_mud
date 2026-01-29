#ifndef DROW_DEFINITIONS
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "/sys/filter_funs.h"
#include <std.h>
#include <const.h>
#include <wa_types.h>

#define DGUILD "/d/Kalad/common/wild/pass/guild/"
#define PASS "/d/Kalad/common/wild/pass/"
#define DROW_DEFINITIONS
#define GUILD_NAME      "Drow Academy"
#define GUILD_SHADOW    DGUILD + "drow_shadow"
#define DROW_SOUL       DGUILD + "drow_soul"
#define TAX 1
#define GUILD_TYPE   "lay" && "occ"
#define TP this_player()
#define IS_MEMBER TP->query_bit("Kalad",FOURTH_GROUP,DROW_GUILD_BIT)
#define GUILD_STYLE "layman"
#endif

/*
 *  Defs.h file for Thanar guild.
 */

#include "/d/Kalad/defs.h"

#ifndef THANAR_DEFS
#define THANAR_DEFS

#define THANAR(obj)    "/d/Kalad/common/guilds/thanar/obj"
#define OLDTHANAR(obj) "/d/Kalad/common/caravan/thanar/obj"

#define TAX            2
#define GUILD_NAME     "Thanarian human race guild"
#define GUILD_TYPE     "race"
#define GUILD_STYLE    "race"
#define GUILD_SHADOW   "/d/Kalad/common/guilds/thanar/thanar_shadow"
#define THANAR_SOUL    "/d/Kalad/common/guilds/thanar/thanar_soul"
#define IS_MEMBER(ob)  (ob->test_bit("Kalad", 4, 4))
#define SOULDESC(s)    (this_player()->add_prop(LIVE_S_SOULEXTRA, (s)))

#endif


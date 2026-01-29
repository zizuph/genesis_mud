#include <stdproperties.h>

#define THANAR(obj) "/d/Kalad/common/guilds/thanar/new/obj"
#define PRIVATE_BOARD THANAR(log/thanar_private)

#define GUILD_NAME "Thanarian human race guild"
#define GUILD_TYPE "race"
#define GUILD_STYLE "race"
#define TAX 2

#define GUILD_SHADOW THANAR(thanar_shadow)
#define THANAR_SOUL THANAR(thanar_soul)

#define IS_MEMBER(ob) (ob->test_bit("Kalad",4,4))
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

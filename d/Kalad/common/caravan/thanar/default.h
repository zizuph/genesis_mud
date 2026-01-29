#define GUILD_NAME "Thanarian human race guild"
#define GUILD_TYPE "race"
#define GUILD_STYLE "race"
#define GUILD_SHADOW "/d/Kalad/common/caravan/thanar/thanar_shadow"
#define THANAR_SOUL "/d/Kalad/common/caravan/thanar/thanar_soul"
#define IS_MEMBER(ob) (ob->test_bit("Kalad",4,4))
#define TAX 2
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

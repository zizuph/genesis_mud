#define GUILD_NAME "Duergar race guild"
#define GUILD_TYPE "race"
#define GUILD_STYLE "race"
#define DUERGAR_SHADOW "/d/Kalad/common/guilds/duergar_shadow"
#define DUERGAR_SOUL "/d/Kalad/common/guilds/duergar_soul"
#define IS_MEMBER(ob) (ob->test_bit("Kalad",4,6))
#define TAX 2
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

#define GUILD_NAME "Riders of the Dark Alliance"
#define GUILD_TYPE "layman"
#define GUILD_STYLE "fighter"
#define RIDER_SHADOW "/d/Kalad/common/guilds/riders/rider_shadow"
#define RIDER_SOUL "/d/Kalad/common/guilds/riders/rider_soul"
#define TAX 6
#define TAX_NON_RACE 8
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))
#define IS_MEMBER(xxx)  (xxx->query_guild_name_lay() == GUILD_NAME)

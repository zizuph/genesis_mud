#define GUILD_NAME "Riders of the Red Fang"
#define GUILD_TYPE "layman"
#define GUILD_STYLE "fighter"
#define RIDER_SHADOW "/d/Kalad/common/wild/pass/goblin/guild/riders/rider_shadow"
#define RIDER_SOUL "/d/Kalad/common/wild/pass/goblin/guild/riders/rider_soul"
#define TAX 7
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))
#define IS_MEMBER(xxx)  (xxx->query_guild_name_lay == GIULD_NAME)
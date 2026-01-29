#define GUILD_NAME "Riders of the Red Fang"
#define GUILD_TYPE "lay"
#define GUILD_STYLE "lay"
#define RIDER_SHADOW "/d/Kalad/common/wild/pass/goblin/guild/riders/rider_shadow"
#define RIDER_SOUL "/d/Kalad/common/wild/pass/goblin/guild/riders/rider_soul"
#define IS_MEMBER(ob) (ob->test_bit("Kalad",4,8))
#define TAX 2
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

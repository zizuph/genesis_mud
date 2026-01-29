#define GUILD_NAME "Drow race guild"
#define GUILD_TYPE "race"
#define GUILD_STYLE "race"
#define DROW_SHADOW "/d/Kalad/common/wild/pass/drow/guild/drow_shadow"
#define DROW_SOUL "/d/Kalad/common/wild/pass/drow/guild/drow_soul"
#define IS_MEMBER(ob) (ob->test_bit("Kalad",4,5))
#define TAX 3
#define SOULDESC(s) (TP->add_prop(LIVE_S_SOULEXTRA, (s)))

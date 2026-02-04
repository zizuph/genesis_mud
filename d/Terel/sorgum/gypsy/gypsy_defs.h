#define GUILD_NAME     "Gypsies"
#define GUILD_TYPE     "occupational"
#define GUILD_STYLE    "cleric"

#define GUILD_TAX      30
#define GUILD_DIR      "/d/Terel/sorgum/gypsy/"
#define GUILD_SHADOW   (GUILD_DIR + "gypsy_shadow")
#define GUILD_SOUL     (GUILD_DIR + "gypsy_soul")

#define GUILD_HELP     (GUILD_DIR + "help")

#define GYPSY_ILLEGAL_RACE ({"elf"})

#define MEMBER(xx)  ((xx)->query_guild_member(GUILD_NAME))

#define BANISHED      (GUILD_DIR + "banished")

/* Gypsy skills */
#define GYPSY_RANK 130600
#define GYPSY_LORE 130601


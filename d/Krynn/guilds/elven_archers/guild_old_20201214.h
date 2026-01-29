/* Guild.h */

#define GUILD_NAME                      "Ansalon Elvish Archers"
#define GUILD_STYLE                     "ranger"
#define GUILD_TAX_OCC                   29
#define GUILD_TAX_LAY                   12

#define GUILD_DIR                       "/d/Krynn/guilds/elven_archers/"
#define GUILD_OBJ                       (GUILD_DIR + "obj/")
#define GUILD_GURU                      (GUILD_DIR + "guru/")
#define GUILD_LOG                       (GUILD_DIR + "log/")
#define GUILD_LIB                       (GUILD_DIR + "lib/")
#define SPECIALS                        (GUILD_DIR + "specials/")
#define HELP_DIR                        (GUILD_DIR + "help/")
#define ROOMS                           (GUILD_DIR + "rooms/")

#define OPTIONS_MANAGER                 (GUILD_LIB + "options_manager")
#define GUILD_CMDSOUL                   (GUILD_LIB + "archer_soul")
#define LAY_SHADOW                      (GUILD_LIB + "lay_shadow")
#define OCC_SHADOW                      (GUILD_LIB + "occ_shadow")

#define TRAINER                         (GUILD_DIR + "trainer")

/* Guru Quest */

#define GROUP                           3
#define Q_BIT                           19
#define GURU_SH                         (GUILD_GURU + "guru_sh")
#define GURU_DRYAD                      (GUILD_GURU + "dryad")
#define GURU_SEEDLING                   (GUILD_GURU + "seedling")
#define DRYAD_BOW                       (GUILD_GURU + "dryad_bow")
#define DRYAD_ARROW                     (GUILD_GURU + "dryad_arrow")
#define DRUID_RITUAL                    (GUILD_GURU + "druid_ritual")
#define HASTE_OBJECT                    (GUILD_GURU + "loremaster_haste")
/* Specials */
#define QUICKSHOT                       (SPECIALS  + "quickshot")
#define SNIPE                           (SPECIALS  + "snipe")
#define DISTANCE_EVADE                  (SPECIALS  + "distance_evade_obj")
#define HUNTERS_MARK                    (SPECIALS  + "hunters_mark")

#define F_AIMSHOT                       "snipe"
#define F_QUICKSHOT                     "quickshot"
/* End of Specials */

#define GUILD_EMBLEM                    (GUILD_DIR + "emblem")

#define JOINROOM                        (ROOMS + "joinroom")
#define START_ROOM                      (ROOMS + "hut_entrance")
#define ROAD_ROOM                       "/d/Krynn/qualinesti/forest/forest25"
#define SS_GUILD_EVASION                108500
#define GUILD_SKILLS                    ({ SS_GUILD_EVASION })

/* The elves always see in the dark, albeit less than perfect, so we want to
 * see if the area is originally dark.
 */
#define VISION_IMPAIRED(ob)                                                    \
        !(CAN_SEE_IN_ROOM(ob) && (max(environment(ob)->query_prop(OBJ_I_LIGHT),\
        ((ob)->query_prop(LIVE_I_SEE_DARK) - 1)) > 0))
                       
// Accordingly to sman set_board_name no / in the end of board 
#define BOARD                           (GUILD_LOG + "board")


#define ARCH_DEBUG(x)        find_player("arman")->catch_msg(x)

/* A unique id for the guild's emblem */
#define GUILD_EMBLEM_ID                 (GUILD_NAME + " emblem")

#define OBJ_O_BELONGS_TO_ARCHER         "_obj_o_belongs_to_archer"

#define ARCHER_MTITLES    ({ "Apprentice Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Noble Elven Archer", \
                             "Noble Elven Archer", \
                             "Expert Marksman of the Elves", \
                             "Expert Marksman of the Elves", \
                             "Expert Marksman of the Elves", \
                             "Huntmaster of the Elves", \
                             "Huntmaster of the Elves", \
                             "Highborn Bowmaster of the Elven Nations"})

#define ARCHER_FTITLES    ({ "Apprentice Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Elven Archer", \
                             "Noble Elven Archer", \
                             "Noble Elven Archer", \
                             "Expert Markswoman of the Elves", \
                             "Expert Markswoman of the Elves", \
                             "Expert Markswoman of the Elves", \
                             "Huntmistress of the Elves", \
                             "Huntmistress of the Elves", \
                             "Highborn Bowmistess of the Elven Nations"})

#define ARCHER_EMTITLES   ({ "Apprentice Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Nightstalker", \
                             "Dark Elven Nightstalker", \
                             "Haughty Dark Elven Marksman", \
                             "Haughty Dark Elven Marksman", \
                             "Haughty Dark Elven Marksman", \
                             "Fallen Huntmaster of the Dark Elves", \
                             "Fallen Huntmaster of the Dark Elves", \
                             "Outcast Bowmaster of the Elven Nations"})

#define ARCHER_EFTITLES   ({ "Apprentice Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Nightstalker", \
                             "Dark Elven Nightstalker", \
                             "Haughty Dark Elven Markswoman", \
                             "Haughty Dark Elven Markswoman", \
                             "Haughty Dark Elven Markswoman", \
                             "Fallen Huntmistress of the Dark Elves", \
                             "Fallen Huntmistress of the Dark Elves", \
                             "Outcast Bowmistress of the Elven Nations"})

#define ARCHER_QUAL_MTITLES   ({ "Apprentice Wildrunner of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Noble Elven Archer of the Qualinesti Elves", \
                             "Noble Elven Archer of the Qualinesti Elves", \
                             "Expert Marksman of the Qualinesti Elves", \
                             "Expert Marksman of the Qualinesti Elves", \
                             "Expert Marksman of the Qualinesti Elves", \
                             "Huntmaster of the Qualinesti Elves", \
                             "Huntmaster of the Qualinesti Elves", \
                             "Highborn Bowmaster of the Qualinesti Elves"})

#define ARCHER_QUAL_FTITLES   ({ "Apprentice Wildrunner of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Elven Archer of the Qualinesti Elves", \
                             "Noble Elven Archer of the Qualinesti Elves", \
                             "Noble Elven Archer of the Qualinesti Elves", \
                             "Expert Markswoman of the Qualinesti Elves", \
                             "Expert Markswoman of the Qualinesti Elves", \
                             "Expert Markswoman of the Qualinesti Elves", \
                             "Huntmistress of the Qualinesti Elves", \
                             "Huntmistress of the Qualinesti Elves", \
                             "Highborn Bowmistress of the Qualinesti Elves"})

#define ARCHER_SILV_MTITLES   ({ "Apprentice Wildrunner of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Noble Elven Archer of House Protector", \
                             "Noble Elven Archer of House Protector", \
                             "Elite Marksman of the Silvanesti Elves", \
                             "Elite Marksman of the Silvanesti Elves", \
                             "Elite Marksman of the Silvanesti Elves", \
                             "Huntmaster of the Silvanesti Elves", \
                             "Huntmaster of the Silvanesti Elves", \
                             "Highborn Bowmaster of the Silvanesti Elves"})

#define ARCHER_SILV_FTITLES   ({ "Apprentice Wildrunner of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Elven Archer of House Protector", \
                             "Noble Elven Archer of House Protector", \
                             "Noble Elven Archer of House Protector", \
                             "Elite Markswoman of the Silvanesti Elves", \
                             "Elite Markswoman of the Silvanesti Elves", \
                             "Elite Markswoman of the Silvanesti Elves", \
                             "Huntmistress of the Silvanesti Elves", \
                             "Huntmistress of the Silvanesti Elves", \
                             "Highborn Bowmistress of the Silvanesti Elves"})

#define ARCHER_KAG_MTITLES   ({ "Apprentice Wildrunner of the Kagonesti Elves", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Clan Archer of the Kagonesti Elves", \
                             "Clan Archer of the Kagonesti Elves", \
                             "Expert Marksman of the Kagonesti Elves", \
                             "Expert Marksman of the Kagonesti Elves", \
                             "Expert Marksman of the Kagonesti Elves", \
                             "Huntmaster of the Kagonesti Elves", \
                             "Huntmaster of the Kagonesti Elves", \
                             "Elder Bowmaster of the Kagonesti Elves"})

#define ARCHER_KAG_FTITLES   ({ "Apprentice Wildrunner of the Kagonesti Elves", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Wild Elf Archer of the Kagonesti Clans", \
                             "Clan Archer of the Kagonesti Elves", \
                             "Clan Archer of the Kagonesti Elves", \
                             "Expert Markswoman of the Kagonesti Elves", \
                             "Expert Markswoman of the Kagonesti Elves", \
                             "Expert Markswoman of the Kagonesti Elves", \
                             "Huntmistress of the Kagonesti Elves", \
                             "Huntmistress of the Kagonesti Elves", \
                             "Elder Bowmistress of the Kagonesti Elves"})

#define ARCHER_DROW_MTITLES   ({ "Apprentice Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Nightstalker", \
                             "Dark Elven Nightstalker", \
                             "Haughty Dark Elven Marksman", \
                             "Haughty Dark Elven Marksman", \
                             "Haughty Dark Elven Marksman", \
                             "Underdark Huntmaster of the Dark Elves", \
                             "Underdark Huntmaster of the Dark Elves", \
                             "House Bowmaster of the Dark Elves"})

#define ARCHER_DROW_FTITLES   ({ "Apprentice Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Archer", \
                             "Dark Elven Nightstalker", \
                             "Dark Elven Nightstalker", \
                             "Haughty Dark Elven Markswoman", \
                             "Haughty Dark Elven Markswoman", \
                             "Haughty Dark Elven Markswoman", \
                             "Underdark Huntmistress of the Dark Elves", \
                             "Underdark Huntmistress of the Dark Elves", \
                             "House Bowmistress of the Dark Elves"})

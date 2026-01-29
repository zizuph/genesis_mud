/*  /d/Faerun/guilds/half_orcs/guild.h
 *
 *  Guildheader for the Half-orcs of Faerun
 *
 *  Nerull 2022.
 *
 */

/* directory paths */
#define HO_GUILD_DIR           "/d/Faerun/guilds/half_orcs/"

#define HO_DOC_DIR             (HO_GUILD_DIR + "doc/")
#define HO_LOG_DIR             (HO_GUILD_DIR + "log/")
#define HO_MASTER_DIR          (HO_GUILD_DIR + "master/")
#define HO_NPC_DIR             (HO_GUILD_DIR + "npc/")
#define HO_OBJ_DIR             (HO_GUILD_DIR + "obj/")
#define HO_ROOMS_DIR           (HO_GUILD_DIR + "rooms/")
#define HO_SHADOWS_DIR         (HO_GUILD_DIR + "shadows/")
#define HO_SOULS_DIR           (HO_GUILD_DIR + "souls/")

#define HO_SAVE_FILE           (HO_MASTER_DIR +"log/ho_save")



// Mappings
#define HO_TUSKS               (HO_MASTER_DIR +"log/ho_tusks")

// Standard stat weighting for spells based on magic guild class
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })




//////////////////////////////////////////////////////////////////////////////////////
// LAY Guildname, type & tax --- ---------------
// RACIAL Guildname, type & tax --- ---------------
#define RACE_HO_GUILD_NAME     "Half-orcs of Faerun"
#define TYPE_RACE              "race"
#define TAX_RACE               2
#define IS_HO_RACIAL_MEMBER(p) ((p)->query_guild_name_race() == RACE_HO_GUILD_NAME)


// Some general defines
#define BSN(x)                         ((x) + "\n")
#define LOW(x)                         lower_case(x)
#define OBJ(obj)                       obj->query_objective()
#define QSW                           query_shadow_who()
#define PRO(obj)             obj->query_pronoun()                            
#define SW                   shadow_who
#define POSS(obj)            obj->query_possessive()
#define WATCHERS(obj)        (filter(filter(all_inventory(environment((obj))), \
                             &->can_see_in_room()), &(obj)->check_seen()) \
                             - ({ (obj) }))

#define IS_WIZ(x) (interactive(x) && \
    SECURITY->query_wiz_rank(x->query_real_name()))
    
#define IS_JR(x)  (interactive(x) && \
                    x->query_real_name()[-2..]=="jr")

#define CORELIB_DIR                  ("/d/Genesis/specials/")



/* files */
#define HO_STD_ROOM            (HO_ROOMS_DIR + "std/ho_std_room")
#define HO_STD_OUTDOOR         (HO_ROOMS_DIR + "std/ho_std_outdoor")
#define HO_MASTER              (HO_MASTER_DIR + "ho_master")

#define HO_MAPPINGS            (HO_MASTER_DIR + "ho_mappings")


#define JOIN_LOG(x,y)       write_file(HO_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define LEAVE_LOG(x,y)      write_file(HO_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            


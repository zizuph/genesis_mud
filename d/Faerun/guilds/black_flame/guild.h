/*  /d/Faerun/guilds/black_flame/guild.h
 *
 *  Guildheader for the Order of the Black Flame
 *
 *  Nerull 2022.
 *
 */

/* directory paths */
#define BF_GUILD_DIR           "/d/Faerun/guilds/black_flame/"

#define BF_DOC_DIR             (BF_GUILD_DIR + "doc/")
#define BF_LOG_DIR             (BF_GUILD_DIR + "log/")
#define BF_MASTER_DIR          (BF_GUILD_DIR + "master/")
#define BF_NPC_DIR             (BF_GUILD_DIR + "npc/")
#define BF_OBJ_DIR             (BF_GUILD_DIR + "obj/")
#define BF_ROOMS_DIR           (BF_GUILD_DIR + "rooms/")
#define BF_SHADOWS_DIR         (BF_GUILD_DIR + "shadows/")
#define BF_SOULS_DIR           (BF_GUILD_DIR + "souls/")
#define BF_SPELLOB_DIR         (BF_GUILD_DIR + "spells/obj/")
#define BF_SPELLS_DIR         (BF_GUILD_DIR + "spells/")

#define BF_SPELL_OBJECT         "Bf_Spell_Object"

#define BF_SAVE_FILE           (BF_MASTER_DIR +"log/bf_save")



// Mappings
#define BF_REP                 (BF_MASTER_DIR +"log/bf_rep")
#define BF_NODES               (BF_MASTER_DIR +"log/bf_nodes")

// Standard stat weighting for spells based on magic guild class
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })

#define MAXNODES                1


//////////////////////////////////////////////////////////////////////////////////////
// LAY Guildname, type & tax --- ---------------
#define LAY_BF_GUILD_NAME      "Order of the Black Flame"
#define TYPE_LAY               "ranger"
#define TAX_LAY                21
#define IS_BF_MEMBER(p)        ((p)->query_guild_name_lay() == LAY_BF_GUILD_NAME)


// Some general defines
#define BSN(x)               ((x) + "\n")
#define LOW(x)               lower_case(x)
#define OBJ(obj)             obj->query_objective()
#define QSW                  query_shadow_who()
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


/* guild item */
#define BF_GUILD_ITEM_LAY            (BF_OBJ_DIR + "bandolier")
#define GUILD_ITEM_NAME_LAY          "_bf_bandolier"


/* files */
#define BF_STD_ROOM            (BF_ROOMS_DIR + "std/bf_std_room")
#define BF_STD_OUTDOOR         (BF_ROOMS_DIR + "std/bf_std_outdoor")
#define BF_MASTER              (BF_MASTER_DIR + "bf_master")

#define BF_MAPPINGS            (BF_MASTER_DIR + "bf_mappings")

#define BF_FLAMES              (BF_SHADOWS_DIR + "black_f_sh")

// Guild specific skill
#define SS_ANATOMY                    152804

#define ROOM_DIR                      "/d/Faerun/guilds/black_flame/rooms/"

#define MEMBER_LIST_UTILITY      ("/d/Faerun/guilds/black_flame/souls/member_list_util")


							
#define JOIN_LOG(x,y)       write_file(BF_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define LEAVE_LOG(x,y)      write_file(BF_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define SPYTOKENPLACEMENT_LOG(x,y)  write_file(BF_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            

#define COOLDOWN_REJOIN_TIME 260000


#define BF_SPECIAL_ABILITY  (BF_GUILD_DIR + "specials/bfspecial")


// Number of spellcharges per charm used
#define CHARM_CHARGES            12

// Spell standard charges
//#define SPELL_STD_CHARGE           15
#define SPELL_STD_CHARGE           1

#define GIFT_1                     0
#define GIFT_2                     2
#define GIFT_3                     4
#define GIFT_4                     6
#define GIFT_5                     8
#define GIFT_6                     10





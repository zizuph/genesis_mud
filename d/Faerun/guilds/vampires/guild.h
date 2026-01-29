/*  /d/Faerun/guilds/vampires/guild.h
 *
 *  Guildheader for Vampires of Faerun
 *
 *  Nerull 2021.
 *
 */

/* directory paths */
#define VAMPIRES_GUILD_DIR           "/d/Faerun/guilds/vampires/"

#define VAMPIRES_DOC_DIR             (VAMPIRES_GUILD_DIR + "doc/")
#define VAMPIRES_LOG_DIR             (VAMPIRES_MASTER_DIR + "log/general_logs/")
#define VAMPIRES_LOG2_DIR            ("/d/Faerun/private/restrictlog/guilds/vampires/")
#define VAMPIRES_MASTER_DIR          (VAMPIRES_GUILD_DIR + "master/")
#define VAMPIRES_NPC_DIR             (VAMPIRES_GUILD_DIR + "npc/")
#define VAMPIRES_OBJ_DIR             (VAMPIRES_GUILD_DIR + "obj/")
#define VAMPIRES_ROOMS_DIR           (VAMPIRES_GUILD_DIR + "rooms/")
#define VAMPIRES_SHADOWS_DIR         (VAMPIRES_GUILD_DIR + "shadows/")
#define VAMPIRES_SOULS_DIR           (VAMPIRES_GUILD_DIR + "souls/")

#define VAMPIRES_SAVE_FILE           (VAMPIRES_MASTER_DIR +"log/vampires_save")
#define VAMPIRES_SEEKER              (VAMPIRES_MASTER_DIR +"log/vampires_seeker")
#define VAMPIRES_WEAPON_SELECTION    (VAMPIRES_MASTER_DIR +"log/vampires_weapon_selection")
#define VAMPIRES_RESILIENCE_GAUGE    (VAMPIRES_MASTER_DIR +"log/vampires_resilience_gauge")
#define VAMPIRES_THIRST_GAUGE        (VAMPIRES_MASTER_DIR +"log/thirst_gauge")
#define VAMPIRES_RANK                (VAMPIRES_MASTER_DIR +"log/vampires_rank")
#define VAMP_BLESSED             (VAMPIRES_MASTER_DIR +"log/vampires_blessed")
#define VAMPIRES_GAUGE               (VAMPIRES_MASTER_DIR +"log/vampires_gauge")
#define VAMPIRESPAWN_TIMER           (VAMPIRES_MASTER_DIR +"log/vampirespawn_timer")

#define VAMPIRES_SPELL_OBJECT         "Vamp_Spell_Object"
#define VAMPIRES_SPELLOB_DIR         (VAMPIRES_GUILD_DIR + "spells/objs/")



//////////////////////////////////////////////////////////////////////////////////////
// OCC Guildname, type & tax --- ---------------
#define OCC_VAMPIRES_GUILD_NAME      "Vampires of Faerun"
#define TYPE_OCC                     "ranger"
#define TAX_OCC                      30
#define IS_VAMP_MEMBER(p)            ((p)->query_guild_name_occ() == OCC_VAMPIRES_GUILD_NAME)

// LAY Guildname, type & tax --- ---------------
#define LAY_VAMPIRES_GUILD_NAME      "Vampires of Faerun"
#define TYPE_LAY                     "magic"
#define TAX_LAY                      21
#define IS_SPAWN_MEMBER(p)           ((p)->query_guild_name_lay() == LAY_VAMPIRES_GUILD_NAME)

// RACIAL Guildname, type & tax --- ---------------
#define RACE_VAMPIRES_GUILD_NAME     "Vampires of Faerun"
#define TYPE_RACE                    "race"
#define TAX_RACE                     2
#define IS_RACIAL_MEMBER(p)          ((p)->query_guild_name_race() == RACE_VAMPIRES_GUILD_NAME)
/////////////////////////////////////////////////////////////////////////////////////

// Standard stat weighting for spells based on magic guild class
#define STAT_WEIGHTING   ({ SKILL_WEIGHT, 60, TS_INT, SKILL_WEIGHT, 20, TS_WIS, SKILL_WEIGHT, 20, TS_DIS })


// Some general defines
#define BSN(x)                         ((x) + "\n")
#define LOW(x)                         lower_case(x)
#define OBJ(obj)                       obj->query_objective()
#define QSW                           query_shadow_who()

#define NO_COFFIN_PLACEMENT            "_no_coffin_placement"

#define IS_WIZ(x) (interactive(x) && \
    SECURITY->query_wiz_rank(x->query_real_name()))
    
#define IS_JR(x)  (interactive(x) && \
                    x->query_real_name()[-2..]=="jr")

#define CORELIB_DIR                  ("/d/Genesis/specials/")

#define GENESIS_TIMEKEEPER  "/d/Sparkle/area/city/lib/genesis_timekeeper"
                       
#define IAM_OBFUSCATED                "_i_am_obfuscated"
#define VAMPIRE_IMM_POINT             "_vamp_imm_prop"

#define VAMPIRE_POWERS_UNLOCK_OB  "/d/Faerun/guilds/vampires/obj/vampire_powers_unlock_ob"

// Need to be 160 avg to join occ vamp                    
#define REQ_AVG_OCC                   160 

// Need to be 160 avg to join lay vamp
#define REQ_AVG_LAY                   160

// Minimum blood for powers to work
#define ABILITY_THRESHOLD             100

// Thirst point chance (1d100)
#define THIRST_POINT_CHANCE          5

#define ROOM_I_VAMP_MELD             "_room_i_vamp_meld"

#define ROOM_S_BLOOD_DIR             "_room_s_blood_dir"
#define LIVE_O_VAMP_DRAINER          "_live_o_vamp_drainer"
#define LIVE_O_OFFERED_BLOOD         "_live_o_offered_blood"
#define YES_NO_OBJECT               (VAMPIRES_OBJ_DIR+"yes_no")

#define NO_VAMP_WEAK_MESSAGE         "_novamp_weak_message"

// Guru quest defines
#define VAMPIRES_ON_GURUQUEST        "_vampires_on_guruquest"   

/* guild item */
#define GUILD_ITEM_OCC               (VAMPIRES_OBJ_DIR + "dark_suit")
#define GUILD_ITEM_NAME_OCC           "_vampires_guild_item_occ"
#define JOIN_CUTSCENE_PARALYZE       (VAMPIRES_OBJ_DIR + "join_cutscene_paralyze")
#define VAMPIRES_REGEN_BASE_OBJ_OCC  (VAMPIRES_GUILD_DIR + "specials/obj/evade_obj_base_occ")
#define VAMPIRES_REGEN_BASE_OBJ_LAY  (VAMPIRES_GUILD_DIR + "specials/obj/evade_obj_base_lay")

#define BLOOD_SHADOW                 (VAMPIRES_GUILD_DIR + "shadows/blood_shadow")

/* files */
#define VAMPIRES_STD_ROOM            (VAMPIRES_ROOMS_DIR + "std/vampires_std_room")
#define VAMPIRES_STD_OUTDOOR         (VAMPIRES_ROOMS_DIR + "std/vampires_std_outdoor")
#define VAMPIRES_MASTER              (VAMPIRES_MASTER_DIR + "vampires_master")


#define VAMPIRES_OBJHANDLER          (VAMPIRES_MASTER_DIR + "vampires_obj_handler")

//#define VAMPIRES_OBJHANDLER          ("/d/Faerun/private/restrictlog/guilds/vampires/vampires_obj_handler.c")


#define VAMPIRES_MAPPINGS            (VAMPIRES_MASTER_DIR + "vampires_mappings")

// Guild specific skill
#define SS_ANATOMY                    152804

//  Vamp puzzles
#define BOX1_PARALYZE                (VAMPIRES_OBJ_DIR + "box1_paralyze")
#define BOX2_PARALYZE                (VAMPIRES_OBJ_DIR + "box2_paralyze")
#define BOX3_PARALYZE                (VAMPIRES_OBJ_DIR + "box3_paralyze")
#define BOX4_PARALYZE                (VAMPIRES_OBJ_DIR + "box4_paralyze")
#define BOX5_PARALYZE                (VAMPIRES_OBJ_DIR + "box5_paralyze")
#define BOX6_PARALYZE                (VAMPIRES_OBJ_DIR + "box6_paralyze")

#define ROOM_DIR                      "/d/Faerun/guilds/vampires/rooms/"

#define PUZZLEBOX1_1  "/d/Faerun/highroad/rooms/beach03.c"
#define PUZZLEBOX1_2  "/d/Faerun/highroad/farms/farm02/garden03.c"
#define PUZZLEBOX1_3  "/d/Faerun/mere/rooms/me32.c"

#define PUZZLEBOX2_1  "/d/Raumdor/common/forest/nforest28.c"
#define PUZZLEBOX2_2  "/d/Genesis/start/dwarf/lvl2/edge3.c"    
#define PUZZLEBOX2_3  "/d/Raumdor/common/temple/temple13.c"
#define PUZZLEBOX2_4  "/d/Ansalon/goodlund/nethosak/forest/room/forest6.c"
#define PUZZLEBOX2_5  "/d/Terel/common/moor/forest/thicket.c"

#define PUZZLEBOX3_1  "/d/Terel/silver/forest_qz/forest_x17.c"
#define PUZZLEBOX3_2  "/d/Krynn/wayreth/forest/forest32.c"
#define PUZZLEBOX3_3  "/d/Gondor/ithilien/emyn-arnen/vrd8.c"
#define PUZZLEBOX3_4  "/d/Gondor/ithilien/poros/manor/garden.c"
#define PUZZLEBOX3_5  "/d/Calia/mountain/road/m33.c"

#define PUZZLEBOX4_1  "/d/Kalad/common/trade/cliffside/house1.c"
#define PUZZLEBOX4_2  "/d/Emerald/blackwall/delrimmon/lakeside/sw_cliff5.c"
#define PUZZLEBOX4_3  "/d/Kalad/common/wild/pass/desert/oasis/o3.c"
#define PUZZLEBOX4_4  "/d/Kalad/common/wild/pass/desert/camp/c21.c"
#define PUZZLEBOX4_5  "/d/Earthsea/gont/beach/beach_rooms/beach09a.c"

#define PUZZLEBOX5_1  "/d/Krynn/solace/forest/toedecave.c"
#define PUZZLEBOX5_2  "/d/Krynn/solace/graves/hole0.c"
#define PUZZLEBOX5_3  "/d/Gondor/morgul/city/barrstr5.c"
#define PUZZLEBOX5_4  "/d/Gondor/ithilien/nforest/slope4.c"
#define PUZZLEBOX5_5  "/d/Shire/eastroad/eastern/erb15.c"

#define PUZZLEBOX6_1  "/d/Faerun/underdark/dark_dom/rooms/tu28.c"
#define PUZZLEBOX6_2  "/d/Gondor/mordor/ungol/lair/stunnel4.c"
#define PUZZLEBOX6_3  "/d/Avenir/common/holm/jungle/lf7.c"
#define PUZZLEBOX6_4  "/d/Calia/sea/sector_1_0_4/wr_14_6_4.c"
#define PUZZLEBOX6_5  "/d/Calia/sea/sector_0_1_4/wr_7_15_4.c"


#define NATIONPLACE_1  ""
#define NATIONPLACE_2  ""
#define NATIONPLACE_3  ""
#define NATIONPLACE_4  ""
#define NATIONPLACE_5  ""
#define NATIONPLACE_6  ""
#define NATIONPLACE_7  ""
#define NATIONPLACE_8  ""
#define NATIONPLACE_9  ""
#define NATIONPLACE_10  ""
#define NATIONPLACE_11 ""
#define NATIONPLACE_12 ""
#define NATIONPLACE_13 ""
#define NATIONPLACE_14 ""
#define NATIONPLACE_15 ""
#define NATIONPLACE_16 ""
#define NATIONPLACE_17 ""
#define NATIONPLACE_18 ""
#define NATIONPLACE_19 ""
#define NATIONPLACE_20 ""
#define NATIONPLACE_21 ""
#define NATIONPLACE_22 ""
#define NATIONPLACE_23 ""
#define NATIONPLACE_24 ""
#define NATIONPLACE_25 ""
#define NATIONPLACE_26 ""
#define NATIONPLACE_27  ""
#define NATIONPLACE_28  ""


#define ANOMALITYPLACE_1 ""
#define ANOMALITYPLACE_2 ""
#define ANOMALITYPLACE_3 ""
#define ANOMALITYPLACE_4 ""
#define ANOMALITYPLACE_5 ""
#define ANOMALITYPLACE_6 ""
#define ANOMALITYPLACE_7 ""
#define ANOMALITYPLACE_8 ""
#define ANOMALITYPLACE_9 ""
#define ANOMALITYPLACE_10 ""
#define ANOMALITYPLACE_11 ""
#define ANOMALITYPLACE_12 ""
#define ANOMALITYPLACE_13 ""
#define ANOMALITYPLACE_14 ""
#define ANOMALITYPLACE_15 ""


#define PUZZLEB1      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box1.c"
#define PUZZLEB2      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box2.c"
#define PUZZLEB3      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box3.c"
#define PUZZLEB4      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box4.c"
#define PUZZLEB5      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box5.c"
#define PUZZLEB6      "/d/Faerun/guilds/vampires/obj/vamp_puzzle_box6.c"

#define NATION_TARGET "/d/Faerun/guilds/vampires/npc/nation_target.c"

#define ANOMALITY     "/d/Faerun/guilds/vampires/obj/shimmering_haze.c"

#define NATION_AGENT1 "/d/Faerun/guilds/vampires/npc/vamp1_tier3.c"
#define NATION_AGENT2 "/d/Faerun/guilds/vampires/npc/vamp2_tier3.c"
#define NATION_AGENT3 "/d/Faerun/guilds/vampires/npc/vamp3_tier3.c"
#define NATION_AGENT4 "/d/Faerun/guilds/vampires/npc/vamp4_tier3.c"
#define NATION_AGENT5 "/d/Faerun/guilds/vampires/npc/vamp5_tier3.c"
#define NATION_AGENT6 "/d/Faerun/guilds/vampires/npc/vamp6_tier3.c"
#define NATION_AGENT7 "/d/Faerun/guilds/vampires/npc/vamp7_tier3.c"
#define NATION_AGENT8 "/d/Faerun/guilds/vampires/npc/vamp8_tier3.c"
#define NATION_AGENT9 "/d/Faerun/guilds/vampires/npc/vamp9_tier3.c"
#define NATION_AGENT10 "/d/Faerun/guilds/vampires/npc/vamp10_tier3.c"

#define AGENT1_PLACE  "/d/Faerun/underdark/dark_dom/rooms/tu60.c"
#define AGENT2_PLACE  "/d/Gondor/ithilien/emyn-arnen/house4.c"
#define AGENT3_PLACE  "/d/Raumdor/common/dungeon/dungeon01.c"
#define AGENT4_PLACE  "/d/Krynn/solamn/palanthas/shipping/fishmonger.c"
#define AGENT5_PLACE  "/d/Calia/argos/metro/rooms/lib4.c"
#define AGENT6_PLACE  "/d/Shire/downs/barrows/bar01_01.c"
#define AGENT7_PLACE  "/d/Avenir/common/outpath/n2.c"
#define AGENT8_PLACE  "/d/Emerald/telberin/arts/auditorium.c"
#define AGENT9_PLACE  "/d/Kalad/common/trade/wall/house1.c"
#define AGENT10_PLACE  "/d/Cirath/tyr/warren/hut1.c"

// Vamp puzzlebox spawntimer. 3 hours
#define PUZZLESPAWN                  10800.0

// Vamp Puzzlebox expiretimer. about 3 hours
#define PUZZLEBOX_EXPIRE             10750.0

// Vampire target expiretimer. about 3 hours
#define TARGET_EXPIRE             10750.0

// Coffintoken popupationtimer. 3 hours.
#define COFFINTOKENSPAWN             10800.0

// Temporary Cooldown objects for blind and silence
// Silence uses a caid ratio of 1.8  (45 caid equals 25 
// second duration). Therefore 90 caid equals 50 seconds duration.
#define STRANGULATE_DURATION            50.0
#define STRANGULATE_COOLDOWN_DURATION  111.0
#define MESMERIZE_COOLDOWN_DURATION     60.0

#define COFFIN_MANAGER   "/d/Faerun/guilds/vampires/master/coffin_manager.c"

//#define COFFIN_MANAGER   "/d/Faerun/private/restrictlog/guilds/vampires/coffin_manager.c"



#define SIRE_MANAGER     "/d/Faerun/guilds/vampires/master/sire_manager.c"
#define THRALL_MANAGER   "/d/Faerun/guilds/vampires/master/thrall_manager.c"

#define TRAIL_LOSS_TIME                600

#define VAMPIRE_IS_ETHEREAL            "_vampire_is_ethereal"
#define VAMPIRE_IS_INVIS               "_vampire_is_invis"
#define VAMPIRE_IS_DAYWALKER           "_vampire_is_daywalker"

#define DRINK_HP                      200
#define DRINK_MANA                      5
#define DRINK_FATIGUE                   4
#define DRINK_INTERVAL                2.0

#define SPECIAL_BLOODGAIN_FACTOR       10

#define LIVE_M_NO_DRAIN               "_live_m_no_drain"
#define VAMP_O_CLING                  "_vamp_o_cling"

#define DRAINER_SUBLOC                "drainer_subloc"
#define DRAINEE_SUBLOC                "drainee_subloc"

#define MEMBER_LIST_UTILITY      ("/d/Faerun/guilds/vampires/souls/member_list_util")


#define COVEN_LOG(x,y)       write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define COFFINSPAWN_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define COFFINBURN_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define HIGHERVAMP_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define COFFINDESTROY_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )

#define LOG1_LOG(x,y)       write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )
                                
#define COFFINPLACEMENT_LOG(x,y)       write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								       4, 15) +" "+ y )
                                       
#define COFFINFIND_LOG(x,y)       write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								       4, 15) +" "+ y )
							
#define JOIN_LOG(x,y)       write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define VAMP_VS_VAMP_LOG(x,y)  write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define LEAVE_LOG(x,y)      write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define SEEKER_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define BOX_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define NATION_TARGET_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define ANOMALITY_TARGET_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define ANOMALITY_REWARD_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define REP_INCREASE_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WARD_LOG(x,y)     write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define ACCEPTDENY_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define THIRST_GAIN_LOG(x,y)      write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                                  4, 15) +" "+ y ) 

#define BLOOD_LOG(x,y)      write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                                  4, 15) +" "+ y )   	

#define TOKEN_LOG(x,y)      write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )     

#define THRALL_POOL_LOG(x,y) write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define WIZARD_ENTRY_VAMP_LOG(x,y)  write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
								4, 15) +" "+ y )      

#define AGE_GAUGE_LOG(x,y)  write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )          

#define SURVIVEBURN_LOG(x,y)  write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )          

                           

                                  
#define PRO(obj)             obj->query_pronoun()                            
#define SW                   shadow_who
#define POSS(obj)            obj->query_possessive()
#define WATCHERS(obj)        (filter(filter(all_inventory(environment((obj))), \
                             &->can_see_in_room()), &(obj)->check_seen()) \
                             - ({ (obj) }))

#define STRANGULATE_ABILITY  (VAMPIRES_GUILD_DIR + "specials/strangulate")
#define EXECUTE_ABILITY      (VAMPIRES_GUILD_DIR + "specials/execute")
#define BLOODLETTER_ABILITY  (VAMPIRES_GUILD_DIR + "specials/bloodletter")
#define TRUCIDATE_ABILITY    (VAMPIRES_GUILD_DIR + "specials/trucidate")
#define MESMERIZE_ABILITY    (VAMPIRES_GUILD_DIR + "specials/mesmerize")

// Other props
#define CHECK_EXPEL           "_check_expelme"
#define TORPOR_ROOM           "_this_is_torporroom"
#define VAMPIRES_GUILDACCEPT  "_vampires_guildaccept"
#define VAMPIRES_GUILDACCEPT2 "_vampires_guildaccept2"
#define REMAIN_STATIONARY     "_vamp_remain_stationary"
#define COFFIN_DESTROYED      "_coffin_destroyed"

// Approximately 4 months for idle out and guildkick for spawns
#define VAMPIRESPAWN_MAX_COUNTDOWNTIMER  2900
#define JOIN_VAMP_CUTSCENE_PARALYZE     (VAMPIRES_OBJ_DIR + "join_vamp_cutscene_paralyze")
#define GLOBAL_UNDEAD_SHADOW             "/d/Genesis/specials/std/undead_shadow.c"
#define VAMP_TURN_ON                     "_vamp_turn_on"

// World entry points
#define GRAVEYARDSPOT1  "/d/Krynn/solace/graves/hole0"
#define GRAVEYARDSPOT2  "/d/Krynn/solace/graves/grave18"
#define GRAVEYARDSPOT3  "/d/Krynn/solace/graves/grave10"
#define GRAVEYARDSPOT4  "/d/Krynn/solace/graves/o_grave1"

#define GRAVEYARDSPOT5  "/d/Terel/common/town/mansion/graveyard/grvw2"
#define GRAVEYARDSPOT6  "/d/Terel/common/town/mansion/graveyard/grve2"
#define GRAVEYARDSPOT7  "/d/Terel/common/town/mansion/graveyard/grve1"
#define GRAVEYARDSPOT8  "/d/Terel/common/town/mansion/graveyard/g2"
#define GRAVEYARDSPOT9  "/d/Terel/common/town/mansion/graveyard/grvyard1"
#define GRAVEYARDSPOT10 "/d/Terel/mountains/ice7"


// OCC vampire abilities. Checks vs Vampire age.
//              Full vampire (1, Fledgeling vampire)
#define VAMP_OCC_ABILITY_1    1451

//                           (3, Neonate Vampire)
#define VAMP_OCC_ABILITY_2    3001 

//                           (5, Ancilla Vampire)
#define VAMP_OCC_ABILITY_3    7001       

//                           (7, Vampire Lord)
#define VAMP_OCC_ABILITY_4    11001       

//                           (Elder vampire req)
#define VAMP_OCC_ABILITY_5    13001

//                           (Metusaleah req)
#define VAMP_OCC_ABILITY_6    15001

//                           (Antediluvian req)
#define VAMP_OCC_ABILITY_7    17001

//                           (Progenitor req)
#define VAMP_OCC_ABILITY_8    22001                                                        
                       

#define VAMP_MAIN_SPECIAL_MAPPING   (VAMPIRES_MASTER_DIR +"log/vamp_main_special")
#define VAMP_OCC_ABILITY_1_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_1")
#define VAMP_OCC_ABILITY_2_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_2")
#define VAMP_OCC_ABILITY_3_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_3")
#define VAMP_OCC_ABILITY_4_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_4")
#define VAMP_OCC_ABILITY_5_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_5")
#define VAMP_OCC_ABILITY_6_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_6")
#define VAMP_OCC_ABILITY_7_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_7")
#define VAMP_OCC_ABILITY_8_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_8")
#define VAMP_OCC_ABILITY_PROGENITOR_MAPPING  (VAMPIRES_MASTER_DIR +"log/vamp_occ_ability_progenitor")

#define THRALL_POOL  (VAMPIRES_MASTER_DIR +"log/thrall_pool")

#define VAMP_TITLE   (VAMPIRES_MASTER_DIR +"log/vampire_title")

#define VAMPIRES_REP  (VAMPIRES_MASTER_DIR +"log/vampires_rep")

#define VAMP_AGENT  (VAMPIRES_MASTER_DIR +"log/vampires_agent")

#define VAMP_PROG  (VAMPIRES_MASTER_DIR +"log/vampires_pathprog")


#define SANCTUARY_COST                3
#define CELERITY_COST                 8
#define DEADEYE_COST                  3
#define ELUSIVENESS_COST              8
#define RESILIENCE_COST               8
#define OBFUSCATE_COST                5
#define LIFEWARD_COST                 8
#define INCOGNITO_COST                3
#define SWARM_COST                   10
#define AMPLIFY_COST                  6
#define AUGUMENTATION_COST            3
#define INFUSION_COST                 6




#define TIER3_1_MIN_REQ_AGE    7001
#define TIER3_1_MIN_REQ_REP      10

#define TIER3_1_AGENT_NR          1
#define TIER3_2_AGENT_NR          2
#define TIER3_3_AGENT_NR          3
#define TIER3_4_AGENT_NR          4
#define TIER3_5_AGENT_NR          5
#define TIER3_6_AGENT_NR          6
#define TIER3_7_AGENT_NR          7
#define TIER3_8_AGENT_NR          8
#define TIER3_9_AGENT_NR          9
#define TIER3_10_AGENT_NR        10

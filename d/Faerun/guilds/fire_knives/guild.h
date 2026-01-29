/*  /d/Faerun/guilds/fire_knives/guild.h
 *
 *  Guildheader.
 *
 *  Nerull 2018.
 *
 */


/* directory paths */
#define FIREKNIVES_GUILD_DIR       "/d/Faerun/guilds/fire_knives/"

#define FIREKNIVES_BOARDS_DIR      (FIREKNIVES_GUILD_DIR + "boards/")
#define FIREKNIVES_DOC_DIR         (FIREKNIVES_GUILD_DIR + "doc/")
#define FIREKNIVES_LOG_DIR         (FIREKNIVES_GUILD_DIR + "log/")
#define FIREKNIVES_LOG2_DIR        ("/d/Faerun/private/restrictlog/guilds/fire_knives/")
#define FIREKNIVES_MASTER_DIR      (FIREKNIVES_GUILD_DIR + "master/")
#define FIREKNIVES_NPC_DIR         (FIREKNIVES_GUILD_DIR + "npc/")
#define FIREKNIVES_OBJ_DIR         (FIREKNIVES_GUILD_DIR + "obj/")
#define FIREKNIVES_LIBRARY_DIR     (FIREKNIVES_GUILD_DIR + "library/")
#define FIREKNIVES_ROOMS_DIR       (FIREKNIVES_GUILD_DIR + "rooms/")
#define FIREKNIVES_SHADOWS_DIR     (FIREKNIVES_GUILD_DIR + "shadows/")
#define FIREKNIVES_SOULS_DIR       (FIREKNIVES_GUILD_DIR + "souls/")
#define STORE_ROOM                 (FIREKNIVES_ROOMS_DIR + "store")

/* Library files and shortcuts */
#define LIBRARY_BOOKS_DIR          (FIREKNIVES_LIBRARY_DIR + "books")
#define LIBRARY_CARD                "_fireknives_library_card"

#define FIREKNIVES_CONTRACT_FILE   (FIREKNIVES_MASTER_DIR +"log/fireknives_contracts")
#define FIREKNIVES_SAVE_FILE       (FIREKNIVES_MASTER_DIR +"log/fireknives_save")
#define ASSASSIN_RANK              (FIREKNIVES_MASTER_DIR +"log/assassin_rank")
#define ASSASSINATION_GAUGE        (FIREKNIVES_MASTER_DIR +"log/assassination_gauge")
#define ASSASSINATION_ACTIV_GAUGE  (FIREKNIVES_MASTER_DIR +"log/activity_gauge")
#define ASSA_XCOUNCIL_COOLDOWN     (FIREKNIVES_MASTER_DIR +"log/x-council_cooldown")

#define ABILITY1                   (FIREKNIVES_MASTER_DIR +"log/ability1")
#define ABILITY2                   (FIREKNIVES_MASTER_DIR +"log/ability2")
#define ABILITY3                   (FIREKNIVES_MASTER_DIR +"log/ability3")
#define ABILITY4                   (FIREKNIVES_MASTER_DIR +"log/ability4")
#define ABILITY5                   (FIREKNIVES_MASTER_DIR +"log/ability5")

// Joiningroom properties and premises
#define I_CAN_JOIN_FIREKNIVES       "_i_can_join_fireknives"
#define I_CAN_JOIN_FIREKNIVES2      "_i_can_join_fireknives2"
#define I_CAN_COMPLETE_CONTRACT     "_i_can_complete_contract"
#define I_CAN_CREATE_CONTRACT       "_i_can_create_contract"
#define I_CAN_VISIT_MEETINGROOM     "_i_can_visit_meetingroom"

// Need to be Hero to join this guild
#define REQ_AVG                     120 

// Guru quest defines
#define FIREKNIVES_ON_GURUQUEST     "_fireknives_on_guruquest"   

/* guild item */
#define GUILD_ITEM                 (FIREKNIVES_OBJ_DIR + "dark_suit")
#define GUILD_ITEM_NAME            "_fireknives_guild_item"

#define VISIT_ITEM_CONFERENCE      (FIREKNIVES_OBJ_DIR + "visit_item_conference")
#define VISIT_ITEM_NAME_CONFERENCE "fireknives_visit_object_conference"

#define VISIT_ITEM_FIST            (FIREKNIVES_OBJ_DIR + "visit_item_fist")
#define VISIT_ITEM_NAME_FIST       "fireknives_visit_object_fist"

#define VISIT_ITEM_MENTOR          (FIREKNIVES_OBJ_DIR + "visit_item_mentor")
#define VISIT_ITEM_NAME_MENTOR     "fireknives_visit_object_mentor"

#define VISIT_ITEM_ELDER           (FIREKNIVES_OBJ_DIR + "visit_item_elder")
#define VISIT_ITEM_NAME_ELDER       "fireknives_visit_object_elder"

#define FULL_MEMBER_CEREMONY       "_fullmember_ceremony"

#define JOIN_CUTSCENE_PARALYZE     (FIREKNIVES_OBJ_DIR + "join_cutscene_paralyze")

#define FULLMEMBER_CUTSCENE_PARALYZE (FIREKNIVES_OBJ_DIR + "fullmember_cutscene_paralyze")

#define FIREKNIVES_REGEN_BASE_OBJ  (FIREKNIVES_GUILD_DIR + "specials/obj/evade_obj_base")

/* files */
#define FIREKNIVES_STD_ROOM        (FIREKNIVES_ROOMS_DIR + "std/fireknives_std_room")
#define FIREKNIVES_STD_OUTDOOR     (FIREKNIVES_ROOMS_DIR + "std/fireknives_std_outdoor")
#define FIREKNIVES_MASTER          (FIREKNIVES_MASTER_DIR + "occ_fireknives_master")
#define FIREKNIVES_MAPPINGS        (FIREKNIVES_MASTER_DIR + "occ_fireknives_mappings")

/* Rank definitions */
#define FIREKNIVES_MIN_RANK_MEMBER  1
#define FIREKNIVES_MAX_RANK_MEMBER  28

// Max prospect rank
#define MAX_PROSPECT_RANK           7

// Min fullmember rank
#define MIN_FULLMEMBER_RANK         8

// Max assassin gauge rank
#define MAX_ASSASSIN_GAUGE          25

// Guild specific skill
#define SS_ART                      152701

// Temporary Cooldown objects for blind and silence
// Silence uses a caid ratio of 1.8  (45 caid equals 25 
// second duration). Therefore 90 caid equals 50 seconds duration.
#define SILENCE_DURATION            50.0
#define BLIND_DURATION              50.0
#define SILENCE_COOLDOWN_DURATION  111.0
#define BLIND_COOLDOWN_DURATION    111.0
#define STUN_COOLDOWN_DURATION     57.0

// Some general defines
#define BSN(x)                      ((x) + "\n")
#define LOW(x)                      lower_case(x)

#define MEMBER_LIST_UTILITY      ("/d/Faerun/guilds/fire_knives/souls/member_list_util")


#define LOG1_LOG(x,y)       write_file(FIREKNIVES_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define LOG2_LOG(x,y)       write_file(FIREKNIVES_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define LOG3_LOG(x,y)       write_file(FIREKNIVES_MASTER_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                                                      
// Various guild logs   

#define WIZARD_ENTRY_APP_BOARD_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WIZARD_ENTRY_LIBRARY_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WIZARD_ENTRY_CONFERENCE_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WIZARD_ENTRY_CONTRACTS_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WIZARD_ENTRY_ELDER_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define WIZARD_ENTRY_FIST_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define WIZARD_ENTRY_MENTOR_LOG(x,y)   write_file(FIREKNIVES_LOG2_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )                           
                            

#define ACTIVITY_LOG(x,y)   write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                         
#define JOIN_LOG(x,y)       write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define JOIN_PER_LOG(x,y)   write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define LEAVE_LOG(x,y)       write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )   

#define EXPELLED_LOG(x,y)   write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )  

#define BLED_LOG(x,y)       write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )                                                     
							

#define FULLMEMBER_LOG(x,y) write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define FULLM_PER_LOG(x,y)  write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )                                                           

#define REWARD_LOG(x,y)     write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y ) 

#define PUNISH_LOG(x,y)     write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define EXECUTE_LOG(x,y)    write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )

#define CRAFTING_LOG(x,y)   write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                            
#define CLIMB_LOG(x,y)      write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )


#define SW                       shadow_who


#define BLIND_ABILITY        (FIREKNIVES_GUILD_DIR + "specials/blind")

#define EVISCERATE_ABILITY   (FIREKNIVES_GUILD_DIR + "specials/eviscerate")

#define STUN_ABILITY         (FIREKNIVES_GUILD_DIR + "specials/stun")

#define ASSASSINATE_ABILITY  (FIREKNIVES_GUILD_DIR + "specials/assassinate")

#define EVADE_ABILITY        (FIREKNIVES_GUILD_DIR + "specials/evade")

#define GAROTTE_ABILITY      (FIREKNIVES_GUILD_DIR + "specials/garotte")

#define BACKSTAB_ABILITY     (FIREKNIVES_GUILD_DIR + "specials/backstab")



// Weaponoil appearances once applied
#define CRIPPLING_FLAME      "verdant acidulated"

#define MANSLAYER_FLAME      "sizzling viridescent"
#define ELDARBANE_FLAME      "sparkling vermilion"
#define DWARFBANE_FLAME      "bubbly hazel"
#define GNOMESLAYER_FLAME    "hizzing solferino"
#define HALFLINGBANE_FLAME   "brewing stygian"
#define GIANTSBANE_FLAME     "smoking indigo"
#define DRAGONBANE_FLAME     "fizzling jaundicy"
#define GREENSLAYER_FLAME    "sputtering lavender"
#define DEATHBANE_FLAME      "searing amber"
#define NATUREBANE_FLAME     "sweltering blanch"


// Fire Knives ART Ability unlocks (based on guild rank) ---------------------
// Trainee levels
//      Weaponcoating (Coats a weapon with toxins(various)
#define AB1                      2   

//      Eviscerate    (Ruthless damage attack)
#define AB2                      5

// Full member levels ------------
//      Garotte       (Silences the target for x seconds)
#define AB3                      10

//      Disarm        (Evasion. Tries to evade attacks)
#define AB4                     15

//      Blind         (Blinds target for x time)
#define AB5                     20

//      N/A           (Not in use atm)
#define AB6                     25

//      Vanish        (Vanish. Allows assassin to poof away.)
#define AB7                     27
//----------------------------------------------------------------------------


// Weapon oils
#define SILVEROIL                  "_silveroil"
#define CRIPPLINGOIL               "_cripplingoil"

#define MANSLAYEROIL               "_manslayeroil"
#define ELDARBANEOIL               "_eldarbaneoil"
#define DWARFBANEOIL               "_dwarfbaneoil"
#define GNOMESLAYEROIL             "_gnomeslayeroil"
#define HALFLINGBANEOIL            "_halflingbaneoil"
#define GIANTSBANEOIL              "_giantsbaneoil"
#define DRAGONBANEOIL              "_dragonoil"
#define GREENSLAYEROIL             "_greenslayeroil"
#define DEATHBANEOIL               "_deathbaneoil"
#define NATUREBANEOIL              "_naturebaneoil"


// Guildname, type & tax --- ---------------
#define FIREKNIVES_GUILD_NAME    "Fire Knives"
#define TYPE_OCC                 "thief"
#define TAX_OCC                  33

#define IS_MEMBER(p) ((p)->query_guild_name_occ() == FIREKNIVES_NAME)
//-----------------------------------------

// Guildtitles 

// Trainee titles
#define FIREKNIVES_TITLE0   "Postulant"
#define FIREKNIVES_TITLE1   "Postulant"
#define FIREKNIVES_TITLE2   "Initiate of the First Level"
#define FIREKNIVES_TITLE3   "Initiate of the Second Level"
#define FIREKNIVES_TITLE4   "Initiate of the Third Level"
#define FIREKNIVES_TITLE5   "Beginning Candidate Inhumer"
#define FIREKNIVES_TITLE6   "Surviving Candidate Inhumer"
#define FIREKNIVES_TITLE7   "Accomplished Candidate Inhumer"

// Full member titles
#define FIREKNIVES_TITLE8   "Lurker in the Shadows"
#define FIREKNIVES_TITLE9   "Stealthy Dart"
#define FIREKNIVES_TITLE10   "Dark Shadow"
#define FIREKNIVES_TITLE11  "Keen Stiletto"
#define FIREKNIVES_TITLE12  "Black Orchid"
#define FIREKNIVES_TITLE13  "Quiet Touch"
#define FIREKNIVES_TITLE14  "Light Tread"
#define FIREKNIVES_TITLE15  "Midnight Shade"
#define FIREKNIVES_TITLE16  "Deadly Breeze"
#define FIREKNIVES_TITLE17  "Endless Twilight"
#define FIREKNIVES_TITLE18  "Silent Shade"
#define FIREKNIVES_TITLE19  "Venom Barb"
#define FIREKNIVES_TITLE20  "Whispering Scythe"
#define FIREKNIVES_TITLE21  "Glint in the Moonlight"
#define FIREKNIVES_TITLE22  "Whisper of Steel"
#define FIREKNIVES_TITLE23  "Poisoned Mist"
#define FIREKNIVES_TITLE24  "Fatal Wish"
#define FIREKNIVES_TITLE25  "Fearsome Asp"
#define FIREKNIVES_TITLE26  "Stygian Wraith"
#define FIREKNIVES_TITLE27  "Ender of Dreams"
#define FIREKNIVES_TITLE28  "Bringer of Endless Night"
#define FIREKNIVES_TITLE29  "Bringer of Endless Night"

// Assassination Gauge titles (bragging righs)
// Full member titles
#define FIREKNIVES_GAUGE_TITLE0   ""
#define FIREKNIVES_GAUGE_TITLE1   ""
#define FIREKNIVES_GAUGE_TITLE2   ", Blooded Assassin"
#define FIREKNIVES_GAUGE_TITLE3   ", Tried Assassin"
#define FIREKNIVES_GAUGE_TITLE4   ", Tried Assassin"
#define FIREKNIVES_GAUGE_TITLE5   ", Tried Assassin"
#define FIREKNIVES_GAUGE_TITLE6   ", Competent Assassin"
#define FIREKNIVES_GAUGE_TITLE7   ", Competent Assassin"
#define FIREKNIVES_GAUGE_TITLE8   ", Competent Assassin"
#define FIREKNIVES_GAUGE_TITLE9   ", Competent Assassin"
#define FIREKNIVES_GAUGE_TITLE10  ", Dangerous Assassin"
#define FIREKNIVES_GAUGE_TITLE11  ", Dangerous Assassin"
#define FIREKNIVES_GAUGE_TITLE12  ", Dangerous Assassin"
#define FIREKNIVES_GAUGE_TITLE13  ", Dangerous Assassin"
#define FIREKNIVES_GAUGE_TITLE14  ", Accomplished Assassin"
#define FIREKNIVES_GAUGE_TITLE15  ", Accomplished Assassin"
#define FIREKNIVES_GAUGE_TITLE16  ", Accomplished Assassin"
#define FIREKNIVES_GAUGE_TITLE17  ", Accomplished Assassin"
#define FIREKNIVES_GAUGE_TITLE18  ", Deadly Assassin"
#define FIREKNIVES_GAUGE_TITLE19  ", Deadly Assassin"
#define FIREKNIVES_GAUGE_TITLE20  ", Deadly Assassin"
#define FIREKNIVES_GAUGE_TITLE21  ", Deadly Assassin"
#define FIREKNIVES_GAUGE_TITLE22  ", Master Assassin"
#define FIREKNIVES_GAUGE_TITLE23  ", Master Assassin"
#define FIREKNIVES_GAUGE_TITLE24  ", Legendary Assassin"

// MINIMUM ASSASSINATION RANK FOR GURU QUEST UNLOCK
#define FIREKNIVES_LEVEL_GURU_SKILLS_UNLOCK     6

// ABILITY UNLOCKS
#define FIREKNIVES_ABILITY1_UNLOCK              2
#define FIREKNIVES_ABILITY2_UNLOCK              3
#define FIREKNIVES_ABILITY3_UNLOCK              4
#define FIREKNIVES_ABILITY4_UNLOCK              5
#define FIREKNIVES_ABILITY_END                 10


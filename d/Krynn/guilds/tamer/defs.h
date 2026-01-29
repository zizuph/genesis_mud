/*
 *  defs.h
 *
 *  Beast Tamers defs.
 *
 *  Created by Carnak, February 2016
 *
 *  Cervidae
 */
 
#ifndef TAMERS_DEFS
#define TAMERS_DEFS

/*
 * Guild Defines
 */

#define GUILDMASTERS            ({ "carnak" })
#define GUILD_NAME              "Beast Tamer"
#define GUILD_STYLE             "ranger"
#define GUILD_TAX               12

#define BETA_TEST               0

/*
 * Paths
 */

#define TDIR                    ("/d/Krynn/guilds/tamer/")
#define CORE                    (TDIR           + "core/")
#define GUILD_SHADOW            (CORE           + "guild_shadow")
#define GUILD_SOUL              (CORE           + "tamer_soul")
#define MANAGER                 (CORE           + "manager")
#define GENUS                   (CORE           + "genus")
#define DATA                    (CORE           + "data/")
#define MEMBERS                 (DATA           + "members/")
#define GENUS_LIST              (DATA           + "genus/")
#define MEMBER_DIR(who)         (MEMBERS        + who)

#define BEAST                   (TDIR           + "beast/")
#define PET_MENU                (BEAST          + "pet_menu")
#define PET_HOUSE               (BEAST          + "pet_house")
#define PET_SOUL                (BEAST          + "pet_soul")
#define PET_BASE                (BEAST          + "base/pet_base")
#define PET_FOOD                (BEAST          + "pet_food")
#define PET_ARMOUR              (BEAST          + "pet_armour")

#define LOGS                    (TDIR           + "logs/")
#define LOGGER                  (LOGS           + "logger")

#define HELP                    (TDIR           + "help/")

#define SPECIALS                (TDIR           + "specials/")

/*
 * SKILLS
 */

                        /*  100 platinum    */
#define SATISFACTION            172800

                        /*  10  minutes     */
#define SKILL_DELAY             600

#define SKILLS          ([                                                     \
        SS_RIDING       :   ({ SS_RIDING,       "ride your pet",    60, 125 }),\
        SS_ANI_HANDL    :   ({ SS_ANI_HANDL,    "handle your pet",  60, 125 }) \
                        ])

#define CAN_SNEAK       ([  "canidae":1 ])
                        

/*
 * ABILITIES / ACHIEVEMENTS
 */

#define TSUMMON                 "_pet_summon"
#define TDISMISS                "_pet_dismiss"
#define TMANEUVER               "_pet_maneuver"
#define TASSIST                 "_pet_assist"
#define TKILL                   "_pet_kill"
#define TCALM                   "_pet_calm"
#define TSCOUT                  "_pet_scout"

#define ALL_ABILITIES           ({  TSUMMON, TDISMISS, TMANEUVER,              \
                                    TASSIST, TKILL, TCALM, TSCOUT })

#define ADD_TAMER_SKILL         "_add_tamer_skill"
#define ADD_PET_SKILL           "_add_pet_skill"
#define HAS_SKILL_BOOST         "_pet_adds_skill"

#define ALL_SKILLS              ({  ADD_TAMER_SKILL, ADD_PET_SKILL,            \
                                    HAS_SKILL_BOOST })

#define FOOD_NO_VALUE           "_food_no_value"
#define FOOD_VALUE              "_food_value"
#define FOOD_VORARE             "_food_vorare"
#define FOOD_POISON             "_food_poison"
#define FOOD_HERB               "_food_herb"
#define FOOD_INN                "_food_inn"

#define ALL_FOOD                ({  FOOD_NO_VALUE, FOOD_VALUE, FOOD_VORARE,    \
                                    FOOD_POISON, FOOD_HERB, FOOD_INN })

#define TAME_NEW_PET            "_tame_new_pet"

#define CAN_MOUNT               "_can_mount"
#define CANNOT_RIDE             "_force_dismount"
#define HAS_FALLEN_RIDING       "_has_fallen_riding"
#define HAS_FALLEN_COMBAT       "_has_fallen_combat"

#define ALL_MOUNT               ({  CAN_MOUNT, HAS_FALLEN_RIDING,              \
                                    CANNOT_RIDE, HAS_FALLEN_COMBAT })

                                    
#define MAX_GUILD_LEVEL 6

#define TITLE_ANI_HANDL         "_title_ani_handl"
#define TITLE_HUNTING           "_title_hunting"
#define TITLE_TRACKING          "_title_tracking"
#define TITLE_LOC_SENSE         "_title_loc_sense"
#define TITLE_SNEAK             "_title_sneak"
#define GENUS_TITLES            "_genus_titles"

#define ALL_TITLES              ({  TITLE_ANI_HANDL, TITLE_HUNTING,            \
                                    TITLE_TRACKING, TITLE_LOC_SENSE,           \
                                    TITLE_SNEAK, GENUS_TITLES })
                                 
#define TITLE_LEVELS            ({                      \
    "Capable ", "Accomplished ", "Talented ",           \
    "Gifted ", "Ardent ", "Fervent ", "Innate "         \
})

#define HIGH_TITLES             ([                      \
    SS_ANI_HANDL:({ "Beastmaster", "Beastmaster" }),    \
    SS_HUNTING  :({ "Huntsman", "Huntress" }),          \
    SS_TRACKING :({ "Tracker", "Tracker" }),            \
    SS_LOC_SENSE:({ "Pathfinder", "Pathfinder" }),      \
    SS_SNEAK    :({ "Scout", "Scout" }),                \
])

#define TITLES                  ({                      \
    "Novice Animal Handler",                            \
    "Inexperienced Animal Handler",                     \
    "Practiced Animal Handler",                         \
    "Experienced Animal Handler",                       \
    "Gifted Animal Handler",                            \
    "Innate Animal Handler",                            \
    "Tamer of Beasts"                                   \
})
                                    
#define PET_INJURY              "_pet_injury"
#define INJURY_TIME             43200
//86400

#define FIND_PET_ARMOUR         "_find_pet_armour"

/*
 * PETS
 */
                        
#define CARNIVORE       ({  "meat", "leftover", "steak"             \
                                                                    \
                        })
                        
#define HERBIVORE       ({  "plant", "grass", "herb"                \
                                                                    \
                        })

#define MAX_PET_SPAWNS  2

#define BIOME_LIST      ([                                          \
        "ArcticTundra"      :   ({"ursidae"}),                      \
        "AlpineTundra"      :   ({}),                               \
                                                                    \
        "AridDesert"        :   ({}),                               \
        "SemiAridDesert"    :   ({}),                               \
        "CoastalDesert"     :   ({}),                               \
        "ColdDesert"        :   ({}),                               \
                                                                    \
        "TemperateForest"   :   ({"suidae"}),                       \
        "TropicalForest"    :   ({}),                               \
        "BorealForest"      :   ({}),                               \
                                                                    \
        "TemperateGrassland":   ({}),                               \
        "TropicalGrassland" :   ({}),                               \
        "SteppeGrassland"   :   ({}),                               \
                        ])

#define PET_LOCS        ([                                          \
                                                                    \
"/w/carnak/workroom.c":"ArcticTundra",                              \
"/w/arman/workroom.c":"TemperateForest",                            \
                                                                    \
                        ])

#define GENDERS     ({  "male", "female"  })
                        
/*  Standard Properties  */

#define CREATION_OBJECT                 "_pet_creation_object"
#define KNIGHT_I_NO_RESCUE              "_knight_i_no_rescue"

/*  HOOKS   */
#define HOOK_TAMER_HEAL_HP              "_hook_tamer_heal_hp"

/* Formula for chance of increasing skill */
#define SUCCESS(skill, matur)           (((skill ? skill : 1) * \
                                         ((skill ? skill : 3) / 3)) / matur)

/* Emotions */

// Base emotions
#define E_ECSTASY                       1
#define E_ADMIRATION                    2
#define E_TERROR                        4
#define E_AMAZEMENT                     8
#define E_GRIEF                        16
#define E_LOATHING                     32
#define E_RAGE                         64
#define E_VIGILANCE                   128

// Emotional Grades
#define E_GRADE_ONE                   256
#define E_GRADE_TWO                   512
#define E_GRADE_THREE                1024
#define E_GRADE_FOUR                 2048
#define E_GRADE_FIVE                 4096

// Graded emotions
#define E_JOY                       (E_ECSTASY      | E_GRADE_ONE)
#define E_SERENITY                  (E_ECSTASY      | E_GRADE_TWO)
#define E_TRUST                     (E_ADMIRATION   | E_GRADE_ONE)
#define E_ACCEPTANCE                (E_ADMIRATION   | E_GRADE_TWO)
#define E_FEAR                      (E_TERROR       | E_GRADE_ONE)
#define E_APPRENHENSION             (E_TERROR       | E_GRADE_TWO)
#define E_SURPRISE                  (E_AMAZEMENT    | E_GRADE_ONE)
#define E_DISTRACTION               (E_AMAZEMENT    | E_GRADE_TWO)
#define E_SADNESS                   (E_GRIEF        | E_GRADE_ONE)
#define E_PENSIVENESS               (E_GRIEF        | E_GRADE_TWO)
#define E_DISGUST                   (E_LOATHING     | E_GRADE_ONE)
#define E_BOREDOM                   (E_LOATHING     | E_GRADE_TWO)
#define E_ANGER                     (E_RAGE         | E_GRADE_ONE)
#define E_ANNOYANCE                 (E_RAGE         | E_GRADE_TWO)
#define E_ANTICIPATION              (E_VIGILANCE    | E_GRADE_ONE)
#define E_INTEREST                  (E_VIGILANCE    | E_GRADE_TWO)

// Derivative emotions
#define E_LOVE                      (E_ECSTASY      | E_ADMIRATION)
#define E_SUBMISSION                (E_TERROR       | E_ADMIRATION)
#define E_AWE                       (E_TERROR       | E_AMAZEMENT)
#define E_DISAPPROVAL               (E_GRIEF        | E_AMAZEMENT)
#define E_REMORSE                   (E_GRIEF        | E_LOATHING)
#define E_CONTEMPT                  (E_RAGE         | E_LOATHING)
#define E_AGGRESSIVENESS            (E_RAGE         | E_VIGILANCE)
#define E_OPTIMISM                  (E_ECSTASY      | E_VIGILANCE)

#endif TAMERS_DEFS
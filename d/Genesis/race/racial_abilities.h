

// Sparkle domain.
#define RACIAL_ABILITY_SKILL  (151999)

#define SELECT_BENEFITS_NOTIFY "_select_benefits_notify"

#define HAS_RACIAL_ABILITY(who, ability)  (who->query_skill(RACIAL_ABILITY_SKILL) & ability)


// Implemented in notify_you_killed_me of generic.c
#define SCAVENGER                (1<<0)
// Implemented in query_critical_hit_frequency of generic.c
#define OPPORTUNISTIC            (1<<1)
// Implemented in configure_racial_bonuses of generic.c
#define SCOTOPIC_VISION          (1<<2)
// Implemented in fleet_footed_footprints of generic.c
#define LIGHT_FOOTED             (1<<3)
// Implemented in query_bank_fee_reduction_percent of generic.c
#define WELL_CONNECTED           (1<<4)
// Implemented in configure_racial_skill_bonuses of generic.c
#define EYE_FOR_DETAIL           (1<<5)
// Implemented in configure_racial_skill_bonuses of generic.c
#define LIGHT_FINGERED           (1<<6)
// Implemented in configure_racial_skill_bonuses of generic.c
#define STEALTHY                 (1<<7)
// Implemented in configure_racial_skill_bonuses of generic.c
#define EXPLORER                 (1<<8)
// Implemented in light_footed_regeneration of generic.c
#define GOOD_MEMORY              (1<<9)
// Implemented in herb_ingest_interval of generic.c
#define APOTHECARY               (1<<10)
// Implemented in configure_racial_bonuses of generic.c
#define RESILIENT                (1<<11)
// Implemented by light_footed_regeneration in generic.c
#define FLEET_FOOTED             (1<<12)
// Implemented in max_weight of generic.c
#define STALWART                 (1<<13)
// Implemented in add_exp_combat of generic.c
#define TENACIOUS                (1<<14)
// Implemented in intoxicated_max of generic.c
#define STRONG_LIVER             (1<<15)
// Implemented in eat_max of generic.c
#define INSATIABLE               (1<<16)


#define SCOTOPIC_VISION_SHADOW_PATH  ("/d/Genesis/specials/new/effects/boons/scotopic_vision_sh")


#define WELL_CONNECTED_PERCENT    (25)
#define OPPORTUNISTIC_MULTIPLIER  (5)
#define MAX_RACIAL_SKILL          (100)
#define RESILIENT_MAGIC_RES       (5)
#define RESILIENT_POISON_RES      (15)
#define LIGHT_FOOTED_PERCENTAGE   (10)
#define TENACIOUS_PERCENTAGE      (10)
#define SCAVENGER_PERCENTAGE      (10)
#define FLEET_FOOTED_PERCENTAGE   (100)
#define FLEET_FOOTED_AMOUNT       (3)
#define FLEET_FOOTED_INTERVAL     (20.0)

#define APOTHECARY_HERB_INTERVAL(cur)    (cur * 5 / 6)
#define F_GOOD_MEMORY(count)           (count * 5 / 4)

#define F_STRONG_LIVER(amt)           (amt * 110 / 100)
#define F_INSATIABLE(amt)           (amt * 110 / 100)

#define F_TENACIOUS_BOOST(exp)  (exp * 2)


#define ABILITIES_TO_NAME (([ SCAVENGER: "scavenger", \
                              OPPORTUNISTIC: "opportunistic", \
                              SCOTOPIC_VISION: "scotopic vision", \
                              LIGHT_FOOTED: "light-footed", \
                              WELL_CONNECTED: "well-connected", \
                              EYE_FOR_DETAIL: "eye for detail", \
                              LIGHT_FINGERED: "light-fingered", \
                              STEALTHY: "stealthy", \
                              EXPLORER: "explorer", \
                              GOOD_MEMORY: "good memory", \
                              APOTHECARY: "apothecary", \
                              RESILIENT: "resilient", \
                              FLEET_FOOTED: "fleet-footed", \
                              STALWART: "stalwart", \
                              TENACIOUS: "tenacious", \
                              STRONG_LIVER: "strong liver", \
                              INSATIABLE: "insatiable" ]))
                              
#define RACE_TO_ABILITIES (([ "human": ({ GOOD_MEMORY, EYE_FOR_DETAIL, LIGHT_FINGERED, TENACIOUS, SCAVENGER, APOTHECARY }), \
                              "goblin": ({ STALWART, SCAVENGER, OPPORTUNISTIC, LIGHT_FINGERED, STEALTHY, RESILIENT }), \
                              "elf" : ({ FLEET_FOOTED, SCOTOPIC_VISION, APOTHECARY, EXPLORER, STEALTHY, LIGHT_FOOTED }), \
                              "dwarf": ({ STALWART, GOOD_MEMORY, RESILIENT, STRONG_LIVER, INSATIABLE, EYE_FOR_DETAIL }), \
                              "gnome" : ({ RESILIENT, SCOTOPIC_VISION, EYE_FOR_DETAIL, STEALTHY, GOOD_MEMORY, WELL_CONNECTED }), \
                              "hobbit": ({ STEALTHY, FLEET_FOOTED, INSATIABLE, TENACIOUS, OPPORTUNISTIC, EXPLORER }) ]))
                              

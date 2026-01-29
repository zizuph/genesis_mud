/* 
 * FACTION HANDLER Header File
 */

#ifndef EMERALD_FACTION_HEADER
#define EMERALD_FACTION_HEADER

#define FACTION_HANDLER "/d/Emerald/sys/global/faction_handler"

#define ADD_FACTION(p,g,a) FACTION_HANDLER->add_faction(p,g,a)
#define QUERY_FACTION(p,g) FACTION_HANDLER->query_faction(p,g)

/*
 * Default Faction Rankings Based on a -100 to 100 Scale
 * See the doc on the faction handler for more detailed
 * explanation on what each rank means.
 */
#define FACRANK_KOS                 -100
#define FACRANK_KILLALERT           -80
#define FACRANK_SHOUTGUARDS         -60
#define FACRANK_SILENTALERT         -40
#define FACRANK_COMPLAIN            -1
#define FACRANK_QUESTALLOW          11
#define FACRANK_FRIENDLY            31
#define FACRANK_BESTFRIEND          51
#define FACRANK_HEROADMIRE          71
#define FACRANK_HEROROYAL           86

/*
 * Default Penalties/Bonuses for certain actions based on -100 to 100 Scale
 * See the doc on the faction handler for a more detailed explanation of
 * each value.
 */
#define FACACTION_KILLPUBLIC        -40
#define FACACTION_KILLNPC           -15
#define FACACTION_SMALLANNOY        -1
#define FACACTION_BIGANNOY          -4
#define FACACTION_SMALLHELP          1
#define FACACTION_BIGHELP            4
#define FACACTION_KILLENEMYNPC       15
#define FACACTION_KILLENEMYPUBLIC    40

/*
 * Faction Group Name Definitions: City of Avular
 */

#define FG_AVULAR_CITIZENS            "AvularCitizens"
#define FG_AVULAR_MERCHANTS           "AvularMerchants"
#define FG_AVULAR_MAGES		      "AvularMages"
#define FG_AVULAR_GUARDS              "AvularGuards"

/*
 * Faction Group Name Definitions: Temple of Eternity
 */
#define FG_ETEMPLE_CITIZENS           "EternityTempleCitizens"
#define FG_ETEMPLE_GUARDS             "EternityTempleGuards"

/*
 * Faction Group Name Definitions: City of Telberin
 */
#define FG_TELBERIN_GUARDS            "TelberinGuards"
#define FG_TELBERIN_ROYALTY           "TelberinRoyalty"
#define FG_TELBERIN_MERCHANTS         "TelberinMerchants"

#endif

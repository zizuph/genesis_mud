/*                                                *
 *         Titles for the Shadow Union            *
 * Modelled after Mercade's Rockfriend titles     *
 *             Cirion 032196                      *
 *
 * Revisions:
 *   Lucius, Apr 2016: Removed never used Elect code
 *   Lucius, May 2016: Removed never-used titles.
 *   Lucius, Jul 2017: Compacted title defines.
 *
 *
 * Everyone with SS_OCCUP >= MAX_SS_OCCUP
 * will get the maximum title.
 */
#define MAX_SS_OCCUP	205

#define BAD_TITLE       "Lesser Warrior of the Shadow Union"
#define GOOD_TITLE      "Pride of the Shadow Union"
#define GURU_TITLE      "K'miasil Tornu"

#define TEAM_TITLE      "Grim Crusader of the Shadow Union"

#define UNION_TITLES ({ \
      "Union Neophyte",				\
      "Dark Novice",				\
      ({ "Shadow Recruit", 			\
	 "Shadow Convert" }),			\
      ({ "Shadow Son", 				\
	 "Shadow Daughter" }),			\
      "Shadow's Floriat",			\
      "Shadow Adherent",			\
      "Shadow Disciple",			\
      "Union Seigneur",				\
      "Disciple of Shadow",			\
      "Shadow Lansquenet",			\
      "Higher Shadow Lansquenet",		\
      "Exalted Shadow Lansquenet",		\
      "Warrior of Shadow",			\
      "Adept Warrior of Shadow",		\
      "High Warrior of Shadow",			\
      "Exalted Warrior of Shadow",		\
      "Intrepid Warrior of the Shadow Union",	\
      "Epinastor of the Shadow Union",		\
      "Shadow Intaglio",			\
      ({ "Shadow's Scion", 			\
	 "Shadow's Favoured Daughter" }),	\
      ({ "Master Warrior of Shadow",		\
	 "Mistress Warrior of Shadow" }),	\
      ({ "High Master Warrior of Shadow",	\
	 "High Mistress Warrior of Shadow" }),	\
      "Legendary Warrior of Shadow",		\
      "Legendary Warrior of Shadow",		\
      "Archetypal Warrior of Shadow",		\
      "Archetypal Warrior of Shadow",		\
      "Potent Shadow of the Abyss",		\
      "Potent Shadow of the Abyss",		\
      "Recondite Spectre of Darkness" 		})

#define U_SPHERE_TITLES ([ \
    SPH_BEAUTY: ({	\
	"Aesthete",				\
	"Fair",					\
	"Flower of Shadow",			\
	"Keeper of the Union Vaults",		\
	"Philosopher",				\
	"Philosophical Warrior of Shadow",	\
	"Poet",					\
	"Purveyor of Beauty",			\
	"Shadow's Necissis",			\
	"Shalyl of the Sublime",		\
	"Warrior-Poet of the Shadow Union",	\
    }),			\
    SPH_DIPLOMACY: ({	\
	"Ambassador of the Shadow Union",	\
	"Diplomat",				\
	"Envoy",				\
	"Liason",				\
	"Liason to the Outlands",		\
	"Liason of the Shadow Union",		\
	({ "Master of Union Diplomacy",		\
	   "Mistress of Union Diplomacy" }),	\
    }),			\
    SPH_DUTY: ({	\
	"Dutiful",				\
	"Dutiful Warrior of Shadows",		\
	"Keeper of the Halls of Shadow",	\
	"Named",				\
	"Packbearer of the Union",		\
	"Servant of the God's Will",		\
	"Servant of the Idrys' Will",		\
	"Union Guild-keeper",			\
    }),			\
    SPH_FLAME: ({	\
	"Diviner of Jazur's Will",		\
	"Empath of Jazur",			\
	"Flame-keeper",				\
	"Herald of the Flame",			\
	"Keeper of the Flame",			\
	"Mystical",				\
	"Mystic of the Shadow Union",		\
	"Mystical Warrior of Shadow",		\
	"Oracle of the Flame",			\
	"Oracle",				\
	"Soul of the Flame",			\
    }),			\
    SPH_HISTORY: ({	\
	"Chief Archivist of the Union",		\
	"Chronicler of the Shadows",		\
	"Historian of the Union",		\
	"Learned",				\
	"Polemic",				\
	"Polemic Scribe of Unity",		\
	"Recondite Scholar of Shadows",		\
	"Scholar",				\
	"Watcher of the Hours",			\
    }),			\
    SPH_INQUISITION: ({	\
	"Inquisitor of the Union",		\
	"Just",					\
	({ "Master of Inquisition",		\
	   "Mistress of Inquisition" }),	\
	"Questioner",				\
	"Questioner of the Shadow Union",	\
	"Righteous",				\
	"Seeker of the God's Truth",		\
	"Seeker of the Idrys' Truth",		\
	"Shadow's Inquest",			\
    }),			\
    SPH_INTEL: ({	\
	"Agent of Shadow",			\
	"Dark Eye Of Shadows",			\
	"Eye of the Shadow Union",		\
	({ "Master of Secrets",			\
	   "Mistress of Secrets" }),		\
	"One who Watches",			\
	"Shadow's Intrigue",			\
	"Shadow's Scrutiny",			\
	"Vigilant",				\
	"Vigilant Warrior of Shadows",		\
	"Watchful",				\
    }),			\
    SPH_ISOLATION: ({	\
	"Austere Warrior of Shadow",		\
	"Eremite",				\
	"Reclusive Warrior of Shadow",		\
	"Shadow Pariah",			\
	"Shadow Recluse",			\
	"Shadow Warrior Emeritus",		\
	"Union Ascetic",			\
    }),			\
    SPH_MENTOR: ({	\
	"Erudite",				\
	"Forge of Unity",			\
	"Instructor of Shadow",			\
	"Keeper of Shadow Novices",		\
	"Mentor of the Shadow Union",		\
	"Mentor",				\
	"Prelector of the Union",		\
	"Wise",					\
    }),			\
    SPH_PROTECTION: ({	\
	"Defender of the Flame",		\
	"Defender of Sybarus",			\
	"Guardian of the Flame",		\
	"Guardian of Sybarus",			\
	"Protector of Shadows",			\
	"Protector of Sybarus",			\
	"Shadow's Scourge",			\
	"Vigilant",				\
	"Zealot",				\
	"Zealous",				\
    }),			\
    SPH_TRAINING: ({	\
	"Trainee of Shadow",			\
	"Shadow Initiate",			\
	"Shadow Novice",			\
	"Student of Unity",			\
    }),			\
    SPH_VENGEANCE: ({	\
	"Avenger of Shadows",			\
	"Feared",				\
	"Righteous",				\
	({ "Master of Shadow Zealots",		\
	   "Mistress of Shadow Zealots" }),	\
	"Shadow Fist of the Union",		\
	"Shadow's Vengeance",			\
	"Vengeful Hand of Zaren",		\
	"Wrath of Zaren",			\
    }),			\
    SPH_VOICE: ({	\
	"Beloved of the Flari",			\
	"Eloquent",				\
	"Mellifluous Voice of Unity",		\
	"Speaker",				\
	"Speaker of the Union",			\
	"Voice",				\
	"Voice of the Elders",			\
	"Voice of the Shadow Union",		\
	"Voice of Unity",			\
    }), 		\
    SPH_WEAPONRY: ({	\
	({ "Blade Master of the Union",		\
	   "Blade Mistress of the Union" }),	\
	"Dagger of Shadows",			\
	"Honed",				\
	"Shadow's Blade",			\
	"Shadow's Edge",			\
	"Sharp",				\
	({ "Union Master at Arms",		\
	   "Union Mistress at Arms" }),		\
	"Weapons Master of the Union",		\
    }), \
])

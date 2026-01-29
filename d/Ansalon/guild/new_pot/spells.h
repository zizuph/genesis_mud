#ifndef _POT_SPELLS_H
#define _POT_SPELLS_H

#define POT_SPELL_DIR	"/d/Ansalon/guild/new_pot/spells/"

#define PIDENTIFY_ID	(1)
#define PHEAL_ID	(1 << 1)
#define PBLIND_ID	(1 << 2)
#define PSLOW_ID	(1 << 3)
#define PTELL_ID	(1 << 4)
#define PSCRY_ID	(1 << 5)
#define PRESTORE_ID	(1 << 6)
#define PALIGN_ID	(1 << 7)
#define PCURSE_ID	(1 << 8)
#define PBLESS_ID	(1 << 9)
#define PMIRAGE_ID	(1 << 10)
#define PGEM_ID		(1 << 11)
#define PEYES_ID	(1 << 12)
#define PPAIN_ID	(1 << 13)
#define PHAMMER_ID	(1 << 14)
//#define PDRAIN_ID	(1 << 15)
#define PHEARING_ID	(1 << 16)
#define PTALON_ID	(1 << 17)
#define PSUMMON_ID	(1 << 18)
//#define PIMPRECATE_ID	(1 << 19)
#define PPLANESWALK_ID	(1 << 20)
#define PSCOURGE_ID	(1 << 21)

#define SPELL_LIST ({		\
    PIDENTIFY_ID, "pidentify",	\
        PHEAL_ID, "pheal",	\
       PBLIND_ID, "pblind",	\
        PSLOW_ID, "pslow",	\
        PTELL_ID, "ptell",	\
        PSCRY_ID, "pscry",	\
     PRESTORE_ID, "prestore",	\
       PALIGN_ID, "palign",	\
       PCURSE_ID, "pcurse",	\
       PBLESS_ID, "pbless",	\
         PGEM_ID, "pgem",	\
        PEYES_ID, "peyes",	\
        PPAIN_ID, "ppain",	\
      PHAMMER_ID, "phammer",	\
     PHEARING_ID, "phearing",	\
       PTALON_ID, "ptalon",	\
      PSUMMON_ID, "psummon",	\
  PPLANESWALK_ID, "pplaneswalk",\
     PSCOURGE_ID, "pscourge",	\
     PMIRAGE_ID, "pmirage"	\
})
/*
 * Deprecated Spells:
 *

     PIMPRECATE_ID, "pimprecate",	\
     PDRAIN_ID, "pdrain",	\
 */

#define BLESS_ID	"pot_bless_id"
#define BLIND_ID	"pot_blind_id"
#define SLOW_ID		"pot_slow_id"
#define PAIN_ID		"pot_pain_id"
#define PARA_ID		"pot_para_id"
#define EYES_ID		"pot_eyes_id"
#define HAMMER_ID	"pot_hammer_id"
#define HEARING_ID	"pot_hearing_id"
#define DRAGON_ID	"pot_summon_id"
#define IMPRECATE_ID	"pot_imprecate_id"
#define SCOURGE_ID	"pot_scourge_id"

#define BLESS_OBJ	(POT_SPELL_DIR + "obj/pbless")
#define BLIND_OBJ	(POT_SPELL_DIR + "obj/pblind")
#define SLOW_OBJ	(POT_SPELL_DIR + "obj/pslow")
#define PAIN_OBJ	(POT_SPELL_DIR + "obj/ppain")
#define PARA_OBJ	(POT_SPELL_DIR + "obj/paranoia")
#define EYES_OBJ	(POT_SPELL_DIR + "obj/peyes")
#define HAMMER_OBJ	(POT_SPELL_DIR + "obj/phammer")
#define HEARING_OBJ	(POT_SPELL_DIR + "obj/phearing")
#define DRAGON_OBJ	(POT_SPELL_DIR + "obj/psummon")
#define IMPRECATE_OBJ	(POT_SPELL_DIR + "obj/pimprecate")

#define SPELLS_UPDATED  1
#define NEW_SPELLS      2
#define GOT_SPELL       4
#define SPELLS_REVOKED  8

#endif /* _POT_SPELLS_H */

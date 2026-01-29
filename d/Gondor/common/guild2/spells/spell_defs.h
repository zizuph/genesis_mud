#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define MORGUL_S_SPELL_FAIL    "A power greater than the Dark Lord prevents you from casting the spell.\n"
#define MORGUL_I_SPELL_POWER		"_morgul_i_spell_power"

#define MORGUL_S_DOLLOST_POISON 	(MORGUL_POTIONS + "dollost_poison")
#define MORGUL_S_DOLLOST_POISON_NAME 	"_dollost_poison_effect"

#define MORGUL_S_BERICHELKH_POISON 	(MORGUL_POTIONS + "berichelkh_poison")
#define MORGUL_S_BERICHELKH_POISON_NAME "_berichelkh_poison_effect"

#define MORGUL_S_CORCOSUNK_EFFECT	(MORGUL_SPELL_OBJS + "corcosunk_effect")

#define MORGUL_S_MORTIRIO_OBJECT 	(MORGUL_SPELL_OBJS + "mortirio_ob")
#define MORGUL_O_MORTIRIO_OBJECT 	"_Morgul_o_mortirio_object"
#define MORGUL_S_MORTIRIO_SHADOW 	(MORGUL_SPELL_OBJS + "mortirio_shadow")
#define MORGUL_S_BLACK_BREATH		(MORGUL_POISONS + "black_breath")
#define MORGUL_S_MORGURTH_EFFECT 	(MORGUL_SPELL_OBJS + "morgurth_effect")
#define MORGUL_S_MORGURTH_EFFECT_NAME 	"_morgurth_potion_effect"
#define MORGUL_S_ARHAL_EFFECT		(MORGUL_SPELL_OBJS + "arhal_effect")
#define MORGUL_S_LOMINEN_EFFECT		(MORGUL_SPELL_OBJS + "lominen_effect")
#define MORGUL_I_SULAMBAR_RES		"_morgul_i_sulambar_res"
#define MORGUL_S_SULAMBAR_POISON	(MORGUL_POISONS + "sulambar_poison")
#define MORGUL_S_NENAMARTH_EFFECT	(MORGUL_SPELL_OBJS + "nenamarth_effect")
#define MORGUL_S_NENAMARTH_EFFECT_NAME	"_nenamarth_potion_effect"
#define MORGUL_S_NENNAUR_EFFECT		(MORGUL_SPELL_OBJS + "nennaur_effect")
#define MORGUL_S_NENNAUR_EFFECT_NAME	"_nennaur_potion_effect"
#define MORGUL_I_NO_SUMMON_STEED	"_morgul_i_no_summon_steed"
#define MORGUL_O_STEED				"_morgul_o_steed"
#define MORGUL_S_NARUSSE_SHADOW		(MORGUL_SPELL_OBJS + "narusse_sh")
#define MORGUL_S_BRAGOLLACH_EFFECT		(MORGUL_SPELL_OBJS + "bragollach_effect")
#define MORGUL_S_BRAGOLLACH_EFFECT_NAME         "_bragollach_potion_effect"
#define MORGUL_S_ASHES				(MORGUL_SPELL_OBJS + "ashes")

/*
 * The leftovers of these 'organs' are used explicitly as ingredient.
 * Other leftovers may be used irrespective of their organ type.
 */
#define MORGUL_SPECIFIC_LEFTOVERS ({ "skull", "eye" })

/*
 * Level	Spell
 *     0	palanquendo
 *     1	mortirio
 *     3	naro
 *     4	arhalgul
 *     5	dramalgos
 *     7	faugoroth
 *     8   sauthacuith
 *     9	ringurth
 *    11	dollost
 *    12	ephessul
 *    13	naro
 *    14	thunaur
 *    15	nifarist
 *    16	gostangwedh
 *    17	artirith
 *    18	crabandir
 *    19	morthul
 *    21	sulambar
 *    23	naro
 *    25	yalarochrama
 */
#define MS_ARHAL_MIN  4
#define MS_ARTIR_MIN 17
#define MS_CRABA_MIN 18
#define MS_DOLLO_MIN 11
#define MS_DRAMA_MIN  5
#define MS_EPHES_MIN 12
#define MS_FAUGO_MIN  7
#define MS_GOSTA_MIN 16
#define MS_MORTH_MIN 19
#define MS_MORTI_MIN  1
#define MS_NARO1_MIN  3
#define MS_NARO2_MIN 13
#define MS_NARO3_MIN 23
#define MS_NARUS_MIN 10
#define MS_NIFAR_MIN 15
#define MS_OREKI_MIN  2
#define MS_PALAN_MIN  0
#define MS_RINGU_MIN  9
#define MS_SAUTH_MIN  8
#define MS_SULAM_MIN 21
#define MS_THUNA_MIN 14
#define MS_YALAR_MIN 25

/* added 2 to these times since the builtin delay of 2 is gone
 * gnadnar 5 feb 98
 */
#define MS_ARHAL_TIME 12
#define MS_ARTIR_TIME 12
#define MS_CRABA_TIME 17
#define MS_DOLLO_TIME  7
#define MS_DRAMA_TIME  2
#define MS_EPHES_TIME  7
#define MS_FAUGO_TIME  2
#define MS_GOSTA_TIME 12
#define MS_MORTH_TIME  3
#define MS_MORTI_TIME 12
#define MS_NARO_TIME  12
#define MS_NARUS_TIME 17
#define MS_NIFAR_TIME 12
#define MS_OREKI_TIME  2
#define MS_PALAN_TIME  5
#define MS_RINGU_TIME  7
#define MS_SAUTH_TIME 17
#define MS_SULAM_TIME 12
#define MS_THUNA_TIME  2
#define MS_YALAR_TIME 17


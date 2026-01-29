//
// deities.h
//
// * Lucius Jun 2009: Much cleanup, re-working and blessings addition.
//
#ifndef __AVENIR_DEITIES_H__
#define __AVENIR_DEITIES_H__
/*
 * Various altar states.
 */
#define ALTAR_IS_BLOODY		"_altar_is_bloody"
#define ALTAR_IS_BROKEN		"_altar_is_broken"
#define ALTAR_IS_DEFILED	"_altar_is_defiled"
#define ALTAR_IS_OCCUPIED	"_altar_is_occupied"
#define ALTAR_IS_OFFERING	"_altar_is_offering"
/*
 * Props set in players
 */
#define I_MADE_OFFERING		"_live_i_made_offering"
#define I_MADE_BLOOD_OFFERING	"_live_i_made_blood_offering"
#define I_DRANK_WITH_SYBARUN_GOD "_live_i_drank_with_Sybarun_God"
/*
 * Handle various 'offering' object defines.
 */
#define OFFERING_FOR(X)		"__offering_for_" + (X)
/*
 * This prop will make an object acceptable at all altars.
 */
#define UNIVERSAL_OFFERING	OFFERING_FOR("Universal")
/*
 * The altars test for these prop for alternative offering functions
 */
#define SPECIAL_OFFERING	OFFERING_FOR("Special")
/*
 * Currently used defines to denote which Idrys
 * this item is a suitable offering for.
 */
#define ACLOLTHAYR_OFFERING	OFFERING_FOR("aclolthayr")
#define CAHOR_OFFERING		OFFERING_FOR("cahor")
#define HIZARBIN_OFFERING	OFFERING_FOR("hizarbin")
#define JAZUR_OFFERING		OFFERING_FOR("jazur")
#define MIZRUN_OFFERING		OFFERING_FOR("mizrun")
#define NITIKAS_OFFERING	OFFERING_FOR("nitikas")
#define SACHLUPH_OFFERING	OFFERING_FOR("sachluph")
#define SAIR_OFFERING		OFFERING_FOR("sair")
#define SALILUS_OFFERING	OFFERING_FOR("salilus")
#define SCHLACHLIL_OFFERING	OFFERING_FOR("schlachlil")
#define SISERA_OFFERING		OFFERING_FOR("sisera")
/*
 * Idrys which do no currently have useable altars or
 * have any blessed items in their name.
 */
#if 0 /* Unused */
#define AZAUPH_OFFERING		OFFERING_FOR("azauph")
#define BUCAPHI_OFFERING	OFFERING_FOR("bucaphi")
#define HAHABI_OFFERING		OFFERING_FOR("hahabi")
#define MASCARVIN_OFFERING	OFFERING_FOR("mascarvin")
#define NANTUR_OFFERING		OFFERING_FOR("nantur")
#define PLALGUS_OFFERING	OFFERING_FOR("plalgus")
#define SABRUS_OFFERING		OFFERING_FOR("sabrus")
#define SIALUL_OFFERING		OFFERING_FOR("sialul")
#define TACRITAN_OFFERING	OFFERING_FOR("tacritan")
#define TABRIS_OFFERING		OFFERING_FOR("tabris")
#define TAROB_OFFERING		OFFERING_FOR("tarob")
#define THAGRINUS_OFFERING	OFFERING_FOR("thagrinus")
#define ZAHUN_OFFERING		OFFERING_FOR("zahun")
#define ZAREN_OFFERING		OFFERING_FOR("zaren")
#define ZEFFAR_OFFERING		OFFERING_FOR("zeffar")
#define ZIZUPH_OFFERING		OFFERING_FOR("zizuph")
#endif /* UNUSED */

/*
 * Blessing properties for players / npc's.
 * These are "minute" values.
 */
#define BLESSING_SHORT		10
#define BLESSING_NORMAL		30
#define BLESSING_LONG		60

#define IDRYS_BLESSINGS		"__idrys_blessings_map"
/*
 * Add a blessing to 'who', 'for' which idrys?
 */
#define ADD_BLESSING(who, for)	(who)->add_prop(IDRYS_BLESSINGS, \
    (who->query_prop(IDRYS_BLESSINGS) ?: ([ ])) + ([ for : time() ]))
/*
 * Remove a blessing to 'who', 'for' which idrys? 
 * Should never really be necessary.
 */
#define REM_BLESSING(who, for)	(who)->add_prop(IDRYS_BLESSINGS, \
    m_delete(who->query_prop(IDRYS_BLESSINGS), for))
/*
 * Check if 'who' has had a blessing 'for' which idrys.
 * Doesn't check if the blessing is still "valid".
 */
#define CHECK_BLESSING(who, for) \
    (!m_sizeof(who->query_prop(IDRYS_BLESSINGS)) ? 0 : \
	who->query_prop(IDRYS_BLESSINGS)[for])
/*
 * Check for a still valid blessing to 'who', 'for' which idrys.
 * 'val' is how long ago to check for in minutes.
 */
#define VALID_BLESSING(who, for, val) \
    (!m_sizeof(who->query_prop(IDRYS_BLESSINGS)) ? 0 : \
	(time() - who->query_prop(IDRYS_BLESSINGS)[for]) <= \
	(val * 60))


#endif /* __AVENIR_DEITIES_H__ */

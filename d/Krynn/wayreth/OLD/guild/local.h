/*
 * Include file for the WoHS guild
 */

#ifndef _WOHS_DEF
#define _WOHS_DEF

/*
 *  Guild object add_name's
 */
#define GUILD_NAME		"Wizards of High Sorcery"
#define GUILD_TYPE	        "magic"
#define GUILD_OBJECT		"_wohs_magic_robe_"
#define SPELL_BOOK              "_wohs_spell_book_"
#define TESTING_STAFF		"_wohs_staff_of_testing_"
#define ACCEPT_PARALYZE_NAME    "_wohs_accept_paralyze_"

/*
 *  Guild props
 */
#define WOHS_S_TEACHER          "_wohs_s_teacher"
#define WOHS_I_GOT_INTRO        "_wohs_i_got_intro"
#define WOHS_AM_KNOWN           "_wohs_am_known"
#define TEST_RESULT             "_wohs_i_test_result"
#define WOHS_TEST_CONTROL       "_wohs_o_test_control"

#define WOHS_SUB		"wohs_subloc"

/*
 * These values for the TEST_RESULT prop determine the results
 * of the end of the Test sequence
 */

#define TEST_SUCCESS		1
#define TEST_SUCCESS_GIFT	2
#define TEST_FAIL_DEMOTE	3
#define TEST_FAIL_DIE	        4
#define TEST_FAIL_BANISH	5

#define INTERACTIVE_CON		filter(users(), ADMIN->query_conclave_member)

#define SS_WOHS_LEVEL_MOD       108400
#define SS_WOHS_RANK_PERMIT     108401

#define NPC_NUITARI             WNPC + "nuitari"
#define NPC_LUNITARI            WNPC + "lunitari"
#define NPC_SOLINARI            WNPC + "solinari"
#define WOHS_CHARM              GOBJ + "charm"

#define ADMIN                   "/d/Krynn/wayreth/guild/admin/admin"
#define ADMINFILE               "/d/Krynn/wayreth/guild/admin/ADMINSAVE"
#define ROBEBASE                "/d/Krynn/wayreth/guild/obj/robe_base"
#define ACCEPT_PARALYZE         "/d/Krynn/wayreth/guild/obj/accept_paralyze"
#define WOHS_STAFF_OF_TESTING	"/d/Krynn/wayreth/guild/obj/staff_of_testing"

#define WOHS_CMD_WIZARD        ("/d/Krynn/wayreth/guild/obj/wohs_cmd_wizard")
#define WOHS_CMD_CONCLAVE      ("/d/Krynn/wayreth/guild/obj/wohs_cmd_conclave")
#define WOHS_CMD_NORMAL        ("/d/Krynn/wayreth/guild/obj/wohs_cmd_normal")

#define TRUE_RACES      ({ "elf","half-elf","human" })

#define APPRENTICE_AS_M_TITLES  ({ "Fresh Tyro of Sorcery", \
				   "Minor Initiate of Sorcery", \
				   "Initiate of Sorcery", \
				   "Devoted Initiate of Sorcery", \
				   "Lesser Novice of Sorcery", \
				   "Novice of Sorcery", \
				   "Devoted Novice of Sorcery", \
				   "Experienced Novice of Sorcery", \
                                   "Lesser Student of Sorcery", \
                                   "Student of Sorcery", \
                                   "Devoted Student of Sorcery", \
                                   "Experienced Student of Sorcery" })

#define APPRENTICE_AS_F_TITLES  ({ "Fresh Tyro of Sorcery", \
				   "Minor Initiate of Sorcery", \
				   "Initiate of Sorcery", \
				   "Devoted Initiate of Sorcery", \
				   "Lesser Novice of Sorcery", \
				   "Novice of Sorcery", \
				   "Devoted Novice of Sorcery", \
				   "Experienced Novice of Sorcery", \
                                   "Lesser Student of Sorcery", \
                                   "Student of Sorcery", \
                                   "Devoted Student of Sorcery", \
                                   "Experienced Student of Sorcery" })

/* Old titles
#define APPRENTICE_AS_F_TITLES  ({ "apprentice", \
				   "initiate", \
				   "student of Magic", \
				   "apprentice of Magic", \
				   "apprentice Magician", \
				   "Magician", \
				   "apprentice Sorceress", \
				   "Sorceress" })
				   */

#define HEAD_TITLE              "Grand Master of the Tower of Wayreth"
#define WHITE_M_CONCLAVE_TITLE  "Master of the Order of the White Robes"
#define BLACK_M_CONCLAVE_TITLE  "Master of the Order of the Black Robes"
#define RED_M_CONCLAVE_TITLE    "Master of the Order of the Red Robes"
#define WHITE_F_CONCLAVE_TITLE  "Mistress of the Order of the White Robes"
#define BLACK_F_CONCLAVE_TITLE  "Mistress of the Order of the Black Robes"
#define RED_F_CONCLAVE_TITLE    "Mistress of the Order of the Red Robes"

#define WIZARD_BLACK_F_AS_TITLES(o)     ({ "Lesser " + o + "Wizard", \
		   "Wizard of the Ninth " + o + "Circle", \
		   "Wizard of the Eighth " + o + "Circle", \
		   "Wizard of the Seventh " + o + "Circle", \
		   "Wizard of the Sixth " + o + "Circle", \
		   "Wizard of the Fifth " + o + "Circle", \
		   "Wizard of the Fourth " + o + "Circle", \
		   "Wizard of the Third " + o + "Circle", \
		   "Wizard of the Second " + o + "Circle", \
		   "Wizard of the First " + o + "Circle", \
		   "Greater " + o + "Wizard", \
		   o + "High Wizard", \
		   "High Mage of the Ninth " + o + "Circle", \
		   "High Mage of the Eighth " + o + "Circle", \
		   "High Mage of the Seventh " + o + "Circle",\
		   "High Mage of the Sixth " + o + "Circle", \
		   "High Mage of the Fifth " + o + "Circle", \
		   "High Mage of the Fourth " + o + "Circle", \
		   "Trimorte", \
		   "Sister to Darkness", \
		     "Blackmage" })

#define WIZARD_BLACK_M_AS_TITLES(o)	({ "Lesser " + o + "Wizard", \
		   "Wizard of the Ninth " + o + "Circle", \
		   "Wizard of the Eighth " + o + "Circle", \
		   "Wizard of the Seventh " + o + "Circle", \
		   "Wizard of the Sixth " + o + "Circle", \
		   "Wizard of the Fifth " + o + "Circle", \
		   "Wizard of the Fourth " + o + "Circle", \
		   "Wizard of the Third " + o + "Circle", \
		   "Wizard of the Second " + o + "Circle", \
		   "Wizard of the First " + o + "Circle", \
		   "Greater " + o + "Wizard", \
		   o + "High Wizard", \
		   "High Mage of the Ninth " + o + "Circle", \
		   "High Mage of the Eighth " + o + "Circle", \
		   "High Mage of the Seventh " + o + "Circle",\
		   "High Mage of the Sixth " + o + "Circle", \
		   "High Mage of the Fifth " + o + "Circle", \
		   "High Mage of the Fourth " + o + "Circle", \
		   "Trimorte", \
		   "Brother to Darkness", \
		     "Blackmage" })

#define WIZARD_AS_TITLES(o)     ({ "Lesser " + o + "Wizard", \
		   "Wizard of the Ninth " + o + "Circle", \
		   "Wizard of the Eighth " + o + "Circle", \
		   "Wizard of the Seventh " + o + "Circle", \
		   "Wizard of the Sixth " + o + "Circle", \
		   "Wizard of the Fifth " + o + "Circle", \
		   "Wizard of the Fourth " + o + "Circle", \
		   "Wizard of the Third " + o + "Circle", \
		   "Wizard of the Second " + o + "Circle", \
		   "Wizard of the First " + o + "Circle", \
		   "Greater " + o + "Wizard", \
		   o + "High Wizard", \
		   "High Mage of the Ninth " + o + "Circle", \
		   "High Mage of the Eighth " + o + "Circle", \
		   "High Mage of the Seventh " + o + "Circle",\
		   "High Mage of the Sixth " + o + "Circle", \
		   "High Mage of the Fifth " + o + "Circle", \
		   "High Mage of the Fourth " + o + "Circle", \
		   "High Mage of the Third " + o + "Circle", \
		   "High Mage of the Second " + o + "Circle", \
		     "High Mage of the First " + o + "Circle" })

#define HEAD_LEVEL              100
#define CONCLAVE_LEVEL          99

#define TYPE_APPRENTICE         "apprentice"
#define TYPE_WHITE              "white"
#define TYPE_RED                "red"
#define TYPE_BLACK              "black"

#define BIT_GROUP               3
#define BIT_BIT1                6
#define BIT_BIT2                7
#define BIT_BIT3                8

#define IS_BANNED(x)            (ADMIN->check_banned(x) != 0)
#define IS_CONCLAVE(x)          (ADMIN->query_conclave_member(x))
#define IS_MEMBER(x)            (ADMIN->query_wohs_member(x))

#define THIS_GUILD(x)           (x->query_guild_name_occ() == GUILD_NAME)
#define GUILDMASTERS            ({"rastlin", "belize", "karath",\
                                       "kentari"})
#define VALID_RACE(x)           ((member_array(x->query_race_name(), \
                                               TRUE_RACES) == -1) ? 0 : 1)
#define TEACHER(x)              (x->query_prop(WOHS_S_TEACHER))
#define ADD_MEMBER(x)           (ADMIN->add_wohs_member(x))

#define GUILD_ALLOW_WIELD       ({ "/d/Krynn/wayreth/guild/obj/staff", \
				})

#define GUILD_ALLOW_WEAR        ({ "/d/Krynn/wayreth/guild/black/robe", \
				   "/d/Krynn/wayreth/guild/red/robe", \
				   "/d/Krynn/wayreth/guild/white/robe", \
                                   "/d/Emerald/common/marriage/ring", \
            "/d/Krynn/common/armours/herb_gloves", \
            "/d/Krynn/solace/new_village/obj/wise_object", \
            "/d/Calia/sea/objects/mermaid_ring", \
            "/d/Gondor/common/obj/ithilien_badge", \
				})

/* For the ADMINSAVE.o file, the structure of gMembers */

#define ASM_APPRENTICE          0
#define ASM_TYPE                1
#define ASM_STARTING_ROOM       2
#define ASM_DESTINATIONS        3
#define ASM_REWARD	        4
#define ASM_REWARDER	        5

#endif _WOHS_DEF





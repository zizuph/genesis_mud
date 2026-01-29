#ifndef _MORGUL_SPELL_DEFS_H
#define _MORGUL_SPELL_DEFS_H

#include <tasks.h>
#include <ss_types.h>

#define MORGUL_SPELL_DIR    "/d/Gondor/common/guild2/newspells/"
#define GENESIS_SPELL_DIR    "/d/Genesis/newmagic/"

#define SPELL_TELL    (GENESIS_SPELL_DIR + "spells/tell")
#define SPELL_BOLT    (GENESIS_SPELL_DIR + "spells/bolt")
#define SPELL_IDENTIFY   (GENESIS_SPELL_DIR + "spells/identify")

#define SPELL_INHERIT   (MORGUL_SPELL_DIR +"spell_inherit")
#define SPELL_INHERIT_TEST	  (MORGUL_SPELL_DIR +"spell_inherit2")
#define SPELL_OBJECT    (GENESIS_SPELL_DIR + "spell_effect_object")
#define SPELL_LIB       (GENESIS_SPELL_DIR + "spell")
#define SPELL_RESIST    (MORGUL_SPELL_DIR + "resist")

#define SPELL_OBJ_DIR      MORGUL_SPELL_DIR + "obj/"


#define MORGUL_S_MORTHUL_TGT  "_Morgul_Morthul_Orb_Target_"
#define MORGUL_O_MORTHUL_ORB  (SPELL_OBJ_DIR + "shadow_orb")

#define MORGUL_I_SULAMBAR_RES "_morgul_i_sulambar_res"
#define CRABANDIR_SH    SPELL_OBJ_DIR+ "crabandir_sh.c"
#define STEED_ROOM      SPELL_OBJ_DIR + "steed_room"
#define STEED           SPELL_OBJ_DIR + "steed"
#define RESISTANCE_MODIFIER 0

/*
 * Level        Spell
 *     0        palanquendo
 *     1        mortirio
 *     2        orekir        // NEW 24-Sept-2007, Opened:
 *     3        naro
 *     4        arhalgul
 *     5        dramalgos
 *     7        faugoroth
 *     8        sauthacuith
 *     9        ringurth
 *    10        narusse
 *    11        dollost
 *    12        ephessul
 *    13        naro
 *    14        thunaur
 *    15        nifarist
 *    16        gostangwedh
 *    17        artirith
 *    18        crabandir
 *    19        morthul
 *    21        sulambar
 *    23        naro
 *    25        yalarochrama
 */

/*
 *If you correct these values don't forget checking add_morgul_spells
 *in spell_obj.c
 */
#define MS_PALAN_MIN  0
#define MS_MORTI_MIN  1
#define MS_OREKI_MIN  2
#define MS_NARO1_MIN  3
#define MS_ARHAL_MIN  4
#define MS_DRAMA_MIN  5
#define MS_FAUGO_MIN  7
#define MS_SAUTH_MIN  8
#define MS_RINGU_MIN  9
#define MS_NARUS_MIN 10
#define MS_DOLLO_MIN 11
#define MS_EPHES_MIN 12
#define MS_NARO2_MIN 13
#define MS_THUNA_MIN 14
#define MS_NIFAR_MIN 15
#define MS_GOSTA_MIN 16
#define MS_ARTIR_MIN 17
#define MS_CRABA_MIN 18
#define MS_MORTH_MIN 19
#define MS_SULAM_MIN 21
#define MS_NARO3_MIN 23
#define MS_YALAR_MIN 25


#endif

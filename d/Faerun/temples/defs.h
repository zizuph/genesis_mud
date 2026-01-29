/*
 * Defs file for Temples
 * Created by Finwe, July 2006
 */
#include "/d/Faerun/sys/paths.h"
#include "/sys/alignment.h"

// Root directory
//#define TEMPLE_DIR         "/d/Faerun/temples/"

// Base files
#define BASE_TEMPLE     (TEMPLE_DIR + "base_temple.c")
#define BASE_EMBLEM     (TEMPLE_DIR + "base_emblem.c")

// Misc defines
#define TOKEN_NAME      "_deity_emblem"

// alignments
#define HOLY            ALIGN_HOLY
#define SAINTLY         ALIGN_SAINTLY
#define BLESSED         ALIGN_BLESSED
#define DEVOUT          ALIGN_DEVOUT
#define GOOD            ALIGN_GOOD
#define SWEET           ALIGN_SWEET
#define NICE            ALIGN_NICE
#define SYMPATHETIC     ALIGN_SYMPATHETIC
#define TRUSTWORTHY     ALIGN_TRUSTWORTHY
#define AGREEABLE       ALIGN_AGREEABLE
#define NEUTRAL         ALIGN_NEUTRAL
#define DISAGREEABLE    ALIGN_DISAGREEABLE
#define UNSYMPATHETIC   ALIGN_UNSYMPATHETIC
#define SINISTER        ALIGN_SINISTER
#define WICKED          ALIGN_WICKED
#define NASTY           ALIGN_NASTY
#define MALEVOLENT      ALIGN_MALEVOLENT
#define BEASTLY         ALIGN_BEASTLY
#define DENOMIC         ALIGN_DEMONIC
#define DAMNED          ALIGN_DAMNED

// min align levels for clubs.
#define AL_GOOD         TRUSTWORTHY
#define AL_NEUTRAL      ALIGN_NEUTRAL
#define AL_EVIL         UNSYMPATHETIC
#define AL_NEUT_GOOD    AGREEABLE
#define AL_NEUT_EVIL    DISAGREEABLE

// Deity Dirs
#define CYRIC_DIR       (TEMPLE_DIR + "cyric/")
#define HELM_DIR        (TEMPLE_DIR + "helm/")
#define ILMATER_DIR     (TEMPLE_DIR + "ilmater/")
#define LATH_DIR        (TEMPLE_DIR + "lathander/")
#define TYMORA_DIR      (TEMPLE_DIR + "tymora/")
#define TYR_DIR         (TEMPLE_DIR + "tyr/")

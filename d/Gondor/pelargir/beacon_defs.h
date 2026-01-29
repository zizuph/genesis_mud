/**************************** a 74-char line ****************************/
/*
 * /d/Gondor/pelargir/beacon_defs.h
 *
 * Copyright (C) August 20, 1998 by Ron Miller (Tyr)
 *
 * These are the def's that recur throughout beacon quest files
 *
 */
 

#pragma strict_types


#define LENS_NAME             "_lighthouse_lens"
#define LENS_FILE             (PELAR_DIR + "obj/lens")
#define LENSBRACKET_FILE      (PELAR_DIR + "obj/lensbracket")

#define MIRROR_NAME           "_lighthouse_mirror"
#define MIRROR_FILE           (PELAR_DIR + "obj/mirror")
#define MIRRORBRACKET_FILE    (PELAR_DIR + "obj/mirrorbracket")

#define LANTERN_NAME          "_pelargir_beacon_lantern"
#define LANTERN_FILE          (PELAR_DIR + "obj/lantern")
#define LANTERNBRACKET_FILE   (PELAR_DIR + "obj/lanternbracket")
#define LANTERN_BRACKET       "_lighthouse_lantern"

#define LAMPROOM              (PELAR_DIR + "docks/lamproom")
#define LUMENDIL_FILE         (PELAR_DIR + "npc/lumendil")
#define OILKEG_FILE           (PELAR_DIR + "obj/oilkeg")

/* possible states of contents of the brackets */
#define NONE_HERE               0
#define LENS_HERE               1
#define LANTERN_HERE            3
#define MIRROR_HERE             5
#define LENS_LANTERN_HERE   (LENS_HERE + LANTERN_HERE)              /*4*/
#define LENS_MIRROR_HERE    (LENS_HERE + MIRROR_HERE)               /*6*/
#define LANTERN_MIRROR_HERE (LANTERN_HERE + MIRROR_HERE)            /*8*/
#define ALL_HERE            (LENS_HERE + LANTERN_HERE + MIRROR_HERE)/*9*/

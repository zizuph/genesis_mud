/*
 *  /d/Faerun/sys/areas.h
 *
 *  Contains all the different domain/area path definitions.
 *  Do not use hardcoded paths in any of the objects, always refer
 *  to a define.
 *
 *  Created by Finwe, July 2014
 */

// FAERUN_DIR is defined in sys/paths.h

/* Area directories */
// Path for High Road between Neverwinter and Waterdeep
#define HIGH_RD_DIR         (FAERUN_DIR + "highroad/")

// Path for Kryptgarden
#define KRYPTG_DIR          (FAERUN_DIR + "kryptg/rooms/")

// Path for Mere of the Dead Men
#define ME_DIR              (FAERUN_DIR + "mere/rooms/")

// Path for Triboar and surrounding area, including Triboar Cut/Path
#define TRIBOAR_DIR         (FAERUN_DIR + "triboar/")

// Path for Red Cliffs, the beach area, and sea leading to Warlocks
#define RED_CLIFFS_DIR      (FAERUN_DIR + "red_cliffs/")
#define RC_BEACH_DIR        (RED_CLIFFS_DIR + "rooms/beach/")
#define RC_SEA_DIR          (RED_CLIFFS_DIR + "rooms/sea/")
#define RC_ISLANDS_DIR      (RED_CLIFFS_DIR + "rooms/islands/")

/* SWORD COAST REGION PATHS */
#define SWORD_COAST_DIR     (FAERUN_DIR + "swordcoast/")

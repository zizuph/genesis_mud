// file name:        /d/Avenir/common/dead/mascarvin/defs.h	
// creator(s):       Lilith, May 2021
// revision history: 
// purpose:          Relative paths and other defines for 
//                   Meet Mascarvin Quest, other defs in dead.h
// note:            
// bug(s):           
// to-do:

#include "/d/Avenir/common/dead/dead.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/macros.h"
#include <math.h>

#define DEBUG(x)    find_living("lilith")->catch_tell("#MASQ# " + x + "\n")

// HOLE is where you gain access to this area
#define HOLE       "/d/Avenir/common/dead/catacombs/crypt_s7"
#define CHALICE     (MASQ + "chalice")
#define MAZE         MASQ + "maze/"
#define PANEL       (MASQ + "spots")
#define PASSAGE     (MASQ + "passage")
#define SKULL       (MAZE + "skull")
#define RESTING     (MASQ + "resting")
#define RAGING      (MASQ + "raging")

// The goddess of death and rebirth herself
#define MASCARVIN   (MASQ + "mascarvin")
// Mascarvin's Magical Flame Rose
#define FLAME_ROSE  (OBJ + "rose_fire")
#define TABLE       (OBJ + "table_goddess")
#define PARA        (OBJ + "paralyze_thief")
#define POISON      (OBJ + "poison_thief")
#define RIPOISON    (OBJ + "poison_rude")

// This one is used for the maze quest.
#define WORD_PROP     "_Avenir_MASQ_maze_words"
// This one is used for the dot pattern room.
#define SAW_PATTERN   "_Avenir_MASQ_saw_pattern"
// Tracking the sequence of events in the player
#define MASQ_SEQ      "_Avenir_Mascarvin_Sequence"
#define BAAAD_MORTAL  "_i_am_baaad_mortal"

#define PARA_ID       "_Mascarvin_thief_paralyze"
#define POISON_ID     "_Mascarvin_thief_poison"
#define RIPO_ID       "_Mascarvin_rude_poison"

// Words on the MAZE room thresholds are gods of the hours
#define WORDS ({ "Sair-Salilus", "Tabris-Zeffar", "Zaren", \
                 "Hahabi-Mizrun", "Plalgus", "Sachluph-Hizarbin", \
				 "Nantur-Thagrinus", "Nitikas-Zahun", "Sabrus", \
                 "Cahor-Tarob", "Tacritan-Zizuph", "Jazur-Sisera"  })

// Alternative words for possible future use to change things up 
// These are the 6 elements and the 6 forms of magic in sybarite lang
#define WORDS2 ({  "t'aeris",  "hla'jeran",  "tsa-dara",  "ilaris", \
                   "m'tenit",  "ry'alt",  "flar-Idrys",  "hl'endh", \
                   "pr'aith",  "chrai'ni", "st'aeris",  "maedon" })





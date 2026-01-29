/* 
*   Half-Giants village in the pass overhauled.
*   /d/Kalad/common/wild/pass/giantpass/
*   Local definition for the Giant recode
*/

#include "/d/Kalad/defs.h"

/* Pathname aliases */
#define PARENT              ("/d/Kalad/common/wild/pass/giants/")
#define LOCAL_LOG_DIR       (PARENT + "logs/")
#define STDIR               (PARENT + "std/")
#define RDIR                (PARENT + "rooms/")
#define KHERB               ("/d/Kalad/common/herbs/")
#define ARM                 (PARENT + "arm/")
#define WEP                 (PARENT + "wep/")
#define OBJ                 (PARENT + "obj/")
#define LIV                 (PARENT + "npc/")

#define GENSPECIALS         ("/d/Genesis/specials/guilds/")
#define M_DEBUG(x)          find_player("meton")->catch_msg("[hgiant] " + x + "\n")

#define GIANTDESC ({"This being looks vaguely human in features, but "\
    + "that is where all similarities end. He stands at least sixteen "\
    + "feet tall and walks more in the fashion of an ape, than as a "\
    + "human.\n",\
    "A sixteen feet tall humanoid, standing like an ape, looking at you "\
    + "with very dull eyes.\n",\
    "This hill giant is a selfish, dimwitted brute that hunt and raid in "\
    + "constant search of food. Its skin are tanned from a life spent "\
    + "beneath the sun.\n",\
    "A hill giant with a light tan skin, with brown hair. It seems "\
    + "to have spent less time out raiding compared to the other hill "\
    + "giants. It is wearing a very dirty hide cloak.\n"})

#define GIANTADVERBS ({"sneaky", "brutal", "malicious", "savage",\
    "malevolent", "scarred", "wicked", "cruel", "evil", "nasty",\
    "ghastly", "horrible", "scary", "fearsome", "massive", "strong",\
    "foul"})

#define WOLFDESC ({"An enormous shaggy wolf. The large size indicates "\
    + "this wolf belongs to the dire family of wolves, a larger and more "\
    + "aggressive variety of the common wolf.\n",\
    "A great shaggy wolf. It seems to be a dire wolf, larger and more "\
    + "aggressive than common wolves.\n",\
    "A wolf, much larger than the common wolves you've seen before. This "\
    + "must be a dire wolf, the larger and more aggressive kind of "\
    + "wolf.\n",\
    "A dire wolf, much greater and much more aggressive than a normal "\
    + "wolf. This creature will certainly not try to avoid eating you.\n"})

#define WOLFITEM ({ARM + "apron", ARM + "bed_erobe",\
    ARM + "bed_skeff", ARM + "collar", ARM + "dress",\
    ARM + "earring", ARM + "gold_chain", ARM + "high-heels",\
    ARM + "pearl_necklace", ARM + "piwafwi", ARM + "silk_skirt",\
    ARM + "silk_tunic", ARM + "silver_pendant", ARM + "tcbelt",\
    ARM + "tgbelt", ARM + "goblin_trainer_armring",\
    ARM + "goblin_armring"})

#define GOBLINDESC ({"A common goblin, covered in filth and possessing "\
    + "scabrous red skin. It glares directly at you with a surprising "\
    + "amount of intelligence in its coal black eyes.\n",\
    "A filthy, scabrous goblin. It glares at you with an unnerving "\
    + "amount of intelligence in its beady red eyes, giving you the "\
    + "impression that perhaps goblins aren't as stupid as most people "\
    + "portray them to be.\n",\
    "A goblin raider, filthy and ready to kill you at a moments notice. "\
    + "You are certain it is looking at you with murderous intent.\n",\
    "A filthy goblin raider, always looking for the next prey. It is "\
    + "ready to rob anyone.\n"})

#define GOBLINADVERBS ({"sneaky", "brutal", "malicious", "savage",\
    "malevolent", "scarred", "wicked", "cruel", "evil", "nasty",\
    "ghastly", "horrible", "scary", "fearsome", "massive", "strong",\
    "foul"})

#define GOBLINWEAPONS ({WEP + "bed_espear.c", WEP + "bed_esword.c",\
    WEP + "bed_m_sword.c", WEP + "bed_ssword.c", WEP + "gg_club.c",\
    WEP + "gclub.c", WEP + "gg_sword.c", WEP + "lm_spear.c",\
    WEP + "lmk_spear.c", WEP + "tgaxe.c"})

#define HEIGHT ({"extremely short","very short","short",\
    "of normal length","tall","very tall","extremely tall"})

#define WIDTH ({"very skinny","skinny","lean","of normal width","plump",\
    "fat","very fat"})
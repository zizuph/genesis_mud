/*
 *  /w/Sparkle/area/city/bank/defs.h
 *  Defs for sparkle bank
 *
 * Created March 2008, by Aeg (Matthew Morin)
 */
 

#include "../defs.h"

#define BANK_ROOM   (BANK_DIR + "room/")
#define BANK_OBJ    (BANK_DIR + "obj/")
#define BANK_NPC    (BANK_DIR + "npc/")


/* Now the actual defines! */
#define TP          this_player()
#define TO          this_object()
#define TI          this_interactive()
#define PO          previous_object()
#define QSW         query_shadow_who()


#define HE_SHE(o)   (o)->query_pronoun()
#define HIS_HER(o)  (o)->query_possessive()
#define HIM_HER(o)  (o)->query_objective()
#define QRACE(o)    (o)->query_race_name()
#define QTRACE(o)   (o)->query_race()
#define ENV(o)      environment(o)
#define E(o)        environment(o)
#include "../defs.h"
/* Abbreviations */

#define TP this_player()
#define TO this_object()
#define POSS TP->query_possessive()
#define PRON TP->query_pronoun()

/* paths */

#define TRAVELLER "/d/Earthsea/travellers/room"
#define CITY "/d/Earthsea/gont/gont_city"
#define CITYROOM CITY+"/rooms"
#define STREET CITYROOM + "/city_street"
#define PALACE CITYROOM+"/palace"
#define WEP CITY+"/wep"
#define ARM CITY+"/arm"
#define OBJ CITY+"/obj"
#define LIV CITY + "/liv"
#define TA_ITEMS "/d/Earthsea/gont/tenalders/obj/items/"
#define CALIA_LINE "/d/Earthsea/ships/calia_line"
#define BEACH_CLIFF "/d/Earthsea/gont/beach/cliff_rooms/cliff01"


#define HARREKKI LIV + "/harrekki.c"
#define F_CLUB WEP + "/f_club.c"
#define SHORT_SWORD WEP + "/g_sword1.c"
#define DAGGER WEP + "/c_dagger"
#define IRON_HELM  ARM + "/iron_helm.c"
#define IRON_PLATE ARM + "/iron_plate.c"
#define LEATHER_HELM ARM + "/leather_helm.c"
#define JERKIN    ARM + "/jerkin.c"
#define IRON_RINGMAIL ARM + "/iron_ringmail.c"
#define BANDANNA ARM + "/bandanna.c"
#define SASH ARM + "/sash.c"
#define CAP ARM + "/sailor_cap.c"
#define CUTLASS WEP + "/cutlass.c"
#define BREECHES ARM + "/breeches.c"
#define MCLOAK ARM + "/cloak.c"
#define MRING ARM + "/ring.c"
#define MDAGGER WEP + "/m_dagger.c"
#define HARMONICA OBJ + "/harmonica.c"
#define SCRAMASAX WEP + "/scramasax.c"


#define GUARD1 LIV + "/guard1"
#define GUARD2 LIV + "/guard2"
#define GUARD3 LIV + "/guard3"
#define GUARD4 LIV + "/guard4"
#define TGUARD1 LIV + "/tguard1"
#define TGUARD2 LIV + "/tguard2"
#define TGUARD3 LIV + "/tguard3"
#define TGUARD4 LIV + "/tguard4"
#define SAILOR1  LIV + "/sailor1"
#define SAILOR2 LIV + "/sailor2"
#define SAILOR3 LIV + "/sailor3"
#define SAILOR4  LIV + "/sailor4"
#define SAILOR5 LIV + "/sailor5"
#define SAILORS (({ SAILOR1, SAILOR2, SAILOR3, SAILOR4,\
SAILOR5 }))

#define PASS_NOT_OK "_pass_not_ok"


#define SHOP_STORE_ROOM  VROOM + "sol_store2"
#define OBJ_S_CREST    "_obj_s_crested"
#define OBJ_S_CREST_INFO "_obj_s_crest_info"
#define OBJ_M_NO_ALTER "_obj_m_no_alter"


#define ADJS             ({ query_crest(), "solamnian" })
#define CRESTS           ({"platinum kingfisher", "deep blue kingfisher",  \
                           "bronze crown", "flaming phoenix",              \
                           "deep blue dolphin", "silver sword",            \
                           "red-brown bison's horn", "platinum rose",      \
                           "platinum dragon", "silver triangle",           \
                           "black rose", "solamnian"})
/*
#define COLOURL          "brown, green, silver, white"
#define GREEN_ING        ({ "angurth", "athelas", "basil", "chervil",      \
                            "clove", "fennel", "green bean",               \
                            "dill", "green onion", "handasse", "hemlock",  \
                            "laurel", "mint", "oregano", "savory",         \
                            "tarragon", "thyme", "tuo" })
#define BROWN_ING        ({ "astaldo", "caraway", "tyelka", "ungolestel" })
#define SILVER_ING       ({ "ithilgil", "curugwath", "madwort",            \
                            "frostheal" })
*/
#define LONG(x)          ("The " + query_crest_desc(x) +                \
                          " You can make out some engraved writing on the "+\
                          "armour, in the common tongue its says:\n" +      \
                          "\"This is a replica of a " + x->short() + ".\"\n\n\t"+\
                          "Signed Bjorn Armstrong of Vingaard Keep.\n")

#define RLONG(x)         ("The " + query_crest_desc(x) +                \
                          " You can make out some engraved writing on the "+\
                          "armour, in the common tongue its says:\n" +      \
                          "\"This is a replica of a " +                  \
                          x->query_prop(OBJ_S_CREST)[0] + ".\"\n\n\t"+\
                          "Signed Bjorn Armstrong of Vingaard Keep.\n")

#define ARM_SMITH        ("/d/Krynn/solamn/vin/npc/bjorn")
#define SHORT(x)        (query_pair(x, 0) +                \
                         "solamnian " + query_true_name(x, 0) + \
                         query_lcrest() )
#define PSHORT(x)       (query_pair(x, 1) +                \
                         "solamnian " + query_true_name(x, 1) + \
                          query_lcrest() )
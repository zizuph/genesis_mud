#define OBJ_S_PAINTED    "_obj_s_painted"
#define OBJ_S_PAINT_INFO "_obj_s_paint_info"
#define ADJS             ({ query_colour(), "gondorian" })
#define COLOUR           ({ "brown", "green", "silver", "dust", "white" })
#define COLOURL          "brown, green, silver, white" 
#define GREEN_ING        ({ "angurth", "athelas", "basil", "chervil",      \
                            "clove", "fennel", "green bean",               \
                            "dill", "green onion", "handasse", "hemlock",  \
                            "laurel", "mint", "oregano", "savory",         \
                            "tarragon", "thyme", "tuo" })
#define BROWN_ING        ({ "astaldo", "caraway", "tyelka", "ungolestel" })
#define SILVER_ING       ({ "ithilgil", "curugwath", "madwort",            \
                            "frostheal" })
#define LONG(x)          ("This " + query_true_name(x, 0) + " has been " + \
                          "painted " + query_colour() + ". A picture " +   \
                          "of a white tree with seven stars above " +      \
                          "marks it with the emblem of Gondor.\n" +        \
                          "Studying it closely, you can tell that " +      \
                          "it used to be a " + x->short() + ".\n")
#define RLONG(x)         ("This " + query_true_name(x, 0) + " has been " + \
                          "painted " + query_colour() + ". A picture " +   \
                          "of a white tree with seven stars above " +      \
                          "marks it with the emblem of Gondor.\n" +        \
                          "Studying it closely, you can tell that " +      \
                          "it used to be a " +                             \
                          x->query_prop(OBJ_S_PAINTED)[1] + ".\n")
#define PLACE            "Gondor"
#define PAINTER         ("/d/Gondor/minas/npc/miriel")
#define SHORT(x)        (query_pair(x, 0) + query_colour() +               \
                         " gondorian " + query_true_name(x, 0) )
#define PSHORT(x)       (query_pair(x, 1) + query_colour() +               \
                         " gondorian " + query_true_name(x, 1) )

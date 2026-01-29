#define OBJ_S_PAINTED    "_obj_s_painted"
#define OBJ_S_PAINT_INFO "_obj_s_paint_info"
#define ADJS             ({ query_colour(), "sybarun" })
#define COLOUR           ({ "red", "green", "purple",})
#define COLOURL          "red, green, purple" 
/* Minerals have been ground to make pigments for paint for millenia */
#define GREEN_ING        ({ "jade", "peridot", "chrysoprase", "emerald" })
					   /* No fire opal--sacred to Sair */
#define RED_ING        ({ "carnelian", "jasper", "ruby", "bloodstone"})
// query_gem_name for violet spinel is spinel and for blue spinel 
// it is spinel_blue
#define PURPLE_ING       ({ "amethyst", "violet spinel", "blue spinel",   \
                            "sapphire" })
#define PURPLE_ID        ({ "amethyst", "spinel", "spinel_blue", "sapphire"})
#define LONG(x)          ("This " + query_true_name(x, 0) + " has been " + \
                          "painted " + query_colour() + " and decorated " +   \
                          "with the golden trefoil of Sybarus." +      \
                          "\n" +        \
                          "Studying it closely, you can tell that " +      \
                          "it used to be a " + x->short() + ".\n")
#define RLONG(x)         ("This " + query_true_name(x, 0) + " has been " + \
                          "painted " + query_colour() + "and decorated " +   \
                          "with the golden trefoil of Sybarus." +      \
                          "\n" +        \
                          "Studying it closely, you can tell that " +      \
                          "it used to be a " +                             \
                          x->query_prop(OBJ_S_PAINTED)[1] + ".\n")
#define PLACE            "Sybarus"
#define PAINTER         ("/d/Avenir/common/outpost/mon/painter")
#define SHORT(x)        (query_pair(x, 0) + query_colour() +               \
                         " sybarun " + query_true_name(x, 0) )
#define PSHORT(x)       (query_pair(x, 1) + query_colour() +               \
                         " sybarun " + query_true_name(x, 1) )

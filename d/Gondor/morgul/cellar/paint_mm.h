#define OBJ_S_PAINTED      "_obj_s_painted"
#define OBJ_S_PAINT_INFO   "_obj_s_paint_info"
#define PLAYER_S_PAINT_ING "_player_s_paint_ing"
#define ADJS               ({ query_colour(), "morgul" })
#define COLOUR             ({ "red", "gold", "dust", "black" })
#define COLOURL            "red, gold, black" 
#define RED_ING            ({ "coccinea", "holly berry", "lothore",          \
                              "myrtleberry", "suranie", "redweed", "seregon" })
#define GOLD_ING           ({ "alfirin", "annalda", "lissuin"  })
#define LONG(x)            ("This " + query_true_name(x, 0) + " has been " + \
                            "painted " + query_colour() + ". A picture " +   \
                            "of the Moon " +    \
                            "disfigured with a ghastly face of death " +     \
                            "marks this armour with the emblem of " +        \
                            "Minas Morgul.\nStudying it closely, you " +     \
                            "can tell that it used to be a " +               \
                            x->short() + ".\n")
#define RLONG(x)           ("This " + query_true_name(x, 0) + " has been " + \
                            "painted " + query_colour() + ". A picture " +   \
                            "of the Moon " +    \
                            "disfigured with a ghastly face of death " +     \
                            "marks this armour with the emblem of " +        \
                            "Minas Morgul.\nStudying it closely, you " +     \
                            "can tell that it used to be a " +               \
                            x->query_prop(OBJ_S_PAINTED)[1] + ".\n")
#define PLACE              "Minas Morgul"
#define SHORT(x)           (query_pair(x, 0) + query_colour() +              \
                            " morgul " + query_true_name(x, 0) )
#define PSHORT(x)          (query_pair(x, 1) + query_colour() +              \
                            " morgul " + query_true_name(x, 1) )
#define PAINTER            (MORGUL_DIR + "npc/gruzgh.c")

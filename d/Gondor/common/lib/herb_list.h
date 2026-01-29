/*
 *	/d/Gondor/common/lib/herb_list.h
 *
 *	Do not include this file!
 *	Do this instead:
 *	string *herbs = HERB_MASTER->query_herbs();
 *	Then use 'herbs' as you would use HERBS when including this file!
 *
 *	Olorin, November 1995
 */
#define HERBS ({ HERB_DIR + "alfirin", \
                 HERB_DIR + "astaldo", \
                 HERB_DIR + "athelas", \
                 HERB_DIR + "attanar", \
                 HERB_DIR + "basil", \
                 HERB_DIR + "blueberry", \
                 HERB_DIR + "blung", \
                 HERB_DIR + "bpotato", \
                 HERB_DIR + "caraway", \
                 HERB_DIR + "catnip", \
                 HERB_DIR + "chervil", \
                 HERB_DIR + "clove", \
                 HERB_DIR + "coccinea", \
                 HERB_DIR + "curugwath", \
                 HERB_DIR + "dill", \
                 HERB_DIR + "fennel", \
                 HERB_DIR + "foxglove", \
                 HERB_DIR + "garlic", \
                 HERB_DIR + "ginger", \
                 HERB_DIR + "gonion", \
                 HERB_DIR + "handasse", \
                 HERB_DIR + "hemlock", \
                 HERB_DIR + "holly", \
                 HERB_DIR + "laurel", \
                 HERB_DIR + "lissuin", \
                 HERB_DIR + "lothore", \
                 HERB_DIR + "marjoram", \
                 HERB_DIR + "mint", \
                 HERB_DIR + "myrtle", \
                 HERB_DIR + "nettle", \
                 HERB_DIR + "oregano", \
                 HERB_DIR + "redweed", \
                 HERB_DIR + "rosemary", \
                 HERB_DIR + "rpotato", \
                 HERB_DIR + "saffron", \
                 HERB_DIR + "sage", \
                 HERB_DIR + "savory", \
                 HERB_DIR + "seregon", \
                 HERB_DIR + "sumac", \
                 HERB_DIR + "suranie", \
                 HERB_DIR + "tarragon", \
                 HERB_DIR + "thyme", \
                 HERB_DIR + "tuo", \
                 HERB_DIR + "tyelka", \
                 HERB_DIR + "ungolestel", \
                 SHIRE_HERB_DIR + "parsley", \
                 SHIRE_HERB_DIR + "pawnrose", \
                 SHIRE_HERB_DIR + "huckleberry", \
                 SHIRE_HERB_DIR + "lianor_berry", \
              })

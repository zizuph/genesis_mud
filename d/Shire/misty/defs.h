/*
 * Defs file for Varian
 *
 * Varian - 2017
 */

#include <std.h>

#define VAR "/w/varian/"

#define HERB_MAX    200
#define HERB_LOOKUP ([ \
    "adildra" :              "/d/Faerun/herbs/herb_files/adildra", \
    "adillyp weed" :         "/d/Shire/common/herbs/adillyp", \
    "alfirin" :              "/d/Gondor/common/herbs/alfirin", \
    "amanita" :              "/d/Krynn/common/herbs/amanita", \
    "amaranth" :             "/d/Faerun/herbs/herb_files/amaranth", \
    "angel tears" :          "/d/Faerun/herbs/herb_files/angel_tears", \
    "angelica" :             "/d/Faerun/herbs/herb_files/angelica", \
    "angeltear" :            "/d/Krynn/common/herbs/angeltear", \
    "angurth" :              "/d/Gondor/common/herbs/angurth", \
    "anna" :                 "/d/Gondor/rhovanion/herbs/anna", \
    "annalda" :              "/d/Gondor/common/herbs/annalda", \
    "argil" :                "/d/Terel/common/herbs/argil", \
    "aromatic cedar" :       "/d/Khalakhor/common/herbs/arom_cedar", \
    "asparagus" :            "/d/Krynn/common/herbs/asparagus", \
    "aspen bark" :           "/d/Earthsea/herbs/herb_files/aspen_bark", \
    "astaldo" :              "/d/Gondor/common/herbs/astaldo", \
    "athelas" :              "/d/Gondor/common/herbs/athelas", \
    "athly" :                "/d/Calia/argos/silent_forest/herbs/athly", \
    "attanar" :              "/d/Gondor/common/herbs/attanar", \
    "basil" :                "/d/Gondor/common/herbs/basil", \
    "beach plum" :           "/d/Krynn/common/herbs/bch_plum", \
    "beach willow" :         "/d/Krynn/common/herbs/bch_willow", \
    "beaked sedge" :         "/d/Krynn/common/herbs/bkd_sedge", \
    "beatha" :               "/d/Khalakhor/common/herbs/beatha", \
    "bee balm" :             "/d/Faerun/herbs/herb_files/bee_balm", \
    "belladonna" :           "/d/Avenir/common/herbs/belladonna", \
    "bellarnon" :            "/d/Faerun/herbs/herb_files/bellarnon", \
    "bergamot" :             "/d/Earthsea/herbs/herb_files/bergamot", \
    "bilberry" :             "/d/Shire/common/herbs/bilberry", \
    "black bean" :           "/d/Gondor/common/herbs/bean_black", \
    "black carrot" :         "/d/Gondor/common/herbs/carrot_black", \
    "black currant" :        "/d/Krynn/common/herbs/blk_currant", \
    "black potato" :         "/d/Gondor/common/herbs/bpotato", \
    "black raspberry" :      "/d/Gondor/common/herbs/braspberry", \
    "black rush" :           "/d/Faerun/herbs/herb_files/black_rush", \
    "blackberry" :           "/d/Gondor/common/herbs/blackberry", \
    "blackroot" :            "/d/Shire/common/herbs/blackroot", \
    "blade" :                "/d/Kalad/common/herbs/blade", \
    "blood creep" :          "/d/Avenir/common/herbs/bloodcreep", \
    "bloodfruit" :           "/d/Faerun/herbs/herb_files/bloodfruit", \
    "bloodweed" :            "/d/Kalad/common/herbs/bloodweed", \
    "blue gentian flower" :  "/d/Earthsea/herbs/herb_files/blue_gentian", \
    "blueberry" :            "/d/Gondor/common/herbs/blueberry", \
    "blung" :                "/d/Gondor/common/herbs/blung", \
    "borage" :               "/d/Faerun/herbs/herb_files/borage", \
    "breadroot" :            "/d/Krynn/common/herbs/breadroot", \
    "broad bean" :           "/d/Gondor/common/herbs/bean_fava", \
    "broccoli" :             "/d/Earthsea/herbs/herb_files/broccoli", \
    "brown slime" :          "/d/Krynn/common/herbs/brownslime", \
    "bull kelp" :            "/d/Krynn/common/herbs/bull_kelp", \
    "bunchberry" :           "/d/Krynn/common/herbs/bunchberry", \
    "bur reed" :             "/d/Krynn/common/herbs/bur_reed", \
    "buttercup" :            "/d/Faerun/herbs/herb_files/buttercup", \
    "button mushroom" :      "/d/Faerun/herbs/herb_files/button_mushroom", \
    "calendula" :            "/d/Shire/common/herbs/calendula", \
    "caraway" :              "/d/Gondor/common/herbs/caraway", \
    "carlith" :              "/d/Avenir/common/herbs/carlith", \
    "carolden" :             "/d/Faerun/herbs/herb_files/carolden", \
    "catnip" :               "/d/Gondor/common/herbs/catnip", \
    "cattail" :              "/d/Krynn/common/herbs/cattail", \
    "chantrelle" :           "/d/Krynn/common/herbs/chantrelle", \
    "chartess" :             "/d/Avenir/common/herbs/chartess", \
    "chervil" :              "/d/Gondor/common/herbs/chervil", \
    "chicory" :              "/d/Krynn/common/herbs/chicory", \
    "chives" :               "/d/Shire/common/herbs/chives", \
    "chokecherry" :          "/d/Krynn/common/herbs/chokecherry", \
    "cinquefoil" :           "/d/Earthsea/herbs/herb_files/cinquefoil", \
    "cladina" :              "/d/Krynn/common/herbs/cladina", \
    "clove" :                "/d/Gondor/common/herbs/clove", \
    "coccinea" :             "d/Gondor/common/herbs/coccinea", \
    "coffee bean" :          "/d/Earthsea/herbs/herb_files/coffee", \
    "columbine" :            "/d/Shire/common/herbs/columbine", \
    "common hop" :           "/d/Krynn/common/herbs/hop", \
    "coralline red alga" :   "/d/Krynn/common/herbs/coral_alga", \
    "cord grass" :           "/d/Krynn/common/herbs/cord_grass", \
    "cranberry" :            "/d/Krynn/common/herbs/cranberry", \
    "crocus" :               "/d/Krynn/common/herbs/crocus", \
    "culkas" :               "/d/Gondor/common/herbs/culkas", \
    "curugwath" :            "/d/Gondor/common/herbs/curugwath", \
    "daffodil" :             "/d/Shire/common/herbs/daffodil", \
    "dajla" :                "/d/Kalad/common/herbs/dajla", \
    "dandelion" :            "/d/Krynn/common/herbs/dandelion", \
    "darfern" :              "/d/Kalad/common/herbs/darfern", \
    "darkroot" :             "/d/Emerald/herbs/darkroot", \
    "dead man's fingers" :   "/d/Faerun/herbs/herb_files/dm_fingers", \
    "dill" :                 "/d/Gondor/common/herbs/dill", \
    "drudgeworth" :          "/d/Kalad/common/herbs/drudgeworth", \
    "eel grass" :            "/d/Krynn/common/herbs/eel_grass", \
    "elidross" :             "/d/Krynn/common/herbs/elidross", \
    "elkhorn kelp" :         "/d/Krynn/common/herbs/elkhorn_kelp", \
    "emmelti" :              "/d/Earthsea/herbs/herb_files/emmelti", \
    "evendim grass" :        "/d/Shire/common/herbs/grass", \
    "feather boa kelp" :     "/d/Faerun/herbs/herb_files/feather_boa_kelp", \
    "fennel" :               "/d/Gondor/common/herbs/fennel", \
    "fiddlehead" :           "/d/Krynn/common/herbs/fdlhead", \
    "firemoss" :             "/d/Faerun/herbs/herb_files/firemoss", \
    "fireweed" :             "/d/Krynn/common/herbs/fireweed", \
    "flameroot" :            "/d/Kalad/common/herbs/flameroot", \
    "footleaf" :             "/d/Faerun/herbs/herb_files/footleaf", \
    "fordinfa" :             "/d/Avenir/common/herbs/fordinfa", \
    "four leaf clover" :     "/d/Earthsea/herbs/herb_files/clover4", \
    "foxglove" :             "/d/Gondor/common/herbs/foxglove", \
    "frostheal" :            "/d/Gondor/common/herbs/frostheal", \
    "fucus" :                "/d/Krynn/common/herbs/fucus", \
    "fungari" :              "/d/Kalad/common/herbs/fungari", \
    "fungiarbo" :            "/d/Shire/common/herbs/treemushroom"])

#define HERB_LOOKUP2 ([ \
    "garlic" : "/d/Gondor/common/herbs/garlic", \
    "ginger" :               "/d/Gondor/common/herbs/ginger", \
    "ginseng" :              "/d/Earthsea/herbs/herb_files/ginseng", \
    "glimmer root" :         "/d/Shire/common/herbs/glimmer", \
    "glowcap" :              "/d/Faerun/herbs/herb_files/glowcap", \
    "glowshroom" :           "/d/Kalad/common/herbs/glowshroom", \
    "goats rue" :            "/d/Shire/common/herbs/goats_rue", \
    "green bean" :           "/d/Gondor/common/herbs/bean_green", \
    "green onion" :          "/d/Gondor/common/herbs/gonion", \
    "green pine" :           "/d/Khalakhor/common/herbs/green_pine", \
    "green slime" :          "/d/Krynn/common/herbs/greenslime", \
    "grey willow" :          "/d/Krynn/common/herbs/grey_willow", \
    "gylvir" :               "/d/Faerun/herbs/herb_files/gylvir", \
    "handasse" :             "/d/Gondor/common/herbs/handasse", \
    "hawthorn" :             "/d/Krynn/common/herbs/hawthorn", \
    "hazelnut" :             "/d/Krynn/common/herbs/hazelnut", \
    "hellebore stinkwort" :  "/d/Krynn/common/herbs/hellebore", \
    "hemlock" :              "/d/Gondor/common/herbs/hemlock", \
    "henblind" :             "/d/Shire/common/herbs/hen", \
    "hensbane" :             "/d/Shire/common/herbs/hensbane", \
    "holly berry" :          "/d/Gondor/common/herbs/holly", \
    "honeysuckle" :          "/d/Khalakhor/common/herbs/honeysuckle", \
    "horsetail" :            "/d/Krynn/common/herbs/horsetail", \
    "huckleberry" :          "/d/Shire/common/herbs/huckleberry", \
    "illavina" :             "/d/Faerun/herbs/herb_files/illavina", \
    "ithilgil" :             "/d/Gondor/common/herbs/ithilgil", \
    "jewelweed" :            "/d/Krynn/common/herbs/jewelweed", \
    "khuz" :                 "/d/Shire/common/herbs/khuz", \
    "kidney bean" :          "/d/Gondor/common/herbs/bean_kidney", \
    "kuko" :                 "/d/Kalad/common/herbs/kuko", \
    "labrador tea" :         "/d/Krynn/common/herbs/labr_tea", \
    "lady's slipper" :       "/d/Krynn/common/herbs/lady_slipper", \
    "lamia" :                "/d/Shire/common/herbs/lamia", \
    "laminaria" :            "/d/Krynn/common/herbs/laminaria", \
    "laranthas" :            "/d/Shire/common/herbs/laranthas", \
    "laurel" :               "/d/Gondor/common/herbs/laurel", \
    "lavendar" :             "/d/Faerun/herbs/herb_files/lavender", \
    "lianor berry" :         "/d/Shire/common/herbs/lianor_berry", \
    "licorice" :             "/d/Krynn/common/herbs/licorice", \
    "lilac" :                "/d/Khalakhor/common/herbs/lilac", \
    "lima bean" :            "/d/Gondor/common/herbs/bean_lima", \
    "lissuin" :              "/d/Gondor/common/herbs/lissuin", \
    "little orange carrot" : "/d/Gondor/common/herbs/carrot_wild", \
    "lobelia" :              "/d/Faerun/herbs/herb_files/lobelia", \
    "locoweed" :             "/d/Krynn/common/herbs/locoweed", \
    "lore" :                 "/d/Kalad/common/herbs/lore", \
    "lorea" :                "/d/Faerun/herbs/herb_files/lorea", \
    "lothore" :              "/d/Gondor/common/herbs/lothore", \
    "loyol" :                "/d/Emerald/herbs/loyol", \
    "lukilvor" :             "/d/Terel/common/herbs/lukilvor", \
    "madwort" :              "/d/Gondor/common/herbs/madwort", \
    "maicari" :              "/d/Faerun/herbs/herb_files/maicari", \
    "mandrake" :             "/d/Krynn/common/herbs/mandrake", \
    "marigold" :             "/d/Gondor/common/herbs/marigold", \
    "marjoram" :             "/d/Gondor/common/herbs/marjoram", \
    "maroea" :               "/d/Shire/common/herbs/maroea", \
    "marshmallow" :          "/d/Shire/common/herbs/marshmallow", \
    "marymoor" :             "/d/Faerun/herbs/herb_files/marymoor", \
    "mindleech" :            "/d/Kalad/common/herbs/mindleech", \
    "mint" :                 "/d/Gondor/common/herbs/mint", \
    "mittikna" :             "/d/Avenir/common/herbs/mittikna", \
    "moly" :                 "/d/Earthsea/herbs/herb_files/moly", \
    "monkshood" :            "/d/Earthsea/herbs/herb_files/monkshood", \
    "moosho" :               "/d/Terel/common/herbs/moosho", \
    "morel" :                "/d/Earthsea/herbs/herb_files/morel", \
    "morgurth" :             "/d/Gondor/common/herbs/morgurth", \
    "morning glory" :        "/d/Earthsea/herbs/herb_files/morning_glory", \
    "myrtleberry" :          "/d/Gondor/common/herbs/myrtle", \
    "narcissus" :            "/d/Avenir/common/herbs/narcissus", \
    "nasturtium" :           "/d/Shire/common/herbs/nasturtium", \
    "nethra" :               "/d/Avenir/common/herbs/nethra", \
    "nettle" :               "/d/Gondor/common/herbs/nettle", \
    "nightshade" :           "/d/Kalad/common/herbs/nightshade", \
    "nilgu" :                "/d/Earthsea/herbs/herb_files/nilgu", \
    "numbis" :               "/d/Kalad/common/herbs/numbis", \
    "oakmoss" :              "/d/Earthsea/herbs/herb_files/oakmoss", \
    "oede" :                 "/d/Faerun/herbs/herb_files/oede", \
    "onoclea" :              "/d/Krynn/common/herbs/onoclea", \
    "orange carrot" :        "/d/Gondor/common/herbs/carrot", \
    "oregano" :              "/d/Gondor/common/herbs/oregano", \
    "oreste" :               "/d/Shire/common/herbs/oreste", \
    "osarni" :               "/d/Faerun/herbs/herb_files/osarni", \
    "oyster mushroom" :      "/d/Faerun/herbs/herb_files/oyster_mushroom"])

#define HERB_LOOKUP3 ([ \
    "paramol" :              "/d/Earthsea/herbs/herb_files/paramol", \
    "parsley" :              "/d/Shire/common/herbs/parsley", \
    "pawnrose" :             "/d/Shire/common/herbs/pawnrose", \
    "peanut" :               "/d/Gondor/common/herbs/peanut", \
    "pendick-flower" :       "/d/Earthsea/herbs/herb_files/pendick_flower", \
    "pepper" :               "/d/Gondor/common/herbs/red_pepper", \
    "pindan" :               "/d/Shire/common/herbs/pindan", \
    "poison ivy" :           "/d/Krynn/common/herbs/poison_ivy", \
    "portabello" :           "/d/Faerun/herbs/herb_files/portabello_mushroom", \
    "pumpkin" :              "/d/Kalad/common/herbs/pumpkin", \
    "purple carrot" :        "/d/Shire/common/herbs/purple_carrot", \
    "ramira" :               "/d/Terel/common/herbs/ramira", \
    "ranindir" :             "/d/Faerun/herbs/herb_files/ranindir", \
    "raspberry" :            "/d/Krynn/common/herbs/raspberry", \
    "red alga" :             "/d/Faerun/herbs/herb_files/red_algae", \
    "red potato" :           "/d/Gondor/common/herbs/rpotato", \
    "red raspberry" :        "/d/Gondor/common/herbs/raspberry", \
    "redeye" :               "/d/Kalad/common/herbs/redeye", \
    "redweed" :              "/d/Gondor/common/herbs/redweed", \
    "ripplebark" :           "/d/Faerun/herbs/herb_files/ripplebark", \
    "ronwath" :              "/d/Avenir/common/herbs/ronwath", \
    "rosemary" :             "/d/Gondor/common/herbs/rosemary", \
    "rushwash" :             "/d/Earthsea/herbs/herb_files/rushwash", \
    "saffron" :              "/d/Gondor/common/herbs/saffron", \
    "sage" :                 "/d/Gondor/common/herbs/sage", \
    "salt wort" :            "/d/Krynn/common/herbs/salt_wort", \
    "sargassum" :            "/d/Krynn/common/herbs/sargassum", \
    "sarsaparilla" :         "/d/Krynn/common/herbs/sarsaparilla", \
    "saskatoon" :            "/d/Krynn/common/herbs/saskatoon", \
    "savory" :               "/d/Gondor/common/herbs/savory", \
    "sea bubble" :           "/d/Krynn/common/herbs/sea_bubble", \
    "sea grape" :            "/d/Faerun/herbs/herb_files/sea_grape", \
    "sea kelp" :             "/d/Earthsea/herbs/herb_files/kelp", \
    "sea lettuce" :          "/d/Krynn/common/herbs/sea_lettuce", \
    "seaside grass" :        "/d/Krynn/common/herbs/ss_grass", \
    "sebre" :                "/d/Terel/common/herbs/sebre", \
    "selevon" :              "/d/Faerun/herbs/herb_files/selevon", \
    "seregon" :              "/d/Gondor/common/herbs/seregon", \
    "shadow onion" :         "/d/Avenir/common/herbs/shadow_onion", \
    "shamrock" :             "/d/Khalakhor/common/herbs/shamrock", \
    "simbelmyne" :           "/d/Gondor/common/herbs/simbelmyne", \
    "skullcap" :             "/d/Krynn/common/herbs/skullcap", \
    "skunk berries" :        "/d/Earthsea/herbs/herb_files/skunk", \
    "smooth camas" :         "/d/Krynn/common/herbs/sm_camas", \
    "soapweed" :             "/d/Krynn/common/herbs/soapweed", \
    "solinaith" :            "/d/Krynn/common/herbs/solinaith", \
    "sparkweed" :            "/d/Earthsea/herbs/herb_files/sparkweed", \
    "sphagnum" :             "/d/Krynn/common/herbs/sphagnum", \
    "spinach" :              "/d/Earthsea/herbs/herb_files/spinach", \
    "sterling leaf" :        "/d/Sparkle/area/tutorial/herbs/leaf", \
    "strangleweed" :         "/d/Avenir/common/herbs/strangleweed", \
    "strawberry" :           "/d/Gondor/common/herbs/strawberry", \
    "streyroot" :            "/d/Calia/argos/silent_forest/herbs/streyroot", \
    "sumac" :                "/d/Gondor/common/herbs/sumac", \
    "sun stones" :           "/d/Faerun/herbs/herb_files/sun_stone", \
    "suranie" :              "/d/Gondor/common/herbs/suranie", \
    "surf grass" :           "/d/Krynn/common/herbs/surf_grass", \
    "sussur" :               "/d/Faerun/herbs/herb_files/sussur", \
    "tangleshoot" :          "/d/Krynn/common/herbs/tangleshoot", \
    "tansy" :                "/d/Shire/common/herbs/tansy", \
    "tarragon" :             "/d/Gondor/common/herbs/tarragon", \
    "three leaf clover" :    "/d/Earthsea/herbs/herb_files/clover3", \
    "thyme" :                "/d/Gondor/common/herbs/thyme", \
    "tiger lily" :           "/d/Krynn/common/herbs/tiger_lily", \
    "tobacco" :              "/d/Shire/common/herbs/tobacco", \
    "tomato" :               "/d/Earthsea/herbs/herb_files/tomato", \
    "tuo" :                  "/d/Gondor/common/herbs/tuo", \
    "tyelka" :               "/d/Gondor/common/herbs/tyelka", \
    "ungolestel" :           "/d/Gondor/common/herbs/ungolestel", \
    "valerian" :             "/d/Faerun/herbs/herb_files/valerian", \
    "veronica" :             "/d/Krynn/common/herbs/veronica", \
    "vinerot" :              "/d/Kalad/common/herbs/vinerot", \
    "white cedar" :          "/d/Khalakhor/common/herbs/cedar_bark", \
    "white hallow" :         "/d/Earthsea/herbs/herb_files/w_hallow", \
    "whitehorn" :            "/d/Terel/common/herbs/whitehorn", \
    "wilcol" :               "/d/Terel/common/herbs/wilcol", \
    "wild cucumber" :        "/d/Krynn/common/herbs/wild_cuke", \
    "wild plum" :            "/d/Krynn/common/herbs/wild_plum", \
    "wild strawberry" :      "/d/Gondor/common/herbs/wstrawberry", \
    "wintergreen leaf" :     "/d/Earthsea/herbs/herb_files/wintergreen", \
    "witch grass" :          "/d/Earthsea/herbs/herb_files/witch_grass", \
    "yam" :                  "/d/Gondor/common/herbs/yam", \
    "yarrow" :               "/d/Earthsea/herbs/herb_files/yarrow", \
    "yave" :                 "/d/Gondor/rhovanion/herbs/yave", \
    "ylpoe" :                "/d/Terel/common/herbs/ylpoe" ])

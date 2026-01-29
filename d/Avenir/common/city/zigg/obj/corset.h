#ifndef __ZIG_CORSETS__
#define __ZIG_CORSETS__

#ifndef CORSET_MAKER
private static string *colours = ({
	"black", "dark", "ebony", "charcoal", "gray",
	"silvery",  "white", "light", "pale", "cream", "ivory", "buff",
	"beige", "ecru", "golden", "yellow", "tawny", "saffron",
	"amber", "chartreuse", "green", "emerald", "viridian", "olive",
	"khaki", "jade", "aquamarine", "teal", "blue", "azure",
	"cerulean", "sapphire", "turquoise", "indigo", "orange",
	"apricot", "coral", "peach", "pink", "fuschia", "scarlet",
	"rose", "red", "blood-red", "burgundy", "cerise", "crimson", "ruby",
	"magenta", "maroon", "russet", "vermillion", "purple", "amethyst",
	"lavender", "lilac", "mauve", "plum", "violet", "brown",
	"coppery", "chocolate", "fawn", "mahogany", "ochre",
	"sable", "sepia", "tan", "umbre", "rainbow",
});
/*
 * 0 = variable.
 * 1 = cost additive
 * 2 = help text
 */
private static mapping fabrics = ([
        "cambric"  : ({  0, 1, "This cambric is of the thinnest "+
                        "possible weave. It is the finest form of linen "+
                        "available in Sybarus." }),
        "chamois"  : ({  1, 5, "The chamois is a very "+
                        "soft, pliable leather dressed with exp"+
                        "ensive, scented oils that lend a water-"+
                        "resistent quality." }),
        "coutil"   : ({  2, 1, "Coutil is a tightly woven cotton twill "+
			"cloth that is very durable. It is sleek "+
			"looking and has a smooth finish." }),
        "linen"    : ({  3, 2, "Linen is a simple yet elegant fabric "+
                        "made from spun flax-fiber woven very fine." }),
        "leather"  : ({  4, 10, "This leather comes from "+
                        "the tiny deer native to the Sybarus Holm. "+
                        "It has been tanned to bring out the fine "+
                        "grain, texture and suppleness of the skin." }),
        "muslin"   : ({  5, 3, "The muslin is a simple fabric of "+
                        "plain weave, made from spun cotton fibres. It "+
                        "takes dyes and imprints very easily, making "+
                        "it a fabric favoured by those fond of "+
                        "bright colours." }),
        "samite"   : ({  6, 9, "This samite cloth is com"+
                        "posed of very heavy silk fibers interwov"+
                        "en with strands of silver." }),
        "satin"    : ({  7, 3, "This is an example of perfect, "+
                        "glossy satin made with painstakingly-woven "+
                        "silken threads." }),
        "silk"     : ({  9, 2, "The luxury of silk is unsurpas"+
                        "sed by any other fabric. This particular "+
                        "cloth is of the highest-quality weave, making "+
                        "it both lustrous and durable." }),
        "snakeskin" : ({ 10, 15, "The snakeskin is shiny and "+
			"finely-scaled with vibrant color that is not "+
			"dyed, but consistant with the natural color of "+
			"snakes specially created and bred in Sybarus." }),
        "suede"    : ({ 11, 9, "The suede is made from kid "+
                        "leather of the highest quality that has "+
                        "been carefully abraded so as to raise a "+
                        "fine, soft nap on the material." }),
        "velvet"   : ({ 12, 5, "This velvet is very plush, "+
                        "and so carefully woven that you are unable "+
                        "to see the individual loops of silk which "+
                        "form the soft, slightly napped surface." }),
        "webcloth" : ({ 13, 15, "The webcloth material has "+
                        "the appearance and lightness of silk, but "+
                        "is very strong and resistant to tearing. "+
                        "It is known to be an extremely rare and "+
                        "thus rather expensive material." }),
]);
/*
 * 0 = variable.
 * 1 = cost additive
 * 2 = help text
 *
 * Some lacing is optional, so we start at 1.
 */
private static mapping lacing = ([
	"leather"       : ({ 1, 1,
	    "These are strips of sybarun goat leather that is strong "+
	    "but still somewhat supple enough to serve as lacing." }),
	"silk cord"     : ({ 2, 2,
	    "Fibers of silk from the common worm that are twined "+
	    "together into cords." }),
	"webcloth cord" : ({ 3, 3,
	    "Strands of the native and durable sybarun webcloth that "+
	    "are joined together into lacing cords." }),
	"satin ribbon"  : ({ 4, 4,
	    "Strips of regular satin that are cut and resewn in such "+
	    "a fashion as to form thin strips, or ribbons, that are "+
	    "also suitable as lacing." }),
]);
/*
 * 0 = variable.
 * 1 = cost additive
 * 2 = help text
 *
 * Busk material requires a busk, so starts at 1.
 */
private static mapping busking = ([
	"whalebone" : ({ 1, 4,
	    "The stiff but moldable bony material from baleen whales. "+
	    "It is the most common material used in corset boning." }),
	"steel"     : ({ 2, 6,
	    "A special type of metal known as \"spring steel\". "+
	    "It is light, strong and remembers its shape "+
	    "even after yielding to pressure." }),
	"oak"       : ({ 3, 2,
	    "Oak wood is prized for its strength, elasticity and "+
	    "durability. It is also light and easy to carve." }),
	"ash"       : ({ 4, 2,
	    "A strong durable wood of an ash tree that is also both "+
	    "lightweight and elastic." }),
	"willow"    : ({ 5, 3,
	    "The lightweight wood of a willow tree, chosen for "+
	    "being both tough and pliable." }),
	"kesoit"    : ({ 6, 5,
	    "The wood of a sybarun kesoit tree. These pieces are hard "+
	    "to obtain but are amazingly strong and flexible for a piece "+
	    "of timber." }),
]);
#endif  /* CORSET_MAKER */

/*
 * 0 = variable setting,
 * 1 = cost additive,
 * 2 = next process,
 * 3 = help desc,
 *
 * NOTE: all processes must indicate a next process, except last one.
 */
#define BEGIN_PROCESS  "material"
private static mapping process = ([
    "material"   : ({ "#fabrics", "mat_colour" }),
    "mat_colour" : ({ "@colours", "lining" }),
    "lining"     : ({ "#fabrics", "lin_colour" }),
    "lin_colour" : ({ "@colours", "style" }),

    "style"    : ([
	"underbust" : ({ 0, 10, "length",
	    "This type of corset fits snuggly beneath the "+
	    "breasts." }),
	 "overbust" : ({ 1, 15, "straps",
	     "This type of corset covers the breasts and "+
	     "molds the bustline in a variety of ways." }),
	]),
    "straps"   : ([
	 "no straps" : ({ 0, 0, "bust_nostrap",
	     "A strapless corset, this choice determines the "+
	     "types of bustlines available." }),
	 "straps" : ({ 1, 3, "bust_strap",
	     "A corset with shoulder straps, this choice determines "+
	     "the types of bustlines available." }),
	]),
    /* 0 for bustline is the underbust-bustline. */
    "bust_nostrap" : ([
	  "straight" : ({ 1, 2, "length",
	      "This bustline runs in a straight line across the breasts." }),
	  "plunging" : ({ 2, 2, "length",
	      "This bustline forms a plunging vee, exposing the valley "+
	      "between the breasts." }),
	"sweetheart" : ({ 3, 3, "length",
	    "This is a curved bustline that molds the breasts and "+
	    "is shaped like the upper portion of a heart design." }),
	]),
    "bust_strap"   : ([
	"square" : ({ 4, 2, "length",
	    "The wide, straight straps meet a straight bustline, framing "+
	    "the bosom." }),
	"scoop"  : ({ 5, 2, "length",
	    "The straps are curved, as is the bustline, forming a wide "+
	    "U-shape and displaying ample cleavage." }),
	"halter" : ({ 6, 3, "length",
	    "The straps of the corset meet behind the neck and help to "+
	    "lift the breasts up and together so more cleavage shows "+
	    "through the vee-cut front." }),
	"sweetheart" : ({ 7, 3, "length",
	    "This is a curved bustline that molds the breasts and "+
	    "is shaped like the upper portion of a heart design." }),
	]),
    "length"   : ([
	 "regular" : ({ 0, 0, "hip_cut",
	     "This is the normal length of a corset, it rides the tops "+
	     "of the hips and coasts along the waistline." }),
	"longline" : ({ 1, 5, "hip_cut_long",
	    "This is a style of corset that actually encompasses "+
	    "the waistline and hips for a longer, trimmed look." }),
	]),
    "hip_cut"  : ([
	"straight" : ({ 0, 0, "boning",
	      "This hip cut has the hem running in a straight line "+
	      "along the waist." }),
	   "curve" : ({ 1, 2, "boning",
	      "A hip cut that rides the hips, flaring in a downward "+
	      "curve at the front and slightly less so at the rear." }),
	  "basque" : ({ 2, 2, "boning",
	      "A hip cut that rides the hips then angles downwards "+
	      "in the front to form a point." }),
	]),
    "hip_cut_long"  : ([
	"straight" : ({ 0, 0, "boning",
	      "This hip cut has the hem running in a straight line "+
	      "inches below the waist." }),
	   "curve" : ({ 1, 2, "boning",
	      "A hip cut that rides over the hips, flaring in a downward "+
	      "curve at the front and slightly less so at the rear." }),
	  "basque" : ({ 2, 2, "boning",
	      "A hip cut that rides over the hips then angles downwards "+
	      "in the front to form a point." }),
	"sculpted" : ({ 3, 3, "boning",
	      "This hip cut slides down over the hips, hugging them "+
	      "gracefully while also dipping down in the front." }),
	]),
    "boning"   : ([
	 "light" : ({ 0, 0, "bone_mat",
	     "Light boning gives the corset a loose cage for "+
	     "a casual fit." }),
	"medium" : ({ 1, 3, "bone_mat",
	     "Medium boning gives the corset a more restraining cage for "+
	     "a comfortable but still somewhat relaxed fit." }),
	 "heavy" : ({ 2, 6, "bone_mat",
	     "Heavy boning leads to a corset with a restrictive cage "+
	     "that will enforce its shape on a pliant body." }),
	]),
    "bone_mat" : ([
	"whalebone" : ({ 0, 5, "back_lace",
	        "The stiff but elastic bony material from baleen whales. "+
	        "It is the most common material, hence the "+
	        "term \"boning\"." }),
	   "willow" : ({ 1, 4, "back_lace",
	        "The lightweight wood of a willow tree, chosen for "+
	        "being both tough and pliable." }),
	    "reeds" : ({ 2, 3, "back_lace",
		"These smooth, hollow stems are chosen for their "+
		"stiff flexibility that is retained after drying." }),
	    "steel" : ({ 3, 8, "back_lace",
		"A special type of metal known as \"spring steel\". "+
		"It is difficult to use and obtain, but is prized "+
		"for its strength and ability to remember its shape, "+
	        "even after yielding to pressure." }),
	]),

    "back_lace" : ({ "#lacing",  "bl_colour" }),
    "bl_colour" : ({ "@colours", "grommets" }),

    "grommets" : ([
	"steel" : ({ 1, 1, "busk",
	    "Grommets are eyelets for the laces to slide through so "+
	    "that the corset material doesn't wear abnormally. These "+
	    "grommets are made of a bright and burnished steel." }),
	"ivory" : ({ 2, 3, "busk",
	    "Grommets are eyelets for the laces to slide through so "+
	    "that the corset material doesn't wear abnormally. These "+
	    "grommets are carved from naturally gleaming ivory." }),
	]),

    "busk"     : ([
	"none" : ({ 0, 0, "ornament",
	     "A buskless corset is generally meant for casual and "+
	     "relaxed wear." }),
	 "one" : ({ 1, 3, "busk_mat_one",
	     "A single busk sewn into the front of a corset to keep "+
	     "the figure straight and upright." }),
	 "two" : ({ 2, 5, "busk_mat_two",
	     "A pair of busks results in a two piece corset that is "+
	     "fastened at the front where the busks are sewn in at "+
	     "either side but is also laced up at the rear." }),
	]),

    /* busk_mat requires a busk, so starts at 1 */
    "busk_mat_one" : ({ "#busking", "ornament" }),
    "busk_mat_two" : ({ "#busking", "fastener" }),
    /* Needed for generating descrip. */
    "busk_mat" :     ({ "#busking", "" }),

    "fastener" : ([
	         "lacing" : ({ 1, 2, "front_lace",
	     "This is lacing as the front fastener for the two busks. "+
	     "It is similar to the lacing at the rear of a corset." }),
	"loops and posts" : ({ 2, 5, "ornament",
	     "This fastener is a series of small, steel posts on one "+
	     "busk that fit into steel loops on the other. They are "+
	     "generally concealed by a slight overlapping of the outer "+
	     "corset material." }),
	]),

    /* depends on lacing fastener (front) */
    "front_lace" : ({ "#lacing",  "fl_colour" }),
    "fl_colour"  : ({ "@colours", "ornament"  }),

    /* Last process, return here or at sub-selection. */
    "ornament" : ([
	"none"         : ({ 0, 0, "",
	    "This will give you a corset without any extra "+
	    "trimmings." }),
	"bow"          : ({ 1, 1, "bow_colour",
	    "This will give you a corset with a small bow "+
	    "placed top center along the front." }),
	"piping"       : ({ 2, 3, "pip_colour",
	    "This will give you a corset with colourful "+
	    "bits of piping sewn along outside where the "+
	    "boning runs vertically." }),
	"feather trim" : ({ 3, 4, "ftrim_colour",
	    "This will give you a corset where the bustline is "+
	    "brimming with soft, colourful feathers." }),
	"lace trim"    : ({ 4, 4, "ltrim_colour",
	    "This will give you a corset where the bustline is "+
	    "adorned with soft and delicate lace." }),
	"side lacing"  : ({ 5, 3, "side_lace",
	    "This will give you a corset that is split along the sides "+
	    "as well and is held together with additional lacing." }),
	"buckles"      : ({ 6, 4, "buckle_mat",
	    "This will give you a corset with a set of fashionable "+
	    "buckles sewn along the front that are intended more for "+
	    "show than practicality." }),
	]),
    /* All subs are optional, so start at 1. */
    "buckle_mat" : ([
	 "steel" : ({ 1, 0, "",
	     "These ornamental buckles are shining, polished steel." }),
	"silver" : ({ 2, 2, "",
	     "These ornamental buckles are exquisitely silver-plated." }),
	  "gold" : ({ 3, 4, "",
	     "These ornamental buckles are richly gold-plated." }),
	]),

      "bow_colour" : ({ "@colours", "" }),
      "pip_colour" : ({ "@colours", "" }),
    "ftrim_colour" : ({ "@colours", "" }),
    "ltrim_colour" : ({ "@colours", "" }),

    "side_lace" : ({ "#lacing",  "sl_colour" }),
    "sl_colour" : ({ "@colours", "" }),
]);

#ifdef CORSET_MAKER
/*
 * Verbose preface text used in ordering.
 * There must be one for each potential process.
 * This gets inserted as part of a random string.
 */
private static mapping proc_text = ([
        "material" : "outer material choices",
      "mat_colour" : "outer material colours",
          "lining" : "interior lining fabrics",
      "lin_colour" : "internal lining colours",
           "style" : "overall corset designs",
//          "straps" : "choice of having straps or not",
          "straps" : "options",
      "bust_strap" : "bustlines",
    "bust_nostrap" : "bustlines",
          "length" : "corset lengths",
         "hip_cut" : "designer hip cuts",
    "hip_cut_long" : "designer hip cuts",
          "boning" : "options for boning types",
        "bone_mat" : "boning constructs",
       "back_lace" : "types of back lacing",
       "bl_colour" : "colours for your back lacing",
        "grommets" : "grommet stylings",
            "busk" : "choices for a busk",
    "busk_mat_one" : "materials for your busk",
    "busk_mat_two" : "materials for your busk",
        "fastener" : "types of fasteners",
      "front_lace" : "styles of front lacings",
       "fl_colour" : "front lacing colours",
        "ornament" : "choices for ornamentation",
      "buckle_mat" : "ornamental buckle materials",
      "bow_colour" : "ornamental bow colours",
      "pip_colour" : "ornamental piping colours",
    "ftrim_colour" : "ornamental feather trim colours",
    "ltrim_colour" : "ornamental lace trim colours",
       "side_lace" : "styles of side lacings",
       "sl_colour" : "ornamental side lacing colours",
]);
#endif  /* CORSET_MAKER */

#ifndef CORSET_MAKER
/* This is the order to call the indices to the 'descrip' mapping
 * below to generate a long description for a specific corset.
 */
private static string *desc_order = ({
	"material", "style", "hip_cut", "boning", "bustline",
	"busk", "fastener", "back_lace", "ornament",
});
/* Put descriptive bits here.... */
/* Current maximum of 4 replacements per string. */
private static mapping descrip = ([
    "material" : ({ "This fine garment is made of %s %s with muslin "+
    	"interfacing and %s %s lining.",
	"mat_colour", "material", "lin_colour", "lining" }),

    "style" : ([
	0 : ([ /* Underbust */
	    "key" : "length",
	    0 : ({ "It is made to cover the abdomen, starting just below "+
		"the breasts and covering to just below the waist "+
		"where it "}),
	    1 : ({ "It is made to cover the abdomen, starting just below "+
		"the breasts and dipping just past the hips where it " }),
	    ]),
	1 : ([ /* Overbust */
	    "key" : "length",
	    0 : ({ "It is made to cover the torso, starting low on "+
		"the bust and covering to just below the waist where it " }),
	    1 : ({ "It is made to cover the torso, starting low on "+
		"the bust and dipping just past the hips where it " }),
	    ]),
	]),

    "hip_cut" : ([
	0 :/* straight */({ "ends in a clean, straight line. " }),
	1 :/* curve    */({ "curves along the bottom. " }),
	2 :/* basque   */({ "forms a point in the front center. "  }),
	3 :/* sculpted */({ "is sculpted with curves to flatter them. " }),
	]),

    "boning" : ([
	0 :/* light  */({ "The corset's sixteen %s bones "+
	    "lightly shape the body, providing support with "+
	    "minimal discomfort.", "bone_mat" }),
	1 :/* medium */({ "Twenty-four bones made of stiff %s "+
	    "encircle and shape the body, firmly defining the "+
	    "waist and supporting the bosom.", "bone_mat" }),
	2 :/* heavy  */({ "Thirty-two %s bones beneath the %s form "+
	   "an unyielding cage designed to shape the body exquisitely "+
	    "by lifting the bosom and cinching the waist.",
		"bone_mat", "material" }),
	]),

    "bustline" : ([
	0 :/* underbust  */({ "This corset fits just under the bust, "+
	    "leaving it uncovered while following the natural curve of "+
	    "the breasts to an upward point at the center." }),
	1 :/* straight   */({ "This corset is strapless with a straight "+
	    "bustline. The bones press in and upwards evenly across "+
	    "the chest, displaying the bosom amply as its roundness seems "+
	    "to nearly spill out from its confines." }),
	2 :/* plunging   */({ "This corset is strapless with a plunging "+
	    "vee-shaped bustline. The bones are positioned to press "+
	    "a woman's bosom up and inward, providing a brazen peek of "+
	    "her cleavage through the deep vee-cut." }),
	3 :/* sweetheart */({ "This corset is strapless with a sweetheart "+
	    "bustline that curves flatteringly over a woman's chest, "+
	    "and a slightly cupped top, which shamelessly displays her "+
	    "bosom to its best advantage." }),
	4 :/* square     */({ "Two sturdy shoulder straps pull upward on a "+
	    "straight bustline, forming a square frame to display the "+
	    "bosom. The bones compress and lift the breasts displaying "+
	    "the bosom amply as its roundness seems to nearly spill out "+
	    "from its confines." }),
	5 :/* scoop      */({ "Two sturdy shoulder straps curve slowly to "+
	    "become a scooped bustline. An elegant curve displays the "+
	    "bosom while the bones compress and lift the breasts letting "+
	    "their roundness peek out like two apples out of a barrel." }),
	6 :/* halter     */({ "A sturdy strap runs behind the neck and "+
	    "slowly widens to seamlessly cover the breasts, becoming "+
	    "a plunging vee-shaped bustline. The bones are work with the "+
	    "haltar to press a woman's bosom up and inward, providing a "+
	    "brazen peek of her cleavage through the deep vee-cut." }),
	7 :/* sweetheart */({ "Two sturdy shoulder straps pull upward on a "+
	    "sweetheart bustline that curves flatteringly over a woman's "+
	    "chest, and a slightly cupped top, which shamelessly displays "+
	    "her bosom to its best advantage." }),
	]),

    "busk" : ([
	0 :/* none */({ "The front of this corset is buskless, making it "+
	    "slightly more flexible and comfortable than some others. "+
	    "The even, symmetrical boning also makes it more smooth and "+
	    "uniform.",
	}),
	1 :/* one  */({ "A busk made from %s has been inserted in a "+
	    "pocket running up the middle front of the corset. It "+
	    "holds the front rigidly straight from the waist to the "+
	    "bust and demands excellent posture.", "busk_mat"
	}),
	2 :/* two  */({ "Two %s busks placed in pockets along the "+
	    "center front of the corset make it extremely rigid "+
	    "and demand good posture, while creating a smooth "+
	    "front and flattening the tummy.", "busk_mat"
	}), ]),

    "fastener" : ([
	/* 0 -- nothing, requires 2 busks. */
	1 :/* lacing      */({ "The busks have small, evenly spaced holes, "+
	    "as do the pockets which allow them to be laced together in a "+
	    "fashion similar to the back.",
	}),
	2 :/* loops+posts */({ "The busks have raised steel "+
	    "posts on one side and loops on the other. These allow the "+
	    "busks to be fastened together and allows the corset to be "+
	    "removed without loosening the laces as much.",
	}), ]),

    "back_lace" : ({ "The back of the corset laces from top to bottom "+
	    "with %s, %s criss-crossing through %s grommets, "+
	    "allowing the corset to be adjusted for optimal restraint "+
	    "and comfort, or discomfort, as the case may be.",
		"bl_colour", "back_lace", "grommets" }),

    "ornament" : ([
	/* 0 -- none */
	1 :/* bow     */({ "A little %s bow is tied at the center of the "+
	    "bustline to make the wearer look pretty as a present.",
		"bow_colour"
	}),
	2 :/* piping  */({ "%s piping on the %s trace the paths of the "+
	    "bones beneath creating an intriguing visual effect which "+
	    "further emphasizes the sculpted curves of the wearer.",
		"pip_colour", "material"
	}),
	3 :/* f. trim */({ "Fanciful %s feathers trim the bustline "+
	    "of the corset, adding a playful and exotic "+
	    "touch to its appearance.", "ftrim_colour"
	}),
	4 :/* l. trim */({ "Delicate %s lace forms a scalloped "+
	    "border along the edges of the corset which "+
	    "gives the rigid, revealing garment a hint of %s.",
	     "ltrim_colour", ({"softness","sweetness","innocence"})
	}),
	5 :/* s. lace */({ "%s, %s laces criss-cross up each side of "+
	    "the corset as well, showing little diamonds of bare skin.",
		"sl_colour", "side_lace"
	}),
	6 :/* buckles */({ "Several small, %s buckles fasten over the "+
	     "stomach but are more of a decorative addition than functional.",
		"buckle_mat"
	}), ]),
]);
#endif  /* CORSET_MAKER */

#endif  __ZIG_CORSETS__

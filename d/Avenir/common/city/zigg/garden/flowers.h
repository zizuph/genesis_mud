/*
 * Code for flowers.
 */

private int
help_flower(string str)
{
    string *arr = ({
	"flower","flowers","posy","posies","bouquet","bouquets",
    });

    if (member_array(str, arr) == -1)
	return notify_fail("Help what? Flowers?\n");

    write(read_file(ZIG_RLG + "help.flowers"));
    return 1;
}

/*
 * These are used for singles/posies/bouquets.
 */
#define POSY     (ZIG_RLG + "posy")
#define SINGLE   (ZIG_RLG + "single")
#define BOUQUET  (ZIG_RLG + "bouquet")
#define MANGLED  (ZIG_RLG + "mangled")

#define POSY_NUM  3
#define BOUQ_NUM  6

/*
 * The master list of flowers.
 */
private static mapping m_flowers = ([
  /*
    "flower index" : ({
	({ "primary name", "plural primary name",
	   "alternate name1", "alternate name2", ..., }),
	"This is the description assocatied with this flower.\n",
	"A description of the flowers scent, for when smelling.\n",
	({ "colour choice 1", "colour choice 2", ... }),
	"low_val-high_val",
    }),
   */
    "aster" : ({
	({ "aster", "asters" }),
	"Similar to daisies but growing in a multitude of colors, "+
	  "Asters grow on long stems with alternate, simple leaves. "+
	  "Each blossom contains a central disk of small, tubular "+
	  "petals surrounded by numerous showy, ray-like petals.\n",
	"It has a vague, undistinguished scent.",
	({ "white", "pink", "pale blue", "purple" }),
	"75-150",
    }),
    "bluebell" : ({
	({ "bluebell", "bluebells" }),
	"The lavender-blue flowers are pendulous, bell-shaped "+
	  "and slightly fragrant. They glow in clusters on long stems "+
	  "that bend over at the top, allowing the bell to hang down.\n",
	"It has a faint, fresh fragrance.",
	({ "blue", "lavender", "lavender-blue" }),
	"75-150",
    }),
    "borage" : ({
	({ "borage", "borages", "borage flower", "borage flowers" }),
	"The bright blue, star-shaped flowers make borage one of "+
	  "the prettiest herb plants, though the dark green leaves "+
	  "are rather plain. The flavor of the leaves resembles that "+
	  "of cucumber and both the leaves and flowers are used for "+
	  "culinary and medicinal purposes.\n",
	"The odor is rather like a cucumber.",
	({ "blue", "bright blue" }),
	"75-150",
    }),
    "bachelor's button" : ({
	({ "bachelor's button", "bachelor's buttons",
	    "cornflower", "cornflowers" }),
	"Also known as cornflowers, the upper half of the plant is "+
	  "multi-stemmed, producing many flowers. The leaves are covered with "+
	  "small white hairs causing the plant to have a gray-blue "+
	  "appearance. The blossoms are round and endearingly ragged, "+
	  "growing in cheerfully vivid colors.The original flower color "+
	  "is blue, but it has been bred in white, pink and red.\n",
	"You notice a faintly sweet fragrance.",
	({ "blue", "white", "pink", "red", "gray-blue" }),
	"75-150",
    }),
    "carnation" : ({
	({ "carnation", "carnations" }),
	"Prized for their beauty, color, and fragrance, "+
	  "carnations have narrow opposite leaves and long, "+
	  "slightly branching stems that terminate in large, "+
	  "ruffled, double flowers.\n",
	"It has a very pleasant, spicy fragrance.",
	({ "red", "white", "yellow", "green", "pink" }),
	"75-150",
    }),
    "chrysanthemum" : ({
	({ "chrysanthemum", "chrysanthemums" }),
	"Chrysanthemums have large showy blossoms which "+
	  "resemble very shaggy daisies. They are highly "+
	  "prized, ornamental flowers.\n",
	"It has a distinctive, though remarkably non-floral, scent.",
	({ "purple", "red", "white", "yellow" }),
	"75-150",
    }),
    "daffodil" : ({
	({ "daffodil", "daffodils" }),
	"Cheery and elegant, Daffodils grow singly "+
	  "upon long, hollow, green stems. They have a trumpet-"+
	  "shaped, ruffled crowns framed by a ring of pointed, "+
	  "ovate petals.\n",
	"It has an unremarkable scent.",
	({ "golden", "white", "yellow" }),
	"75-150",
    }),
    "daisy" : ({
	({ "daisy", "daisies" }),
	"Daisies have bright yellow centers "+
	  "and white outer petals. These flowers are small "+
	  "and cheerful, growing on sturdy stems.\n",
	"A very subtle, floral scent tantalizes your nose.",
	({ "white" }),
	"30-75",
    }),
    "delphinium" : ({
	({ "larkspur", "larkspurs", "delphinium", "delphiniums" }),
	"The leaves of larkspur are deeply lobed with 3 to 7 toothed, "+
	  "pointed lobes. The main flowering stem is erect, and is topped "+
	  "by many flowers, which can vary between purple, blue, red, "+
	  "yellow or white. The flower has five petals which grow together "+
	  "to form a hollow flower with a spur at the end.\n",
	"It has a very light, distinctive scent.",
	({ "white", "light blue", "deep blue", "purple-blue",
	   "red", "yellow" }),
	"75-150",
    }),
    "dragonflower" : ({
	({ "dragonflower", "dragonflowers" }),
	"Also known as Dragon's-mouth, the dainty flowers are a member "+
	  "of the orchid family. They vagely resemble the mouth of a "+
	  "dragon, with a deep-red throat and a long, protruding lip "+
	  "rimmed with a fringe of pale, white hairs.\n",
	"It has a very faint, but rather foul, odor.",
	({ "red", "white", "purple", "deep pink", "violet", "pink",
	   "yellow", "orange" }),
	"75-150",
    }),
    "forget-me-not" : ({
	({ "forget-me-not", "forget-me-nots" }),
	"Forget-me-nots are tiny, delicate blossoms borne "+
	  "upon thin stalks. The yellow centers are surrounded "+
	  "by five tender petals which are delicately tinted "+
	  "with colour.\n",
	"It has an unforgettable floral scent.",
	({ "blue", "white", "pink" }),
	"75-150",
    }),
    "freesia" : ({
	({ "freesia", "freesias" }),
	"Freesia are very elegant, arched rows of exquisitely scented "+
	  "flowers, prized for their beauty and longevity. The tubular "+
	  "flowers grow from delicate, spikelike racemes.\n",
	"The freesia has an incredibly lovely and unique fragrance, "+
	  "which you inhale deeply.",
	({ "white", "golden yellow", "orange", "red", "pink",
	   "mauve", "lavender", "purple" }),
	"75-150",
    }),
    "heliotrope" : ({
	({ "heliotrope", "heliotropes",
	   "heliotrope flower", "heliotrope flowers" }),
	"Heliotrope plants have attractive dark green, crinkled foliage "+
	  "with masses of small, dark purple flowers. White and lavender "+
	  "flowers are rarer. The flowers are very fragrant.\n",
	"It has a wonderful floral, distinctive, heavy scent, "+
	  "with cherry and vanilla notes.",
	({ "dark purple", "white", "lavender" }),
	"75-150",
    }),
    "hibiscus" : ({
	({ "hibiscus", "hibiscus", }),
	"Hibiscus flowers have long, yellow stamens protruding from "+
	  "the centers of their vividly coloured petals. It is "+
	  "an exotic and unusual flower, with a dark green "+
	  "stem and bushy, ovate leaves.\n",
	"It scent is unremarkable.",
	({ "white", "pink", "red", "purple", "yellow" }),
	"75-150",
    }),
    "hollyhock" : ({
	({ "hollyhock", "hollyhocks", "hollyhock flower",
	   "hollyhocks flowers", "hollyhock plant", "hollyhock plants" }),
	"Hollyhocks are stately, majestic, towering plants that add "+
	  "beauty wherever they are grown. They produce many clear, "+
	  "lovely colors ranging from white to black and include shades "+
	  "of pink, flesh, rose-pink, salmon-rose, golden yellow, canary-"+
	  "yellow, dark red, purple-crimson, dark maroon, white and "+
	  "combinations of practically all these colors with either white "+
	  "centers or white margins. They're leaves are large, coarse and "+
	  "grow mostly in clumps at the base of the plant. The long spikes "+
	  "of flowers grow extremely tall and there are usually from five "+
	  "to nine blossoms in bloom on each well grown stalk.\n",
	"You notice an extremely faint, sweetscent.",
	({ "white", "black", "pink", "rose", "salmon", "golden", "yellow",
	   "canary-yellow", "dark red", "purple", "crimson", "maroon",
	   "white" }),
	"75-150",
    }),
    "honeysuckle" : ({
	({ "honeysuckle", "honeysuckles" }),
	"Honeysuckle's graceful, fragrant blossoms grow on a "+
	  "handsome, twining vine that bears broad, opposite leaves.\n",
	"It has a pleasantly sweet and very distinctive floral scent.",
	({ "white", "yellow" }),
	"75-150",
    }),
    "iris" : ({
	({ "iris", "irises" }),
	"Iris is a colorful, orchidlike flower "+
	  "which has prominent gold tufts at the base of its "+
	  "petals. The linear, swordlike leaves, and small, "+
	  "showy flowers are symmetrical and, despite their "+
	  "elaborate appearance, relatively simple.\n",
	"You are unable to distinguish its scent.",
	({"purple", "blue-violet", "blue", "deep red", "red", "white" }),
	"75-150",
    }),
    "lavender" : ({
	({ "lavender", "lavenders",
	   "lavender blossom", "lavender blossoms" }),
	"A member of the mint family, lavender is known for its delicate, "+
	  "fernlike leaves and small, delightfully fragrant flowers.\n",
	"What a lovely scent!",
	({ "pale purple" }),
	"75-150",
    }),
    "lilac" : ({
	({ "lilac", "lilacs" }),
	"Lilacs are harvested from bushes with simple, ovate leaves. "+
	  "The flowers grow in dense, pyramidal clusters of smaller "+
	  "blossoms, which have a heady, rich scent.\n",
	"It has a wonderfully strong, floral scent that is "+
	  "very distinctive.",
	({ "purple", "pink", "white", "blue" }),
	"75-150",
    }),
    "lily" : ({
	({ "lily", "lilies" }),
	"Lilies possess an elegant symmetry. The brilliantly hued "+
	  "flowers are tubular, with three petals and three sepals of "+
	  "similar appearance. Sometimes they are striped and speckled, "+
	  "giving it a rather exotic appearance.\n",
	"It has a very delicate scent that reminds you of soap.",
	({ "white", "yellow", "orange", "pink", "red", "purple",
	   "bronze", "black", "cream" }),
	"150-250",
    }),
    "marigold" : ({
	({ "marigold", "marigolds" }),
	"The flowers are composed of a dense arrangement of ray like "+
	  "petals that come in yellow, orange and a unique bronze color.\n",
	"It has musky, pungent scent.",
	({ "deep red", "red", "orange", "yellow", "bright yellow", "golden" }),
	"75-150",
    }),
    "moonflower" : ({
	({ "moonflower", "moonflowers",
	   "moonflower vine", "moonflower vines" }),
	"The moonflower is a vigorous twining vine that is a close "+
	  "relative of the morning glory vine. It has similar heart "+
	  "shaped leaves that are a rich green which provide a beautiful "+
	  "backdrop for the spectacular moonflowers. The blossoms are "+
	  "fluted funnels sculpted in purest alabaster white, each about "+
	  "the diameter of a saucer. In the Outlands, the blossoms open "+
	  "in the evening and last through the night before they are "+
	  "withered by the morning sun, thus earning the name moonflower "+
	  "or sometimes evening glory. Each flower that withers is usually "+
	  "replaced by another blossom, or even two, the next day. "+
	  "These vines were found to thrive in the diffuse light of the "+
	  "sybarun caverns, the blooms lasting far longer. Still each "+
	  "bloom opens once and lasts a day before it withers and is "+
	  "quickly replaced by another.\n",
	"It has a heavy, exotic, almost wild scent.",
	({ "white" }),
	"200-300",
    }),
    "morning glory" : ({
	({ "morning glory", "morning glories",
	   "morning glory vine", "morning glory vines" }),
	"Morning glory vines grow very fast and produce a daily crop "+
	  "of blue, purple, pink, scarlet, white or multicolored single "+
	  "or double trumpet-shaped flowers. The flowers are normally "+
	  "open only from dawn to midmorning, but many varieties will hold "+
	  "their blossoms longer, especially in cloudy weather or the "+
	  "dimmer light of the sybarun cavern. Profusely flowering against "+
	  "a background of pale green foliage, they quickly form lovely "+
	  "hedges or screens. The vines are sometimes used as a temporary "+
	  "ground cover, and do well in hanging baskets and containers.\n",
	"It has no detectable floral smell.",
	({ "purple", "blue", "pink", "scarlet", "black", "violet" }),
	"75-150",
    }),
    "orchid" : ({
	({ "orchid", "orchids" }),
	"Also known as Fairy Slipper. It has a single leaf petiole and "+
	  "a single flower that is borne at the top of a bare "+
	  "stalk. The lip of the flower is large and pouchlike, "+
	  "resembling a slipper, while the sac is marked with "+
	  "purple and bears a patch of fine yellow hairs. It is "+
	  "a truly exquisite flower of inspirational beauty.\n",
	"It has a very delicate, vaguely meaty smell.",
	({ "white", "pink", "lavender", "yellow" }),
	"150-200",
    }),
    "pansy" : ({
	({ "pansy", "pansies", "dream pansy", "dream pansies" }),
	"Pansies are a species of violets. They have been bred in a "+
	  "rainbow of colours, ranging from gold and orange though to "+
	  "purple, violet, and a blue so deep it seems to be black. "+
	  "They are quite a hardy plant with two top petals overlapping "+
	  "slightly, two side petals, beards where the three lower petals "+
	  "join the center of the flower, a single bottom petal with a "+
	  "slight indentation. Many pansies have black splotches which "+
	  "many liken to a face, imagining they have an expressive quality.\n",
	"You perceive a very subtle, delicate perfume-like aroma.",
	({ "white", "pink", "red", "orange", "yellow", "blue",
	   "purple", "black" }),
	"75-150",
    }),
    "passionflower" : ({
	({"passionflower", "passionflowers",  }),
	"An exotic-looking, highly aromatic flower, it has large "+
	  "three-lobed, serrated leaves with beautifully intricate "+
	  "flowers that are nearly as large as the palm of your hand. "+
	  "Its three stamens rise prominently above the twelve "+
	  "recurving petals and the colourful fringe surrounding "+
	  "them, the combination of which has created a unique flower "+
	  "instantly recognizable as passionflower.\n",
	"Its scent is sweet and intoxicating.",
	({ "pink", "red", "orange", "yellow", "purple" }),
	"150-250",
    }),
    "peony" : ({
	({ "peony", "peonies" }),
	"The peony has spectacular, showy flowers of extraordinary hue.\n",
	"It has a strong, floral scent.",
	({ "pink", "red", "white", "yellow", "deep pink",
	   "blood red", "scarlet" }),
	"75-150",
    }),
    "penny black" : ({
	({ "penny black", "penny black flowers" }),
	"Penny black nemophilia are well loved wildflowers because "+
	  "of their dainty two-tone flowers and airy, light green "+
	  "foliage. They have very dark, almost black petals with a "+
	  "lacy white or silverish picotee edge.\n",
	"It has a faintly herbal scent.",
	({ "black" }),
	"75-150",
    }),
    "petunia" : ({
	({ "petunia", "petunias" }),
	"Petunias have small, ovate leaves that are covered with sticky "+
	  "hairs and are loaded with large, trumpet-shaped blossoms "+
	  "with frilly edges. Petunias are available in shades of white, "+
	  "yellow, pink, blue, purple, and red as well as bicolors, and "+
	  "as single or double flowers. They are hardy plants and many "+
	  "have a light, sweet fragrance, especially the blue petunia "+
	  "varieties.\n",
	"It has a light, sweet fragrance.",
	({ "white", "pink", "red", "orange", "yellow", "fuchsia",
	   "blue", "purple", "black" }),
	"75-150",
    }),
    "poppy" : ({
	({ "poppy", "poppies" }),
	"Ornamental poppies have deeply dissected leaves and a long, "+
	  "slender stalk. Their large, showy flower vivid in hue, with "+
	  "an inner layer of velvety petals surrounding a black and "+
	  "yellow center. They are very striking and unusual flowers.\n",
	"It has a relaxing, spicy and very sweet scent.",
	({ "white", "pink", "yellow", "orange", "red", "blue" }),
	"75-150",
    }),
    "rose" : ({
	({ "rose", "roses" }),
	"Roses are prized for their rich colors, fragrance, and elegant "+
	  "forms. Dozens of silky overlapping petals spiral outward from "+
	  "a central bud, slowly opening into a gloriously beautiful "+
	  "blossom. The stem is covered with sharp thorns.\n",
	"Such a glorious scent, so heady as to be almost over-powering!",
	({ "red", "white", "scarlet", "black", "yellow", "pink",
	   "violet", "orange", "crimson", "blood red" }),
	"150-200",
    }),
    "snapdragon" : ({
	({ "snapdragon", "snapdragons" }),
	"Snapdragons have short, linear leaves along a central stem, "+
	  "topped by dense clusters of brightly colored flowers. Known "+
	  "as snapdragons from the flowers' fancied resemblance "+
	  "to the face of a dragon that opens and closes its mouth when "+
	  "properly squeezed (thus the 'snap'). They come in shades of "+
	  "yellow, red, pink, orange, bronze, lavender and white.\n",
	"They have a clean, light, lovely scent.",
	({ "red", "white", "purple", "deep pink", "violet", "pink",
	   "yellow", "orange" }),
	"75-150",
    }),
    "sweetpea" : ({
	({ "sweetpea", "sweetpeas" }),
	"The sweet-smelling flowers come in a wide range of colors and "+
	  "are the main feature of this climbing plant. The vines grow "+
	  "to a moderate length and like to climb but also do well "+
	  "in hanging baskets and raised planters where they can "+
	  "spill over.\n",
	"A very sweet, slightly spicy scent fills your nose.",
	({ "red", "white", "blue", "pink", "purple" }),
	"75-150",
    }),
    "tuberose" : ({
	({ "tuberose", "tuberoses" }),
	"Tuberose flowers grow on spiking stems that stalk up to the size "+
	  "of a small dwarf. The beautiful, white, tubular shaped flowers "+
	  "grow between sword-shaped leaves. There are both single and "+
	  "double flowering varieties to choose from.\n",
	"The fragrance is rich, sultry and wonderful.",
	({ "pale pink", "red", "cream", "white" }),
	"75-150",
    }),
    "tulip" : ({
	({ "tulip", "tulips" }),
	"A small, delicate tulip of a variety that is found exclusively "+
	  "in Sybarus. This bell-shaped flower is borne on a single scape "+
	  "and is variegated in various shades of the same colour.\n",
	"It has a spicy, and vaguely sandalwood scent.",
	({ "scarlet", "red", "crimson", "yellow", "orange",
	   "lemon yellow" }),
	"75-150",
    }),
    "verbana" : ({
	({ "verbana", "verbanas", "verbana flower", "verbana flowers" }),
	"The leaves are usually opposite, simple, and in many species "+
	  "hairy, often densely so. The flowers are small, white, pink, "+
	  "purple or blue, with five petals, and borne in dense spikes.\n",
	"It has a grassy smell with a touch of lemon.",
	({ "red", "rose", "peach", "pink", "purple", "lavender", "blue",
	   "white" }),
	"75-150",
    }),
    "viola" : ({
	({ "violet", "violets", "viola", "violas" }),
	"Most violets are small perennial plants, but a few are "+
	  "annual plants and some are small shrubs. They typically "+
	  "have heart-shaped leaves, and asymmetrical flowers with "+
	  "four upswept or fan-shaped petals, two each side, and one "+
	  "broad, lobed lower petal pointing downward. The shape of "+
	  "the petals defines many species, for example, some violets "+
	  "have a spur on the end of each petal. Flower colours vary "+
	  "many are violet as their name suggests, and some are blue, "+
	  "yellow, white or cream; some are bicolored, often blue and "+
	  "yellow. Rarely they can appear a deep black.\n",
	"For a moment you think you catch a soft, floral "+
	  "scent but it eludes you before you can truly smell it.",
	({ "black", "yellow", "white", "cream", "purple", "blue" }),
	"75-150",
    }),
    "wildflower" : ({
	({ "wildflower", "wildflowers" }),
	"They are small flowers of all colors and shapes which grow "+
	  "profusely without tending.\n",
	"You detect a fresh, soft floral fragrance.",
	({ "white", "pink", "red", "orange", "yellow", "green",
	   "blue", "purple", }),
	"75-150",
    }),
    "zinnia" : ({
	({ "zinnia", "zinnias" }),
	"The wild form is a coarse, upright, bushy annual "+
	  "with solitary daisylike flowerheads on long stems, and "+
	  "opposite, sandpapery, lance shaped leaves. The ray flowers "+
	  "are purple, the discs yellow and black. The size of the flowers "+
	  "varies but they are generally large to extremely large. There "+
	  "are zinnias with white, cream, green, yellow, apricot, orange, "+
	  "red, bronze, crimson, purple, and lilac flowers; zinnias with "+
	  "striped, speckled and bicolored flowers; zinnias with double, "+
	  "semi-double and dahlia-like pompon flowers.\n",
	"It has a lingering clean, heavy floral scent with grassy notes.",
	({ "white", "deep red", "orange", "yellow", "green", "purple", "cream",
	   "apricot", "red", "bronze", "crimson", "lilac" }),
	"75-150",
    }),
]);

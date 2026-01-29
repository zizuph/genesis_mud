/*
 * - felix.h
 *
 * This file holds the orders defines for things Felix sells.
 */
#ifndef __FELIX_CARDOZA_ORDERS__
#define __FELIX_CARDOZA_ORDERS__

/* This is the path to the dir holding felix and items. */
#define PATH "/d/Raumdor/common/drakmere/felix/"

/* Felix's save file. */
#define SAVE MASTER

/* Log questions for which there is no prepared answer? */
#define LOG_QUESTIONS   (PATH + "question.log")
/* This will log claim errors. */
#define LOG_ERRORS      (PATH + "error.log")

/*
 * This is the annoyance threshold. Once this is reached or surpassed
 * then the person will be blacklisted.
 */
#define THRESHOLD	(5 + random(5))

/*
 * The actual define that holds the orders and their properties.
 * Format is:
 *   m_orders = ([ "name": ({ "path", cost, time, limit, desc, }), ])
 *
 *  name = The name the item should be orded / displayed as.
 *  path = Filepath to object to be clones.
 *  cost = Item cost in platinum.
 *  time = Order completion time in seconds.
 * limit = Max # orderable per person per day.
 *  desc = Short description of item for sale.
 * ldesc = Long description of item for sale.
 *
 * Notes:
 * ~~~~~
 * Felix will only process ONE order at a time.
 * Bugging him during an order annoys and pisses him off.
 * Cash is also required UP FRONT, before he will work.
 * No refunds, no guarantee of service.
 */
#define M_ORDERS ([ \
    "balm":({ (PATH + "scar_balm"), 125, 60, 1, "scar removal balm", \
	    "It is a balm used to remove scars from your body.  "+ \
   	    "You simply rub it into your skin and wait while the "+ \
   	    "magic of the balm takes hold." }), \
   "salve":({ (PATH + "beauty_salve"), 5, 30, 5, "beauty ointment", \
  	    "It is a salve whose magical properties can enhance ones "+ \
  	    "outward physical appearance for a limited time.  Be warned "+ \
  	    "though that overuse can have disastrous effects!" }), \
    ])

/* Indexes into the orders array. */
#define O_PATH  0
#define O_COST  1
#define O_TIME  2
#define O_LIMIT 3
#define O_DESC  4
#define O_LDESC 5

/*
 * This define contains commands for felix while he is preparing items.
 * It's an array of strings that get passed to command().
 * Each element is processed in order.
 * If one of the elements is an array, one will be chosen randomly.
 * Format is:
 *    mapping m_describe ([ "item": ({ "text", ({ "rand", "rand" }), }), ])
 *
 * item = The name of the item the text is for.
 * text = Some text to get passed to command().
 * rand = Some randomized text to get passed to command().
 *
 * Notes:
 * ~~~~~
 * An entry here is REQUIRED, if you don't have one, Felix will not work.
 * Do not have more elements then you have the time set for
 * as the increment between commands is dynamically generated.
 */
#define M_DESCRIBE ([ \
    "balm":({ "emote turns his back and gathers some items.", \
              "emote mixes some ingredients together.", \
              ({ "say Ooops!", "say Darn, how does this go again?" }), \
              "emote finishes mixing up the balm and puts it in a jar." }), \
   "salve":({ "emote gathers up some stuff and stuffs it in a jar.", }) \
    ])

/*
 * This is where optional extra's for items may be defined.
 * Format is:
 *   mapping m_extras ([ "item": ({ "desc", ({ options }), }), ]);
 *
 *    item = Must correspond with an item in the m_orders mapping.
 *    desc = Felix will 'say' this line before listing the actual options.
 * options = The actual options.
 *
 * Notes:
 * ~~~~~
 * You can specify multiple extra's per item, simple keep adding them on
 * in the order of: "desc", ({ options }).  He will process each of these
 * in the order they are specified.  If he encounters an error in the
 * format, he will stop processing and halt the order.
 *
 * The extras are passed onto the object when it is claimed via the
 * 'setup_extras' function and the extras are passed as an array with
 * the index order of options being as they were asked.  You have to do
 * the processing within the object itself to use this information.
 *
 * A second argument (object)this_player() is passed to that function as well
 * in case you wish to do anything based on the claimant.
 * Example declaration:
 *     public void setup_extras(string *extra, object player)
 */
#define M_EXTRAS ([ \
    "balm":({ "You can have your balm made in the following colours:", \
	({ "green", "yellow", "blue", "orange", "silver", "gold", \
	   "translucent" }), }), \
    ])

#endif  __FELIX_CARDOZA_ORDERS__

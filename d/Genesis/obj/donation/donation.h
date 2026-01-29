/*
 * /d/Genesis/obj/donation/donation.h
 *
 * Genesis is a toroid. Holy is the donut! This is the donation header file.
 *
 * Author: Mercade
 * Date  : August 4, 1998
 */

/*
 * DONATION_COLLECTORS
 *
 * List the names of the wizards responsible for collecting donations.
 */
#define DONATION_COLLECTORS ( ({ "lilith", "mercade", "mrpr", "cherek" }) )

/*
 * DONATION_BOARD
 * DONATION_BROOCH
 * DONATION_COLUMN
 * DONATION_MASTER
 * DONATION_OFFICE
 *
 * These contain the filenames of respectively the donation board, the
 * brooch, the column with the names of the contributors, the master
 * object that registers and the treasury office.
 */
#define DONATION_DIR    ("/d/Genesis/obj/donation/")
#define DONATION_BOARD  (DONATION_DIR + "board")
#define DONATION_BROOCH (DONATION_DIR + "brooch")
#define DONATION_COLUMN (DONATION_DIR + "column")
#define DONATION_MASTER ("/secure/donation")
#define DONATION_OFFICE (DONATION_DIR + "office")

/*
 * BROOCH_ID
 *
 * Unique name of the brooch item.
 */
#define DONOR_BROOCH_ID "_genesis_donor_brooch_"

/*
 * DONATION_SAVE
 *
 * This is the filename of the save object for all donations.
 */
#define DONATION_SAVE ("/data/donations")

/*
 * DONATION_LOG
 *
 * This is the filename of the log file for donations.
 */
#define DONATION_LOG ("/syslog/log/DONATIONS")

/*
 * DONATION_LIMIT_BRONZE
 * DONATION_LIMIT_SILVER
 * DONATION_LIMIT_GOLD
 * DONATION_LIMIT_PLATINUM
 *
 * These are the minimum amounts in converted US$ that a player should donate
 * to receive a particular donut.
 */
#define DONATION_LIMIT_BRONZE   ( 1)
#define DONATION_LIMIT_SILVER   (10)
#define DONATION_LIMIT_GOLD     (25)
#define DONATION_LIMIT_PLATINUM (50)

/*
 * DONATION_TOTAL_1998_EUR
 * DONATION_TOTAL_1998_USD
 *
 * Total amount donated in 1998 campaign in euro (converted) and US$.
 */
#define DONATION_TOTAL_1998_EUR (5086)
#define DONATION_TOTAL_1998_USD (5595)

/*
 * DONATION_CURRENCIES
 *
 * Only these currencies should be used. When players donate in another
 * currency, it should first be added here.
 *
 * Australia      AUS$
 * Canada         CAN$
 * Czech Republic CZC
 * European Union EUR
 * Great Britain  GBP
 * Israel         NIS
 * Norway         NKR
 * Poland         PLZ
 * Sweden         SEK
 * United States  US$
 */
#define DONATION_CURRENCIES ( ({ "AUS$", "CAN$", "CZC", "EUR", "GBP", "NIS", \
    "NKR", "PLZ", "SEK", "US$" }) )

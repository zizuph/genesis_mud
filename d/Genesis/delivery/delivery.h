/* /d/Genesis/delivery/delivery.h
 *
 * The include file for the delivery offices.
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 06/06/95
 *
 * Please include this file in your offices and use
 * these definitions.
 */

#define DELIVERY_DIR        "/d/Genesis/delivery/"
#define DELIVERY_MASTER     (DELIVERY_DIR + "master")
#define DELIVERY_PACKET     DELIVERY_DIR + "packet"
#define DELIVERY_OFFICE     DELIVERY_DIR + "office"
#define EXAMPLE_PACKET      DELIVERY_DIR + "example_packet"

#define PLAYER_O_DELIVERY   "_player_o_delivery"

/* The price is the price in silver coins. This uses the fact that within a
 * domain you get 24-48 silvers, and between domains 72-144.
 */
#define DELIVERY_GENERAL_EXP(price) (10 * (price))

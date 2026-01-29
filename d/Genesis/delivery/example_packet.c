/* /d/Genesis/delivery/example_packet.c
 * 
 * This is the example packet used in the delivery currently.
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 06/07/95
 *
 * This is the only valid packet currently. In the future it will be
 * possible to write own packets, but not yet. This file will then
 * show you how to write one.
 *
 * Anyway, the packet's shouldn't be modified too much to make them
 * recognizable for everyone. Since they're not worth anything anyway
 * there's no real need to change much.
 */

#include "/d/Genesis/delivery/delivery.h"

#pragma save_binary

inherit DELIVERY_PACKET;

/* that's all for now ;-) */
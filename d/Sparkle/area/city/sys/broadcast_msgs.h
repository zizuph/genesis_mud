/*
 *  /d/Sparkle/area/city/sys/broadcast_msgs.h
 *
 *  These are the default messages that will be broadcast from various
 *  locations in the city to nearby rooms. The name of the definition
 *  is of the format:
 *
 *      ORIGIN_TO_DESTINATION_TYPE
 *
 *      ORIGIN      - the room in which the movement to broadcast occured
 *      DESTINATION - the room in which the movement might be seen
 *      TYPE        - either ARRIVE or LEAVE depending on whether the
 *                    movement is to enter or leave the room.
 *
 *  So, for example, if we are wanting to have a standard broadcast for
 *  someone arriving on a nearby rooftop to the street below:
 *
 *      ROOF_TO_STREET_ARRIVE
 *
 *  ... would be the name we use for the define.
 */

#define  ROOF_TO_STREET_ARRIVE    \
           "A sudden movement catches your eye as MOVER perches on"  \
         + " a nearby rooftop."
#define  ROOF_TO_STREET_LEAVE     \
           "MOVER moves along a nearby rooftop and climbs out of sight."
#define  ALL_TO_ROOF_ARRIVE       \
           "MOVER arrives walking along the WHERE below."
#define  ALL_TO_ROOF_LEAVE        \
           "MOVER moves along the WHERE below and passes from view."
#define  BELOW_TO_DOCK_ALL        \
           "A sudden movement catches your eye between the gaps in the"  \
         + " boards at your feet."
#define  DOCK_TO_BELOW_ARRIVE     \
           "The boards above your head creak as someone moves onto the"  \
         + " dock."
#define  DOCK_TO_BELOW_LEAVE      \
           "Footfalls move along the dock above, growing fainter as"     \
         + "whoever might be up there moves out of earshot."

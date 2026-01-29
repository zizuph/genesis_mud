// The clock object
#undef   CLOCK
#define  CLOCK                       ("/d/Gondor/common/mordor/sys/clock")

// Domains who use this clock (for messages) :
#define  ME_DOMAINS  ({ "Gondor", "Shire", "Rhovanion", "Mordor", })

// Time definitions :
/*
#define  MINUTE                    0x0000003C // 60 seconds
#define  HOUR                      0x00000E10 // MINUTE * 60
#define  DAY                       0x00015180 // HOUR * 24
#define  MONTH                     0x00278D00 // DAY * 30
#define  YEAR                      0x01DA9C00 // MONTH * 12
*/
#define  MINUTE                          (60)
#define  HOUR                   (MINUTE * 60)
#define  DAY                      (HOUR * 24)
#define  MONTH                     (DAY * 30)
#define  YEAR                    (MONTH * 12)

#define  MOON_NEW                           1
#define  MOON_WAXING_CRESCENT               2
#define  MOON_WAXING_HALF                   3
#define  MOON_WAXING_GIBBOUS                4
#define  MOON_FULL                          5
#define  MOON_WANING_GIBBOUS                6
#define  MOON_WANING_HALF                   7
#define  MOON_WANING_CRESCENT               8

// The various days of interest in the year.  We pick the winter
// solstice to occur on Dec 21st as it typically does, but since
// our calendar is only 360 days, we'll just offset the others
// by three months each precisely to divide up the year.  However,
// Dec 22nd would be precisely 3 months past the start of our
// clock (what a coincidence) so we'll assume our clock starts
// on the autumn equinox, and combined with the assumptions
// about the moon, the cosmic alignment must mean armageddon!
#define  WINTER_SOLSTICE           0x0076A700 // Dec 22
#define  SPRING_EQUINOX            0x00ED4E00 // Mar 22
#define  SUMMER_SOLSTICE           0x0163F500 // Jun 22
#define  AUTUMN_EQUINOX            0x01DA9C00 // Sep 22

// We'll define 5 visible positions for the moon and sun, as
// we're being simple.  We're assuming the lands of interest
// are not on the equator, so days are varying length during
// the year.
#define  POSITION_NOT_VISIBLE               0
#define  POSITION_EASTERN_HORIZON           1
#define  POSITION_EASTERN_RISING            2
#define  POSITION_OVERHEAD                  3
#define  POSITION_WESTERN_SINKING           4
#define  POSITION_WESTERN_HORIZON           5

// Ring-quest stages :
#define  RQ_NONE                            0
#define  RQ_GANDALF_IN_BAGEND               1
#define  RQ_OSGILIATH_ATTACK                2
#define  RQ_LEFT_HOBBITON                   3
#define  RQ_ARRIVED_IN_RIVENDELL            4
#define  RQ_LEFT_RIVENDELL                  5
#define  RQ_ARRIVED_IN_LOTHLORIEN           6
#define  RQ_LEFT_LOTHLORIEN                 7
#define  RQ_LEFT_HENNETH_ANNUN              8
#define  RQ_ENTERED_MORDOR                  9
#define  RQ_QUEST_ENDED                    10

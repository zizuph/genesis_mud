/* some defines for the chariot and depot rooms */
 
/* locations of chariot along the route */
#define NO_WHERE     0
#define AT_DOCKS     1
#define IN_FOREST    2
#define IN_MOUNTAINS 3
#define IN_VALLEY    4
#define IN_CITY      5
#define AT_DEPOT     6
 
/* status of chariot */
#define IDLE         0
#define EN_ROUTE     1
 
/* path to arrival rooms */
#define DOCKS_ROOM    (ROOM_DIR+"docksdepot")
#define DEPOT_ROOM    (ROOM_DIR+"depot")
 
/* paths to incoming (docks->depot) and outgoing (depot->docks) chariots */
#define OUT_CHARIOT_ROOM      (ROOM_DIR+"on_out_chariot")
#define IN_CHARIOT_ROOM       (ROOM_DIR+"on_in_chariot")
 
/* property added to player when he/she pays for ride, removed when boards */
#define PAID_PROP             "_argos_chariot_paid_prop"
 
/* views outside chariot at different locations ('exa view' when on char.) */
#define VIEW ({                                                              \
   "No where.",                                                              \
   "The chariot is at the depot of the docks of Calia, the team of horses "+ \
   "awaiting the crack of the whip to depart.",                              \
   "A dense forest of hardwoods crowds the narrow path the team follows, "+  \
   "the trees whizzing by as you speed past them.",                          \
   "A stiff cold wind buffets the chariot as the team struggles to "+        \
   "pull it's load through steep mountains. Large boulders lay all "+        \
   "around landscape, the chariot following a marble road through "+         \
   "the rocky terrain.",                                                     \
   "The chariot is rolling along a marble road in a beautifully forested "+  \
   "valley, following a rushing river on its northern bank. Flowering "+     \
   "trees splash bits of white and pink in the shade of the towering "+      \
   "hardwoods.",                                                             \
   "The chariot is making its way through the streets of Argos, lined "+     \
   "with their white marble buildings and magnificent temples. The "+        \
   "streets are crowded with people and guards, making way for the "+        \
   "oncoming chariot.",                                                      \
   "The chariot is at the Strathmos of Argos surrounded by a high iron "+    \
   "fence. The team of horses await the crack of the whip to depart."        \
})
 
/* messages written to chariot room while en route to simulate trip */
#define TRIP_MSG ({                                                          \
   "The chariot rolls into oblivion.",                                       \
   "The chariot rolls into the depot at the docks of Calia.",                \
   "The chariot makes its way through a dense forest along a narrow path.",  \
   "The chariot slows as the strong team pulls it through the mountains.",   \
   "The chariot rolls down a marble road along a rushing river.",            \
   "The chariot makes its way through the busy streets of Argos.",           \
   "The chariot rolls into the fenced-in Strathmos of Argos."                \
})
 
/* standardized function to log errors */
void logerr(string msg) {
   log_file("chariot_err",ctime(time())+": "+msg+".\n");
}

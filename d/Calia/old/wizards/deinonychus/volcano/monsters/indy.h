#define BIT0 0	/* Bit-numbers for the quests */
#define BIT1 1
#define BIT2 2
#define GROUP 1	/* group of quest-bits */
#define LAST_QUEST 0	/* number of last available quest */

/* global variables */
string *quest_objects = ({
  "ptegg",
  "t-rex-tooth",
  "",
  "",
  "",
  "",
  "",
});

string *commands = ({
  "say I would be very glad if you could bring me an egg of a pteranodon.",
  "say What I miss in my collection is a huge tooth of a tyrannosaurus " +
       "rex. I would appreciate if you could bring me one.",
  "",
  "",
  "",
  "",
  "",
});

int *quest_points =
({
  1000,
  1000,
     0,
     0,
     0,
     0,
     0,
});


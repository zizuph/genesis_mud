#ifndef _KHALAKHOR_QUESTS
#define _KHALAKHOR_QUESTS 1

#define SW_SE_SPEIR   0
#define N_SPEIR_ISLES 1
#define CADU_NEW      2
#define CADU_OLD      3
#define GUILD_MISC    4    
    
#define KHALAKHOR_QUESTS ({ \
  ([ \
    "qm": "/d/Khalakhor/se_speir/port/npc/fahlmar", \
    "quests": ({ \
      ([ \
        "name": "Port Macdunn Introduction Tour", \
        "bit": 0, \
        "classification": "T1", \
        "old_xp": 50, \
        "new_xp": 450, \
        "new_bit": 10, \
        "hint": "intro_tour.txt", \
      ]), \
      ([ \
        "name": "Port Macdunn Inspection Tour", \
        "bit": 1, \
        "classification": "T1", \
        "old_xp": 70, \
        "new_xp": 150, \
        "new_bit": 11, \
        "hint": "intro_tour.txt", \
      ]), \
      ([ \
        "name": "Incense Quest", \
        "bit": 2, \
        "classification": "T2I1", \
        "old_xp": 2000, \
        "new_xp": 4500, \
        "new_bit": 12, \
        "hint": "incense.txt", \
      ]), \
      ([ \
        "name": "Post Office Tour", \
        "bit": 3, \
        "classification": "T1", \
        "old_xp": 150, \
        "new_xp": 900, \
        "new_bit": 13, \
        "hint": "post_office.txt", \
      ]), \
      ([ \
        "name": "Honeycombs", \
        "bit": 4, \
        "classification": "T2I2", \
        "old_xp": 2500, \
        "new_xp": 8400, \
        "new_bit": 14, \
        "hint": "honeycombs.txt", \
      ]), \
      ([ \
        "name": "Blubber Oil", \
        "bit": 5, \
        "classification": "I2", \
        "old_xp": 1300, \
        "new_xp": 7500, \
        "new_bit": 15, \
        "hint": "incense.txt", \
      ]), \
      ([ \
        "name": "Eil-Galaith Entrance", \
        "bit": 6, \
        "classification": "P1I1", \
        "old_xp": 150, \
        "new_xp": 750, \
        "new_bit": 16, \
        "hint": "galaith.txt", \
      ]), \
    }), \
  ]), \
  ([ \
    "qm": "/d/Khalakhor/inisi/roke/npc/angler", \
    "quests": ({ \
      ([ \
        "name": "Cadu baits", \
        "bit": 100, \
        "xp": 750, \
        "classification": "T2I1", \
        "hint": "some-hint-file.txt" \
      ]) \
    }) \
  ]), \
  ([ \
    "group": "GUILDS", \
    "quests": ({ \
      ([ \
        "name": "Blademaster Membership", \
        "bit": 80, \
        "orb": "always_false", \
      ]), \
    }) \
  ]) \
})
#endif

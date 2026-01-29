/* 	this is a special file of the town Gelan

    coder(s):   Merlin and Maniac

    history:    28.9.94     everything south of gate removed Maniac
                    8.94    mapping corrected & completed   Maniac 
                    8.94    documentation expanded          Maniac
                10. 2.93    installed some documentation    Merlin
                17. 1.93    created                         Merlin

    purpose:	mapping with with the whole connection graph of the rooms
                in Gelan. 
                Pease be careful when adding a new room, you have to add
                the room to all rooms between the room and the nearest 
                meeting room

    to do:      none
    bug:        none known
*/


/*
 * The mapping has entry for all rooms with the guard system. Modify this
 * mapping only when you're really sure what you are doing! Read the
 * explanation below, and if you're still not sure check with Merlin
 * or Maniac.
 *
 * The mapping is quite a deep structure. Each room entry has an array 
 * associated with it containing all the information necessary to 
 * allow one to reach the room from any other room in the system.
 * The array entries are as follows, and will be further explained
 * below.
 *
 *          [0]     nearest meeting point of the room
 *          [1]     array with the directions to all meeting point rooms 
 *                  ([1][0] - [1][3])
 *          [2]     mapping containing any directions to get to 
 *                  any rooms for which this room is on its path from
 *                  the nearest meeting point. 
 *                  You have also to include the actual room in the mapping,
 *                  as direction give DUMMY, NOT 0 !!!
 *
 * Some further explanations are clearly in order here. Firstly, what are
 * meeting points? Well basically Gelan is divided into four sectors,
 * with a certain room at their centre called the "meeting point" of that 
 * sector. The sectors are north, south, east and west.
 *       The meeting points are: 
 *                           "standby_guards" - south
 *                           "square_westend" - west
 *                           "square_eastend" - east
 *                           "square_northend_center_e" - north
 *
 * Observe that the mapping entry for each room shows the correct 
 * next direction to go in order to get to a any meeting point. 
 * This means that from any room one can get to any meeting point you want.
 *
 * Now, in each sector, the meeting point is a nucleus from which one can
 * reach any room in that sector. Each meeting point entry carries the  
 * next direction to go in order to reach any room in that sector. For any
 * room that is right next to the meeting point one simply has to follow 
 * that direction. But if
 * there are intervening rooms between the meeting point and some other 
 * room in that sector, intervening rooms must carry the next direction on
 * the path to reach rooms further out in that sector. 
 * Thus from any meeting point in a sector we can reach any room in that 
 * sector. 
 *
 * Coupling these two conclusion statements together, we can now reach 
 * any room in Gelan from any other room in Gelan, first by going to the
 * nearest meeting point to that room if necessary, and then following 
 * the directions all the way to the destination.
 * 
 * NOTE 1:  
 *   MP_SOUTH = 0
 *   MP_WEST = 1
 *   MP_EAST = 2
 *   MP_NORTH = 3
 * 
 * NOTE 2: For clarity, the rest of the path from one room to 
 * another has been added in comments where appropriate.
 * For instance, taking a hypothetical example room entry:
 *    "room_1":       ({ MP_NORTH,
 *                       ({"south", "south", "north", "south"}),
 *                       (["room_1":                   DUMMY,
 *                         "room_2":                   "east",
 *                                                     * south *
 *                         "room_3":                   "west"])})
 *
 *  To get to room_2 from room_1 one has to go east then south,
 *  to get to room_3 from room_1, one only has to go west.
 *  --
*/


mapping rooms = ([
     "alchemist":     ({ MP_WEST,
                        ({"east",      "east",     "east",     "east" }),
                        (["alchemist":                        DUMMY])}),

     "bakery":        ({ MP_SOUTH,
                        ({"west",      "west",     "west",     "west" }),
                        (["bakery":                           DUMMY])}),

     "bank":          ({ MP_WEST,
                        ({"east",      "east",     "east",     "east" }),
                        (["bank":                             DUMMY,
                          "banklockers":                    "south"])}),

     "banklockers":   ({ MP_WEST,
                        ({"north",     "north",    "north",    "north"}),
                        (["banklockers":                      DUMMY])}),

     "blacksmith":    ({ MP_WEST,
                        ({"east" ,     "north",    "east",     "north"}),
                        (["blacksmith":                       DUMMY])}),

     "castle_road_e1":({ MP_NORTH,
                        ({"south",     "southwest","south",    "south"}),
                        (["castle_road_e1":                   DUMMY,
                          "guards_info":                     "east",
                          "guards_offices":                  "east",
                          "castle_road_e2":                 "north",
                          "guards_headquarter":             "north",
                          "guards_chief":                   "north",
                          "guards_powdery_n":           "northwest",
                          "guards_restroom_n":          "northwest",
                          "guards_armoury_n":           "northwest",
                          "castle_road_w2":             "northwest",
                          "square_northend_e":          "southeast",
                          "guards_jail_nice":           "southeast",
                          "guards_jail_bad":            "southeast"])}),

     "castle_road_e2":({ MP_NORTH,
                         ({"south",    "south",    "south",    "south"}),
                         (["castle_road_e2":                  DUMMY,
                           "guards_headquarter":             "east",
                           "guards_chief":                   "east",
                           "guards_powdery_n":               "west",
                           "guards_restroom_n":              "west",
                           "guards_armoury_n":               "west",
                           "castle_road_w2":                 "west"])}),

     "castle_road_w1":({ MP_NORTH,
                         ({"south",    "south",    "south","southeast"}),
                         (["castle_road_w1":                  DUMMY,
                           "guards_powdery_n":              "north",
                           "guards_restroom_n":             "north",
                           "guards_armoury_n":              "north",
                           "castle_road_w2":                "north",
                           "castle_road_e1":                 "east",
                           "castle_road_e2":            "northeast",
                           "guards_info":                    "east",
                                                         /* east */
                           "guards_offices":                 "east",
                           "guards_headquarter":        "northeast",
                           "guards_chief":              "northeast",
                           "square_northend_w":         "southwest",
                           "square_northend_center_w":      "south"])}),

     "castle_road_w2":({ MP_NORTH,
                         ({"south",    "south",    "south",    "south"}),
                         (["castle_road_w2":                  DUMMY,
                           "guards_powdery_n":               "west",
                           "guards_restroom_n":              "west",
                           "guards_armoury_n":               "west",
                           "castle_road_e2":                 "east",
                           "guards_headquarter":             "east",
                           "guards_chief":                   "east",
                           "castle_road_e1":            "southeast",
                           "guards_info":               "southeast",
                                                        /* east */
                           "guards_offices":            "southeast",
                           "square_northend_e":         "southeast",
                                                      /* southeast */
                           "guards_jail_nice":          "southeast",
                           "guards_jail_bad":           "southeast"])}),

     "citizen":       ({ MP_EAST,
                         ({"south",    "south",    "south",    "south"}),
                         (["citizen":                         DUMMY])}),

     "fountain_e":    ({ MP_EAST,
                         ({"southwest","west",     "east",    "north"}),
                         (["fountain_e":                      DUMMY,
                           "fountain_statue_e":              "west",
                           "fountain_southend_e":         "southwest"])}),

     "fountain_northend_e":({ MP_EAST,
                         ({"south",    "west",     "east",    "north"}),
                         (["fountain_northend_e":             DUMMY])}),

     "fountain_northend_w":({ MP_WEST,
                         ({"south",    "west",     "east",    "north"}),
                         (["fountain_northend_w":             DUMMY])}),

     "fountain_southend_e":({ MP_EAST,
                         ({"south",    "west",  "northeast",  "north"}),
                         (["fountain_southend_e":             DUMMY])}),

     "fountain_southend_w":({ MP_WEST,
                         ({"south",    "west",     "east",    "north"}),
                         (["fountain_southend_w":             DUMMY])}),

     "fountain_statue_e":({ MP_EAST,
                         ({"south",    "west",     "east",    "north"}),
                         (["fountain_statue_e":               DUMMY])}),

     "fountain_statue_w":({ MP_WEST,
                         ({"south",    "west",     "east",    "north"}),
                         (["fountain_statue_w":               DUMMY])}),

     "fountain_w":    ({ MP_WEST,
                         ({"southeast","west",     "east",    "north"}),
                         (["fountain_w":                      DUMMY,
                           "fountain_statue_w":              "east"])}),

     "gate":          ({ MP_SOUTH,
                         ({"east",    "north",    "north",   "north"}),
                         (["gate":                            DUMMY,
                           "standby_guards":                 "east"])}), 

     "grocery":       ({ MP_WEST,
                         ({"east",     "north",    "east",    "north"}),
                         (["grocery":                         DUMMY])}),

     "guards_armoury_n":({ MP_NORTH,
                         ({"east",     "east",     "east",    "east" }),
                         (["guards_armoury_n":                DUMMY,
                           "guards_powdery_n":               "down",
                           "guards_restroom_n":                "up"])}),

     "guards_armoury_se":({ MP_SOUTH,
                         ({"southwest","west",     "west",    "west" }),
                         (["guards_armoury_se":                DUMMY,
                           "guards_powdery_se":               "down",
                           "guards_restroom_se":                "up"])}),

     "guards_armoury_sw":({ MP_SOUTH,
                         ({"east",     "east",     "east",    "east" }),
                         (["guards_armoury_sw":                DUMMY,
                           "guards_powdery_sw":               "down",
                           "guards_restroom_sw":                "up",
                           "gate":                       "southeast"])}),

     "guards_chief":  ({ MP_NORTH,
                         ({"south",    "west",     "south",   "west"}),
                         (["guards_chief":                     DUMMY,
                           "guards_offices":                 "south",
                           "guards_jail_nice":               "south",
                           "guards_jail_bad":                "south"])}),

     "guards_headquarter":({ MP_NORTH,
                         ({"south",    "west",     "south",   "west"}),
                         (["guards_headquarter":               DUMMY,
                           "guards_chief":                    "east",
                           "guards_info":                    "south",
                           "guards_offices":                  "east",
                           "square_northend_e":              "south",
                           "guards_jail_nice":               "south",
                           "guards_jail_bad":                "south"])}),

     "guards_info":   ({ MP_NORTH,
                         ({"south",    "west",     "south",   "south"}),
                         (["guards_info":                      DUMMY,
                           "guards_offices":                  "east",
                           "guards_headquarter":              "east",
                           "guards_chief":                   "north",
                           "square_northend_e":              "south",
                           "guards_jail_nice":                "east",
                           "guards_jail_bad":                 "east"])}),

     "guards_jail_bad":({ MP_NORTH,
                         ({"up",       "up",       "up",      "up"  }),
                         (["guards_jail_bad":                  DUMMY])}),

     "guards_jail_nice":({ MP_NORTH,
                         ({"west",     "west",     "westt",   "west"  }),
                         (["guards_jail_nice":                 DUMMY,
                           "guards_jail_bad":                 "down",
                           "guards_offices":                 "north",
                           "guards_chief":                   "north"])}),

     "guards_offices":({ MP_NORTH,
                         ({"south",    "west",     "south",   "west"}),
                         (["guards_offices":                   DUMMY,
                           "guards_chief":                   "north",
                           "guards_jail_nice":               "south",
                           "guards_jail_bad":                "south"])}),

     "guards_powdery_n":({ MP_NORTH,
                         ({"up",       "up",       "up",      "up"  }),
                         (["guards_powdery_n":                 DUMMY])}),

     "guards_powdery_se":({ MP_SOUTH,
                         ({"up",       "up",       "up",      "up"  }),
                         (["guards_powdery_se":                DUMMY])}),

     "guards_powdery_sw":({ MP_SOUTH,
                         ({"up",       "up",       "up",      "up"  }),
                         (["guards_powdery_sw":                DUMMY])}),

     "guards_restroom_n":({ MP_NORTH,
                         ({"down",     "down",     "down",    "down"}),
                         (["guards_restroom_n":                DUMMY])}),

     "guards_restroom_se":({ MP_SOUTH,
                         ({"down",     "down",     "down",    "down"}),
                         (["guards_restroom_se":               DUMMY])}),

     "guards_restroom_sw":({ MP_SOUTH,
                         ({"down",     "down",     "down",    "down"}),
                         (["guards_restroom_sw":               DUMMY])}),

     "hairdresser":   ({ MP_EAST,
                         ({"west",     "west",     "west",    "west"}),
                         (["hairdresser":                      DUMMY])}),

     "inn":           ({ MP_NORTH,
                         ({"south",    "south",    "south",   "south"}),
                         (["inn":                              DUMMY,
                           "inn_sleeping":                      "up",
                           "inn_cellar":                      "down"])}),

     "inn_cellar":    ({ MP_NORTH,
                         ({"up",       "up",       "up",      "up"   }),
                         (["inn_cellar":                       DUMMY])}),

     "lavatory":      ({ MP_EAST,
                         ({"west",     "west",     "north",    "west" }),
                         (["lavatory":                         DUMMY])}),

     "palace_road_ne":({ MP_SOUTH,
                         ({"south",   "northwest","northeast","north"}),
                         (["palace_road_ne":                   DUMMY,
                           "fountain_southend_e":            "north",
                                                          /* north */
                           "square_southend_center_e":       "north",
                           "square_southend_e":          "northeast",
                           "bakery":                     "northeast",
                                                         /* east */
                           "stables_e":                       "east"])}),

     "palace_road_nw":({ MP_SOUTH,
                         ({"south","northwest", "northeast","northeast"}),
                         (["palace_road_nw":                   DUMMY,
                           "fountain_southend_w":            "north",
                                                          /* north */ 
                           "grocery":                    "northwest",
                                                         /* west */
                           "square_southend_center_w":       "north",
                           "square_southend_w":          "northwest",
                           "stables_w":                       "west"])}),

     "palace_road_se":({ MP_SOUTH,
                         ({"south", "northwest",  "north",   "north"}),
                         (["palace_road_se":                   DUMMY,
                           "fountain_southend_e":            "north",
                                                           /* north */
                                                           /* north */
                           "bakery":                         "north",
                                                       /* northeast */
                                                           /* east */
                           "square_southend_center_e":       "north",
                                                          /* north */
                           "square_southend_e":              "north",
                                                      /* northeast */    
                           "palace_road_ne":                 "north",
                           "stables_e":                      "north"
                                                           /*east*/ ])}),

     "palace_road_sw":({ MP_SOUTH,
                         ({"southeast","north",    "north",    "north"}),
                         (["palace_road_sw":                   DUMMY,
                           "fountain_southend_w":            "north",
                                                       /* north */
                                                       /* north */
                           "grocery":                        "north",
                                                     /* northwest */
                                                        /* west */
                           "square_southend_w":              "north",
                                                      /* northwest */
                           "square_southend_center_w":       "north",
                                                          /* north */
                           "stables_w":                      "north",
                                                           /* west */
                           "palace_road_nw":                 "north",
                           "guards_armoury_sw":               "west",
                           "guards_restroom_sw":              "west",
                                                             /* up */ 
                           "guards_powdery_sw":               "west",
                                                            /* down */
                           "gate":                           "south"])}),

     "pillory_e":     ({ MP_NORTH,
                         ({"south",    "west",     "east",     "north"}),
                         (["pillory_e":                        DUMMY,
                           "square_central_e":               "south",
                           "pillory_w":                       "west",
                           "square_central_w":           "southwest"])}),

     "pillory_w":     ({ MP_NORTH,
                         ({"south",    "west",     "east",     "northeast"}),
                         (["pillory_w":                        DUMMY,
                           "square_central_w":               "south",
                           "guards_powdery_n":               "north",
                           "guards_restroom_n":              "north",
                           "guards_armoury_n":               "north",
                           "castle_road_w2":             "northeast",
                                                     /* northwest */
                                                     /* north */
                           "square_nw":                       "west",
                           "inn":                        "northwest",
                                                         /* north */
                           "post":                       "northwest",
                                                         /* west */
                           "pillory_e":                       "east",
                           "square_central_e":                "east"])}),

     "post":          ({ MP_NORTH,
                         ({"east",     "south",    "east",     "east"}),
                         (["post":                             DUMMY,
                           "square_corner_nw":               "south",
                           "alchemist":                      "south"
                                                          /* west */ ])}),

     "road_e":        ({ MP_EAST,
                         ({"west",     "west",     "west",     "west"}),
                         (["road_e":                           DUMMY])}),

     "road_w":        ({ MP_WEST,
                         ({"east",     "east",     "east",     "east"}),
                         (["road_w":                           DUMMY])}),

     "school":        ({ MP_EAST,
                         ({"west",     "west",     "west",     "west"}),
                         (["school":                           DUMMY])}),

     "shop":          ({ MP_WEST,
                         ({"east",     "east",     "east",     "east"}),
                         (["shop":                             DUMMY,
                           "shopback":                       "up"])}),

     "shopback":      ({ MP_WEST,
                         ({"down",    "down",    "down",    "down"}),
                         (["shopback":                         DUMMY])}),

     "square_central_e":({ MP_NORTH,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_central_e":                 DUMMY])}),

     "square_central_w":({ MP_NORTH,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_central_w":                 DUMMY])}),

     "square_corner_ne":({ MP_EAST,
                         ({"southwest","west",    "south", "northwest"}),
                         (["square_corner_ne":                 DUMMY])}),

     "square_corner_nw":({ MP_WEST,
                         ({"southeast","south",   "east",  "northeast"}),
                         (["square_corner_nw":                 DUMMY,
                           "alchemist":                       "west"])}),

     "square_corner_se":({ MP_EAST,
                         ({"southwest","west",    "north",     "north"}),
                         (["square_corner_se":                 DUMMY])}),

     "square_corner_sw":({ MP_WEST,
                         ({"southeast","north",    "east",     "north"}),
                         (["square_corner_sw":                 DUMMY,
                           "grocery":                         "south"])}),

     "square_e":        ({ MP_EAST,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_e":                         DUMMY,
                           "fountain_northend_e":             "west",
                                                            /* west */
                           "square_fountain_ne":              "west"])}),

     /* east meeting point */
     "square_eastend":({ MP_EAST,
                         ({"southwest","west",     0,         "northwest"}),
                         (["square_eastend":                   DUMMY,
                           "square_corner_ne":           "northwest",
                                                         /* north */
                           "citizen":                        "north",
                                                         /* north */
                           "square_mide":                "northwest",
                                                         /* west */
                           "square_en":                  "northwest",
                           "square_eastend_n":               "north",
                           "school":                         "north",
                                                           /* east */
                           "fountain_northend_e":             "west",
                                                           /* west */
                                                           /* west */
                           "square_fountain_ne":              "west",
                                                           /* west */
                           "square_e":                        "west",
                           "road_e":                          "east",
                           "fountain_statue_e":          "southwest",
                                                           /* west */
                                                           /* west */
                           "fountain_e":                 "southwest",
                                                           /* west */
                           "fountain_southend_e":        "southwest",
                                                           /* west */
                                                       /* southwest */
                           "square_fountain_e":          "southwest",
                           "square_eastend_s":               "south",
                           "hairdresser":                    "south",
                                                           /* east */
                           "square_se":                  "southwest",
                                                       /* southwest */
                           "square_corner_se":           "southwest",
                                                         /* south */
                           "lavatory":                       "south"      
                                                         /* south */ 
                                                                  ])}),

     "square_eastend_n":({ MP_EAST,
                         ({"southwest","west",     "south","northwest"}),
                         (["square_eastend_n":                 DUMMY,
                           "citizen":                        "north",
                           "school":                         "east"])}),

     "square_eastend_s":({ MP_EAST,
                         ({"southwest","west",     "north",    "north"}),
                         (["square_eastend_s":                 DUMMY,
                           "lavatory":                       "south",
                           "hairdresser":                     "east"])}),

     "square_en":     ({ MP_EAST,
                         ({"southwest","west","southeast","northwest"}),
                         (["square_en":                        DUMMY,
                           "square_mide":                     "west",
                           "square_corner_ne":               "north"])}),

     "square_fountain_e":({ MP_EAST,
                         ({"southwest","west","northeast",     "north"}),
                         (["square_fountain_e":                DUMMY,
                           "fountain_statue_e":               "west",
                                                            /* west */
                           "fountain_e":                      "west",
                           "fountain_southend_e":             "west",
                                                        /* southwest */
                           "square_se":                  "southwest",
                           "square_corner_se":               "south"])}),

     "square_fountain_ne":({ MP_EAST,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_fountain_ne":               DUMMY,
                           "fountain_northend_e":             "west"])}),

     "square_fountain_nw":({ MP_WEST,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_fountain_nw":               DUMMY,
                           "fountain_northend_w":             "east"])}),

     "square_fountain_w":({ MP_WEST,
                         ({"southeast","northwest","east",     "north"}),
                         (["square_fountain_w":                DUMMY,
                           "fountain_statue_w":               "east",
                                                            /* east */
                           "fountain_w":                      "east",
                           "fountain_southend_w":        "southeast",
                                                           /* east */ 
                           "grocery":                         "south",
                                                            /* south */
                           "square_corner_sw":               "south",
                           "square_sw":                  "southeast"])}),

     "square_mide":   ({ MP_EAST,
                         ({"south",    "west",     "east",     "north"}),
                         (["square_mide":                      DUMMY])}),

     "square_midw":   ({ MP_WEST,
                         ({"south",    "west",     "east", "northeast"}),
                         (["square_midw":                      DUMMY])}),

     "square_ne":     ({ MP_NORTH,
                         ({"southwest","west","southeast", "northwest"}),
                         (["square_ne":                        DUMMY,
                           "square_corner_ne":                "east"])}),


     /* North meeting point*/
     "square_northend_center_e": ({ MP_NORTH,
                         ({"south", "southwest", "southeast", 0}),
                         (["square_northend_center_e":         DUMMY,
                           "castle_road_e1":                 "north", 
                           "castle_road_e2":                 "north", 
                                                           /* north */
                           "castle_road_w1":             "northwest", 
                           "castle_road_w2":             "northwest", 
                                                           /* north */
                           "guards_info":                     "east", 
                                                           /* north */
                           "inn":                             "west", 
                                                           /* west */
                                                           /* north */
                           "jail":                            "east", 
                                                           /* east */
                           "pillory_e":                      "south",
                           "pillory_w":                  "southwest",
                           "post":                            "west",
                                                           /* west */
                                                           /* west */
                           "square_corner_ne":           "southeast",
                                                           /* east */
                           "square_central_e":               "south",
                                                           /* south */
                           "square_central_w":           "southwest",
                                                           /* south */
                           "square_ne":                  "southeast",
                           "square_northend_center_w":        "west",
                           "square_northend_e":               "east",
                           "square_northend_w":               "west",
                                                            /* west */
                           "square_nw":                  "southwest"
                                                            /* west */ 
                           ]) }),   

     "square_northend_center_w": ({ MP_NORTH,  
                        ({"southeast","southwest","southeast","east"}), 
                        ([ "square_northend_center_w":     DUMMY,
                           "square_northend_w":            "west",
                           "post":                         "west",
                                                        /* west */
                           "inn":                          "west"
                                                       /* north */])}),
  
     "square_northend_e":   ({ MP_NORTH,
                      ({"southwest","southwest","south","west"}),
                      (["square_northend_e":               DUMMY,
                        "guards_info":                    "north"])}),
 
     "square_northend_w":   ({ MP_NORTH,
                      ({"south","southwest","southeast","east"}),
                      (["square_northend_w":               DUMMY,
                        "post":                    "west",
                        "inn":                     "north"])}),

     "square_nw":     ({ MP_NORTH,
                        ({"southeast","southwest","southeast","east"}),
                        (["square_nw":                       DUMMY])}),
                        
 
     "square_se":     ({ MP_EAST,
                         ({"southwest","west", "northeast",    "north"}),
                         (["square_se":                        DUMMY])}),

     "square_southend_center_e":({ MP_SOUTH,
                         ({"south",    "west",     "northeast","north"}),
                         (["square_southend_center_e":         DUMMY,
                           "fountain_southend_e":            "north"])}),

     "square_southend_center_w":({ MP_SOUTH,
                         ({"south",    "northwest","east",   "north"}),
                         (["square_southend_center_w":         DUMMY,
                           "fountain_southend_w":            "north"])}),

     "square_southend_e":({ MP_SOUTH,
                         ({"southwest","west",  "northeast", "north"}),
                         (["square_southend_e":                DUMMY,
                           "bakery":                          "east"])}),

     "square_southend_w":({ MP_SOUTH,
                         ({"southeast","north",    "east",   "north"}),
                         (["square_southend_w":                DUMMY,
                           "grocery":                         "west"])}),

     "square_sw":     ({ MP_WEST,
                         ({"southeast","northwest","east",   "north"}),
                         (["square_sw":                        DUMMY,
                           "fountain_southend_w":             "east"])}), 

     "square_w":      ({ MP_WEST,
                         ({"south",    "west",     "east",   "northeast"}),
                         (["square_w":                         DUMMY,
                           "fountain_northend_w":             "east",
                                                            /* east */
                           "square_fountain_nw":              "east"])}),

    /* west meeting point */
     "square_westend":({ MP_WEST,
                         ({"southeast",0,          "east", "northeast"}),
                         (["square_westend":                   DUMMY,
                           "shopback":                       "north",
                                                           /* west */
                                                            /* up */
                           "alchemist":                  "northeast",
                                                         /* north */
                                                          /* west */
                           "grocery":                    "southeast",
                                                          /* south */
                                                          /* south */
                           "square_corner_nw":           "northeast",
                                                         /* north */
                           "shop":                           "north",
                                                         /* west */
                           "square_westend_n":               "north",
                           "square_wn":                  "northeast",
                           "road_w":                          "west",
                           "square_w":                        "east",
                           "square_fountain_nw":              "east",
                                                           /* east */
                           "fountain_northend_w":             "east",
                                                           /* east */
                                                           /* east */
                           "fountain_southend_w":         "southeast",
                                                        /* southeast */
                                                           /* east */
                           "bank":                           "south",
                                                           /* west */
                           "square_westend_s":               "south",
                           "square_fountain_w":          "southeast",
                           "fountain_w":                 "southeast",
                                                          /* east */
                           "fountain_statue_w":          "southeast",
                                                         /* east */
                                                         /* east */
                           "banklockers":                    "south",
                                                         /* west */
                           "blacksmith":                     "south",
                                                         /* south */
                           "square_corner_sw":           "southeast",
                                                         /* south */
                           "square_sw":                  "southeast"
                                                       /* southeast */])}),

     "square_westend_n":({ MP_WEST,
                         ({"southeast","south",    "east",     "northeast"}),
                         (["square_westend_n":                 DUMMY,
                           "shop":                            "west",
                           "shopback":                        "west"
                                                             /* up */])}),
     "square_westend_s":({ MP_WEST,
                         ({"southeast","north",    "east",     "northeast"}),
                         (["square_westend_s":                 DUMMY,
                           "bank":                            "west",
                           "banklockers":                     "west",
                           "blacksmith":                     "south"])}),

     "square_wn":     ({ MP_WEST, 
                         ({"southeast","southwest","east",     "northeast"}),
                         (["square_wn":                        DUMMY,
                           "alchemist":                      "north",
                                                            /* west */
                           "square_corner_nw":               "north",
                           "square_midw":                     "east"])}),

     "stables_e":     ({ MP_SOUTH,
                         ({"west",     "west",     "west",     "west"}),
                         (["stables_e":                        DUMMY])}),

     "stables_w":     ({ MP_SOUTH,
                         ({"east",     "east",     "east",     "east"}),
                         (["stables_w":                        DUMMY])}),

     /* south meeting point */
     "standby_guards":({ MP_SOUTH,
                         ({0,          "north",    "north",    "north"}),
                         (["standby_guards":                   DUMMY,
                           "fountain_southend_w":        "northwest",
                                                          /* north */
                                                          /* north */
                                                          /* north */
                           "fountain_southend_e":            "north",
                                                          /* north */
                                                          /* north */
                                                          /* north */
                           "grocery":                    "northwest",
                                                         /* north */
                                                      /* northwest */
                                                         /* west */
                           "square_southend_w":          "northwest",
                                                         /* north */
                                                     /* northwest */
                           "square_southend_center_w":   "northwest",
                                                        /* north */
                                                        /* north */
                           "sguare_southend_center_e":       "north",
                                                        /* north */
                                                        /* north */
                           "square_southend_e":              "north",
                                                        /* north */
                                                    /* northeast */
                           "bakery":                         "north",
                                                        /* north */
                                                    /* northeast */
                                                        /* east */
                           "stables_w":                  "northwest",
                                                       /* north */
                                                       /* west */
                           "guards_armoury_sw":          "northwest",
                                                        /* west */
                           "guards_restroom_sw":         "northwest",
                                                       /* west */
                                                        /* up */
                           "guards_powdery_sw":          "northwest",
                                                       /* west */
                                                       /* down */
                           "palace_road_sw":             "northwest",
                           "palace_road_se":                 "north",
                           "palace_road_ne":                 "north",
                                                          /* north */
                           "palace_road_nw":             "northwest",
                                                          /* north */
                           "guards_armoury_se":          "northeast",
                           "guards_restroom_se":         "northeast",
                                                         /* up */
                           "guards_powdery_se":          "northeast",
                                                          /* down */
                           "gate":                            "west"])}),
     ]);


/* 	this file contains the pathes to all objects in Gelan, please modify
    here.

    The id names have to be U N I Q U E  !!!!!
    The best is to choose ids which are the filename of the file without a
    path, for rooms using the guard system this is essential !


    coder(s):   Merlin

    history:
                21.10.94    added bottle and orgulas        Deinonychus
                 5.10.94    added patients                  Merlin
                 5.10.94    added stdDoc and contract       Merlin
                20.09.94    added all my objects            Maniac 
		14.09.94    added poster-textfiles	    Deinonychus
                 7.9.94     added the board room            Maniac
                03.02.94    updated to the inn              Deinonychus
		18. 4.93    neatened things a bit           Glykron
                14. 4.93    changed school to Damax         Merlin	
	         7. 4.93    added Dinos 'desc'              Merlin
                27. 3.93    added SNARF_HOSPITAL	    Snarf
	        27. 2.93    added lavatory rooms            Merlin
                26. 2.93    moved palace road               Merlin
                26. 2.93    added poster                    Deinonychus
                24. 2.93    added map and map_box           Deinonychus
                23. 2.93    inserted the rest of my files   Zawion
                21. 2.93    moved rooms and doors           Merlin
                20. 2.93    added hair_shadow               Glykron
                20. 2.93    added guide, moved rooms        Merlin
                20. 2.93    added tour_ticket               Deinonychus
                16. 2.93    some updated                    Merlin
                15. 2.93    moved some rooms                Merlin
                15. 2.93    added SNARF_FOUNTAIN to paths   Snarf
                12. 2.93    moved some rooms                Merlin
                10. 2.93    moved monsters                  Merlin
                 8. 2.93    added DAMAX_ROOMS to paths      Damax
                 8. 2.93    removed an error                Merlin
                 7. 2.93    removed error                   Merlin
                25.01.93    updated to the inn              Zawion
                24. 1.93    some files moved                Merlin
                14. 1.93    created                         Merlin

*/

mapping rooms_path =        ([
    "alchemist":                TOWN_ROOMS          + "alchemist.c",
    "bakery":                   MANIAC_ROOMS        + "bakery.c",
    "bank":                     GLYKRON_ROOMS       + "bank.c",
    "banklockers":              TOWN_ROOMS          + "banklockers.c",
    "blacksmith":               MANIAC_ROOMS        + "blacksmith.c",
    "boardroom":                TOWN_ROOMS          + "boardroom.c",
    "castle_road_e1":           DINO_ROOMS          + "castle_road_e1.c",
    "castle_road_e2":           DINO_ROOMS          + "castle_road_e2.c",
    "castle_road_w1":           DINO_ROOMS          + "castle_road_w1.c",
    "castle_road_w2":           DINO_ROOMS          + "castle_road_w2.c",
    "citizen":                  TOWN_ROOMS          + "citizen.c",
    "drawbridge":               MERLIN_ROOMS        + "drawbridge.c",
    "entrance_road":            MERLIN_ROOMS        + "entrance_road.c",
    "fountain_e":               MANIAC_ROOMS        + "fountain_e.c",
    "fountain_northend_e":      MANIAC_ROOMS        + "fountain_northend_e.c",
    "fountain_northend_w":      MANIAC_ROOMS        + "fountain_northend_w.c",
    "fountain_southend_e":      MANIAC_ROOMS        + "fountain_southend_e.c",
    "fountain_southend_w":      MANIAC_ROOMS        + "fountain_southend_w.c",
    "fountain_statue_e":        MANIAC_ROOMS        + "fountain_statue_e.c",
    "fountain_statue_w":        MANIAC_ROOMS        + "fountain_statue_w.c",
    "fountain_w":               MANIAC_ROOMS        + "fountain_w.c",
    "gate":                     MERLIN_ROOMS        + "gate.c",
    "grocery":                  TOWN_ROOMS          + "grocery.c",
    "guards_armoury_n":         TOWN_ROOMS          + "guards_armoury_n.c",
    "guards_armoury_se":        TOWN_ROOMS          + "guards_armoury_se.c",
    "guards_armoury_sw":        TOWN_ROOMS          + "guards_armoury_sw.c",
    "guards_chief":             TOWN_ROOMS          + "guards_chief.c",
    "guards_headquarter":       TOWN_ROOMS          + "guards_headquarter.c",
    "guards_info":              DINO_ROOMS          + "guards_info.c",
    "guards_jail_bad":          TOWN_ROOMS          + "guards_jail_bad.c",
    "guards_jail_nice":         TOWN_ROOMS          + "guards_jail_nice.c",
    "guards_offices":           TOWN_ROOMS          + "guards_offices.c",
    "guards_powdery_n":         TOWN_ROOMS          + "guards_powdery_n.c",
    "guards_powdery_se":        TOWN_ROOMS          + "guards_powdery_se.c",
    "guards_powdery_sw":        TOWN_ROOMS          + "guards_powdery_sw.c",
    "guards_restroom_n":        TOWN_ROOMS          + "guards_restroom_n.c",
    "guards_restroom_se":       TOWN_ROOMS          + "guards_restroom_se.c",
    "guards_restroom_sw":       TOWN_ROOMS          + "guards_restroom_sw.c",
    "hairdresser":              GLYKRON_ROOMS       + "hairdresser.c",
    "hospital":			TOWN_ROOMS    	    + "hospital.c",
    "inn":                      DINO_ROOMS          + "inn.c",
    "inn_cellar":               TOWN_ROOMS          + "inn_cellar.c",
    "inn_hall":                 TOWN_ROOMS          + "inn_hall.c",
    "inn_bar":                  TOWN_ROOMS          + "inn_bar.c",
    "lavatory":                 MERLIN_ROOMS        + "lavatory.c",
    "lavatory_female":          MERLIN_ROOMS        + "lavatory_female.c",
    "lavatory_male":            MERLIN_ROOMS        + "lavatory_male.c",
    "lavatory_neutral":         MERLIN_ROOMS        + "lavatory_neutral.c",
    "palace_road_ne":           DINO_ROOMS          + "palace_road_ne.c",
    "palace_road_nw":           DINO_ROOMS          + "palace_road_nw.c",
    "palace_road_se":           DINO_ROOMS          + "palace_road_se.c",
    "palace_road_sw":           DINO_ROOMS          + "palace_road_sw.c",
    "pillory_e":                TOWN_ROOMS          + "pillory_e.c",
    "pillory_w":                TOWN_ROOMS          + "pillory_w.c",
    "post":                     GLYKRON_ROOMS       + "post.c",
    "road_e":                   TOWN_ROOMS          + "road_e.c",
    "road_w":                   TOWN_ROOMS          + "road_w.c",
    "school":                   TOWN_ROOMS          + "school.c",
    "shop":                     MANIAC_ROOMS        + "shop.c",
    "shopback":                 MANIAC_ROOMS        + "shopback.c",
    "square_central_e":         DINO_ROOMS          + "square_central_e.c",
    "square_central_w":         DINO_ROOMS          + "square_central_w.c",
    "square_corner_ne":         DINO_ROOMS          + "square_corner_ne.c",
    "square_corner_nw":         DINO_ROOMS          + "square_corner_nw.c",
    "square_corner_se":         DINO_ROOMS          + "square_corner_se.c",
    "square_corner_sw":         DINO_ROOMS          + "square_corner_sw.c",
    "square_e":                 DINO_ROOMS          + "square_e.c",
    "square_eastend":           DINO_ROOMS          + "square_eastend.c",
    "square_eastend_n":         DINO_ROOMS          + "square_eastend_n.c",
    "square_eastend_s":         DINO_ROOMS          + "square_eastend_s.c",
    "square_en":                DINO_ROOMS          + "square_en.c",
    "square_fountain_e":        DINO_ROOMS          + "square_fountain_e.c",
    "square_fountain_ne":       DINO_ROOMS          + "square_fountain_ne.c",
    "square_fountain_nw":       DINO_ROOMS          + "square_fountain_nw.c",
    "square_fountain_w":        DINO_ROOMS          + "square_fountain_w.c",
    "square_mide":              DINO_ROOMS          + "square_mide.c",
    "square_midw":              DINO_ROOMS          + "square_midw.c",
    "square_ne":                DINO_ROOMS          + "square_ne.c",
    "square_northend_center_e": DINO_ROOMS          + "square_northend_center_e.c",
    "square_northend_center_w": DINO_ROOMS          + "square_northend_center_w.c",
    "square_northend_e":        DINO_ROOMS          + "square_northend_e.c",
    "square_northend_w":        DINO_ROOMS          + "square_northend_w.c",
    "square_nw":                DINO_ROOMS          + "square_nw.c",
    "square_se":                DINO_ROOMS          + "square_se.c",
    "square_southend_center_e": DINO_ROOMS          + "square_southend_center_e.c",
    "square_southend_center_w": DINO_ROOMS          + "square_southend_center_w.c",
    "square_southend_e":        DINO_ROOMS          + "square_southend_e.c",
    "square_southend_w":        DINO_ROOMS          + "square_southend_w.c",
    "square_sw":                DINO_ROOMS          + "square_sw.c",
    "square_w":                 DINO_ROOMS          + "square_w.c",
    "square_westend":           DINO_ROOMS          + "square_westend.c",
    "square_westend_n":         DINO_ROOMS          + "square_westend_n.c",
    "square_westend_s":         DINO_ROOMS          + "square_westend_s.c",
    "square_wn":                DINO_ROOMS          + "square_wn.c",
    "stables_e":                TOWN_ROOMS          + "stables_e.c",
    "stables_w":                TOWN_ROOMS          + "stables_w.c",
    "standby_guards":           MERLIN_ROOMS        + "standby_guards.c",
                            ]);

mapping objects_path =     ([
    "bottle":                   DINO_OBJECTS        + "bottle.c",
    "contract":                 MERLIN_OBJECTS      + "contract.c",
    "croissant":                MANIAC_OBJECTS      + "croissant.c",
    "custard_pie":              MANIAC_OBJECTS      + "custard_pie.c",
    "fat_cake":                 MANIAC_OBJECTS      + "fat_cake.c",
    "flame":                    MANIAC_OBJECTS      + "flame.c",
    "ghost":                    MANIAC_OBJECTS      + "ghost.c",
    "map":			DINO_OBJECTS	    + "map.c",
    "map_box":			DINO_OBJECTS	    + "map_box.c",
    "poster":			DINO_OBJECTS	    + "poster.c",
    "tour_ticket":		DINO_OBJECTS	    + "ticket.c",
    "sesame_bread":             MANIAC_OBJECTS      + "sesame_bread.c",
    "shortcake":                MANIAC_OBJECTS      + "shortcake.c",
                            ]);

mapping weapons_path =     ([
    "app_sword":                MERLIN_WEAPONS      + "apprentice_sword.c",
    "exp_sword":                MERLIN_WEAPONS      + "exp_sword.c",
    "fighter_sword":            MERLIN_WEAPONS      + "fighter_sword.c",
    "smithhammer":              MANIAC_WEAPONS      + "smithhammer.c",
                            ]);

mapping armours_path =     ([
    "app_boots":                MERLIN_ARMOURS      + "apprentice_boots.c",
    "app_gauntlets":            MERLIN_ARMOURS      + "apprentice_gauntlets.c",
    "app_gloves":               MERLIN_ARMOURS      + "apprentice_gloves.c",
    "app_helmet":               MERLIN_ARMOURS      + "apprentice_helmet.c",
    "app_leggins":              MERLIN_ARMOURS      + "apprentice_leggings.c",
    "app_plate":                MERLIN_ARMOURS      + "apprentice_plate.c",
    "exp_boots":                MERLIN_ARMOURS      + "exp_boots.c",
    "exp_gauntlets":            MERLIN_ARMOURS      + "exp_gauntlets.c",
    "exp_gloves":               MERLIN_ARMOURS      + "exp_gloves.c",
    "exp_helmet":               MERLIN_ARMOURS      + "exp_helmet.c",
    "exp_leggings":             MERLIN_ARMOURS      + "exp_leggings.c",
    "exp_plate":                MERLIN_ARMOURS      + "exp_plate.c",
    "fighter_boots":            MERLIN_ARMOURS      + "fighter_boots.c",
    "fighter_gauntlets":        MERLIN_ARMOURS      + "fighter_gauntlets.c",
    "fighter_gloves":           MERLIN_ARMOURS      + "fighter_gloves.c",
    "fighter_helmet":           MERLIN_ARMOURS      + "fighter_helmet.c",
    "fighter_leggings":         MERLIN_ARMOURS      + "fighter_leggings.c",
    "fighter_plate":            MERLIN_ARMOURS      + "fighter_plate.c",
    "cloak_eye":                MERLIN_ARMOURS      + "magic_cloak_guard_eye.c",
    "rawarmour":                MANIAC_ARMOURS      + "rawarmour",
                            ]);

mapping doors_path =        ([
   "lavatory_f":                MERLIN_DOORS        + "lavatory_f.c",
   "lavatory_female":           MERLIN_DOORS        + "lavatory_female.c",
   "lavatory_m":                MERLIN_DOORS        + "lavatory_m.c",
   "lavatory_male":             MERLIN_DOORS        + "lavatory_male.c",
   "lavatory_n":                MERLIN_DOORS        + "lavatory_n.c",
   "lavatory_neutral":          MERLIN_DOORS        + "lavatory_neutral.c",
   "palace_road_ne":            DINO_DOORS          + "palace_road_ne.c",
   "palace_road_nw":            DINO_DOORS          + "palace_road_nw.c",
   "stables_e":                 TOWN_DOORS          + "stables_e.c",
   "stables_w":                 TOWN_DOORS          + "stables_w.c",
                            ]);

mapping specials_path =     ([
    "desc":                     DINO_SPECIALS       + "desc.c",
    "gelan_cmdsoul":            TOWN_SPECIALS       + "gelan_cmdsoul.c",
    "guard":                    MERLIN_SPECIALS     + "guard.c",
    "head_guard":               MERLIN_SPECIALS     + "head_guard.c",
    "path":                     TOWN_SPECIALS       + "path.c",
    "patients":                 MERLIN_SPECIALS     + "patients",
    "timer":                    MERLIN_SPECIALS     + "timer.c",
    "weather":                  MERLIN_SPECIALS     + "weather.c",
    "hair_shadow":		GLYKRON_SPECIALS    + "hair_shadow.c",
                            ]);

mapping monsters_path =     ([
   "app_fighter":               MERLIN_MONSTERS     + "apprentice_fighter.c",
   "baker":                     MANIAC_MONSTERS     + "baker.c",
   "bigoudi":                   MANIAC_MONSTERS     + "bigoudi.c",
   "bubba":                     MANIAC_MONSTERS     + "bubba.c",
   "coiney":                    MANIAC_MONSTERS     + "coiney.c", 
   "entrance_guard":            MERLIN_MONSTERS     + "entrance_guard.c",
   "exp_fighter":               MERLIN_MONSTERS     + "exp_fighter.c",
   "fighter":                   MERLIN_MONSTERS     + "fighter.c",
   "guide":                     DINO_MONSTERS       + "guide.c",
   "orgulas":                   DINO_MONSTERS       + "orgulas.c",
   "ska":                       MANIAC_MONSTERS     + "ska.c",
   "stdDoc":                    MERLIN_MONSTERS     + "stdDoc.c",
                            ]);

mapping texts_path =     ([
   "gelanposter":               DINO_TEXTS	    + "gelan.poster",
   "palaceposter":              DINO_TEXTS	    + "palace.poster",
   "dinosauriaposter":          DINO_TEXTS	    + "dinosauria.poster",
                            ]);


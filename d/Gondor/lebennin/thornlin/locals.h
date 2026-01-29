/*
 *
 * Definitions for ~Gondor/lebennin/thornlin/ ...
 *
 * By ^Sir Boromir, Feb 95 (15/02 - 1995)
 *
 */

/*
  done, additions or wishes ...

  WHO        -     When    -    WHAT AND WHY
------------------------------------------------------------------------
Boromir        2 MAR. 95      INSIDE...makes it possible to add the prob
                              ROOM_I_INSIDE just by typing 'INSIDE' in
                              the file.
Boromir          MAY  95      Added STDDOOR - As soon as the door at the
                              given path is a Genesis std. please correct
                              the path to /std/door
Boromir        9 JUNE 95      Add path's for NPC's to use with 
                              set_restrain_path
Boromir       11 JUNE 95      Added MINDOLLIUN item
------------------------------------------------------------------------
*/

#ifndef LOSSAR_DEFINITIONS
#define LOSSAR_DEFINITIONS

#include "/d/Gondor/defs.h"

#ifdef OBJ_DIR
#undef OBJ_DIR
#endif
#define OBJ_DIR         (THORN_DIR + "obj/")

#ifdef NPC_DIR
#undef NPC_DIR
#endif
#define NPC_DIR         (THORN_DIR + "npc/")

#ifdef STDDOOR
#undef STDDOOR
#endif
#define STDDOOR 	LIB_DIR + "door"

#ifdef INSIDE
#undef INSIDE
#endif
#define INSIDE		add_prop(ROOM_I_INSIDE, 1)

#ifdef CITY_PATH
#undef CITY_PATH
#endif
#define CITY_PATH 	THORN_DIR+"r2a",THORN_DIR+"r2b",THORN_DIR+"r2c",\
			THORN_DIR+"r2d",THORN_DIR+"r3",THORN_DIR+"garden"

#ifdef ROAD_PATH
#undef ROAD_PATH
#endif
#define ROAD_PATH	CITY_PATH,THORN_DIR+"r1",THORN_DIR+"r4",THORN_DIR+"r5",\
			THORN_DIR+"r6",THORN_DIR+"r7"

#ifdef FIELD_PATH	
#undef FIELD_PATH
#endif
#define FIELD_PATH	THORN_DIR+"f1",THORN_DIR+"f2",THORN_DIR+"f3",\
			THORN_DIR+"f4",THORN_DIR+"f5",THORN_DIR+"f6",\
			THORN_DIR+"f7",THORN_DIR+"f8",THORN_DIR+"f9",\
			THORN_DIR+"t1",THORN_DIR+"t2",THORN_DIR+"open_field"

#ifdef CITY_HOUSES
#undef CITY_HOUSES
#endif
#define CITY_HOUSES	THORN_DIR+"guardhouse",THORN_DIR+"inn",\
			THORN_DIR+"small_farm",THORN_DIR+"house",\
			THORN_DIR+"house2"

#ifdef THORN_HOUSES
#undef THORN_HOUSES
#endif
#define THORN_HOUSES	CITY_HOUSES,THORN_DIR+"hut"

#ifdef MILITIA_1ST_PATH
#undef MILITIA_1ST_PATH
#endif
#define MILITIA_1ST_PATH	set_restrain_path(({ROAD_PATH}))

#ifdef MILITIA_2ND_PATH
#undef MILITIA_2ND_PATH
#endif
#define MILITIA_2ND_PATH	set_restrain_path(({ROAD_PATH,CITY_PATH}))

#ifdef MILITIA_3RD_PATH
#undef MILITIA_3RD_PATH
#endif
#define MILITIA_3RD_PATH	set_restrain_path(({CITY_PATH,CITY_HOUSES}))

#ifdef MILITIA_4TH_PATH
#undef MILITIA_4TH_PATH
#endif
#define MILITIA_4TH_PATH	set_restrain_path(({ROAD_PATH,THORN_HOUSES,\
				FIELD_PATH}))

#ifdef ANIMAL_1ST_PATH
#undef ANIMAL_1ST_PATH
#endif
#define ANIMAL_1ST_PATH set_restrain_path(({CITY_PATH}))

#ifdef ANIMAL_2ND_PATH
#undef ANIMAL_2ND_PATH
#endif
#define ANIMAL_2ST_PATH set_restrain_path(({ROAD_PATH}))

#ifdef ANIMAL_3RD_PATH
#undef ANIMAL_3RD_PATH
#endif
#define ANIMAL_3RD_PATH set_restrain_path(({ROAD_PATH,FIELD_PATH}))

 
#endif

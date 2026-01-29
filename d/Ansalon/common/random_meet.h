/* created by Aridor 06/22/93 */

#define MEETING                 "/d/Ansalon/common/random_meet.c"
#define RANDOM_MEET(file)       (MEETING)->get_random_clone(file)
#define GET_RANDOM_OBJECT(file) (MEETING)->get_random_clone(file)
#define GET_RANDOM_NAME(file)   (MEETING)->get_random_name(file)

#define ROOMFINDER		"/d/Ansalon/common/random_meet.c"
#define GET_RANDOM_ROOM(path)	(ROOMFINDER)->get_random_room(path)


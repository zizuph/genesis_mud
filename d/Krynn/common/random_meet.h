/* created by Aridor 06/22/93 */

#define RANDOM_MASTER           "/d/Krynn/common/random_meet"
#define RANDOM_MEET(file)       (RANDOM_MASTER)->get_random_clone(file)
#define GET_RANDOM_OBJECT(file) (RANDOM_MASTER)->get_random_clone(file)
#define GET_RANDOM_NAME(file)   (RANDOM_MASTER)->get_random_name(file)
#define GET_RANDOM_ROOM(path)	(RANDOM_MASTER)->get_random_room(path)

